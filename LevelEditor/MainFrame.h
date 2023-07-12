#pragma once

#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/aui/framemanager.h>
#include "AutoTextControl.h"

#include <vector>

#include "ViewportMode.h"
#include "DataView.h"
#include "OutputView.h"

#include "String.h"

#include <Atmos/FilePath.h>
#include <Atmos/GridPosition.h>
#include <Atmos/FieldID.h>

namespace Creation
{
    namespace Viewport
    {
        class Viewport;
    }

    class MainFrame : public wxFrame
    {
    private:
        // This window events
        // File menu
        void OnNewFile(wxCommandEvent &e);
        void OnOpenFile(wxCommandEvent &e);
        void OnSaveFile(wxCommandEvent &e);
        void OnSaveFileAs(wxCommandEvent &e);
        void OnClose(wxCommandEvent &e);
        void OnExit(wxCommandEvent &e);

        // Edit menu
        void OnCut(wxCommandEvent &e);
        void OnCopy(wxCommandEvent &e);
        void OnPaste(wxCommandEvent &e);
        void OnUndo(wxCommandEvent &e);
        void OnRedo(wxCommandEvent &e);
        void OnEditWorldStart(wxCommandEvent &e);
        void OnSettings(wxCommandEvent &e);

        // View menu
        void OnViewEmptyTiles(wxCommandEvent &e);
        void OnViewEmptyEntities(wxCommandEvent &e);

        // Add menu
        void OnAddField(wxCommandEvent &e);

        // Regular tools
        void OnNewTool(wxCommandEvent &e);
        void OnOpenTool(wxCommandEvent &e);
        void OnSaveTool(wxCommandEvent &e);
        void OnSaveAsTool(wxCommandEvent &e);
        void OnCloseWorldTool(wxCommandEvent &e);
        void OnExitTool(wxCommandEvent &e);

        void OnCutTool(wxCommandEvent &e);
        void OnCopyTool(wxCommandEvent &e);
        void OnPasteTool(wxCommandEvent &e);

        void OnUndoTool(wxCommandEvent &e);
        void OnRedoTool(wxCommandEvent &e);

        // Game-specific tools
        void OnAssetsTool(wxCommandEvent &e);
        void OnRegistriesTool(wxCommandEvent &e);
        void OnGameDataTool(wxCommandEvent &e);
        void OnTilesTool(wxCommandEvent &e);
        void OnEntitiesTool(wxCommandEvent &e);
        void OnBuildTool(wxCommandEvent &e);
        void OnPlayTool(wxCommandEvent &e);

        // View panel
        void OnFieldChanged(::Atmos::FieldID value);

        void OnIdle(wxIdleEvent &e);
        wxDECLARE_EVENT_TABLE();
    private:
        wxAuiManager *aui;

        wxArrayString fieldIDStrings;

        Viewport::Viewport *viewport;
        std::unique_ptr<DataView> dataView;

        wxPanel *viewPanel;
        AutoTextControl<::Atmos::FieldID> fieldChange;
        AutoTextControl<::Atmos::GridPosition::ValueT, 0> viewZ;

        std::unique_ptr<OutputView> outputView;

        // ATFE = AttachedToFieldExisting
        std::vector<wxMenuItem*> menuItemsATFE;
        // ATFE = AttachedToFieldExisting
        std::vector<int> toolsATFE;

        void New();
        void Open();
        void SaveAs();
        void CloseWorld();
        void Exit();

        void Cut();
        void Copy();
        void Paste();

        void OnNewField(Atmos::FieldID id);
        void OnRemoveField(Atmos::FieldID id);
        void SelectField(Atmos::FieldID id);

        void OnTool(Viewport::Mode set, DataViewState::Type dataViewSet, int idToggled);
        void ToggleTools(bool toggle);
        bool NoToolsToggled() const;
        void EnableTools(bool enable);

        void EnableViewport();
        void DisableViewport();

        // Returns if the dialog suceeded in saving
        bool SaveBuildFileDialog();
        // Doesn't actually save anything. Opens a dialog and returns the string that is the location it should be saved in
        // "" if invalid
        ::Atmos::FilePath GetBuildFileDialogPath(const String &verb);
        void ResetEnvironment();
    public:
        MainFrame(const wxPoint &pos, const wxSize &size);
        ~MainFrame();

        Atmos::GridPosition::ValueT GetZView() const;

        DataView* GetDataView();
        void OutputMessage(const String &message);

        // Returns if the save succeeded
        bool Save();
    };

    MainFrame* GetMainFrame();
}