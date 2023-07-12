
#include "DataView.h"

#include "DataViewStateAssets.h"
#include "DataViewStateEntities.h"
#include "DataViewStateGameData.h"
#include "DataViewStateRegistries.h"
#include "DataViewStateTiles.h"
#include "DataBreakdownWXItemData.h"

#include "Viewport.h"
#include "Application.h"
#include "Assert.h"

#include <wx/treectrl.h>
#include <wx/panel.h>
#include <wx/propgrid/propgrid.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/button.h>

namespace Creation
{
    void DataView::OnTreeDelete(wxTreeEvent &e)
    {
        Deselect(e.GetItem());
    }

    void DataView::OnTreeSelectionChanged(wxTreeEvent &e)
    {
        if (curState == states.end())
        {
            e.Skip();
            return;
        }

        // Intersection
        if (wxGetKeyState(wxKeyCode::WXK_ALT) && !wxGetKeyState(wxKeyCode::WXK_SHIFT) && !wxGetKeyState(wxKeyCode::WXK_CONTROL))
        {
            // Retrieve all groups with the same type_info as the selected item
            std::vector<DataViewSelection::Group*> groups(DataViewSelection::GetGroups(typeid(*static_cast<DataBreakdownWXItemData*>(treeCtrl->GetItemData(e.GetItem()))->data)));

            // The groups selected are the intersection between selected items, and the type_info selected
            std::vector<wxTreeItemId> passSelect;
            for (auto &groupLoop : groups)
                for(auto &loop : *groupLoop)
                    passSelect.push_back(loop->GetTreeItemID());
            DeselectAll();
            ChangeSelection(passSelect, std::vector<wxTreeItemId>());

            e.Skip();
            return;
        }

        std::unordered_set<wxTreeItemId, wxTreeItemIDHasher> useSet(selectedTreeIDs);
        std::unordered_set<wxTreeItemId, wxTreeItemIDHasher> select, deselect;
        wxArrayTreeItemIds retrieved;
        treeCtrl->GetSelections(retrieved);
        for (auto &loop : retrieved)
        {
            if (useSet.find(loop) == useSet.end())
                // Was not in the selected ID set
                select.emplace(wxTreeItemId(loop));
            else
                // Was in the selected ID set
                useSet.erase(loop);
        }

        // Everything in the selected ID set still here is to be deselected
        deselect = useSet;

        {
            std::vector<wxTreeItemId> passSelect, passDeselect;
            for (auto loop = select.begin(); loop != select.end(); ++loop)
            {
                if (deselect.erase(*loop) == 0)
                    passSelect.push_back(*loop);
            }

            for (auto loop = deselect.begin(); loop != deselect.end(); ++loop)
                passDeselect.push_back(*loop);

            ChangeSelection(passSelect, passDeselect);
        }

        e.Skip();
    }

    void DataView::OnTreeExpanded(wxTreeEvent &e)
    {
        auto propCategory = static_cast<DataBreakdownWXItemData*>(treeCtrl->GetItemData(e.GetItem()))->data->GetPropertyCategory();
        if(propCategory)
            propertyGrid->Expand(propCategory);
    }

    void DataView::OnTreeCollapsed(wxTreeEvent &e)
    {
        auto propCategory = static_cast<DataBreakdownWXItemData*>(treeCtrl->GetItemData(e.GetItem()))->data->GetPropertyCategory();
        if(propCategory)
            propertyGrid->Collapse(propCategory);
    }

    void DataView::OnEditorSize(wxSizeEvent &e)
    {
        EditorPanel()->Layout();
    }

    void DataView::OnEditorIdle(wxIdleEvent &e)
    {
        if (!refreshOnIdle)
        {
            e.Skip();
            return;
        }
        
        propertyGrid->Refresh();
        propertyGrid->SetSplitterLeft();
        propertyGrid->Refresh();
        propertyGrid->FitColumns();
        refreshOnIdle = false;

        e.Skip();
    }

    void DataView::OnEditorExpanded(wxPropertyGridEvent &e)
    {
        auto treeItemID = static_cast<DataBreakdownWXItemData*>(e.GetProperty()->GetClientObject())->data->GetTreeItemID();
        if (treeItemID.IsOk())
            treeCtrl->Expand(treeItemID);
    }

    void DataView::OnEditorCollapsed(wxPropertyGridEvent &e)
    {
        auto treeItemID = static_cast<DataBreakdownWXItemData*>(e.GetProperty()->GetClientObject())->data->GetTreeItemID();
        if (treeItemID.IsOk())
            treeCtrl->Collapse(treeItemID);
    }

    void DataView::OnAddButton(wxCommandEvent &e)
    {
        Add();
        e.Skip();
    }

    void DataView::OnRemoveButton(wxCommandEvent &e)
    {
        Remove();
        e.Skip();
    }

    void DataView::OnExpandAllButton(wxCommandEvent &e)
    {
        ExpandAll();
        e.Skip();
    }

    void DataView::OnCollapseAllButton(wxCommandEvent &e)
    {
        CollapseAll();
        e.Skip();
    }

    void DataView::OnUnselectAllButton(wxCommandEvent &e)
    {
        UnselectAll();
        e.Skip();
    }

    void DataView::OnKeyDown(wxKeyEvent &e)
    {
        // Add
        if (e.GetKeyCode() == 'A' && e.ControlDown())
            Add();
        // Remove
        else if (e.GetKeyCode() == 'R' && e.ControlDown())
            Remove();
        // Expand all
        else if (e.GetKeyCode() == 'E' && e.ControlDown())
            ExpandAll();
        // Collapse all
        else if (e.GetKeyCode() == 'W' && e.ControlDown())
            CollapseAll();
        // Unselect all
        else if (e.GetKeyCode() == 'U' && e.ControlDown())
            UnselectAll();
    }

    void DataView::Add()
    {
        if (curState == states.end() || !DataViewSelection::AnySelected() || !IsSelectedAddingEnabled())
            return;
        
        auto group = DataViewSelection::GetOnlyPrimaryGroup();
        if (!group)
            return;

        if (group->size() == 1)
            static_cast<DataBreakdownWXItemData*>(treeCtrl->GetItemData((*group->begin())->GetTreeItemID()))->data->CreateAddToCommand()->Commit();
        else
        {
            Command::AnyGroup *groupCommand = Command::AnyGroup::Create();
            for (auto &loop : *group)
                groupCommand->Add(static_cast<DataBreakdownWXItemData*>(treeCtrl->GetItemData(loop->GetTreeItemID()))->data->CreateAddToCommand());
            groupCommand->Commit();
        }
    }

    void DataView::Remove()
    {
        if (curState == states.end() || !DataViewSelection::AnySelected() || !IsSelectedRemovingEnabled())
            return;

        auto group = DataViewSelection::GetOnlyPrimaryGroup();
        if (!group)
            return;

        if (group->size() == 1)
            static_cast<DataBreakdownWXItemData*>(treeCtrl->GetItemData((*group->begin())->GetTreeItemID()))->data->CreateRemoveThisCommand()->Commit();
        else
        {
            Command::AnyGroup *groupCommand = Command::AnyGroup::Create();
            for (auto &loop : *group)
                groupCommand->Add(static_cast<DataBreakdownWXItemData*>(treeCtrl->GetItemData(loop->GetTreeItemID()))->data->CreateRemoveThisCommand());
            groupCommand->Commit();
        }
    }

    void DataView::ExpandAll()
    {
        if (selectedTreeIDs.empty())
            treeCtrl->ExpandAll();
        else
        {
            for (auto &loop : selectedTreeIDs)
                treeCtrl->ExpandAllChildren(loop);
        }
    }

    void DataView::CollapseAll()
    {
        if (selectedTreeIDs.empty())
            treeCtrl->CollapseAll();
        else
        {
            for (auto &loop : selectedTreeIDs)
                treeCtrl->CollapseAllChildren(loop);
        }
    }

    void DataView::UnselectAll()
    {
        treeCtrl->UnselectAll();
    }

    DataBreakdownWXItemData* DataView::ExtractData(wxTreeItemId ID)
    {
        if (ID.IsOk())
            return static_cast<DataBreakdownWXItemData*>(treeCtrl->GetItemData(ID));
        else
            return nullptr;
    }

    void DataView::CheckSetupEditor()
    {
        // If the primary group size is 1, then create editor pieces and setup add/remove button
        if (DataViewSelection::PrimaryGroupCount() == 1)
        {
            // Enable buttons
            addButton->Enable(IsSelectedAddingEnabled());
            removeButton->Enable(IsSelectedRemovingEnabled());

            (*DataViewSelection::GetOnlyPrimaryGroup()->begin())->CreateEditorProperties(nullptr);
            PropertyGrid()->FitColumns();
            EditorPanel()->Layout();
        }
        else
        {
            for (auto &loop : selectedTreeIDs)
                static_cast<DataBreakdownWXItemData*>(treeCtrl->GetItemData(loop))->data->DestroyEditorProperties(false);

            // Disable buttons
            addButton->Enable(false);
            removeButton->Enable(false);
        }
    }

    DataView::SelectedSet::iterator DataView::Deselect(SelectedSet::iterator itr)
    {
        wxTreeItemId id(*itr);
        DataBreakdownWXItemData* itemData = ExtractData(id);
        if (!itemData->data->IsSelected())
            return ++itr;

        SelectedSet::iterator ret = selectedTreeIDs.erase(itr);
        itemData->data->DeselectThis();
        (*curState)->Deselect(id);
        Viewport::viewport->DeselectItem(id);
        treeCtrl->SelectItem(id, false);
        CheckSetupEditor();
        return ret;
    }

    bool DataView::IsSelectedAddingEnabled() const
    {
        auto group = DataViewSelection::GetOnlyPrimaryGroup();
        if (!group)
            return false;

        return (*group->begin())->IsAddingEnabled();
    }

    bool DataView::IsSelectedRemovingEnabled() const
    {
        auto group = DataViewSelection::GetOnlyPrimaryGroup();
        if (!group)
            return false;

        return (*group->begin())->CanRemoveThis();
    }

    DataView::DataView(wxWindow *parent, wxWindow *totalPanel) : refreshOnIdle(false)
    {
        // Tree
        {
            // Name
            wxStaticText *name = new wxStaticText(totalPanel, wxID_ANY, "Tree");
            totalPanel->GetSizer()->Add(name, 0, wxALIGN_CENTER);

            // Buttons
            wxBoxSizer *verticalButtonSizer = new wxBoxSizer(wxVERTICAL);
            totalPanel->GetSizer()->Add(verticalButtonSizer, 0, wxEXPAND);

            wxBoxSizer *topButtonSizer = new wxBoxSizer(wxHORIZONTAL);
            verticalButtonSizer->Add(topButtonSizer, 0, wxALIGN_CENTER);

            // Add button
            addButton = new wxButton(totalPanel, wxID_ANY, "Add", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
            topButtonSizer->Add(addButton, 0, wxEXPAND);
            addButton->SetToolTip("Ctrl-A");
            addButton->Bind(wxEVT_BUTTON, &DataView::OnAddButton, this);
            addButton->Disable();

            // Remove button
            removeButton = new wxButton(totalPanel, wxID_ANY, "Remove", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
            topButtonSizer->Add(removeButton, 0, wxEXPAND);
            removeButton->SetToolTip("Ctrl-R");
            removeButton->Bind(wxEVT_BUTTON, &DataView::OnRemoveButton, this);
            removeButton->Disable();

            wxBoxSizer *bottomButtonSizer = new wxBoxSizer(wxHORIZONTAL);
            verticalButtonSizer->Add(bottomButtonSizer, 0, wxALIGN_CENTER);

            // Expand all button
            expandAllButton = new wxButton(totalPanel, wxID_ANY, "Expand All", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
            bottomButtonSizer->Add(expandAllButton, 0, wxEXPAND);
            expandAllButton->SetToolTip("Ctrl-E");
            expandAllButton->Bind(wxEVT_BUTTON, &DataView::OnExpandAllButton, this);

            // Collapse all button
            collapseAllButton = new wxButton(totalPanel, wxID_ANY, "Collapse All", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
            bottomButtonSizer->Add(collapseAllButton, 0, wxEXPAND);
            collapseAllButton->SetToolTip("Ctrl-W");
            collapseAllButton->Bind(wxEVT_BUTTON, &DataView::OnCollapseAllButton, this);

            // Unselect all button
            unselectAllButton = new wxButton(totalPanel, wxID_ANY, "Unselect All", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
            bottomButtonSizer->Add(unselectAllButton, 0, wxEXPAND);
            unselectAllButton->SetToolTip("Ctrl-U");
            unselectAllButton->Bind(wxEVT_BUTTON, &DataView::OnUnselectAllButton, this);

            // Tree panel
            treeScroller = new wxScrolledWindow(totalPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL | wxALWAYS_SHOW_SB);
            treeScroller->SetScrollRate(1, 1);
            totalPanel->GetSizer()->Add(treeScroller, 1, wxEXPAND | wxTOP, 10);

            treeScroller->SetSizer(new wxBoxSizer(wxVERTICAL));

            // Tree ctrl
            treeCtrl = new wxTreeCtrl(treeScroller, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_MULTIPLE | wxTR_HIDE_ROOT | wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT);
            treeCtrl->Bind(wxEVT_TREE_DELETE_ITEM, &DataView::OnTreeDelete, this);
            treeCtrl->Bind(wxEVT_TREE_SEL_CHANGED, &DataView::OnTreeSelectionChanged, this);
            treeCtrl->Bind(wxEVT_KEY_DOWN, &DataView::OnKeyDown, this);
            treeScroller->GetSizer()->Add(treeCtrl, 1, wxEXPAND);
            treeRootID = treeCtrl->AddRoot("Root");
        }

        // Editor panel
        editorPanel = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxSize(300, 0), wxHSCROLL | wxVSCROLL | wxALWAYS_SHOW_SB);
        editorPanel->SetSizer(new wxBoxSizer(wxVERTICAL));
        editorPanel->SetScrollRate(5, 5);
        editorPanel->SetAutoLayout(false);
        editorPanel->Bind(wxEVT_SIZE, &DataView::OnEditorSize, this);

        // Property Grid
        propertyGrid = new wxPropertyGrid(editorPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE | wxPG_STATIC_SPLITTER);
        propertyGrid->SetExtraStyle(wxWS_EX_PROCESS_IDLE);
        editorPanel->GetSizer()->Add(propertyGrid, 1, wxEXPAND);
        propertyGrid->Bind(wxEVT_PG_ITEM_EXPANDED, &DataView::OnEditorExpanded, this);
        propertyGrid->Bind(wxEVT_PG_ITEM_COLLAPSED, &DataView::OnEditorCollapsed, this);
        treeCtrl->Bind(wxEVT_TREE_ITEM_COLLAPSED, &DataView::OnTreeCollapsed, this);
        treeCtrl->Bind(wxEVT_TREE_ITEM_EXPANDED, &DataView::OnTreeExpanded, this);
        propertyGrid->Bind(wxEVT_IDLE, &DataView::OnEditorIdle, this);

        states.push_back(StatePtr(new DataViewStateAssets(this)));
        states.push_back(StatePtr(new DataViewStateRegistries(this)));
        states.push_back(StatePtr(new DataViewStateGameData(this)));
        states.push_back(StatePtr(new DataViewStateTiles(this)));
        states.push_back(StatePtr(new DataViewStateEntities(this)));
        curState = states.end();
    }

    DataView::~DataView()
    {
        treeCtrl->Unbind(wxEVT_TREE_DELETE_ITEM, &DataView::OnTreeDelete, this);
        treeCtrl->Unbind(wxEVT_TREE_SEL_CHANGED, &DataView::OnTreeSelectionChanged, this);
        propertyGrid->SetEvtHandlerEnabled(false);
    }

    void DataView::SelectState(StateType type, bool clearBreakdowns)
    {
        if (curState == states.begin() + type)
            return;

        if (curState != states.end())
        {
            (*curState)->Stop();
            if(clearBreakdowns)
                (*curState)->DestroyBreakdowns();
        }

        selectedTreeIDs.clear();
        DataViewSelection::Clear();

        addButton->Enable(false);
        removeButton->Enable(false);

        if (type == StateType::NONE)
        {
            curState = states.end();
            addButton->Disable();
            removeButton->Disable();
            return;
        }

        curState = states.begin() + type;
        (*curState)->Start();
    }

    void DataView::Select(wxTreeItemId ID)
    {
        if (!ID.IsOk())
            return;

        DataBreakdownWXItemData* itemData = ExtractData(ID);
        if (itemData->data->IsSelected())
            return;

        selectedTreeIDs.emplace(ID);
        // Select this as a primary
        itemData->data->SelectThisPrimary();
        (*curState)->Select(ID);
        Viewport::viewport->SelectItem(ID);
        CheckSetupEditor();
    }

    void DataView::Deselect(wxTreeItemId ID)
    {
        if (!ID.IsOk())
            return;

        DataBreakdownWXItemData* itemData = ExtractData(ID);
        if (!itemData->data->IsSelected())
            return;

        selectedTreeIDs.erase(ID);
        itemData->data->DeselectThis();
        (*curState)->Deselect(ID);
        Viewport::viewport->DeselectItem(ID);
        CheckSetupEditor();
    }

    void DataView::DeselectAll()
    {
        (*curState)->DeselectAll();
    }

    void DataView::ChangeSelection(const std::vector<wxTreeItemId> &select, const std::vector<wxTreeItemId> &deselect)
    {
        // Temporarily unbind from the tree selection event so that we don't get into an infinite loop
        treeCtrl->Unbind(wxEVT_TREE_SEL_CHANGED, &DataView::OnTreeSelectionChanged, this);

        for (auto loop : deselect)
        {
            treeCtrl->UnselectItem(loop);

            selectedTreeIDs.erase(loop);
            DataBreakdownWXItemData *itemData = ExtractData(loop);
            CREATION_ASSERT_MESSAGE(itemData, "This data must exist.");
            itemData->data->DeselectThis();
            (*curState)->Deselect(loop);
            Viewport::viewport->DeselectItem(loop);
        }

        for (auto loop : select)
        {
            treeCtrl->SelectItem(loop);

            selectedTreeIDs.emplace(loop);
            DataBreakdownWXItemData *itemData = ExtractData(loop);
            CREATION_ASSERT_MESSAGE(itemData, "This data must exist.");
            itemData->data->SelectThisPrimary();
            (*curState)->Select(loop);
            Viewport::viewport->SelectItem(loop);
        }

        CheckSetupEditor();

        // Rebind the event
        treeCtrl->Bind(wxEVT_TREE_SEL_CHANGED, &DataView::OnTreeSelectionChanged, this);
    }

    void DataView::ClearSelection()
    {
        for (auto loop = selectedTreeIDs.begin(); loop != selectedTreeIDs.end();)
            loop = Deselect(loop);
    }

    void DataView::CreateBreakdownsFromScratch()
    {
        FreezeWidgets();

        for (auto &loop : states)
        {
            loop->DestroyBreakdowns();
            loop->CreateBreakdownsFromScratch();
        }

        ThawWidgets();
    }

    void DataView::DestroyBreakdowns()
    {
        for (auto &loop : states)
            loop->DestroyBreakdowns();
    }

    void DataView::FreezeWidgets()
    {
        treeCtrl->Freeze();
        editorPanel->Freeze();
    }

    void DataView::ThawWidgets()
    {
        treeCtrl->Thaw();
        editorPanel->Thaw();
    }

    void DataView::RefreshOnIdle()
    {
        refreshOnIdle = true;
    }

    DataView::State* DataView::GetCurrentState()
    {
        if (curState == states.end())
            return nullptr;

        return curState->get();
    }

    wxTreeCtrl* DataView::Tree()
    {
        return treeCtrl;
    }

    const wxTreeCtrl* DataView::Tree() const
    {
        return treeCtrl;
    }

    wxScrolledWindow* DataView::TreeScroller()
    {
        return treeScroller;
    }

    const wxScrolledWindow* DataView::TreeScroller() const
    {
        return treeScroller;
    }

    wxTreeItemId DataView::TreeRootID() const
    {
        return treeRootID;
    }

    wxPanel* DataView::EditorPanel()
    {
        return editorPanel;
    }

    const wxPanel* DataView::EditorPanel() const
    {
        return editorPanel;
    }

    wxPropertyGrid* DataView::PropertyGrid()
    {
        return propertyGrid;
    }

    const wxPropertyGrid* DataView::PropertyGrid() const
    {
        return propertyGrid;
    }

    wxButton* DataView::AddButton()
    {
        return addButton;
    }

    const wxButton* DataView::AddButton() const
    {
        return addButton;
    }

    wxButton* DataView::RemoveButton()
    {
        return removeButton;
    }

    const wxButton* DataView::RemoveButton() const
    {
        return removeButton;
    }
}