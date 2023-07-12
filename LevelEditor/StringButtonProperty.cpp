
#include "StringButtonProperty.h"

#include "MainFrame.h"

#include "StringSelectionDialog.h"
#include <wx/propgrid/propgrid.h>

namespace Creation
{
    wxIMPLEMENT_DYNAMIC_CLASS(StringButtonProperty, wxPGTextCtrlEditor);

    wxString StringButtonProperty::GetName() const
    {
        return "StringButtonEditor";
    }

    wxPGWindowList StringButtonProperty::CreateControls(wxPropertyGrid *propGrid, wxPGProperty *property, const wxPoint &pos, const wxSize &size) const
    {
        wxPGMultiButton* buttons = new wxPGMultiButton(propGrid, size);
        buttons->Add("...");
        wxPGWindowList list = wxPGTextCtrlEditor::CreateControls(propGrid, property, pos, buttons->GetPrimarySize());
        buttons->Finalize(propGrid, pos);
        list.SetSecondary(buttons);
        return list;
    }

    bool StringButtonProperty::OnEvent(wxPropertyGrid *propGrid, wxPGProperty *property, wxWindow *ctrl, wxEvent &event) const
    {
        if (event.GetEventType() == wxEVT_BUTTON)
        {
            wxPGMultiButton* buttons = (wxPGMultiButton*)propGrid->GetEditorControlSecondary();
            if (event.GetId() == buttons->GetButtonId(0))
            {
                StringSelectionDialog dialog(GetMainFrame(), "Strings");
                dialog.Set(strings);
                if (!dialog.ShowModal())
                    return false;

                auto selected = dialog.GetSelected();
                if (!selected)
                    return false;

                onChanged(*selected);
            }
        }

        return wxPGTextCtrlEditor::OnEvent(propGrid, property, ctrl, event);
    }

    void StringButtonProperty::AddString(const String &add)
    {
        strings.push_back(add);
    }

    void StringButtonProperty::AddString(String &&add)
    {
        strings.push_back(std::move(add));
    }

    void StringButtonProperty::SetStrings(StringVector &&set)
    {
        strings = std::move(set);
    }
}