#include "MainFrame.h"

#include <wx/artprov.h>
#include <wx/textdlg.h>
#include <wx/msgdlg.h>
#include <wx/toolbar.h>
#include <wx/menuitem.h>
#include <wx/menu.h>
#include <wx/filedlg.h>
#include <wx/stattext.h>
#include "Viewport.h"
#include "SettingsDialog.h"
#include "ToWxWidgets.h"

#include "AssetEditingMode.h"
#include "TerrainEditingMode.h"
#include "EntityBoundaryEditingMode.h"
#include "EntityEditingMode.h"
#include "PaintTool.h"
#include "SelectTool.h"
#include "MoveTool.h"

#include "RenderReliquary.h"
#include "LoggingSink.h"

namespace Creation
{
    MainFrame::MainFrame(
        const wxPoint& position,
        const wxSize& size,
        const std::shared_ptr<Atmos::Logging::Logger>& logger)
        :
        wxFrame(nullptr, wxID_ANY, "", position, size),
        outputView(std::make_unique<OutputView>(this, 100)),
        logger(logger),
        stack(CreateStack(*this->logger)),
        aui(new wxAuiManager(this, 0))
    {
        Setup();

        stack->commands.activate();
    }

    MainFrame::~MainFrame()
    {
        viewport->Destroy();

        stack.reset();

        aui->UnInit();
    }

    void MainFrame::Log(const Atmos::Logging::Log& log)
    {
        logger->Log(log);
    }

    void MainFrame::Log(
        const String& message,
        Atmos::Logging::Severity severity,
        std::optional<Atmos::Logging::Details> details)
    {
        logger->Log(message, severity, details);
    }

    wxPanel& MainFrame::CreateMainPanel()
    {
        const auto mainPanel = new wxPanel(this);
        mainPanel->SetSizer(new wxBoxSizer(wxVERTICAL));
        return *mainPanel;
    }

    void MainFrame::SetupViewPanel(wxPanel& mainPanel)
    {
        const auto viewPanel = new wxPanel(
            &mainPanel,
            wxID_ANY,
            wxDefaultPosition,
            wxSize(250, 45),
            wxNO_BORDER | wxTAB_TRAVERSAL);
        const auto fieldChangeTextCtrl = selectedField.InitWrapped(viewPanel);
        selectedField.SetOnEnterFunction(Chroma::CreateFunction(&MainFrame::FieldSelectedEvent, *this));

        const auto viewPanelSizer = new wxBoxSizer(wxVERTICAL);
        viewPanel->SetSizer(viewPanelSizer);

        const auto fieldSizer = new wxBoxSizer(wxVERTICAL);
        viewPanelSizer->Add(fieldSizer, 0, wxEXPAND);
        fieldSizer->Add(new wxStaticText(viewPanel, wxID_ANY, "Field:"), 0, wxALIGN_CENTER);
        fieldSizer->Add(fieldChangeTextCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

        mainPanel.GetSizer()->Add(viewPanel, 0, wxEXPAND);
    }

    std::unique_ptr<MainFrameStack> MainFrame::CreateStack(Atmos::Logging::Logger& logger)
    {
        return std::make_unique<MainFrameStack>(logger);
    }

    void MainFrame::Setup()
    {
        SetupStatusBar();
        SetupMenuBar();
        SetupToolBar();

        logger->AddSink<LoggingSink>(*outputView, *GetStatusBar());

        auto& mainPanel = CreateMainPanel();

        auto& nexusSelection = stack->state.nexusSelection;
        auto& history = stack->state.history;

        const auto propertiesEditor = new Editing::PropertiesEditor(
            nexusSelection,
            this);
        const auto propertiesTree = new Editing::PropertiesTree(
            nexusSelection,
            Editing::NexusHistory(history, nexusSelection),
            &mainPanel);
        mainPanel.GetSizer()->Add(propertiesTree, 1, wxEXPAND);

        auto viewportAndRenderReliquary = CreateViewportAndRenderReliquary();
        viewport = std::get<0>(viewportAndRenderReliquary);
        stack->state.renderReliquary = std::move(std::get<1>(viewportAndRenderReliquary));

        stack->state.editor = std::make_unique<Editing::Editor>(
            stack->viewport,
            *propertiesEditor,
            *propertiesTree,
            *stack->state.renderReliquary,
            history,
            nexusSelection);

        SetupMainPane(mainPanel);
        SetupEditorPane(*propertiesEditor);
        SetupViewportPane(*viewport);
        SetupOutputViewPane(*outputView->Listbox());

        aui->Update();

        SetupViewPanel(mainPanel);

        DisableRequiresWorld();

        Maximize();
        Centre();

        this->SetExtraStyle(wxWS_EX_PROCESS_IDLE);

        SyncViewMenuItems();

        SyncTitle();

        SubscribeToCommands(*viewport);
        SubscribeToEvents();
    }

    void MainFrame::SetupMainPane(wxPanel& mainPanel)
    {
        auto paneInfo = CreateDefaultPaneInfo();
        paneInfo.Left();
        paneInfo.Caption("Main");
        paneInfo.Layer(2);
        paneInfo.BestSize(250, -1);
        aui->AddPane(&mainPanel, paneInfo);
    }

    void MainFrame::SetupEditorPane(Editing::PropertiesEditor& propertiesEditor)
    {
        auto paneInfo = CreateDefaultPaneInfo();
        paneInfo.Left();
        paneInfo.Caption("Editor");
        paneInfo.Layer(1);
        paneInfo.BestSize(400, -1);
        aui->AddPane(&propertiesEditor, paneInfo);
    }

    void MainFrame::SetupViewportPane(Editing::Viewport& viewport)
    {
        auto paneInfo = CreateDefaultPaneInfo();
        paneInfo.Center();
        paneInfo.Caption("Viewport");
        aui->AddPane(&viewport, paneInfo);
    }

    void MainFrame::SetupOutputViewPane(wxListBox& outputView)
    {
        auto paneInfo = CreateDefaultPaneInfo();
        paneInfo.Bottom();
        paneInfo.Caption("Output View");
        paneInfo.Layer(0);
        paneInfo.BestSize(-1, 150);
        aui->AddPane(&outputView, paneInfo);
    }

    wxAuiPaneInfo MainFrame::CreateDefaultPaneInfo()
    {
        wxAuiPaneInfo paneInfo;
        paneInfo.CaptionVisible(true);
        paneInfo.PaneBorder(false);
        paneInfo.Gripper(false);
        paneInfo.GripperTop(false);
        paneInfo.Floatable(false);
        paneInfo.CloseButton(false);
        paneInfo.Movable(false);
        return paneInfo;
    }

    void MainFrame::SetupMenuBar()
    {
        const auto menuBar = new wxMenuBar();
        SetMenuBar(menuBar);

        SetupFileMenu(*menuBar);
        SetupEditMenu(*menuBar);
        SetupViewMenu(*menuBar);
        SetupAddMenu(*menuBar);
    }

    void MainFrame::SetupFileMenu(wxMenuBar& menuBar)
    {
        const auto menu = new wxMenu();
        menu->Append(NewFileId, "New");
        menu->Append(OpenFileId, "Open");
        menuItemsRequiresWorld.push_back(menu->Append(SaveFileId, "Save"));
        menuItemsRequiresWorld.push_back(menu->Append(SaveFileAsId, "Save As"));
        menuItemsRequiresWorld.push_back(menu->Append(CloseFieldId, "Close"));
        menu->AppendSeparator();
        menu->Append(wxID_EXIT);

        menuBar.Append(menu, "File");
    }

    void MainFrame::SetupEditMenu(wxMenuBar& menuBar)
    {
        const auto menu = new wxMenu();
        cutLink.menuItem = menu->Append(EditCutId, "Cut\tCtrl-X");
        copyLink.menuItem = menu->Append(EditCopyId, "Copy\tCtrl-C");
        pasteLink.menuItem = menu->Append(EditPasteId, "Paste\tCtrl-V");
        undoLink.menuItem = menu->Append(EditUndoId, "Undo\tCtrl-Z");
        redoLink.menuItem = menu->Append(EditRedoId, "Redo\tCtrl-Y");
        menu->AppendSeparator();
        menuItemsRequiresWorld.push_back(menu->Append(EditWorldStartId, "World Start"));
        menu->AppendSeparator();
        menu->Append(EditSettingsId, "Settings");

        menuBar.Append(menu, "Edit");
    }

    void MainFrame::SetupViewMenu(wxMenuBar& menuBar)
    {
        const auto menu = new wxMenu();

        const auto viewportMenu = new wxMenu();
        menu->AppendSubMenu(viewportMenu, "Viewport");
        viewTerrainMenuItem = viewportMenu->AppendCheckItem(ViewTerrainId, "Terrain");
        viewEntityBoundaryMenuItem = viewportMenu->AppendCheckItem(ViewEntityBoundaryId, "Entity Boundary");
        viewEntitiesMenuItem = viewportMenu->AppendCheckItem(ViewEntitiesId, "Entities");

        menuBar.Append(menu, "View");
    }

    void MainFrame::SetupAddMenu(wxMenuBar& menuBar)
    {
        const auto menu = new wxMenu();
        menuItemsRequiresWorld.push_back(menu->Append(CreateFieldId, "Create\tCtrl-F"));
        menuItemsRequiresWorld.push_back(menu->Append(DestroyFieldId, "Destroy\tCtrl-D"));

        menuBar.Append(menu, "Field");
    }

    void MainFrame::SetupToolBar()
    {
        auto toolbar = CreateToolBar(wxTB_HORIZONTAL | wxTB_FLAT);

        const auto addTool = [&toolbar](size_t id, wxBitmap&& bitmap, wxString&& help)
        {
            toolbar->AddTool(id, "", bitmap, help);
        };

        const auto addRequiresWorldTool = [this, &toolbar](size_t id, wxBitmap&& bitmap, wxString&& help)
        {
            toolbar->AddTool(id, "", bitmap, help);
            toolsRequiresWorld.push_back(id);
        };

        addTool(NewFileToolId, wxArtProvider::GetBitmap(wxART_NEW, wxART_TOOLBAR), "New");
        addTool(OpenFileToolId, wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_TOOLBAR), "Open");
        addRequiresWorldTool(SaveFileToolId, wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_TOOLBAR), "Save");
        addRequiresWorldTool(SaveFileAsToolId, wxArtProvider::GetBitmap(wxART_FILE_SAVE_AS, wxART_TOOLBAR), "Save As");
        addRequiresWorldTool(CloseWorldToolId, wxArtProvider::GetBitmap(wxART_CLOSE, wxART_TOOLBAR), "Close");
        addTool(ExitToolId, wxArtProvider::GetBitmap(wxART_QUIT, wxART_TOOLBAR), "Exit");
        toolbar->AddSeparator();
        addTool(CutToolId, wxArtProvider::GetBitmap(wxART_CUT, wxART_TOOLBAR), "Cut");
        cutLink.tool = CutToolId;
        addTool(CopyToolId, wxArtProvider::GetBitmap(wxART_COPY, wxART_TOOLBAR), "Copy");
        copyLink.tool = CopyToolId;
        addTool(PasteToolId, wxArtProvider::GetBitmap(wxART_PASTE, wxART_TOOLBAR), "Paste");
        pasteLink.tool = PasteToolId;
        addTool(UndoToolId, wxArtProvider::GetBitmap(wxART_UNDO, wxART_TOOLBAR), "Undo");
        undoLink.tool = UndoToolId;
        addTool(RedoToolId, wxArtProvider::GetBitmap(wxART_REDO, wxART_TOOLBAR), "Redo");
        redoLink.tool = RedoToolId;
        toolbar->AddSeparator();
        toolbar->AddCheckTool(
            AssetsToolId,
            "Assets",
            wxBitmap(wxT("images\\assets_tool.png"), wxBITMAP_TYPE_PNG),
            wxNullBitmap,
            wxT("Assets"));
        toolsRequiresWorld.push_back(AssetsToolId);
        toolbar->AddCheckTool(
            TerrainToolId,
            "Terrain",
            wxBitmap(wxT("images\\terrain_tool.png"), wxBITMAP_TYPE_PNG),
            wxNullBitmap,
            wxT("Terrain"));
        toolsRequiresWorld.push_back(TerrainToolId);
        toolbar->AddCheckTool(
            EntityBoundaryToolId,
            "Entity Boundary",
            wxBitmap(wxT("images\\entity_boundary_tool.png"), wxBITMAP_TYPE_PNG),
            wxNullBitmap,
            wxT("Entity Boundary"));
        toolsRequiresWorld.push_back(EntityBoundaryToolId);
        toolbar->AddCheckTool(
            EntitiesToolId,
            "Entities",
            wxBitmap(wxT("images\\entities_tool.png"), wxBITMAP_TYPE_PNG),
            wxNullBitmap,
            wxT("Entities"));
        toolsRequiresWorld.push_back(EntitiesToolId);
        toolbar->AddSeparator();
        toolbar->AddCheckTool(
            SelectToolId,
            "Select",
            wxBitmap(wxT("images\\select_tool.png"), wxBITMAP_TYPE_PNG),
            wxNullBitmap,
            wxT("Select"));
        toolsRequiresWorld.push_back(SelectToolId);
        toolbar->AddCheckTool(
            PaintToolId,
            "Paint",
            wxBitmap(wxT("images\\paint_tool.png"), wxBITMAP_TYPE_PNG),
            wxNullBitmap,
            wxT("Paint"));
        toolsRequiresWorld.push_back(PaintToolId);
        toolbar->AddCheckTool(
            MoveToolId,
            "Move",
            wxBitmap(wxT("images\\move_tool.png"), wxBITMAP_TYPE_PNG),
            wxNullBitmap,
            wxT("Move"));
        toolsRequiresWorld.push_back(MoveToolId);
        toolbar->AddSeparator();
        addRequiresWorldTool(
            BuildToolId,
            wxBitmap(wxT("images\\build_tool.png"), wxBITMAP_TYPE_PNG),
            "Build");
        addRequiresWorldTool(
            PlayToolId,
            wxBitmap(wxT("images\\play_tool.png"), wxBITMAP_TYPE_PNG),
            "Play");
        toolbar->Realize();
    }

    void MainFrame::SetupStatusBar()
    {
        SetStatusBar(new wxStatusBar(this, wxID_ANY, 0));
        GetStatusBar()->SetFieldsCount(2);
    }

    void MainFrame::SubscribeToCommands(Editing::Viewport& viewport)
    {
        stack->commands.activate.On(std::bind(&MainFrame::SyncEditor, this));
        stack->commands.deactivate.On(std::bind(&MainFrame::SyncEditor, this));
        stack->commands.newWorld.On(std::bind(&MainFrame::OnWorldChanged, this));
        stack->commands.existingWorld.On(std::bind(&MainFrame::OnWorldChanged, this));
        stack->commands.closeWorld.On(std::bind(&MainFrame::OnWorldChanged, this));
        stack->commands.changeSettings.On(std::bind(&MainFrame::SyncViewMenuItems, this));
        stack->commands.saveWorld.On(std::bind(&MainFrame::SyncTitle, this));
        stack->commands.saveWorldAs.On(std::bind(&MainFrame::SyncTitle, this));
        stack->commands.startWorld.On(std::bind(&MainFrame::WorldStarted, this));
        stack->commands.stopWorld.On(std::bind(&MainFrame::WorldStopped, this));

        stack->commands.cut.On(std::bind(&MainFrame::SyncCutCopyPasteButtons, this));
        stack->commands.copy.On(std::bind(&MainFrame::SyncCutCopyPasteButtons, this));
        stack->commands.paste.On(std::bind(&MainFrame::SyncCutCopyPasteButtons, this));

        stack->commands.editingMode.On(std::bind(&MainFrame::SyncTools, this));
        stack->commands.editingTool.On(std::bind(&MainFrame::SyncTools, this));

        stack->commands.exit.On(std::bind(&MainFrame::Exit, this));

        auto& history = stack->state.history;
        auto& nexusSelection = stack->state.nexusSelection;

        stack->viewport.commands.mouseMoved.OnArguments(std::bind(&MainFrame::ViewportMouseMovedEvent, this, std::placeholders::_1));
        history.onDo.Subscribe(&MainFrame::OnHistoryDo, *this);
        history.onUndo.Subscribe(&MainFrame::OnHistoryUndo, *this);
        history.onChanged.Subscribe(&MainFrame::OnHistoryChanged, *this);
        nexusSelection.onChanged.Subscribe(&MainFrame::OnNexusSelectionChanged, *this);
    }

    void MainFrame::SubscribeToEvents()
    {
        Bind(wxEVT_MENU, &MainFrame::NewFileEvent, this, NewFileId);
        Bind(wxEVT_MENU, &MainFrame::OpenFileEvent, this, OpenFileId);
        Bind(wxEVT_MENU, &MainFrame::SaveFileEvent, this, SaveFileId);
        Bind(wxEVT_MENU, &MainFrame::SaveFileAsEvent, this, SaveFileAsId);
        Bind(wxEVT_MENU, &MainFrame::CloseEvent, this, CloseFieldId);
        Bind(wxEVT_MENU, &MainFrame::ExitEvent, this, wxID_EXIT);

        Bind(wxEVT_MENU, &MainFrame::CutEvent, this, EditCutId);
        Bind(wxEVT_MENU, &MainFrame::CopyEvent, this, EditCopyId);
        Bind(wxEVT_MENU, &MainFrame::PasteEvent, this, EditPasteId);
        Bind(wxEVT_MENU, &MainFrame::UndoEvent, this, EditUndoId);
        Bind(wxEVT_MENU, &MainFrame::RedoEvent, this, EditRedoId);
        Bind(wxEVT_MENU, &MainFrame::EditWorldStartEvent, this, EditWorldStartId);
        Bind(wxEVT_MENU, &MainFrame::SettingsEvent, this, EditSettingsId);

        Bind(wxEVT_MENU, &MainFrame::ViewTerrainEvent, this, ViewTerrainId);
        Bind(wxEVT_MENU, &MainFrame::ViewEntityBoundaryEvent, this, ViewEntityBoundaryId);
        Bind(wxEVT_MENU, &MainFrame::ViewEntitiesEvent, this, ViewEntitiesId);

        Bind(wxEVT_MENU, &MainFrame::CreateFieldEvent, this, CreateFieldId);
        Bind(wxEVT_MENU, &MainFrame::DestroyFieldEvent, this, DestroyFieldId);

        Bind(wxEVT_TOOL, &MainFrame::NewToolEvent, this, NewFileToolId);
        Bind(wxEVT_TOOL, &MainFrame::OpenToolEvent, this, OpenFileToolId);
        Bind(wxEVT_TOOL, &MainFrame::SaveToolEvent, this, SaveFileToolId);
        Bind(wxEVT_TOOL, &MainFrame::SaveAsToolEvent, this, SaveFileAsToolId);
        Bind(wxEVT_TOOL, &MainFrame::CloseWorldToolEvent, this, CloseWorldToolId);
        Bind(wxEVT_TOOL, &MainFrame::ExitToolEvent, this, ExitToolId);
        Bind(wxEVT_TOOL, &MainFrame::CutToolEvent, this, CutToolId);
        Bind(wxEVT_TOOL, &MainFrame::CopyToolEvent, this, CopyToolId);
        Bind(wxEVT_TOOL, &MainFrame::PasteToolEvent, this, PasteToolId);
        Bind(wxEVT_TOOL, &MainFrame::UndoToolEvent, this, UndoToolId);
        Bind(wxEVT_TOOL, &MainFrame::RedoToolEvent, this, RedoToolId);

        Bind(wxEVT_TOOL, &MainFrame::AssetsToolEvent, this, AssetsToolId);
        Bind(wxEVT_TOOL, &MainFrame::TerrainToolEvent, this, TerrainToolId);
        Bind(wxEVT_TOOL, &MainFrame::EntityBoundaryToolEvent, this, EntityBoundaryToolId);
        Bind(wxEVT_TOOL, &MainFrame::EntitiesToolEvent, this, EntitiesToolId);

        Bind(wxEVT_TOOL, &MainFrame::SelectToolEvent, this, SelectToolId);
        Bind(wxEVT_TOOL, &MainFrame::PaintToolEvent, this, PaintToolId);
        Bind(wxEVT_TOOL, &MainFrame::MoveToolEvent, this, MoveToolId);

        Bind(wxEVT_TOOL, &MainFrame::BuildToolEvent, this, BuildToolId);
        Bind(wxEVT_TOOL, &MainFrame::PlayToolEvent, this, PlayToolId);

        Bind(wxEVT_ACTIVATE, &MainFrame::ActiveChangedEvent, this);

        Bind(wxEVT_IDLE, &MainFrame::IdleEvent, this);
    }

    std::tuple<Editing::Viewport*, std::unique_ptr<Arca::Reliquary>> MainFrame::CreateViewportAndRenderReliquary()
    {
        auto viewport = new Editing::Viewport(stack->viewport, this, wxID_ANY);
        auto renderReliquary = CreateRenderReliquary(
            stack->state.vulkanGraphicsManager,
            stack->state.sdlTextManager,
            stack->state.realAssetResourceManager,
            Atmos::Spatial::Size2D{ 10, 10 },
            *stack->state.logger,
            reinterpret_cast<HWND>(viewport->GetHandle()));
        stack->viewport.state.reliquary = renderReliquary.get();
        return { viewport, std::move(renderReliquary) };
    }

    void MainFrame::SyncViewportActivated()
    {
        
    }

    void MainFrame::Activate()
    {
        stack->commands.activate();
    }

    void MainFrame::Deactivate()
    {
        stack->commands.deactivate();
    }

    void MainFrame::New()
    {
        const auto path = NewBuildFileDialog();
        if (path)
            stack->commands.newWorld(*path);
    }

    void MainFrame::Open()
    {
        const auto path = OpenBuildFileDialog();
        if (path)
            stack->commands.existingWorld(*path);
    }

    void MainFrame::Save()
    {
        if (!stack->state.currentWorld)
            SaveBuildFileDialog();

        stack->commands.saveWorld();
    }

    void MainFrame::SaveAs()
    {
        SaveBuildFileDialog();
    }

    void MainFrame::CloseWorld()
    {
        stack->commands.closeWorld();
    }

    void MainFrame::Exit()
    {
        Close(true);
    }

    void MainFrame::Undo()
    {
        stack->commands.undo();
    }

    void MainFrame::Redo()
    {
        stack->commands.redo();
    }

    void MainFrame::Cut()
    {
        stack->commands.cut();
    }

    void MainFrame::Copy()
    {
        stack->commands.copy();
    }

    void MainFrame::Paste()
    {
        stack->commands.paste();
    }

    void MainFrame::AssetMode()
    {
        stack->commands.editingMode(typeid(Editing::AssetMode));
    }

    void MainFrame::TerrainMode()
    {
        stack->commands.editingMode(typeid(Editing::TerrainMode));
    }

    void MainFrame::EntityBoundaryMode()
    {
        stack->commands.editingMode(typeid(Editing::EntityBoundaryMode));
    }

    void MainFrame::EntityMode()
    {
        stack->commands.editingMode(typeid(Editing::EntityMode));
    }

    void MainFrame::SelectTool()
    {
        stack->commands.editingTool(typeid(Editing::SelectTool));
    }

    void MainFrame::PaintTool()
    {
        stack->commands.editingTool(typeid(Editing::PaintTool));
    }

    void MainFrame::MoveTool()
    {
        stack->commands.editingTool(typeid(Editing::MoveTool));
    }

    void MainFrame::Build()
    {
        stack->commands.buildWorld();
    }

    void MainFrame::Play()
    {
        stack->commands.startWorld();
    }

    void MainFrame::CreateField()
    {
        const auto id = CreateFieldDialog();
        if (id)
        {
            stack->commands.createAndChangeField(*id);
            OnNewField(*id);
        }
    }

    void MainFrame::DestroyField()
    {
        if (stack->state.FieldCount() == 1)
            MessageDialog("Cannot delete the only field in the world.");
        else
        {
            const auto id = DeleteFieldDialog();
            if (id)
                stack->commands.destroyField(*id);
        }
    }

    void MainFrame::Settings()
    {
        const auto settings = SettingsDialog(Creation::settings);
        if (settings)
            ChangeSettings(*settings);
    }

    void MainFrame::ChangeSettings(Creation::Settings settings)
    {
        stack->commands.changeSettings(settings);
    }

    void MainFrame::Idle()
    {
        stack->commands.idle();
    }

    void MainFrame::OnWorldChanged()
    {
        if (stack->state.currentWorld)
            EnableRequiresWorld();
        else
        {
            DisableRequiresWorld();

            stack->state.editor->HideRoot();

            SetStatusText("", 1);
        }

        SyncEditor();
        SyncTitle();
        Refresh();
    }

    void MainFrame::OnNewField(Atmos::World::FieldID id)
    {
        selectedField.ChangeValue(id);
    }

    void MainFrame::ChangeField(Atmos::World::FieldID id)
    {
        stack->commands.changeField(id);
    }

    void MainFrame::OnHistoryDo(Editing::HistoryArgs args)
    {
        SetStatusText(StatusTextFromCommand(true, args.message));
    }

    void MainFrame::OnHistoryUndo(Editing::HistoryArgs args)
    {
        SetStatusText(StatusTextFromCommand(false, args.message));
    }

    void MainFrame::OnHistoryChanged(Editing::History* history)
    {
        SyncUndoRedoButtons();
        SyncTitle();
    }

    String MainFrame::StatusTextFromCommand(bool forward, const String& message)
    {
        return message + (forward ? " done." : " undone.");
    }

    void MainFrame::OnNexusSelectionChanged(const Editing::NexusSelection::Delta&)
    {
        SyncCutCopyPasteButtons();
    }

    void MainFrame::WorldStarted()
    {
        Disable();
    }

    void MainFrame::WorldStopped()
    {
        Enable();
        Raise();
    }

    void MainFrame::SaveBuildFileDialog()
    {
        const auto path = BuildFileDialog("Save", settings.buildPath);
        if (path)
            stack->commands.saveWorldAs(*path);
    }

    std::optional<File::Path> MainFrame::BuildFileDialog(const String& verb, const File::Path& directory)
    {
        wxFileDialog dialog(
            this,
            _(verb + " build file"),
            "",
            "",
            "atb files (*.atb)|*.atb",
            wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        dialog.SetDirectory(directory.string());
        return dialog.ShowModal() != wxID_CANCEL
            ? dialog.GetPath().ToStdString()
            : std::optional<File::Path>{};
    }

    std::optional<File::Path> MainFrame::NewBuildFileDialog()
    {
        return BuildFileDialog("Use", settings.buildPath);
    }

    std::optional<File::Path> MainFrame::OpenBuildFileDialog()
    {
        wxFileDialog dialog(
            this,
            _("Open build file"),
            "",
            "",
            "atb files (*.atb)|*.atb",
            wxFD_OPEN | wxFD_FILE_MUST_EXIST);

        dialog.SetDirectory(settings.buildPath.string());
        return dialog.ShowModal() != wxID_CANCEL
            ? dialog.GetPath().ToStdString()
            : std::optional<File::Path>{};
    }

    std::optional<Atmos::World::FieldID> MainFrame::CreateFieldDialog()
    {
        wxTextEntryDialog dialog(this, "Enter in field ID.");
        wxTextValidator validator(wxFILTER_DIGITS | wxFILTER_EMPTY | wxFILTER_EXCLUDE_LIST);
        validator.SetExcludes(WxWidgets::ToStringArray(stack->state.AllFieldIDs()));
        dialog.SetTextValidator(validator);
        return dialog.ShowModal() == wxID_OK
            ? Atmos::FromString<Atmos::World::FieldID>(dialog.GetValue().ToStdString())
            : std::optional<Atmos::World::FieldID>{};
    }

    std::optional<Atmos::World::FieldID> MainFrame::DeleteFieldDialog()
    {
        wxTextEntryDialog dialog(this, "Enter in field ID.");
        wxTextValidator validator(wxFILTER_DIGITS | wxFILTER_EMPTY | wxFILTER_INCLUDE_LIST);
        validator.SetIncludes(WxWidgets::ToStringArray(stack->state.AllFieldIDs()));
        dialog.SetTextValidator(validator);
        return dialog.ShowModal() == wxID_OK
            ? Atmos::FromString<Atmos::World::FieldID>(dialog.GetValue().ToStdString())
            : std::optional<Atmos::World::FieldID>{};
    }

    std::optional<Settings> MainFrame::SettingsDialog(Creation::Settings settings)
    {
        Creation::SettingsDialog dialog(settings, this, "Settings");
        return dialog.ShowModal() != wxID_CANCEL
            ? dialog.Settings()
            : std::optional<Creation::Settings>{};
    }

    void MainFrame::MessageDialog(const String& message)
    {
        wxMessageDialog dialog(this, message);
        dialog.ShowModal();
    }

    void MainFrame::EnableRequiresWorld()
    {
        for (const auto& item : menuItemsRequiresWorld)
            item->Enable(true);
        for (const auto& tool : toolsRequiresWorld)
            GetToolBar()->EnableTool(tool, true);

        SyncUndoRedoButtons();
        SyncCutCopyPasteButtons();
    }

    void MainFrame::DisableRequiresWorld()
    {
        for (const auto& item : menuItemsRequiresWorld)
        {
            if (item->IsCheckable())
                item->Check(false);
            item->Enable(false);
        }
        for (const auto& tool : toolsRequiresWorld)
        {
            GetToolBar()->ToggleTool(tool, false);
            GetToolBar()->EnableTool(tool, false);
        }

        SyncUndoRedoButtons();
        SyncCutCopyPasteButtons();
    }

    void MainFrame::SyncTitle()
    {
        const auto& state = stack->state;
        const auto title =
            (shouldHaveChangedTitleAddition ? changedTitleAddition : "")
            + baseTitle
            + (state.currentWorld ? " - " + state.currentWorld->BuildFilePath().filename().string() : "");

        SetTitle(title);
    }

    void MainFrame::MenuToolLink::Enable(const MainFrame& mainFrame)
    {
        menuItem->Enable();
        mainFrame.GetToolBar()->EnableTool(tool, true);
    }

    void MainFrame::MenuToolLink::Disable(const MainFrame& mainFrame)
    {
        menuItem->Enable(false);
        mainFrame.GetToolBar()->ToggleTool(tool, false);
        mainFrame.GetToolBar()->EnableTool(tool, false);
    }

    void MainFrame::SyncViewMenuItems()
    {
        viewTerrainMenuItem->Check(settings.viewTerrain);
        stack->state.editor->ViewTerrain(settings.viewTerrain);
        viewEntityBoundaryMenuItem->Check(settings.viewEntityBoundary);
        stack->state.editor->ViewEntityBoundary(settings.viewEntityBoundary);
        viewEntitiesMenuItem->Check(settings.viewEntities);
        stack->state.editor->ViewEntities(settings.viewEntities);
    }

    void MainFrame::SyncUndoRedoButtons()
    {
        const auto& state = stack->state;
        const auto canReverse = state.history.CanReverse();
        if (canReverse)
            undoLink.Enable(*this);
        else
            undoLink.Disable(*this);

        const auto canForward = state.history.CanForward();
        if (canForward)
            redoLink.Enable(*this);
        else
            redoLink.Disable(*this);
    }

    void MainFrame::SyncCutCopyPasteButtons()
    {
        const auto& state = stack->state;
        if (!state.nexusSelection.empty())
        {
            cutLink.Enable(*this);
            copyLink.Enable(*this);
        }
        else
        {
            cutLink.Disable(*this);
            copyLink.Disable(*this);
        }

        if (state.clipboard)
            pasteLink.Enable(*this);
        else
            pasteLink.Disable(*this);
    }

    void MainFrame::SyncTools()
    {
        const auto toolbar = GetToolBar();
        const auto currentModeType = stack->state.editor->CurrentMode();
        const auto currentToolType = stack->state.editor->CurrentTool();

        if (currentModeType)
        {
            const auto type = FromModeType(typeid(*currentModeType));
            for (auto& tool : editingModeTools)
                toolbar->ToggleTool(tool, tool == type);
        }
        else
            for (auto& tool : editingModeTools)
                toolbar->ToggleTool(tool, false);

        if (currentToolType)
        {
            const auto type = FromToolType(typeid(*currentToolType));
            for (auto& tool : editingTools)
                toolbar->ToggleTool(tool, tool == type);
        }
        else
            for (auto& tool : editingTools)
                toolbar->ToggleTool(tool, false);
    }

    int MainFrame::FromModeType(const std::type_index& modeType)
    {
        if (modeType == typeid(Editing::AssetMode))
            return AssetsToolId;
        else if (modeType == typeid(Editing::TerrainMode))
            return TerrainToolId;
        else if (modeType == typeid(Editing::EntityBoundaryMode))
            return EntityBoundaryToolId;
        else if (modeType == typeid(Editing::EntityMode))
            return EntitiesToolId;
        else
            throw std::runtime_error("Attempted to find tool ID for unknown editing mode.");
    }

    int MainFrame::FromToolType(const std::type_index& toolType)
    {
        if (toolType == typeid(Editing::SelectTool))
            return SelectToolId;
        else if (toolType == typeid(Editing::PaintTool))
            return PaintToolId;
        else if (toolType == typeid(Editing::MoveTool))
            return MoveToolId;
        else
            throw std::runtime_error("Attempted to find tool ID for unknown editing tool.");
    }

    void MainFrame::SyncEditor()
    {
        if (stack->state.isActive && stack->state.currentWorld)
            stack->state.editor->Activate();
        else
            stack->state.editor->Deactivate();
    }

    void MainFrame::NewFileEvent(wxCommandEvent& e)
    {
        New();
    }

    void MainFrame::OpenFileEvent(wxCommandEvent& e)
    {
        Open();
    }

    void MainFrame::SaveFileEvent(wxCommandEvent& e)
    {
        Save();
    }

    void MainFrame::SaveFileAsEvent(wxCommandEvent& e)
    {
        SaveAs();
    }

    void MainFrame::CloseEvent(wxCommandEvent& e)
    {
        CloseWorld();
    }

    void MainFrame::ExitEvent(wxCommandEvent& e)
    {
        Exit();
    }

    void MainFrame::CutEvent(wxCommandEvent& e)
    {
        Cut();
    }

    void MainFrame::CopyEvent(wxCommandEvent& e)
    {
        Copy();
    }

    void MainFrame::PasteEvent(wxCommandEvent& e)
    {
        Paste();
    }

    void MainFrame::UndoEvent(wxCommandEvent& e)
    {
        Undo();
    }

    void MainFrame::RedoEvent(wxCommandEvent& e)
    {
        Redo();
    }

    void MainFrame::EditWorldStartEvent(wxCommandEvent& e)
    {}

    void MainFrame::SettingsEvent(wxCommandEvent& e)
    {
        Settings();
    }

    void MainFrame::ViewTerrainEvent(wxCommandEvent& e)
    {
        settings.viewTerrain = viewTerrainMenuItem->IsChecked();
        ChangeSettings(settings);
    }

    void MainFrame::ViewEntityBoundaryEvent(wxCommandEvent& e)
    {
        settings.viewEntityBoundary = viewEntityBoundaryMenuItem->IsChecked();
        ChangeSettings(settings);
    }

    void MainFrame::ViewEntitiesEvent(wxCommandEvent& e)
    {
        settings.viewEntities = viewEntitiesMenuItem->IsChecked();
        ChangeSettings(settings);
    }

    void MainFrame::CreateFieldEvent(wxCommandEvent& e)
    {
        CreateField();
    }

    void MainFrame::DestroyFieldEvent(wxCommandEvent& e)
    {
        DestroyField();
    }

    void MainFrame::NewToolEvent(wxCommandEvent& e)
    {
        New();
    }

    void MainFrame::OpenToolEvent(wxCommandEvent& e)
    {
        Open();
    }

    void MainFrame::SaveToolEvent(wxCommandEvent& e)
    {
        Save();
    }

    void MainFrame::SaveAsToolEvent(wxCommandEvent& e)
    {
        SaveAs();
    }

    void MainFrame::CloseWorldToolEvent(wxCommandEvent& e)
    {
        CloseWorld();
    }

    void MainFrame::ExitToolEvent(wxCommandEvent& e)
    {
        Exit();
    }

    void MainFrame::CutToolEvent(wxCommandEvent& e)
    {
        Cut();
    }

    void MainFrame::CopyToolEvent(wxCommandEvent& e)
    {
        Copy();
    }

    void MainFrame::PasteToolEvent(wxCommandEvent& e)
    {
        Paste();
    }

    void MainFrame::UndoToolEvent(wxCommandEvent& e)
    {
        Undo();
    }

    void MainFrame::RedoToolEvent(wxCommandEvent& e)
    {
        Redo();
    }

    void MainFrame::AssetsToolEvent(wxCommandEvent& e)
    {
        AssetMode();
    }

    void MainFrame::TerrainToolEvent(wxCommandEvent& e)
    {
        TerrainMode();
    }

    void MainFrame::EntityBoundaryToolEvent(wxCommandEvent& e)
    {
        EntityBoundaryMode();
    }

    void MainFrame::EntitiesToolEvent(wxCommandEvent& e)
    {
        EntityMode();
    }

    void MainFrame::SelectToolEvent(wxCommandEvent& e)
    {
        SelectTool();
    }

    void MainFrame::PaintToolEvent(wxCommandEvent& e)
    {
        PaintTool();
    }

    void MainFrame::MoveToolEvent(wxCommandEvent& e)
    {
        MoveTool();
    }

    void MainFrame::BuildToolEvent(wxCommandEvent& e)
    {
        Build();
    }

    void MainFrame::PlayToolEvent(wxCommandEvent& e)
    {
        Play();
    }

    void MainFrame::FieldSelectedEvent()
    {
        ChangeField(selectedField.GetValue());
    }

    void MainFrame::ViewportMouseMovedEvent(Atmos::Spatial::Point2D point)
    {
        const auto gridPosition = Atmos::Spatial::Grid::ToPoint(point);

        const auto statusText =
            "("
            + Atmos::ToString(gridPosition.x)
            + ", "
            + Atmos::ToString(gridPosition.y)
            + ")";
        SetStatusText(statusText, 1);
    }

    void MainFrame::ActiveChangedEvent(wxActivateEvent& e)
    {
        if (stack)
        {
            if (e.GetActive())
                Activate();
            else
                Deactivate();
        }

        e.Skip();
    }

    void MainFrame::IdleEvent(wxIdleEvent& e)
    {
        Idle();
        e.RequestMore();
        e.Skip();
    }
}