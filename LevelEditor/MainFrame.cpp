
#include "MainFrame.h"
#include <wx/artprov.h>
#include <wx/textdlg.h>
#include <wx/toolbar.h>
#include <wx/menuitem.h>
#include <wx/menu.h>
#include <wx/filedlg.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include "CurrentWorld.h"
#include "StringButtonProperty.h"

#include "Viewport.h"

#include "TileViewManager.h"
#include "EntityViewManager.h"
#include "InternalShaders.h"

#include "CommandStack.h"

#include "WorldStartDialog.h"
#include "SettingsDialog.h"

#include "ChildProcesses.h"

#include "DataViewStateTiles.h"
#include "DataViewStateEntities.h"
#include "Application.h"

#include "Settings.h"
#include "SettingsScribe.h"

#include <Atmos/String.h>
#include <Atmos/EntityNameSystem.h>

namespace Creation
{
    static MainFrame *mainFrame = nullptr;

    enum
    {
        // Menu bar
        NEW_FILE,
        OPEN_FILE,
        SAVE_FILE,
        SAVE_FILE_AS,
        CLOSE_FIELD,

        // Edit menu
        EDIT_CUT,
        EDIT_COPY,
        EDIT_PASTE,
        EDIT_UNDO,
        EDIT_REDO,
        EDIT_WORLD_START,
        EDIT_SETTINGS,

        // View menu
        VIEW_EMPTY_TILES,
        VIEW_EMPTY_ENTITIES,

        // Resource menu
        RESOURCE_IMAGE,
        RESOURCE_SOUND,
        RESOURCE_SCRIPT_MODULE,

        // Game object menu
        GAME_OBJECT_ENTITY_TEMPLATE,
        GAME_OBJECT_CHARACTER_CLASS,
        GAME_OBJECT_STATUS_EFFECT,
        GAME_OBJECT_ITEM,
        GAME_OBJECT_SPELL,

        // Add menu
        ADD_FIELD,

        // Toolbar
        NEW_FILE_TOOL,
        OPEN_FILE_TOOL,
        SAVE_FILE_TOOL,
        SAVE_FILE_AS_TOOL,
        CLOSE_WORLD_TOOL,
        EXIT_TOOL,

        CUT_TOOL,
        COPY_TOOL,
        PASTE_TOOL,

        UNDO_TOOL,
        REDO_TOOL,

        // Regular tools
        ASSETS_TOOL,
        REGISTRIES_TOOL,
        GAME_DATA_TOOL,

        TILES_TOOL,
        ENTITIES_TOOL,

        BUILD_TOOL,
        PLAY_TOOL,
        // End toolbar
    };

    template<class Ret, class... Args, class... PassArgs>
    void DoOnTools(wxToolBar &toolbar, Ret(wxToolBar::*func)(Args...), PassArgs && ... args)
    {
        (toolbar.*func)(ASSETS_TOOL, std::forward<PassArgs>(args)...);
        (toolbar.*func)(REGISTRIES_TOOL, std::forward<PassArgs>(args)...);
        (toolbar.*func)(GAME_DATA_TOOL, std::forward<PassArgs>(args)...);
        (toolbar.*func)(TILES_TOOL, std::forward<PassArgs>(args)...);
        (toolbar.*func)(ENTITIES_TOOL, std::forward<PassArgs>(args)...);
    }

    void MainFrame::OnNewFile(wxCommandEvent &e)
    {
        New();
    }

    void MainFrame::OnOpenFile(wxCommandEvent &e)
    {
        Open();
    }

    void MainFrame::OnSaveFile(wxCommandEvent &e)
    {
        Save();
    }

    void MainFrame::OnSaveFileAs(wxCommandEvent &e)
    {
        SaveAs();
    }

    void MainFrame::OnClose(wxCommandEvent &e)
    {
        CloseWorld();
    }

    void MainFrame::OnExit(wxCommandEvent &e)
    {
        Exit();
    }

    void MainFrame::OnCut(wxCommandEvent &e)
    {
        Cut();
    }

    void MainFrame::OnCopy(wxCommandEvent &e)
    {
        Copy();
    }

    void MainFrame::OnPaste(wxCommandEvent &e)
    {
        Paste();
    }

    void MainFrame::OnUndo(wxCommandEvent &e)
    {
        Command::Stack::Undo(1);
    }

    void MainFrame::OnRedo(wxCommandEvent &e)
    {
        Command::Stack::Redo(1);
    }

    void MainFrame::OnEditWorldStart(wxCommandEvent &e)
    {
        WorldStartDialog dialog(CurrentWorld::GetWorldStartField(), this, wxID_ANY);
        dialog.ShowModal();

        CurrentWorld::SetWorldStart(dialog.GetFieldID());
    }

    void MainFrame::OnSettings(wxCommandEvent &e)
    {
        SettingsDialog dialog(this, "Settings");
        if (dialog.ShowModal() == wxID_CANCEL)
            return;

        Settings::SetWorldPath(dialog.GetWorldPath());
        Settings::SetBuildPath(dialog.GetBuildPath());
        Settings::SetAudioAssetPath(dialog.GetAudioAssetPath());
        Settings::SetImageAssetPath(dialog.GetImageAssetPath());
        Settings::SetScriptAssetPath(dialog.GetScriptAssetPath());
        Settings::SetShaderAssetPath(dialog.GetShaderAssetPath());

        SettingsScribeOut scribeOut(Atmos::Environment::GetFileSystem()->GetExePath().Append("Settings.txt"));
        scribeOut.Flush();
        scribeOut.Save();
    }

    void MainFrame::OnViewEmptyTiles(wxCommandEvent &e)
    {
        TileViewManager::ToggleView();
    }

    void MainFrame::OnViewEmptyEntities(wxCommandEvent &e)
    {
        EntityViewManager::ToggleView();
    }

    void MainFrame::OnAddField(wxCommandEvent &e)
    {
        wxTextEntryDialog dialog(this, "Enter in field ID.");
        wxTextValidator validator(wxFILTER_DIGITS | wxFILTER_EMPTY | wxFILTER_EXCLUDE_LIST);
        validator.SetExcludes(fieldIDStrings);
        dialog.SetTextValidator(validator);
        if (dialog.ShowModal() != wxID_OK)
            return;

        auto id = Atmos::FromString<::Atmos::FieldID>(dialog.GetValue().ToStdString());
        CurrentWorld::Add(id);
        SelectField(id);
        OnNewField(id);
    }

    void MainFrame::OnNewTool(wxCommandEvent &e)
    {
        New();
    }

    void MainFrame::OnOpenTool(wxCommandEvent &e)
    {
        Open();
    }

    void MainFrame::OnSaveTool(wxCommandEvent &e)
    {
        Save();
    }

    void MainFrame::OnSaveAsTool(wxCommandEvent &e)
    {
        SaveAs();
    }

    void MainFrame::OnCloseWorldTool(wxCommandEvent &e)
    {
        CloseWorld();
    }

    void MainFrame::OnExitTool(wxCommandEvent &e)
    {
        Exit();
    }

    void MainFrame::OnCutTool(wxCommandEvent &e)
    {
        Cut();
    }

    void MainFrame::OnCopyTool(wxCommandEvent &e)
    {
        Copy();
    }

    void MainFrame::OnPasteTool(wxCommandEvent &e)
    {
        Paste();
    }

    void MainFrame::OnUndoTool(wxCommandEvent &e)
    {
        Command::Stack::Undo();
    }

    void MainFrame::OnRedoTool(wxCommandEvent &e)
    {
        Command::Stack::Redo();
    }

    void MainFrame::OnAssetsTool(wxCommandEvent &e)
    {
        OnTool(Viewport::Mode::NONE, DataViewState::ASSETS, ASSETS_TOOL);
    }

    void MainFrame::OnRegistriesTool(wxCommandEvent &e)
    {
        OnTool(Viewport::Mode::NONE, DataViewState::REGISTRIES, REGISTRIES_TOOL);
    }

    void MainFrame::OnGameDataTool(wxCommandEvent &e)
    {
        OnTool(Viewport::Mode::NONE, DataViewState::GAME_DATA, GAME_DATA_TOOL);
    }

    void MainFrame::OnTilesTool(wxCommandEvent &e)
    {
        OnTool(Viewport::Mode::TILES, DataViewState::TILES, TILES_TOOL);
    }

    void MainFrame::OnEntitiesTool(wxCommandEvent &e)
    {
        OnTool(Viewport::Mode::ENTITIES, DataViewState::ENTITIES, ENTITIES_TOOL);
    }

    void MainFrame::OnBuildTool(wxCommandEvent &e)
    {
        CurrentWorld::Build();
    }

    void MainFrame::OnPlayTool(wxCommandEvent &e)
    {
        CurrentWorld::StartWorld();
    }

    void MainFrame::OnFieldChanged(::Atmos::FieldID value)
    {
        if (CurrentWorld::GetCurrentField()->GetID() == value)
            return;

        if (!CurrentWorld::IsFieldHere(value))
        {
            SetStatusText("The field requested does not exist; ignoring.");
            fieldChange.ChangeValue(CurrentWorld::GetCurrentField()->GetID());
            return;
        }

        SelectField(value);
    }

    void MainFrame::OnIdle(wxIdleEvent &e)
    {
        ChildProcesses::Work();
        e.RequestMore();
        e.Skip();
    }
}

wxBEGIN_EVENT_TABLE(Creation::MainFrame, wxFrame)
    EVT_MENU(NEW_FILE, Creation::MainFrame::OnNewFile)
    EVT_MENU(OPEN_FILE, Creation::MainFrame::OnOpenFile)
    EVT_MENU(SAVE_FILE, Creation::MainFrame::OnSaveFile)
    EVT_MENU(SAVE_FILE_AS, Creation::MainFrame::OnSaveFileAs)
    EVT_MENU(CLOSE_FIELD, Creation::MainFrame::OnClose)
    EVT_MENU(wxID_EXIT, Creation::MainFrame::OnExit)

    EVT_MENU(EDIT_CUT, Creation::MainFrame::OnCut)
    EVT_MENU(EDIT_COPY, Creation::MainFrame::OnCopy)
    EVT_MENU(EDIT_PASTE, Creation::MainFrame::OnPaste)
    EVT_MENU(EDIT_UNDO, Creation::MainFrame::OnUndo)
    EVT_MENU(EDIT_REDO, Creation::MainFrame::OnRedo)
    EVT_MENU(EDIT_WORLD_START, Creation::MainFrame::OnEditWorldStart)
    EVT_MENU(EDIT_SETTINGS, Creation::MainFrame::OnSettings)

    EVT_MENU(VIEW_EMPTY_TILES, Creation::MainFrame::OnViewEmptyTiles)
    EVT_MENU(VIEW_EMPTY_ENTITIES, Creation::MainFrame::OnViewEmptyEntities)

    EVT_MENU(ADD_FIELD, Creation::MainFrame::OnAddField)

    EVT_TOOL(NEW_FILE_TOOL, Creation::MainFrame::OnNewTool)
    EVT_TOOL(OPEN_FILE_TOOL, Creation::MainFrame::OnOpenTool)
    EVT_TOOL(SAVE_FILE_TOOL, Creation::MainFrame::OnSaveTool)
    EVT_TOOL(SAVE_FILE_AS_TOOL, Creation::MainFrame::OnSaveAsTool)
    EVT_TOOL(CLOSE_WORLD_TOOL, Creation::MainFrame::OnCloseWorldTool)
    EVT_TOOL(EXIT_TOOL, Creation::MainFrame::OnExitTool)
    EVT_TOOL(CUT_TOOL, Creation::MainFrame::OnCutTool)
    EVT_TOOL(COPY_TOOL, Creation::MainFrame::OnCopyTool)
    EVT_TOOL(PASTE_TOOL, Creation::MainFrame::OnPasteTool)
    EVT_TOOL(UNDO_TOOL, Creation::MainFrame::OnUndoTool)
    EVT_TOOL(REDO_TOOL, Creation::MainFrame::OnRedoTool)
    EVT_TOOL(ASSETS_TOOL, Creation::MainFrame::OnAssetsTool)
    EVT_TOOL(REGISTRIES_TOOL, Creation::MainFrame::OnRegistriesTool)
    EVT_TOOL(GAME_DATA_TOOL, Creation::MainFrame::OnGameDataTool)
    EVT_TOOL(TILES_TOOL, Creation::MainFrame::OnTilesTool)
    EVT_TOOL(ENTITIES_TOOL, Creation::MainFrame::OnEntitiesTool)
    EVT_TOOL(BUILD_TOOL, Creation::MainFrame::OnBuildTool)
    EVT_TOOL(PLAY_TOOL, Creation::MainFrame::OnPlayTool)

    EVT_IDLE(Creation::MainFrame::OnIdle)
wxEND_EVENT_TABLE()

namespace Creation
{
    void MainFrame::New()
    {
        String path(GetBuildFileDialogPath("Use"));
        if (path == "")
            return;

        ResetEnvironment();
        CurrentWorld::SetFilePath(path);
        for (auto &loop : toolsATFE)
            GetToolBar()->ToggleTool(loop, false);
        CurrentWorld::Add(0);

        if(CurrentWorld::Select(0))
            EnableViewport();

        dataView->CreateBreakdownsFromScratch();

        SetStatusText("New.");
    }

    void MainFrame::Open()
    {
        wxFileDialog dialog(this, _("Open build file"), "", "", "build files (*.build)|*.build", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        
        {
            auto path = Settings::GetBuildPath().GetValue();
            dialog.SetDirectory(path);
            if (dialog.ShowModal() == wxID_CANCEL)
                return;
        }

        ResetEnvironment();
        for (auto &loop : toolsATFE)
            GetToolBar()->ToggleTool(loop, false);
        CurrentWorld::Load(dialog.GetPath().ToStdString());

        EnableViewport();
        dataView->CreateBreakdownsFromScratch();

        SetStatusText("Loaded.");
    }

    void MainFrame::SaveAs()
    {
        SaveBuildFileDialog();
    }

    void MainFrame::CloseWorld()
    {
        ResetEnvironment();

        DisableViewport();

        SetStatusText("Closed.");
    }

    void MainFrame::Exit()
    {
        wxFrame::Close(true);
    }

    void MainFrame::Cut()
    {
        Viewport::viewport->Cut();
    }

    void MainFrame::Copy()
    {
        Viewport::viewport->Copy();
    }

    void MainFrame::Paste()
    {
        Viewport::viewport->Paste();
    }

    void MainFrame::OnNewField(Atmos::FieldID id)
    {
        fieldIDStrings.Add(std::to_string(id));
        fieldChange.ChangeValue(id);
    }

    void MainFrame::OnRemoveField(Atmos::FieldID id)
    {
        fieldIDStrings.Remove(std::to_string(id));
    }

    void MainFrame::SelectField(Atmos::FieldID id)
    {
        dataView->GetSpecificState<DataViewStateTiles>()->DestroyBreakdowns();
        dataView->GetSpecificState<DataViewStateEntities>()->DestroyBreakdowns();
        CurrentWorld::Select(id);
        dataView->GetSpecificState<DataViewStateTiles>()->CreateBreakdownsFromScratch();
        dataView->GetSpecificState<DataViewStateEntities>()->CreateBreakdownsFromScratch();
    }

    void MainFrame::OnTool(Viewport::Mode set, DataViewState::Type dataViewSet, int idToggled)
    {
        bool toolState = GetToolBar()->GetToolState(idToggled);
        ToggleTools(false);
        GetToolBar()->ToggleTool(idToggled, toolState);
        toolState = GetToolBar()->GetToolState(idToggled);

        // If the data view's state is not selected first, then it will dictate logic to the viewport and the viewport will be in the incorrect state
        if (toolState)
            dataView->SelectState(dataViewSet, false);
        else
            dataView->SelectState(DataView::StateType::NONE, false);

        if (set == Viewport::Mode::NONE || !toolState || NoToolsToggled())
            viewport->SetMode(Viewport::Mode::NONE);
        else
            viewport->SetMode(set);
    }

    void MainFrame::ToggleTools(bool toggle)
    {
        DoOnTools(*GetToolBar(), &wxToolBar::ToggleTool, toggle);
    }

    bool MainFrame::NoToolsToggled() const
    {
        auto toolbar = GetToolBar();
        auto check = [&](int id)
        {
            return !toolbar->GetToolState(id);
        };

        return check(ASSETS_TOOL) && check(REGISTRIES_TOOL) && check(GAME_DATA_TOOL) && check(TILES_TOOL) && check(ENTITIES_TOOL);
    }

    void MainFrame::EnableTools(bool enable)
    {
        DoOnTools(*GetToolBar(), &wxToolBar::EnableTool, enable);
    }

    void MainFrame::EnableViewport()
    {
        viewport->Show();
        viewport->Enable();
        viewport->Activate();

        for (auto &loop : menuItemsATFE)
            loop->Enable(true);
        for (auto &loop : toolsATFE)
            GetToolBar()->EnableTool(loop, true);

        SetTitle("Creation Editor - " + CurrentWorld::GetFilePath().GetFileName().GetValue());
        Refresh();
    }

    void MainFrame::DisableViewport()
    {
        viewport->Deactivate();
        viewport->Disable();

        for (auto &loop : menuItemsATFE)
            loop->Enable(false);
        for (auto &loop : toolsATFE)
        {
            GetToolBar()->ToggleTool(loop, false);
            GetToolBar()->EnableTool(loop, false);
        }

        SetTitle("Creation Editor");
        SetStatusText("", 1);
        Refresh();
    }

    bool MainFrame::SaveBuildFileDialog()
    {
        String path(GetBuildFileDialogPath("Save"));
        if (path == "")
            return false;

        CurrentWorld::Save(path);
        SetTitle("Creation Editor - " + CurrentWorld::GetFilePath().GetFileName().GetValue());
        return true;
    }

    ::Atmos::FilePath MainFrame::GetBuildFileDialogPath(const String &verb)
    {
        wxFileDialog dialog(this, _(verb + " build file"), "", "", "build files (*.build)|*.build", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        dialog.SetDirectory(Settings::GetBuildPath().GetValue());
        if (dialog.ShowModal() == wxID_CANCEL)
            return "";

        return dialog.GetPath().ToStdString();
    }

    void MainFrame::ResetEnvironment()
    {
        CurrentWorld::Clear();
        Command::Stack::Clear();
        dataView->DestroyBreakdowns();
        dataView->SelectState(DataView::StateType::NONE, true);
        DisableViewport();
    }

    MainFrame::MainFrame(const wxPoint &pos, const wxSize &size) : wxFrame(nullptr, wxID_ANY, "", pos, size), viewport(nullptr), viewPanel(nullptr)
    {
        mainFrame = this;

        // Register StringButtonProperty
        {
            wxPGEditor *stringButtonProperty = new StringButtonProperty();
            wxPropertyGrid::RegisterEditorClass(stringButtonProperty);
        }

        // Do this here so it can subscribe to Atmos::ErrorHandler's onLogged event
        outputView.reset(new OutputView(this));

        aui = new wxAuiManager(this, 0);

        wxImage::AddHandler(new wxPNGHandler);

        // Menu
        auto menuBar = new wxMenuBar();
        SetMenuBar(menuBar);

        // File menu
        {
            auto menu = new wxMenu();
            menu->Append(NEW_FILE, "New");
            menu->Append(OPEN_FILE, "Open");
            menuItemsATFE.push_back(menu->Append(SAVE_FILE, "Save"));
            menuItemsATFE.push_back(menu->Append(SAVE_FILE_AS, "Save As"));
            menuItemsATFE.push_back(menu->Append(CLOSE_FIELD, "Close"));
            menu->AppendSeparator();
            menu->Append(wxID_EXIT);

            menuBar->Append(menu, "File");
        }

        // Edit menu
        {
            auto menu = new wxMenu();
            menuItemsATFE.push_back(menu->Append(EDIT_CUT, "Cut\tCtrl-X"));
            menuItemsATFE.push_back(menu->Append(EDIT_COPY, "Copy\tCtrl-C"));
            menuItemsATFE.push_back(menu->Append(EDIT_PASTE, "Paste\tCtrl-V"));
            menuItemsATFE.push_back(menu->Append(EDIT_UNDO, "Undo\tCtrl-Z"));
            menuItemsATFE.push_back(menu->Append(EDIT_REDO, "Redo\tCtrl-Y"));
            menu->AppendSeparator();
            menuItemsATFE.push_back(menu->Append(EDIT_WORLD_START, "World Start"));
            menu->AppendSeparator();
            menu->Append(EDIT_SETTINGS, "Settings");

            menuBar->Append(menu, "Edit");
        }

        // View menu
        {
            auto menu = new wxMenu();
            menu->Append(VIEW_EMPTY_TILES, "Empty Tiles");
            menu->Append(VIEW_EMPTY_ENTITIES, "Empty Entities");

            menuBar->Append(menu, "View");
        }

        // Add menu
        {
            auto menu = new wxMenu();
            menuItemsATFE.push_back(menu->Append(ADD_FIELD, "Field\tCtrl-F"));

            menuBar->Append(menu, "Add");
        }

        // Create toolbar
        {
            wxToolBar *toolbar = CreateToolBar(wxTB_HORIZONTAL | wxTB_FLAT);

            auto fieldBitmapButtonCreator = [&](bool addToATFE, size_t id, wxBitmap &&bitmap, wxString &&help)
            {
                toolbar->AddTool(id, "", bitmap, help);
                if (addToATFE)
                    toolsATFE.push_back(id);
            };

            fieldBitmapButtonCreator(false, NEW_FILE_TOOL, wxArtProvider::GetBitmap(wxART_NEW, wxART_TOOLBAR), "New");
            fieldBitmapButtonCreator(false, OPEN_FILE_TOOL, wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_TOOLBAR), "Open");
            fieldBitmapButtonCreator(true, SAVE_FILE_TOOL, wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_TOOLBAR), "Save");
            fieldBitmapButtonCreator(true, SAVE_FILE_AS_TOOL, wxArtProvider::GetBitmap(wxART_FILE_SAVE_AS, wxART_TOOLBAR), "Save As");
            fieldBitmapButtonCreator(true, CLOSE_WORLD_TOOL, wxArtProvider::GetBitmap(wxART_CLOSE, wxART_TOOLBAR), "Close");
            fieldBitmapButtonCreator(false, EXIT_TOOL, wxArtProvider::GetBitmap(wxART_QUIT, wxART_TOOLBAR), "Exit");
            toolbar->AddSeparator();
            fieldBitmapButtonCreator(true, CUT_TOOL, wxArtProvider::GetBitmap(wxART_CUT, wxART_TOOLBAR), "Cut");
            fieldBitmapButtonCreator(true, COPY_TOOL, wxArtProvider::GetBitmap(wxART_COPY, wxART_TOOLBAR), "Copy");
            fieldBitmapButtonCreator(true, PASTE_TOOL, wxArtProvider::GetBitmap(wxART_PASTE, wxART_TOOLBAR), "Paste");
            fieldBitmapButtonCreator(true, UNDO_TOOL, wxArtProvider::GetBitmap(wxART_UNDO, wxART_TOOLBAR), "Undo");
            fieldBitmapButtonCreator(true, REDO_TOOL, wxArtProvider::GetBitmap(wxART_REDO, wxART_TOOLBAR), "Redo");
            toolbar->AddSeparator();
            toolbar->AddCheckTool(ASSETS_TOOL, "Assets", wxBitmap(wxT("Images\\AssetsTool.png"), wxBITMAP_TYPE_PNG), wxNullBitmap, wxT("Assets"));
            toolsATFE.push_back(ASSETS_TOOL);
            toolbar->AddCheckTool(REGISTRIES_TOOL, "Registries", wxBitmap(wxT("Images\\RegistriesTool.png"), wxBITMAP_TYPE_PNG), wxNullBitmap, wxT("Registries"));
            toolsATFE.push_back(REGISTRIES_TOOL);
            toolbar->AddCheckTool(GAME_DATA_TOOL, "Game Data", wxBitmap(wxT("Images\\GameDataTool.png"), wxBITMAP_TYPE_PNG), wxNullBitmap, wxT("GameData"));
            toolsATFE.push_back(GAME_DATA_TOOL);
            toolbar->AddSeparator();
            toolbar->AddCheckTool(TILES_TOOL, "Tiles", wxBitmap(wxT("Images\\TilesTool.png"), wxBITMAP_TYPE_PNG), wxNullBitmap, wxT("Tiles"));
            toolsATFE.push_back(TILES_TOOL);
            toolbar->AddCheckTool(ENTITIES_TOOL, "Entities", wxBitmap(wxT("Images\\EntitiesTool.png"), wxBITMAP_TYPE_PNG), wxNullBitmap, wxT("Entities"));
            toolsATFE.push_back(ENTITIES_TOOL);
            toolbar->AddSeparator();
            fieldBitmapButtonCreator(true, BUILD_TOOL, wxBitmap(wxT("Images\\BuildTool.png"), wxBITMAP_TYPE_PNG), "Build");
            fieldBitmapButtonCreator(true, PLAY_TOOL, wxBitmap(wxT("Images\\PlayTool.png"), wxBITMAP_TYPE_PNG), "Play");
            toolbar->Realize();
        }

        // Status bar
        SetStatusBar(new wxStatusBar(this, wxID_ANY, 0));
        GetStatusBar()->SetFieldsCount(2);

        // Needs panel
        wxPanel *mainPanel = new wxPanel(this);
        mainPanel->SetSizer(new wxBoxSizer(wxVERTICAL));

        // Left panel
        viewPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(250, 45), wxNO_BORDER | wxTAB_TRAVERSAL);
        auto fieldChangeTextCtrl = fieldChange.InitWrapped(viewPanel);
        fieldChange.SetOnSetFunction(function::CreateFunction(&MainFrame::OnFieldChanged, *this));
        auto viewZTextCtrl = viewZ.InitWrapped(viewPanel);

        auto viewPanelSizer = new wxBoxSizer(wxVERTICAL);
        viewPanel->SetSizer(viewPanelSizer);

        // Field/View Z sizer
        {
            auto fieldViewZSizer = new wxBoxSizer(wxHORIZONTAL);
            viewPanelSizer->Add(fieldViewZSizer, 0, wxEXPAND);

            auto fieldSizer = new wxBoxSizer(wxVERTICAL);
            fieldViewZSizer->Add(fieldSizer, 1, wxEXPAND);
            fieldSizer->Add(new wxStaticText(viewPanel, wxID_ANY, "Field:"), 0, wxALIGN_CENTER);
            fieldSizer->Add(fieldChangeTextCtrl, 0, wxEXPAND);

            auto zSizer = new wxBoxSizer(wxVERTICAL);
            fieldViewZSizer->Add(zSizer, 1, wxEXPAND);
            zSizer->Add(new wxStaticText(viewPanel, wxID_ANY, "View Z:"), 0, wxALIGN_CENTER);
            zSizer->Add(viewZTextCtrl, 0, wxEXPAND);
        }

        mainPanel->GetSizer()->Add(viewPanel, 0, wxEXPAND);

        // Data View
        dataView.reset(new DataView(this, mainPanel));
        // Main pane
        wxAuiPaneInfo paneInfo = wxAuiPaneInfo();
        paneInfo.Left();
        paneInfo.Caption("Main");
        paneInfo.CaptionVisible(true);
        paneInfo.PaneBorder(false);
        paneInfo.Gripper(false);
        paneInfo.GripperTop(false);
        paneInfo.Floatable(false);
        paneInfo.CloseButton(false);
        paneInfo.Movable(false);
        paneInfo.Layer(2);
        paneInfo.BestSize(250, -1);
        aui->AddPane(mainPanel, paneInfo);
        // Editor pane
        paneInfo = wxAuiPaneInfo();
        paneInfo.Left();
        paneInfo.Caption("Editor");
        paneInfo.CaptionVisible(true);
        paneInfo.PaneBorder(false);
        paneInfo.Gripper(false);
        paneInfo.GripperTop(false);
        paneInfo.Floatable(false);
        paneInfo.CloseButton(false);
        paneInfo.Movable(false);
        paneInfo.Layer(1);
        aui->AddPane(dataView->EditorPanel(), paneInfo);

        // Viewport
        viewport = new Viewport::Viewport(this, wxID_ANY);
        // Viewport pane
        paneInfo = wxAuiPaneInfo();
        paneInfo.Center();
        paneInfo.Caption("Viewport");
        paneInfo.CaptionVisible(true);
        paneInfo.PaneBorder(false);
        paneInfo.Gripper(false);
        paneInfo.GripperTop(false);
        paneInfo.Floatable(false);
        paneInfo.CloseButton(false);
        paneInfo.Movable(false);
        aui->AddPane(viewport, paneInfo);

        // Error view pane
        paneInfo = wxAuiPaneInfo();
        paneInfo.Bottom();
        paneInfo.Caption("Output View");
        paneInfo.CaptionVisible(true);
        paneInfo.PaneBorder(false);
        paneInfo.Gripper(false);
        paneInfo.GripperTop(false);
        paneInfo.Floatable(false);
        paneInfo.CloseButton(false);
        paneInfo.Movable(false);
        paneInfo.Layer(0);
        paneInfo.BestSize(-1, 150);
        aui->AddPane(outputView->GetListbox(), paneInfo);

        DisableViewport();

        Maximize();
        Centre();

        wxIdleEvent::SetMode(wxIDLE_PROCESS_SPECIFIED);
        this->SetExtraStyle(wxWS_EX_PROCESS_IDLE);

        aui->Update();

        auto fileSystem = Atmos::Environment::GetFileSystem();
        SettingsScribeIn scribeIn(fileSystem->GetExePath().Append("Settings.txt"));
        scribeIn.Load();
    }

    MainFrame::~MainFrame()
    {
        aui->UnInit();
    }

    Atmos::GridPosition::ValueT MainFrame::GetZView() const
    {
        return viewZ.GetValue();
    }

    DataView* MainFrame::GetDataView()
    {
        return dataView.get();
    }

    void MainFrame::OutputMessage(const String &message)
    {
        outputView->OutputMessage(message, true);
    }

    bool MainFrame::Save()
    {
        if (!CurrentWorld::IsFilePathValid())
            return SaveBuildFileDialog();

        CurrentWorld::Save();
        SetStatusText("Saved.");
        return true;
    }

    MainFrame* GetMainFrame()
    {
        return mainFrame;
    }
}