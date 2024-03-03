#include "PropertiesEditor.h"

#include <wx/scrolwin.h>
#include <wx/sizer.h>
#include <wx/propgrid/propgrid.h>

#include "EditableNexusBase.h"

namespace Creation::Editing
{
    PropertiesEditor::PropertiesEditor(
        NexusSelection& nexusSelection,
        wxWindow* parent,
        wxWindowID winid,
        const wxPoint& position,
        const wxSize& size,
        long style,
        const wxString& name)
        :
        wxPanel(parent, winid, position, size, style, name),
        nexusSelection(&nexusSelection)
    {
        auto sizer = new wxBoxSizer(wxVERTICAL);

        scrolledWindow = new wxScrolledWindow(
            this,
            wxID_ANY,
            wxDefaultPosition,
            wxDefaultSize,
            wxHSCROLL | wxVSCROLL | wxALWAYS_SHOW_SB);
        scrolledWindow->SetSizer(new wxBoxSizer(wxVERTICAL));
        scrolledWindow->SetScrollRate(5, 5);
        sizer->Add(scrolledWindow, 1, wxEXPAND);

        grid = new wxPropertyGrid(
            scrolledWindow,
            wxID_ANY,
            wxDefaultPosition,
            wxDefaultSize,
            wxPG_DEFAULT_STYLE);
        grid->SetExtraStyle(wxWS_EX_PROCESS_IDLE);
        scrolledWindow->GetSizer()->Add(grid, 1, wxEXPAND);

        SetSizer(sizer);

        nexusSelection.onChanged.Subscribe(std::bind(&PropertiesEditor::OnNexusSelectionChanged, this, std::placeholders::_1));
    }

    void PropertiesEditor::Clear()
    {
        grid->Clear();
    }

    void PropertiesEditor::CommitChanges()
    {
        grid->CommitChangesFromEditor();
    }

    void PropertiesEditor::OnNexusSelectionChanged(const NexusSelection::Delta&)
    {
        nexusBatch.reset();

        if (
            nexusSelection->empty()
            || nexusSelection->AllTypes().size() > 1
            || dynamic_cast<EditableNexusBase*>(*nexusSelection->begin()) == nullptr)
        {
            return;
        }

        auto start = nexusSelection->begin();

        if (typeid(std::nullptr_t) != typeid(*start))
        {
            const auto asEditable = dynamic_cast<EditableNexusBase*>(*start);
            nexusBatch = asEditable->StartEditingBatch(*grid);
            start = ++start;
        }

        for (auto nexus = start; nexus != nexusSelection->end(); ++nexus)
            nexusBatch->AttemptAdd(**nexus);

        grid->SetSplitterLeft();
    }
}