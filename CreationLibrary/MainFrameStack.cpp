#include "MainFrameStack.h"

#include <Atmos/TypeRegistration.h>
#include <Atmos/LoggingInformation.h>
#include <Atmos/LoggingCurator.h>
#include <Atmos/WorldFileExtension.h>

#include "OutputSettingsFile.h"
#include "InputSettingsFile.h"

namespace Creation
{
    MainFrameState::MainFrameState(Atmos::Logging::Logger& logger) :
        reliquary(CreateReliquary(realAssetResourceManager, logger)),
        childProcesses(logger),
        realAssetResourceManager(logger),
        sdlAudioManager(logger),
        vulkanGraphicsManager(logger),
        sdlTextManager(),
        javaScriptManager(logger),
        logger(&logger)
    {}

    MainFrameState::~MainFrameState()
    {
        javaScriptManager.SetReliquary(nullptr);
        editor.reset();
    }

    bool MainFrameState::HasField(Atmos::World::FieldID fieldID) const
    {
        return currentWorld
            ? currentWorld->HasField(fieldID)
            : false;
    }

    std::vector<Atmos::World::FieldID> MainFrameState::AllFieldIDs() const
    {
        return currentWorld
            ? currentWorld->AllFieldIDs()
            : std::vector<Atmos::World::FieldID>{};
    }

    Field MainFrameState::CurrentField() const
    {
        return currentWorld
            ? currentWorld->CurrentField()
            : Field{};
    }

    size_t MainFrameState::FieldCount() const
    {
        return currentWorld
            ? currentWorld->AllFieldIDs().size()
            : 0;
    }

    std::unique_ptr<Arca::Reliquary> MainFrameState::CreateReliquary(
        Atmos::Asset::Resource::Manager& assetResourceManager,
        Atmos::Logging::Logger& logger)
    {
        Arca::Stage constructorStage;
        constructorStage.Add<Atmos::Logging::Curator>();

        auto origin = Arca::ReliquaryOrigin();
        Atmos::Asset::RegisterTypes(origin, assetResourceManager);
        Atmos::Diagnostics::RegisterTypes(origin);
        origin
            .Register<Atmos::Logging::Curator>()
            .Register<Atmos::Logging::Information>(std::ref(logger))
            .CuratorConstructionPipeline({ constructorStage });

        return origin.Actualize();
    }

    MainFrameCommands::MainFrameCommands(State& state) :
        activate(std::bind(&MainFrameCommands::Activate, this)),
        deactivate(std::bind(&MainFrameCommands::Deactivate, this)),

        newWorld(std::bind(&MainFrameCommands::NewWorld, this, std::placeholders::_1)),
        existingWorld(std::bind(&MainFrameCommands::ExistingWorld, this, std::placeholders::_1)),
        setBuildWorldPath(std::bind(&MainFrameCommands::SetBuildFilePath, this, std::placeholders::_1)),
        closeWorld(std::bind(&MainFrameCommands::CloseWorld, this)),
        saveWorld(std::bind(&MainFrameCommands::SaveWorld, this)),
        saveWorldAs(std::bind(&MainFrameCommands::SaveWorldAs, this, std::placeholders::_1)),
        buildWorld(std::bind(&MainFrameCommands::BuildWorld, this)),
        startWorld(std::bind(&MainFrameCommands::StartWorld, this)),
        stopWorld(),
        createAndChangeField(std::bind(&MainFrameCommands::CreateAndChangeField, this, std::placeholders::_1)),
        changeField(std::bind(&MainFrameCommands::ChangeField, this, std::placeholders::_1)),
        destroyField(std::bind(&MainFrameCommands::DestroyField, this, std::placeholders::_1)),

        cut(std::bind(&MainFrameCommands::Cut, this)),
        copy(std::bind(&MainFrameCommands::Copy, this)),
        paste(std::bind(&MainFrameCommands::Paste, this)),

        undo(std::bind(&MainFrameCommands::Undo, this)),
        redo(std::bind(&MainFrameCommands::Redo, this)),

        editingMode(
            std::bind(&MainFrameCommands::ConvertEditingMode, this, std::placeholders::_1),
            std::bind(&MainFrameCommands::ChangeEditingMode, this, std::placeholders::_1)),
        editingTool(
            std::bind(&MainFrameCommands::ConvertEditingTool, this, std::placeholders::_1),
            std::bind(&MainFrameCommands::ChangeEditingTool, this, std::placeholders::_1)),

        changeSettings(std::bind(&MainFrameCommands::ChangeSettings, this, std::placeholders::_1)),

        exit(),

        idle(std::bind(&MainFrameCommands::Idle, this)),

        state(&state)
    {
        LoadSettings();
    }

    void MainFrameCommands::ResetState()
    {
        state->clipboard = {};
        state->history.Clear();
        state->nexusSelection.Set({});
    }

    void MainFrameCommands::Activate()
    {
        state->isActive = true;
    }

    void MainFrameCommands::Deactivate()
    {
        state->isActive = false;
    }

    void MainFrameCommands::NewWorld(const File::Path& filePath)
    {
        CloseWorld();
        std::filesystem::remove(filePath);
        auto& currentWorld = state->currentWorld;
        const auto fieldChangingData = CurrentFieldChangingData();
        OnFieldChanging();
        currentWorld = World(filePath, WorldFilePathFrom(filePath), *state->logger);
        currentWorld->InsertDefaults();
        currentWorld->CreateAndChangeField(0);
        currentWorld->Save();
        OnWorldChanged();
        OnFieldChanged(fieldChangingData);
        state->reliquary->Do(Atmos::Logging::Log{
            "Started new world.",
            Atmos::Logging::Details{ { "File Path", filePath.string() } } });
    }

    void MainFrameCommands::ExistingWorld(const File::Path& filePath)
    {
        CloseWorld();
        auto& currentWorld = state->currentWorld;
        const auto fieldChangingData = CurrentFieldChangingData();
        OnFieldChanging();
        currentWorld = World(filePath, WorldFilePathFrom(filePath), *state->logger);
        currentWorld->LoadAssets();
        currentWorld->ChangeField(0);
        OnWorldChanged();
        OnFieldChanged(fieldChangingData);
        state->reliquary->Do(Atmos::Logging::Log{
            "Using existing world.",
            Atmos::Logging::Details{ { "File Path", filePath.string() } } });
    }

    void MainFrameCommands::SetBuildFilePath(const File::Path& filePath)
    {
        state->currentWorld->BuildFilePath(filePath);
    }

    void MainFrameCommands::CloseWorld()
    {
        ResetState();
        auto& currentWorld = state->currentWorld;
        if (currentWorld)
        {
            currentWorld.reset();
            OnWorldChanged();
            state->reliquary->Do(Atmos::Logging::Log{ "Closed world." });
        }
    }

    void MainFrameCommands::SaveWorld()
    {
        state->editor->CommitChanges();
        state->currentWorld->Save();
        state->reliquary->Do(Atmos::Logging::Log{ "Saved world." });
        state->savedHistoryPosition = state->history.Position();
    }

    void MainFrameCommands::SaveWorldAs(const File::Path& filePath)
    {
        SetBuildFilePath(filePath);
        SaveWorld();
    }

    void MainFrameCommands::BuildWorld()
    {
        auto& currentWorld = state->currentWorld;
        currentWorld->Build(
            state->sdlAudioManager,
            state->vulkanGraphicsManager,
            state->sdlTextManager,
            state->realAssetResourceManager,
            state->javaScriptManager,
            *state->logger);
        state->reliquary->Do(Atmos::Logging::Log{
            "Built world.",
            Atmos::Logging::Details{ { "File Path", currentWorld->BuildFilePath().string() } } });
    }

    void MainFrameCommands::StartWorld()
    {
        BuildWorld();

        const auto clientFilePath = ClientFilePath();
        const auto worldFilePath = WorldFilePath();
        const auto command = clientFilePath.string() + " " + worldFilePath.string();
        const ChildProcesses::OnExit onExit = [this]()
        {
            stopWorld();
        };
        state->childProcesses.Create(clientFilePath, std::vector{ worldFilePath.string() }, onExit);

        state->reliquary->Do(Atmos::Logging::Log{ "Started world." });
    }

    void MainFrameCommands::CreateAndChangeField(Atmos::World::FieldID fieldID)
    {
        if (state->HasField(fieldID))
        {
            state->reliquary->Do(Atmos::Logging::Log{
                "Cannot create a field with an already occupied ID.",
                Atmos::Logging::Details{{"ID", Atmos::ToString(fieldID)}} });
        }
        else
        {
            const auto fieldChangingData = CurrentFieldChangingData();
            OnFieldChanging();
            state->currentWorld->CreateAndChangeField(fieldID);
            OnFieldChanged(fieldChangingData);
            state->reliquary->Do(Atmos::Logging::Log{
                "Created new field.",
                Atmos::Logging::Details{ { "Field ID", Atmos::ToString(fieldID) } } });
        }
    }

    void MainFrameCommands::ChangeField(Atmos::World::FieldID fieldID)
    {
        if (!state->HasField(fieldID))
        {
            state->reliquary->Do(Atmos::Logging::Log{
                "Cannot change to non-existent field.",
                Atmos::Logging::Details{{"ID", Atmos::ToString(fieldID)}} });
        }
        else
        {
            const auto fieldChangingData = CurrentFieldChangingData();
            OnFieldChanging();
            state->currentWorld->ChangeField(fieldID);
            OnFieldChanged(fieldChangingData);
            state->reliquary->Do(Atmos::Logging::Log{
                "Changed field.",
                Atmos::Logging::Details{ { "Field ID", Atmos::ToString(fieldID) } } });
        }
    }

    void MainFrameCommands::DestroyField(Atmos::World::FieldID fieldID)
    {
        if (!state->HasField(fieldID))
        {
            state->reliquary->Do(Atmos::Logging::Log{
                "Cannot destroy non-existent field.",
                Atmos::Logging::Details{{"ID", Atmos::ToString(fieldID)}} });
        }
        else
        {
            const std::optional<FieldChangingData> fieldChangingData =
                state->CurrentField().id == fieldID ? CurrentFieldChangingData() : std::optional<FieldChangingData>{};
            if (fieldChangingData)
                OnFieldChanging();
            state->currentWorld->DestroyField(fieldID);
            if (fieldChangingData)
                OnFieldChanged(*fieldChangingData);
            state->reliquary->Do(Atmos::Logging::Log{
                "Destroyed field.",
                Atmos::Logging::Details{ { "Field ID", Atmos::ToString(fieldID) } } });
        }
    }

    void MainFrameCommands::Cut()
    {
        RecordHistory();

        auto& selection = state->nexusSelection;
        auto nexusHistory = Editing::NexusHistory(state->history, selection);

        const std::vector remove(selection.begin(), selection.end());
        nexusHistory.Remove(remove);
    }

    void MainFrameCommands::Copy()
    {
        RecordHistory();
    }

    void MainFrameCommands::Paste()
    {
        if (state->clipboard)
            (*state->clipboard)();
    }

    void MainFrameCommands::Undo()
    {
        state->history.Reverse();
    }

    void MainFrameCommands::Redo()
    {
        state->history.Forward();
    }

    std::tuple<std::optional<std::type_index>> MainFrameCommands::ConvertEditingMode(std::optional<std::type_index> modeType)
    {
        const auto currentMode = state->editor->CurrentMode();
        const auto currentModeType = std::type_index(currentMode ? typeid(*currentMode) : typeid(std::nullptr_t));
        return modeType == currentModeType ? std::optional<std::type_index>{} : modeType;
    }

    std::tuple<std::optional<std::type_index>> MainFrameCommands::ConvertEditingTool(std::optional<std::type_index> toolType)
    {
        const auto currentTool = state->editor->CurrentTool();
        const auto currentToolType = std::type_index(currentTool ? typeid(*currentTool) : typeid(std::nullptr_t));
        return toolType == currentToolType ? std::optional<std::type_index>{} : toolType;
    }

    void MainFrameCommands::ChangeEditingMode(std::optional<std::type_index> modeType)
    {
        state->editor->ChangeMode(modeType);
    }

    void MainFrameCommands::ChangeEditingTool(std::optional<std::type_index> toolType)
    {
        state->editor->ChangeTool(toolType);
    }

    void MainFrameCommands::ChangeSettings(Settings settings)
    {
        Creation::settings = settings;
        SaveSettings();
    }

    void MainFrameCommands::Idle()
    {
        state->childProcesses.Work();
    }

    void MainFrameCommands::OnWorldChanged()
    {
        state->editor->WorldChanged(state->currentWorld ? &*state->currentWorld : nullptr);
    }

    void MainFrameCommands::OnFieldChanging()
    {
        state->editor->FieldChanging();
    }

    void MainFrameCommands::OnFieldChanged(FieldChangingData fieldChangingData)
    {
        state->editor->FieldChanged(state->currentWorld->CurrentField());
        state->editor->ChangeMode(fieldChangingData.modeType);
        state->editor->ChangeTool(fieldChangingData.toolType);
    }

    auto MainFrameCommands::CurrentFieldChangingData() -> FieldChangingData
    {
        return { state->editor->ModeType(), state->editor->ToolType() };
    }

    File::Path MainFrameCommands::WorldFilePathFrom(const File::Path& filePath)
    {
        auto worldFileName = filePath.filename();
        worldFileName.replace_extension(Atmos::World::Serialization::worldFileExtension);
        return std::filesystem::current_path() / "an_ex_will_data" / "worlds" / worldFileName;
    }

    File::Path MainFrameCommands::ClientFilePath()
    {
        return std::filesystem::current_path() / "an_ex_will_data" / "AnExWill.exe";
    }

    File::Path MainFrameCommands::WorldFilePath() const
    {
        return state->currentWorld->WorldFilePath();
    }

    void MainFrameCommands::RecordHistory()
    {
        const auto mode = state->editor->CurrentMode();
        const auto paintAction = mode->OnCopy();
        const std::type_index modeType = typeid(*mode);
        state->clipboard = [this, paintAction, modeType]()
        {
            const auto currentMode = state->editor->CurrentMode();
            if (!currentMode || std::type_index(typeid(*currentMode)) != modeType)
                ChangeEditingMode(modeType);

            paintAction();
        };
    }

    void MainFrameCommands::SaveSettings()
    {
        OutputSettingsFile outputFile(SettingsFilePath());
        outputFile.Save(settings);
    }

    void MainFrameCommands::LoadSettings()
    {
        try
        {
            InputSettingsFile inputFile(SettingsFilePath());
            settings = inputFile.Load();
        }
        catch (...)
        {
            state->reliquary->Do(
                Atmos::Logging::Log
                {
                    "Failed to load settings. Using default ones.",
                    Atmos::Logging::Severity::Error
                });
            settings = {};
        }

        if (state->editor)
        {
            state->editor->ViewTerrain(settings.viewTerrain);
            state->editor->ViewEntityBoundary(settings.viewEntityBoundary);
            state->editor->ViewEntities(settings.viewEntities);
        }
    }

    File::Path MainFrameCommands::SettingsFilePath()
    {
        return std::filesystem::current_path() / "settings.txt";
    }

    MainFrameStack::MainFrameStack(Atmos::Logging::Logger& logger) :
        state(logger), commands(state)
    {}
}