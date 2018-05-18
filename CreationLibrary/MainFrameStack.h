#pragma once

#include "Command.h"
#include "ViewportStack.h"

#include "World.h"
#include <Arca/Reliquary.h>
#include "History.h"
#include "NexusSelection.h"
#include "Settings.h"
#include "Editor.h"
#include "ChildProcesses.h"
#include <Atmos/SDLSystem.h>
#include <Atmos/RealAssetResourceManager.h>
#include <Atmos/SDLAudioManager.h>
#include <Atmos/VulkanGraphicsManager.h>
#include <Atmos/SDLTextManager.h>
#include <Atmos/JavaScriptManager.h>

namespace Creation
{
    class MainFrameState
    {
    public:
        bool isActive = false;

        std::optional<World> currentWorld;
        std::unique_ptr<Arca::Reliquary> reliquary;

        Editing::History history;
        size_t savedHistoryPosition = 0;
        Editing::NexusSelection nexusSelection;

        using Clipboard = std::function<void()>;
        std::optional<Clipboard> clipboard;

        ChildProcesses childProcesses;

        std::unique_ptr<Arca::Reliquary> renderReliquary;

        std::unique_ptr<Editing::Editor> editor;

        Atmos::System::SDL sdlSystem;
        Atmos::Asset::Resource::RealManager realAssetResourceManager;
        Atmos::Audio::SDL::Manager sdlAudioManager;
        Atmos::Render::Vulkan::GraphicsManager vulkanGraphicsManager;
        Atmos::Render::SDL::TextManager sdlTextManager;
        Atmos::Scripting::JavaScript::Manager javaScriptManager;
        
        Atmos::Logging::Logger* logger;

        MainFrameState(Atmos::Logging::Logger& logger);
        ~MainFrameState();

        [[nodiscard]] bool HasField(Atmos::World::FieldID fieldID) const;
        [[nodiscard]] std::vector<Atmos::World::FieldID> AllFieldIDs() const;
        [[nodiscard]] Field CurrentField() const;
        [[nodiscard]] size_t FieldCount() const;
    private:
        [[nodiscard]] static std::unique_ptr<Arca::Reliquary> CreateReliquary(
            Atmos::Asset::Resource::Manager& assetResourceManager,
            Atmos::Logging::Logger& logger);
    };

    class MainFrameCommands
    {
    public:
        using State = MainFrameState;

        Command<> activate;
        Command<> deactivate;

        Command<File::Path> newWorld;
        Command<File::Path> existingWorld;
        Command<File::Path> setBuildWorldPath;
        Command<> closeWorld;
        Command<> saveWorld;
        Command<File::Path> saveWorldAs;
        Command<> buildWorld;
        Command<> startWorld;
        Command<> stopWorld;
        Command<Atmos::World::FieldID> createAndChangeField;
        Command<Atmos::World::FieldID> changeField;
        Command<Atmos::World::FieldID> destroyField;

        Command<> cut;
        Command<> copy;
        Command<> paste;

        Command<> undo;
        Command<> redo;

        Command<std::optional<std::type_index>>::Conversion<std::optional<std::type_index>> editingMode;
        Command<std::optional<std::type_index>>::Conversion<std::optional<std::type_index>> editingTool;

        Command<Settings> changeSettings;

        Command<> exit;

        Command<> idle;
    public:
        MainFrameCommands(State& state);
    private:
        State* state;
        void ResetState();
    private:
        void Activate();
        void Deactivate();

        void NewWorld(const File::Path& filePath);
        void ExistingWorld(const File::Path& filePath);
        void SetBuildFilePath(const File::Path& filePath);
        void CloseWorld();
        void SaveWorld();
        void SaveWorldAs(const File::Path& filePath);
        void BuildWorld();
        void StartWorld();
        void CreateAndChangeField(Atmos::World::FieldID fieldID);
        void ChangeField(Atmos::World::FieldID fieldID);
        void DestroyField(Atmos::World::FieldID fieldID);

        void Cut();
        void Copy();
        void Paste();

        void Undo();
        void Redo();

        std::tuple<std::optional<std::type_index>> ConvertEditingMode(std::optional<std::type_index> modeType);
        std::tuple<std::optional<std::type_index>> ConvertEditingTool(std::optional<std::type_index> toolType);
        void ChangeEditingMode(std::optional<std::type_index> modeType);
        void ChangeEditingTool(std::optional<std::type_index> toolType);

        void ChangeSettings(Settings settings);

        void Idle();
    private:
        struct FieldChangingData
        {
            std::optional<std::type_index> modeType;
            std::optional<std::type_index> toolType;
        };
    private:
        void OnWorldChanged();
        void OnFieldChanging();
        void OnFieldChanged(FieldChangingData fieldChangingData);
        [[nodiscard]] FieldChangingData CurrentFieldChangingData();
        [[nodiscard]] static File::Path WorldFilePathFrom(const File::Path& filePath);
        [[nodiscard]] static File::Path ClientFilePath();
        [[nodiscard]] File::Path WorldFilePath() const;

        void RecordHistory();
        
        void SaveSettings();
        void LoadSettings();
        [[nodiscard]] static File::Path SettingsFilePath();
    };
    
    struct MainFrameStack
    {
        ViewportStack viewport;

        using State = MainFrameState;
        State state;

        using Commands = MainFrameCommands;
        Commands commands;

        MainFrameStack(Atmos::Logging::Logger& logger);
    };
}