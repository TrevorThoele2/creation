#pragma once

#include <wx/panel.h>

#include "NexusBatchBase.h"
#include "NexusSelection.h"

class wxScrolledWindow;
class wxPropertyGrid;
class wxPropertyGridEvent;

namespace Creation::Editing
{
    class PropertiesEditor final : public wxPanel
    {
    public:
        PropertiesEditor(
            NexusSelection& nexusSelection,
            wxWindow* parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& position = wxPoint(),
            const wxSize& size = wxSize(),
            long style = wxTAB_TRAVERSAL | wxNO_BORDER,
            const wxString& name = "PropertiesEditor");

        void Clear();

        void CommitChanges();
    private:
        wxScrolledWindow* scrolledWindow;
        wxPropertyGrid* grid;
    private:
        NexusSelection* nexusSelection;
        std::unique_ptr<NexusBatchBase> nexusBatch;
        void OnNexusSelectionChanged(const NexusSelection::Delta& delta);
    };
}