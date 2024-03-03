#pragma once

#include <wx/frame.h>
#include <wx/aui/framemanager.h>
#include <wx/panel.h>
#include <wx/listbox.h>
#include "OutputView.h"
#include "PropertiesEditor.h"
#include "AutoTextControl.h"

#include <vector>

#include "MainFrameStack.h"

namespace Creation::Editing
{
    class Viewport;
}

namespace Creation
{
    class MainFrame final : public wxFrame
    {
    public:
        MainFrame(const wxPoint& position, const wxSize& size, const std::shared_ptr<Atmos::Logging::Logger>& logger);
        ~MainFrame();

        void Log(const Atmos::Logging::Log& log);
        void Log(
            const String& message,
            Atmos::Logging::Severity severity = Atmos::Logging::Severity::Information,
            std::optional<Atmos::Logging::Details> details = {});
    private:
        std::unique_ptr<OutputView> outputView;
    private:
        std::shared_ptr<Atmos::Logging::Logger> logger;
    private:
        std::unique_ptr<MainFrameStack> stack;

        wxAuiManager* aui = nullptr;
        AutoTextControl<Atmos::World::FieldID> selectedField;

        wxPanel& CreateMainPanel();
        void SetupViewPanel(wxPanel& mainPanel);

        [[nodiscard]] static std::unique_ptr<MainFrameStack> CreateStack(Atmos::Logging::Logger& logger);
    private:
        void Setup();

        void SetupMainPane(wxPanel& mainPanel);
        void SetupEditorPane(Editing::PropertiesEditor& propertiesEditor);
        void SetupViewportPane(Editing::Viewport& viewport);
        void SetupOutputViewPane(wxListBox& outputView);

        [[nodiscard]] static wxAuiPaneInfo CreateDefaultPaneInfo();

        void SetupMenuBar();
        void SetupFileMenu(wxMenuBar& menuBar);
        void SetupEditMenu(wxMenuBar& menuBar);
        void SetupViewMenu(wxMenuBar& menuBar);
        void SetupAddMenu(wxMenuBar& menuBar);

        void SetupToolBar();

        void SetupStatusBar();

        void SubscribeToCommands(Editing::Viewport& viewport);
        void SubscribeToEvents();
    private:
        Editing::Viewport* viewport;
        [[nodiscard]] std::tuple<Editing::Viewport*, std::unique_ptr<Arca::Reliquary>> CreateViewportAndRenderReliquary();

        void SyncViewportActivated();
    private:
        void Activate();
        void Deactivate();

        void New();
        void Open();
        void Save();
        void SaveAs();
        void CloseWorld();
        void Exit();

        void Undo();
        void Redo();

        void Cut();
        void Copy();
        void Paste();

        void AssetMode();
        void TerrainMode();
        void EntityBoundaryMode();
        void EntityMode();

        void SelectTool();
        void PaintTool();
        void MoveTool();

        void Build();
        void Play();

        void CreateField();
        void DestroyField();

        void Settings();
        void ChangeSettings(Creation::Settings settings);

        void Idle();

        void OnWorldChanged();

        void OnNewField(Atmos::World::FieldID id);
        void ChangeField(Atmos::World::FieldID id);

        void OnHistoryDo(Editing::HistoryArgs args);
        void OnHistoryUndo(Editing::HistoryArgs args);
        void OnHistoryChanged(Editing::History* history);
        [[nodiscard]] static String StatusTextFromCommand(bool forward, const String& message);

        void OnNexusSelectionChanged(const Editing::NexusSelection::Delta& delta);
    private:
        void WorldStarted();
        void WorldStopped();
    private:
        void SaveBuildFileDialog();
        std::optional<File::Path> BuildFileDialog(const String& verb, const File::Path& directory);
        std::optional<File::Path> NewBuildFileDialog();
        std::optional<File::Path> OpenBuildFileDialog();

        std::optional<Atmos::World::FieldID> CreateFieldDialog();
        std::optional<Atmos::World::FieldID> DeleteFieldDialog();

        std::optional<Creation::Settings> SettingsDialog(Creation::Settings settings);

        void MessageDialog(const String& message);
    private:
        std::vector<wxMenuItem*> menuItemsRequiresWorld;
        std::vector<int> toolsRequiresWorld;

        void EnableRequiresWorld();
        void DisableRequiresWorld();
    private:
        static inline const String baseTitle = "Creation Editor";
        static inline const String changedTitleAddition = "(*) ";

        bool shouldHaveChangedTitleAddition = false;

        void SyncTitle();
    private:
        struct MenuToolLink
        {
            wxMenuItem* menuItem = nullptr;
            int tool = 0;

            void Enable(const MainFrame& mainFrame);
            void Disable(const MainFrame& mainFrame);
        };
    private:
        wxMenuItem* viewTerrainMenuItem = nullptr;
        wxMenuItem* viewEntityBoundaryMenuItem = nullptr;
        wxMenuItem* viewEntitiesMenuItem = nullptr;

        void SyncViewMenuItems();
    private:
        MenuToolLink undoLink;
        MenuToolLink redoLink;

        void SyncUndoRedoButtons();
    private:
        MenuToolLink cutLink;
        MenuToolLink copyLink;
        MenuToolLink pasteLink;

        void SyncCutCopyPasteButtons();
    private:
        void SyncTools();

        [[nodiscard]] int FromModeType(const std::type_index& modeType);
        [[nodiscard]] int FromToolType(const std::type_index& toolType);
    private:
        void SyncEditor();
    private:
        enum
        {
            // Menu bar
            NewFileId,
            OpenFileId,
            SaveFileId,
            SaveFileAsId,
            CloseFieldId,

            // Edit menu
            EditCutId,
            EditCopyId,
            EditPasteId,
            EditUndoId,
            EditRedoId,
            EditWorldStartId,
            EditSettingsId,

            // View menu
            ViewTerrainId,
            ViewEntityBoundaryId,
            ViewEntitiesId,

            // Field menu
            CreateFieldId,
            DestroyFieldId,

            // Toolbar
            NewFileToolId,
            OpenFileToolId,
            SaveFileToolId,
            SaveFileAsToolId,
            CloseWorldToolId,
            ExitToolId,

            CutToolId,
            CopyToolId,
            PasteToolId,

            UndoToolId,
            RedoToolId,

            AssetsToolId,
            TerrainToolId,
            EntityBoundaryToolId,
            EntitiesToolId,

            SelectToolId,
            PaintToolId,
            MoveToolId,

            BuildToolId,
            PlayToolId
        };

        const std::vector<int> editingModeTools =
        {
            AssetsToolId,
            TerrainToolId,
            EntityBoundaryToolId,
            EntitiesToolId
        };

        const std::vector<int> editingTools =
        {
            SelectToolId,
            PaintToolId,
            MoveToolId
        };

        void NewFileEvent(wxCommandEvent& e);
        void OpenFileEvent(wxCommandEvent& e);
        void SaveFileEvent(wxCommandEvent& e);
        void SaveFileAsEvent(wxCommandEvent& e);
        void CloseEvent(wxCommandEvent& e);
        void ExitEvent(wxCommandEvent& e);

        void CutEvent(wxCommandEvent& e);
        void CopyEvent(wxCommandEvent& e);
        void PasteEvent(wxCommandEvent& e);
        void UndoEvent(wxCommandEvent& e);
        void RedoEvent(wxCommandEvent& e);
        void EditWorldStartEvent(wxCommandEvent& e);
        void SettingsEvent(wxCommandEvent& e);

        void ViewTerrainEvent(wxCommandEvent& e);
        void ViewEntityBoundaryEvent(wxCommandEvent& e);
        void ViewEntitiesEvent(wxCommandEvent& e);

        void CreateFieldEvent(wxCommandEvent& e);
        void DestroyFieldEvent(wxCommandEvent& e);

        void NewToolEvent(wxCommandEvent& e);
        void OpenToolEvent(wxCommandEvent& e);
        void SaveToolEvent(wxCommandEvent& e);
        void SaveAsToolEvent(wxCommandEvent& e);
        void CloseWorldToolEvent(wxCommandEvent& e);
        void ExitToolEvent(wxCommandEvent& e);

        void CutToolEvent(wxCommandEvent& e);
        void CopyToolEvent(wxCommandEvent& e);
        void PasteToolEvent(wxCommandEvent& e);

        void UndoToolEvent(wxCommandEvent& e);
        void RedoToolEvent(wxCommandEvent& e);

        void AssetsToolEvent(wxCommandEvent& e);
        void TerrainToolEvent(wxCommandEvent& e);
        void EntityBoundaryToolEvent(wxCommandEvent& e);
        void EntitiesToolEvent(wxCommandEvent& e);

        void SelectToolEvent(wxCommandEvent& e);
        void PaintToolEvent(wxCommandEvent& e);
        void MoveToolEvent(wxCommandEvent& e);

        void BuildToolEvent(wxCommandEvent& e);
        void PlayToolEvent(wxCommandEvent& e);

        void FieldSelectedEvent();

        void ViewportMouseMovedEvent(Atmos::Spatial::Point2D point);

        void ActiveChangedEvent(wxActivateEvent& e);

        void IdleEvent(wxIdleEvent& e);
    };
}