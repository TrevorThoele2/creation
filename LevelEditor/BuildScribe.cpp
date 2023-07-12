
#include "BuildScribe.h"

#include "CurrentWorld.h"
#include "Optional.h"

namespace Creation
{
    namespace Build
    {
        const char *buildExtension = "build";

        void ScribeOut::FieldSaver::OnBeforeObjectSave()
        {
            positionStart = static_cast<SizeT>(scribe.TellStream());
        }

        void ScribeOut::FieldSaver::OnAfterObjectSave()
        {
            size = static_cast<SizeT>(scribe.TellStream() - positionStart);
        }

        void ScribeOut::FieldSaver::SavePlaceholderExtra()
        {
            scribe.WriteNumeric(fieldID);
            scribe.WriteNumeric(size);
        }

        void ScribeOut::FieldSaver::SaveExtra()
        {
            scribe.WriteNumeric(fieldID);
            scribe.WriteNumeric(size);
        }

        ScribeOut::FieldSaver::FieldSaver(ScribeT &scribe) : SkipSaver(scribe)
        {}

        void ScribeOut::OutputHeader()
        {
            if (hasOutputHeader)
                return;

            basicScribe.Save(globals);

            inscription::ContainerSize count(fieldSavers.size());
            basicScribe.Save(count);

            for (auto &loop : fieldSavers)
                loop.SavePlaceholder();
            curSaver = fieldSavers.begin();

            hasOutputHeader = true;
        }

        ScribeOut::ScribeOut(const ::Atmos::FilePath &filePath, inscription::ContainerSize::ValueT fieldCount, OpenMode openMode) : filePath(filePath), basicScribe(filePath, "gaiabuild", 1), hasOutputHeader(false)
        {
            if (openMode == OpenMode::FORCE_EXTENSION)
                this->filePath.SetExtension(buildExtension);

            fieldSavers.resize(fieldCount, FieldSaver(basicScribe));
            int myInt = 1 + 1;
        }

        void ScribeOut::Save(FieldPackage &save)
        {
            OutputHeader();

            // Save the field ID
            curSaver->fieldID = save.id.value;

            // Save the field itself while clearing out the tracking entries made
            basicScribe.StartTrackingSection();
            curSaver->SaveObject(save);
            basicScribe.StopTrackingSection(true);

            ++curSaver;
        }

        const ::Atmos::FilePath& ScribeOut::GetFilePath() const
        {
            return filePath;
        }

        void ScribeIn::FieldHandle::LoadExtra()
        {
            scribe.ReadNumeric(fieldID);
            scribe.ReadNumeric(size);
        }

        ScribeIn::FieldHandle::FieldHandle(ScribeT &scribe) : SkipHandle(scribe), size(0)
        {}

        ScribeIn::ScribeIn(const ::Atmos::FilePath &filePath, OpenMode openMode) : filePath(filePath), basicScribe(filePath, "gaiabuild")
        {
            if (openMode == OpenMode::FORCE_EXTENSION)
                this->filePath.SetExtension(buildExtension);
        }

        void ScribeIn::Load()
        {
            basicScribe.Load(globals);

            inscription::ContainerSize size;
            basicScribe.Load(size);
            while (size-- > 0)
            {
                FieldHandle handle(basicScribe);
                handle.LoadPosition();
                fieldHandles.emplace(handle.fieldID, handle);
            }
        }

        bool ScribeIn::Get(::Atmos::FieldID id, Package<::Atmos::Field> &package)
        {
            typedef Optional<::Atmos::Field> Ret;
            auto found = fieldHandles.find(id);
            if (found == fieldHandles.end())
                return false;

            basicScribe.StartTrackingSection();
            found->second.LoadObject(package);
            basicScribe.StopTrackingSection(true);

            return true;
        }

        void ScribeIn::GetIDs(std::vector<::Atmos::FieldID> &ids) const
        {
            ids.clear();
            for (auto &loop : fieldHandles)
                ids.push_back(loop.second.fieldID);
        }

        const ::Atmos::FilePath& ScribeIn::GetFilePath() const
        {
            return filePath;
        }
    }
}