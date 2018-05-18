#include "WithButtonEditor.h"

#include <wx/artprov.h>
#include <wx/propgrid/propgrid.h>

namespace Creation::Editing
{
    void WithButtonEditor::SetOnButton(const OnButton& onButton)
    {
        this->onButton = onButton;
    }

    wxPGWindowList WithButtonEditor::CreateControls(
        wxPropertyGrid* grid,
        wxPGProperty* property,
        const wxPoint& position,
        const wxSize& size) const
    {
        const auto multiButton = new wxPGMultiButton(grid, size);

        multiButton->Add("...");

        auto windowList = wxPGTextCtrlEditor::CreateControls(
            grid,
            property,
            position,
            multiButton->GetPrimarySize());

        multiButton->Finalize(grid, position);
        windowList.SetSecondary(multiButton);
        return windowList;
    }

    bool WithButtonEditor::OnEvent(
        wxPropertyGrid* grid,
        wxPGProperty* property,
        wxWindow* window,
        wxEvent& event) const
    {
        if (event.GetEventType() == wxEVT_BUTTON)
        {
            const auto multiButton = (wxPGMultiButton*)grid->GetEditorControlSecondary();
            if (event.GetId() == multiButton->GetButtonId(0))
                onButton();
        }
        return wxPGTextCtrlEditor::OnEvent(grid, property, window, event);
    }

    wxString WithButtonEditor::GetName() const
    {
        return "WithButtonEditor";
    }

    wxIMPLEMENT_DYNAMIC_CLASS(WithButtonEditor, wxPGTextCtrlEditor);
}