#pragma once

#include <unordered_set>

#include <wx/panel.h>
#include "TreeCtrl.h"

#include "NexusNode.h"
#include "NexusSelection.h"
#include "NexusHistory.h"

#include "String.h"

namespace Creation::Editing
{
    class PropertiesTree final : public wxPanel
    {
    public:
        PropertiesTree(
            NexusSelection& nexusSelection,
            NexusHistory nexusHistory,
            wxWindow* parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& position = wxPoint(),
            const wxSize& size = wxSize(),
            long style = wxTAB_TRAVERSAL | wxNO_BORDER,
            const wxString& name = "PropertiesTree");

        wxDataViewItem Add(NexusNode& node, const String& label);
        void Remove(wxDataViewItem id);

        void SetItemText(wxDataViewItem id, const std::string& text);

        void Expand(wxDataViewItem id);
        void Collapse(wxDataViewItem id);
        [[nodiscard]] bool IsExpanded(wxDataViewItem id) const;
        
        void SetItemData(wxDataViewItem id, wxClientData* data);
        [[nodiscard]] wxClientData* ItemData(wxDataViewItem id) const;
    protected:
        void DoFreeze() override;
        void DoThaw() override;
    private:
        [[nodiscard]] NexusNode* ParentOf(NexusNode& node) const;
    private:
        TreeCtrl* tree;
    private:
        wxButton* createButton = nullptr;
        wxButton* deleteButton = nullptr;
        wxButton* expandAllButton = nullptr;
        wxButton* collapseAllButton = nullptr;
        wxButton* deselectAllButton = nullptr;

        enum
        {
            CreateButtonId,
            DeleteButtonId,
            ExpandAllButtonId,
            CollapseAllButtonId,
            DeselectAllButtonId
        };

        void SetupButtons(wxSizer& sizer);
        void SyncSequenceButtons();

        void OnAddButton(wxCommandEvent& e);
        void OnRemoveButton(wxCommandEvent& e);
        void OnExpandAllButton(wxCommandEvent& e);
        void OnCollapseAllButton(wxCommandEvent& e);
        void OnDeselectAllButton(wxCommandEvent& e);

        void OnTreeSelectionChanged(wxDataViewEvent& e);
    private:
        NexusSelection* nexusSelection = nullptr;
        ScopedEventConnection selectionChangedConnection;
        void OnNexusSelectionChanged(const NexusSelection::Delta& delta);
    private:
        NexusHistory nexusHistory;
    };
}