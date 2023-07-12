#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include <type_traits>
#include "DataViewState.h"

#include "wxTreeItem.h"
#include <wx/scrolwin.h>

class wxTreeCtrl;
class wxTreeEvent;
class wxStaticText;
class wxButton;
class wxPanel;
class wxPropertyGrid;
class wxPropertyGridEvent;

namespace Creation
{
    class DataBreakdownWXItemData;
    class DataView
    {
    public:
        typedef DataViewState State;
        typedef State::Type StateType;
    private:
        typedef std::unique_ptr<State> StatePtr;
        typedef std::vector<StatePtr> StateVector;
        StateVector states;
        StateVector::iterator curState;

        wxScrolledWindow *treeScroller;
        wxTreeCtrl *treeCtrl;
        wxButton *addButton;
        wxButton *removeButton;
        wxButton *expandAllButton;
        wxButton *collapseAllButton;
        wxButton *unselectAllButton;

        wxScrolledWindow *editorPanel;
        wxPropertyGrid *propertyGrid;

        wxTreeItemId treeRootID;
        typedef std::unordered_set<wxTreeItemId, wxTreeItemIDHasher> SelectedSet;
        SelectedSet selectedTreeIDs;

        bool refreshOnIdle;

        void OnTreeDelete(wxTreeEvent &e);
        void OnTreeSelectionChanged(wxTreeEvent &e);
        void OnTreeExpanded(wxTreeEvent &e);
        void OnTreeCollapsed(wxTreeEvent &e);

        void OnEditorSize(wxSizeEvent &e);
        void OnEditorIdle(wxIdleEvent &e);
        void OnEditorExpanded(wxPropertyGridEvent &e);
        void OnEditorCollapsed(wxPropertyGridEvent &e);

        void OnAddButton(wxCommandEvent &e);
        void OnRemoveButton(wxCommandEvent &e);
        void OnExpandAllButton(wxCommandEvent &e);
        void OnCollapseAllButton(wxCommandEvent &e);
        void OnUnselectAllButton(wxCommandEvent &e);

        void OnKeyDown(wxKeyEvent &e);

        void Add();
        void Remove();
        void ExpandAll();
        void CollapseAll();
        void UnselectAll();

        DataBreakdownWXItemData* ExtractData(wxTreeItemId ID);
        // Called when the editor might need to be setup from the selection
        void CheckSetupEditor();
        SelectedSet::iterator Deselect(SelectedSet::iterator itr);
        bool IsSelectedAddingEnabled() const;
        bool IsSelectedRemovingEnabled() const;
    public:
        DataView(wxWindow *parent, wxWindow *needsPanel);
        ~DataView();
        void SelectState(StateType type, bool clearBreakdowns);
        void Select(wxTreeItemId ID);
        void Deselect(wxTreeItemId ID);
        void DeselectAll();
        void ChangeSelection(const std::vector<wxTreeItemId> &select, const std::vector<wxTreeItemId> &deselect);
        void ClearSelection();

        void CreateBreakdownsFromScratch();
        void DestroyBreakdowns();

        void FreezeWidgets();
        void ThawWidgets();
        void RefreshOnIdle();

        State* GetCurrentState();
        template<class DerivedT>
        DerivedT* GetCurrentState();
        template<class DerivedT>
        DerivedT* GetSpecificState();

        wxTreeCtrl* Tree();
        const wxTreeCtrl* Tree() const;

        wxScrolledWindow* TreeScroller();
        const wxScrolledWindow* TreeScroller() const;

        wxTreeItemId TreeRootID() const;

        wxPanel* EditorPanel();
        const wxPanel* EditorPanel() const;

        wxPropertyGrid* PropertyGrid();
        const wxPropertyGrid* PropertyGrid() const;

        wxButton* AddButton();
        const wxButton* AddButton() const;

        wxButton* RemoveButton();
        const wxButton* RemoveButton() const;
    };

    template<class DerivedT>
    DerivedT* DataView::GetCurrentState()
    {
        if (curState == states.end())
            return nullptr;

        if (DerivedT::type != (*curState)->GetType())
            return nullptr;

        return static_cast<DerivedT*>(curState->get());
    }

    template<class DerivedT>
    DerivedT* DataView::GetSpecificState()
    {
        static_assert(::std::is_base_of<State, DerivedT>::value, "The DerivedT needs to be a base type of State.");
        return static_cast<DerivedT*>((states.begin() + DerivedT::type)->get());
    }
}