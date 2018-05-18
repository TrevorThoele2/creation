#include "PropertiesTree.h"

#include <array>

#include "TreeElementBase.h"
#include "SequenceNexusBase.h"
#include "wxNexusTreeItemData.h"

#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>
#include <wx/button.h>

namespace Creation::Editing
{
    PropertiesTree::PropertiesTree(
        NexusSelection& nexusSelection,
        NexusHistory nexusHistory,
        wxWindow* parent,
        wxWindowID winid,
        const wxPoint& position,
        const wxSize& size,
        long style,
        const wxString& name)
        :
        wxPanel(parent, winid, position, size, style, name),
        nexusSelection(&nexusSelection),
        nexusHistory(nexusHistory)
    {
        auto sizer = new wxBoxSizer(wxVERTICAL);

        const auto nameWidget = new wxStaticText(this, wxID_ANY, "Tree");
        sizer->Add(nameWidget, 0, wxALIGN_CENTER);

        SetupButtons(*sizer);

        auto treeScroller = new wxScrolledWindow(
            this,
            wxID_ANY,
            wxDefaultPosition,
            wxDefaultSize,
            wxHSCROLL | wxVSCROLL | wxALWAYS_SHOW_SB);
        treeScroller->SetScrollRate(1, 1);
        sizer->Add(treeScroller, 1, wxEXPAND | wxTOP, 10);

        treeScroller->SetSizer(new wxBoxSizer(wxVERTICAL));

        tree = new TreeCtrl(
            treeScroller,
            wxID_ANY,
            wxDefaultPosition,
            wxDefaultSize,
            wxDV_NO_HEADER | wxDV_MULTIPLE);
        tree->EnableSystemTheme(false);
        tree->Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, &PropertiesTree::OnTreeSelectionChanged, this);
        treeScroller->GetSizer()->Add(tree, 1, wxEXPAND);

        SetSizer(sizer);

        selectionChangedConnection = nexusSelection.onChanged.Subscribe(&PropertiesTree::OnNexusSelectionChanged, *this);
    }

    wxDataViewItem PropertiesTree::Add(NexusNode& node, const String& label)
    {
        const auto parent = ParentOf(node);
        const auto parentID = parent ? parent->TreeElement()->ID() : wxDataViewItem{};
        return tree->Append(parentID, label, std::make_unique<wxNexusTreeItemData>(node));
    }

    void PropertiesTree::Remove(wxDataViewItem id)
    {
        tree->Unselect(id);
        tree->Delete(id);
    }

    void PropertiesTree::SetItemText(wxDataViewItem id, const std::string& text)
    {
        tree->SetText(id, text);
    }

    void PropertiesTree::Expand(wxDataViewItem id)
    {
        tree->Expand(id);
    }

    void PropertiesTree::Collapse(wxDataViewItem id)
    {
        tree->Collapse(id);
    }

    bool PropertiesTree::IsExpanded(wxDataViewItem id) const
    {
        return tree->IsExpanded(id);
    }

    void PropertiesTree::SetItemData(wxDataViewItem id, wxClientData* data)
    {
        tree->SetData(id, std::unique_ptr<wxClientData>(data));
    }

    wxClientData* PropertiesTree::ItemData(wxDataViewItem id) const
    {
        return tree->DataOf(id);
    }

    void PropertiesTree::DoFreeze()
    {
        tree->Freeze();
    }

    void PropertiesTree::DoThaw()
    {
        tree->Thaw();
    }

    NexusNode* PropertiesTree::ParentOf(NexusNode& node) const
    {
        auto checkNode = node.Parent();
        while (checkNode)
        {
            const auto treeElement = checkNode->TreeElement();
            if (treeElement)
                return checkNode;

            checkNode = checkNode->Parent();
        }

        return nullptr;
    }

    void PropertiesTree::SetupButtons(wxSizer& sizer)
    {
        auto totalButtonSizer = new wxBoxSizer(wxVERTICAL);
        sizer.Add(totalButtonSizer, 0, wxEXPAND);

        auto topButtonSizer = new wxBoxSizer(wxHORIZONTAL);
        totalButtonSizer->Add(topButtonSizer, 0, wxALIGN_CENTER);

        auto bottomButtonSizer = new wxBoxSizer(wxHORIZONTAL);
        totalButtonSizer->Add(bottomButtonSizer, 0, wxALIGN_CENTER);

        auto acceleratorEntries = std::array<wxAcceleratorEntry, 5>();

        {
            createButton = new wxButton(
                this,
                CreateButtonId,
                "Create",
                wxDefaultPosition,
                wxDefaultSize,
                wxBU_EXACTFIT);
            createButton->SetToolTip("Ctrl-A");
            createButton->Bind(wxEVT_BUTTON, &PropertiesTree::OnAddButton, this);
            createButton->Disable();

            acceleratorEntries[0].Set(wxACCEL_CTRL, WXK_CONTROL_A, CreateButtonId);
            topButtonSizer->Add(createButton, 0, wxEXPAND);
        }

        {
            deleteButton = new wxButton(
                this,
                DeleteButtonId,
                "Delete",
                wxDefaultPosition,
                wxDefaultSize,
                wxBU_EXACTFIT);
            deleteButton->SetToolTip("Delete");
            deleteButton->Bind(wxEVT_BUTTON, &PropertiesTree::OnRemoveButton, this);
            deleteButton->Disable();

            acceleratorEntries[1].Set(wxACCEL_NORMAL, WXK_DELETE, DeleteButtonId);
            topButtonSizer->Add(deleteButton, 0, wxEXPAND);
        }

        {
            expandAllButton = new wxButton(
                this,
                ExpandAllButtonId,
                "Expand All",
                wxDefaultPosition,
                wxDefaultSize,
                wxBU_EXACTFIT);
            expandAllButton->SetToolTip("Ctrl-E");
            expandAllButton->Bind(wxEVT_BUTTON, &PropertiesTree::OnExpandAllButton, this);

            acceleratorEntries[2].Set(wxACCEL_CTRL, WXK_CONTROL_E, ExpandAllButtonId);
            bottomButtonSizer->Add(expandAllButton, 0, wxEXPAND);
        }

        {
            collapseAllButton = new wxButton(
                this,
                CollapseAllButtonId,
                "Collapse All",
                wxDefaultPosition,
                wxDefaultSize,
                wxBU_EXACTFIT);
            collapseAllButton->SetToolTip("Ctrl-W");
            collapseAllButton->Bind(wxEVT_BUTTON, &PropertiesTree::OnCollapseAllButton, this);

            acceleratorEntries[3].Set(wxACCEL_CTRL, WXK_CONTROL_W, CollapseAllButtonId);
            bottomButtonSizer->Add(collapseAllButton, 0, wxEXPAND);
        }

        {
            deselectAllButton = new wxButton(
                this,
                DeselectAllButtonId,
                "Deselect All",
                wxDefaultPosition,
                wxDefaultSize,
                wxBU_EXACTFIT);
            deselectAllButton->SetToolTip("Ctrl-U");
            deselectAllButton->Bind(wxEVT_BUTTON, &PropertiesTree::OnDeselectAllButton, this);

            acceleratorEntries[4].Set(wxACCEL_CTRL, WXK_CONTROL_U, DeselectAllButtonId);
            bottomButtonSizer->Add(deselectAllButton, 0, wxEXPAND);
        }

        const wxAcceleratorTable acceleratorTable(acceleratorEntries.size(), acceleratorEntries.data());
        SetAcceleratorTable(acceleratorTable);
    }

    void PropertiesTree::SyncSequenceButtons()
    {
        if (nexusSelection->empty())
        {
            createButton->Disable();
            deleteButton->Disable();
        }
        else
        {
            auto enableAddButton = true;
            auto enableRemoveButton = true;
            for (auto& nexus : *nexusSelection)
            {
                if (enableAddButton && dynamic_cast<SequenceNexusBase*>(nexus) == nullptr)
                    enableAddButton = false;

                if (enableRemoveButton && dynamic_cast<SequenceNexusBase*>(nexus->Parent()) == nullptr)
                    enableRemoveButton = false;
            }

            createButton->Enable(enableAddButton);
            deleteButton->Enable(enableRemoveButton);
        }
    }

    void PropertiesTree::OnAddButton(wxCommandEvent& e)
    {
        auto allSequenceNodes = nexusSelection->AllSequenceNodes();
        const std::vector addTo(allSequenceNodes.begin(), allSequenceNodes.end());
        std::vector<NexusNode*> children;
        for (auto& parent : addTo)
        {
            auto added = parent->Add();
            children.push_back(added);
        }

        nexusHistory.Add(children);
    }

    void PropertiesTree::OnRemoveButton(wxCommandEvent& e)
    {
        const std::vector remove(nexusSelection->begin(), nexusSelection->end());
        nexusHistory.Remove(remove);
        tree->UnselectAll();
    }

    void PropertiesTree::OnExpandAllButton(wxCommandEvent& e)
    {
        tree->ExpandChildren({});
    }

    void PropertiesTree::OnCollapseAllButton(wxCommandEvent& e)
    {
        tree->Collapse({});
    }

    void PropertiesTree::OnDeselectAllButton(wxCommandEvent& e)
    {
        nexusSelection->Set({});
    }

    void PropertiesTree::OnTreeSelectionChanged(wxDataViewEvent& e)
    {
        wxDataViewItemArray array;
        tree->GetSelections(array);

        std::set<NexusNode*> newSelectedNexi;
        for (auto& id : array)
            newSelectedNexi.emplace(dynamic_cast<wxNexusTreeItemData*>(tree->DataOf(id))->node);

        nexusSelection->Set(newSelectedNexi);
    }
    
    void PropertiesTree::OnNexusSelectionChanged(const NexusSelection::Delta& delta)
    {
        for (auto& select : delta.select)
        {
            const auto treeElement = select->TreeElement();
            if (treeElement)
                tree->Select(treeElement->ID());
        }

        for (auto& deselect : delta.deselect)
        {
            const auto treeElement = deselect->TreeElement();
            if (treeElement)
                tree->Unselect(treeElement->ID());
        }

        SyncSequenceButtons();
        tree->Refresh();
    }
}