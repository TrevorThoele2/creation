
#include <wx\app.h>
#include <wx\window.h>
#include <wx\msgdlg.h>
#include <wx\filedlg.h>
#include "Application.h"
#include "MainFrame.h"
#include "Viewport.h"

#include "CurrentWorld.h"

#include <locale>
#include <codecvt>

#include "TileViewManager.h"
#include "EntityViewManager.h"
#include "InternalShaders.h"

#include "ChildProcesses.h"
#include "ExitException.h"
#include "Settings.h"

#include <Atmos\Environment.h>
#include <Atmos\Field.h>
#include <Atmos\FilePath.h>
#include <Atmos\WorldScribe.h>
#include <Atmos\WorldManager.h>
#include <Atmos\AssetPackage.h>

#include "BuildScribe.h"
#include "Selection.h"

namespace Creation
{
    static Optional<::Atmos::FieldID> newFieldID;

    CurrentWorld::~CurrentWorld()
    {
        Atmos::WorldManager::TemporaryUse();
    }

    void CurrentWorld::SaveImpl(const ::Atmos::FilePath &filePath, bool moveFile)
    {
        auto &loadFilePath = Instance().loadFilePath;

        // Input the other fields while outputting the current field
        if (!loadFilePath.IsEmpty())
        {
            ::Atmos::FilePath tempPath(::Atmos::Environment::GetFileSystem()->GetTempDirectoryPath());
            tempPath.Append(filePath.GetFileName());

            typedef std::vector<FieldID> IDs;
            IDs ids;
            IDs::iterator select;

            // Output the world to a temporary directory
            {
                // Make input scribe and fill id vector
                Build::ScribeIn in(loadFilePath);
                try
                {
                    in.Load();
                }
                catch (std::runtime_error &e)
                {
                    wxMessageDialog dialog(nullptr, e.what(), "Error");
                    dialog.ShowModal();
                    throw ExitException();
                }

                in.GetIDs(ids);

                auto useSize = ids.size();
                if (newFieldID)
                    ++useSize;

                Build::ScribeOut out(tempPath, useSize);
                out.globals = globals;
                for (auto loop = ids.begin(); loop != ids.end(); ++loop)
                {
                    if (*loop == fieldPackage.id.Build())
                        out.Save(fieldPackage);
                    else
                    {
                        FieldPackage nPackage;
                        in.Get(*loop, nPackage);
                        out.Save(nPackage);
                    }
                }

                if (newFieldID)
                {
                    FieldPackage nPackage;
                    nPackage.id.value = *newFieldID;
                    out.Save(nPackage);
                }
            }

            if (moveFile)
            {
                std::remove(filePath.c_str());
                // Rename the temporary file (to move it)
                rename(tempPath, filePath.c_str());
            }
        }
        else
        {
            // Just output the new field
            Build::ScribeOut out(filePath, 1);
            out.globals.worldStart = Instance().worldStart;

            FieldPackage nPackage;
            nPackage.id.value = *newFieldID;
            out.Save(nPackage);
        }

        loadFilePath = filePath;
        if(Instance().currentField)
            ConstructAllViewManagers();
    }

    void CurrentWorld::SelectField(FieldID field)
    {
        auto &currentField = Instance().currentField;

        if(currentField)
            DeconstructAllViewManagers();

        // Load field
        {
            try
            {
                Build::ScribeIn in(Instance().loadFilePath);
                in.Load();

                in.Get(field, fieldPackage);
                currentField.reset(new ::Atmos::Field(field));
                ::Atmos::WorldManager::TemporaryUse(currentField.get());
                onFieldChanged();
            }
            catch (std::runtime_error &e)
            {
                wxMessageDialog dialog(nullptr, e.what(), "Error");
                dialog.ShowModal();
                throw ExitException();
            }
        }

        ConstructAllViewManagers();
    }

    ::Atmos::FilePath CurrentWorld::MakeWorldFilePath()
    {
        ::Atmos::FilePath worldFilePath(Settings::GetWorldPath());
        worldFilePath.Append("\\");
        worldFilePath.Append(Instance().buildFilePath.GetFileName());
        return worldFilePath;
    }

    ::Atmos::FilePath CurrentWorld::MakeTemporarySaveFilePath()
    {
        ::Atmos::FilePath filePath = ::Atmos::Environment::GetFileSystem()->GetTempDirectoryPath();
        filePath.Append("Temporary." + String(Build::buildExtension));
        return filePath;
    }

    NullEvent CurrentWorld::onFieldChanged;
    CurrentWorld::FieldPackage CurrentWorld::fieldPackage;
    WorldGlobals CurrentWorld::globals;

    CurrentWorld& CurrentWorld::Instance()
    {
        static CurrentWorld instance;
        return instance;
    }

    void CurrentWorld::Add(FieldID id)
    {
        newFieldID = id;
        SaveImpl(MakeTemporarySaveFilePath(), false);
        newFieldID.Reset();
    }

    void CurrentWorld::Remove(FieldID id)
    {
        DeconstructAllViewManagers();

        auto filePath = MakeTemporarySaveFilePath();

        Atmos::FilePath tempPath(Atmos::Environment::GetFileSystem()->GetTempDirectoryPath());
        tempPath.SetName(filePath.GetFileName());

        typedef std::vector<FieldID> IDs;
        IDs ids;
        IDs::iterator select;

        // Output the world to a temporary directory
        {
            // Make input scribe and fill id vector
            Build::ScribeIn in(filePath);
            try
            {
                in.Load();
            }
            catch (std::runtime_error &e)
            {
                wxMessageDialog dialog(nullptr, e.what(), "Error");
                dialog.ShowModal();
                throw ExitException();
            }

            in.GetIDs(ids);
            std::sort(ids.begin(), ids.end());

            Build::ScribeOut out(tempPath, ids.size());
            out.globals.worldStart = Instance().worldStart;
            for (auto loop = ids.begin(); loop != ids.end(); ++loop)
            {
                if (*loop == id)
                {
                    // Figure out what iterator to select
                    if (id == Instance().currentField->GetID())
                    {
                        IDs::iterator check = loop;
                        if (check == ids.begin() && ids.size() > 1)
                            select = ++check;
                        else if (check == --ids.end())
                            select = --check;
                        else
                            select = ids.end();
                    }

                    continue;
                }

                FieldPackage nPackage;
                in.Get(*loop, nPackage);
                out.Save(nPackage);
            }
        }

        std::remove(filePath);
        // Rename the temporary file (to move it)
        rename(tempPath, filePath);

        if (select != ids.end())
            SelectField(*select);

        ConstructAllViewManagers();
    }

    bool CurrentWorld::Select(FieldID id)
    {
        if (!IsFieldHere(id))
            return false;

        // Check current field and its ID
        {
            auto &currentField = Instance().currentField;
            if (currentField && id == currentField->GetID())
                return false;
        }

        SelectField(id);
        return true;
    }

    CurrentWorld::Field* CurrentWorld::GetCurrentField()
    {
        return Instance().currentField.get();
    }

    bool CurrentWorld::IsFieldValid()
    {
        return GetCurrentField() != nullptr;
    }

    bool CurrentWorld::IsFieldHere(FieldID id)
    {
        if (Instance().loadFilePath.IsEmpty())
            return false;

        Build::ScribeIn in(Instance().loadFilePath);
        try
        {
            in.Load();
        }
        catch (std::runtime_error &e)
        {
            wxMessageDialog dialog(nullptr, e.what(), "Error");
            dialog.ShowModal();
            throw ExitException();
        }

        std::vector<FieldID> ids;
        in.GetIDs(ids);
        for (auto &loop : ids)
        {
            if (loop == id)
                return true;
        }

        return false;
    }

    bool CurrentWorld::FieldsEmpty()
    {
        Build::ScribeIn scribeIn(Instance().loadFilePath);
        try
        {
            scribeIn.Load();
        }
        catch (std::runtime_error &e)
        {
            wxMessageDialog dialog(nullptr, e.what(), "Error");
            dialog.ShowModal();
            throw ExitException();
        }

        std::vector<FieldID> ids;
        scribeIn.GetIDs(ids);
        return ids.empty();
    }

    void CurrentWorld::Clear()
    {
        Instance().buildFilePath = "";
        Instance().loadFilePath = "";
        Instance().worldStart = WorldStartPackage();
        Instance().currentField.reset();

        globals = WorldGlobals();

        Atmos::WorldManager::TemporaryUse();
        newFieldID.Reset();
    }

    void CurrentWorld::SetWorldStart(FieldID id)
    {
        Instance().worldStart.id.value = id;
    }

    CurrentWorld::FieldID CurrentWorld::GetWorldStartField()
    {
        return Instance().worldStart.id.Build();
    }

    void CurrentWorld::Draw(Atmos::Position3D::ValueT z)
    {
        if (!GetCurrentField())
            return;

        GetCurrentField()->renderFragments.SetZOverride(z);
        GetCurrentField()->renderFragments.Render();
    }

    void CurrentWorld::StartWorld()
    {
        if (FieldsEmpty())
        {
            wxMessageDialog dialog(nullptr, "There are no fields to use. Cannot start this world.", "Error");
            dialog.ShowModal();
            return;
        }
        else if (!IsFieldHere(Instance().worldStart.id.Build()))
        {
            wxMessageDialog dialog(nullptr, "The world start's field ID does not correspond to a valid field. Cannot start this world.", "Error");
            dialog.ShowModal();
            return;
        }

        bool hitException = false;
        try
        {
            Build();

            STARTUPINFO startupInfo;
            PROCESS_INFORMATION processInfo;

            ZeroMemory(&startupInfo, sizeof(startupInfo));
            startupInfo.cb = sizeof(startupInfo);
            ZeroMemory(&processInfo, sizeof(processInfo));

            // Create the process
            {
                std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
                std::wstring worldPath;

                {
                    auto &madeWorldPath = MakeWorldFilePath();
                    madeWorldPath.SetExtension(::Atmos::worldExtension);
                    worldPath = (converter.from_bytes(madeWorldPath.c_str()));
                }

                auto fileSystem = Atmos::Environment::GetFileSystem();
                auto length = fileSystem->GetMaxPathLength();
                auto passFilePath = converter.from_bytes(fileSystem->GetExePath().Append("AnExWill\\AnExWill.exe").GetValue());
                std::wstring passArguments(L"\"" + passFilePath + L"\" \"" + worldPath + L"\"");
                CreateProcess(passFilePath.c_str(), &passArguments[0], nullptr, nullptr, false, CREATE_NEW_CONSOLE | CREATE_DEFAULT_ERROR_MODE, nullptr, nullptr, &startupInfo, &processInfo);
            }

            ChildProcesses::Manage(true, processInfo);
            GetMainFrame()->Disable();
        }
        catch(std::runtime_error &e)
        {
            hitException = true;

            GetMainFrame()->OutputMessage(e.what());
            GetMainFrame()->SetStatusText("Starting world failed.");
        }
        catch (...)
        {
            hitException = true;

            GetMainFrame()->OutputMessage("Starting world failed. Unknown reason.");
            GetMainFrame()->SetStatusText("Starting world failed.");
        }

        if (!hitException)
        {
            GetMainFrame()->OutputMessage("Starting world success.");
            GetMainFrame()->SetStatusText("Starting world success.");
        }
    }

    void CurrentWorld::SetFilePath(const FilePath &set)
    {
        Instance().buildFilePath = set;
    }

    const CurrentWorld::FilePath& CurrentWorld::GetFilePath()
    {
        return Instance().buildFilePath;
    }

    bool CurrentWorld::IsFilePathValid()
    {
        return !Instance().buildFilePath.IsEmpty();
    }

    void CurrentWorld::Save()
    {
        if (!IsFilePathValid())
            return;

        SaveImpl(Instance().buildFilePath);
    }

    void CurrentWorld::Save(const FilePath &path)
    {
        SelectionHandler::ClearAll();
        SetFilePath(path);
        Save();
    }

    void CurrentWorld::Load(const FilePath &path)
    {
        Clear();
        SetFilePath(path);
        Instance().loadFilePath = Instance().buildFilePath;
        ::Atmos::FilePath useFilePath(GetFilePath());

        typedef std::vector<FieldID> IDs;
        IDs ids;
        // Find the first ID to use
        {
            Atmos::WorldManager::Instance().eventFinalizeField();
            Build::ScribeIn scribe(useFilePath);
            try
            {
                scribe.Load();
            }
            catch (std::runtime_error &e)
            {
                wxMessageDialog dialog(nullptr, e.what(), "Error");
                dialog.ShowModal();
                throw ExitException();
            }

            SetWorldStart(scribe.globals.worldStart.id.Build());
            scribe.globals.SetAsGlobals(true);
            scribe.GetIDs(ids);
        }

        if (!ids.empty())
        {
            std::sort(ids.begin(), ids.end());
            SelectField(*ids.begin());
        }
    }

    void CurrentWorld::Build()
    {
        if (!IsFilePathValid())
            return;

        GetMainFrame()->OutputMessage("Build started.");
        GetMainFrame()->SetStatusText("Build started.");

        bool hitException = false;
        try
        {
            // Load all of the build packages
            Build::ScribeIn scribeIn(Instance().buildFilePath);
            scribeIn.Load();
            std::vector<Atmos::FieldID> ids;
            scribeIn.GetIDs(ids);

            // Build each asset package individually
            {
                auto adder = [](auto &list, void(*func)(const FilePath&))
                {
                    for (auto &loop : list)
                        (*func)(loop.path.Build());
                };

                adder(globals.audioPackage.value, &::Atmos::AssetPackage::AddAudio);
                adder(globals.imagePackage.value, &::Atmos::AssetPackage::AddImage);
                adder(globals.scriptPackage.value, &::Atmos::AssetPackage::AddScript);
                adder(globals.shaderPackage.value, &::Atmos::AssetPackage::AddShader);
            }

            // Now, save the assets
            ::Atmos::AssetPackage::Save(MakeWorldFilePath());

            ::Atmos::WorldScribeOut scribeOut(MakeWorldFilePath(), ids.size());

            for (auto &loop : ids)
            {
                Build::Package<::Atmos::Field> package;
                scribeIn.Get(loop, package);

                ::Atmos::Field field(0);
                field = std::move(package.Build());
                scribeOut.Save(field);
            }

            ::Atmos::AssetPackage::Clear();
        }
        catch (std::exception &e)
        {
            hitException = true;

            GetMainFrame()->OutputMessage(e.what());
            GetMainFrame()->SetStatusText("Build failed.");
        }
        catch (...)
        {
            hitException = true;

            GetMainFrame()->OutputMessage("Build failed. Unknown reason.");
            GetMainFrame()->SetStatusText("Build failed.");
        }

        if (!hitException)
        {
            GetMainFrame()->OutputMessage("Build complete.");
            GetMainFrame()->SetStatusText("Build complete.");
        }
    }

    ::Atmos::Field* GetCurrentField()
    {
        return CurrentWorld::GetCurrentField();
    }

    ::Atmos::RenderFragmentHandler* GetCurrentRenderFragments()
    {
        auto field = GetCurrentField();
        if (field)
            return &field->renderFragments;
        else
            return nullptr;
    }
}