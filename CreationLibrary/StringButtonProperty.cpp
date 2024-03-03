#include "StringButtonProperty.h"

#include "StringSelectionDialog.h"
#include <wx/propgrid/propgrid.h>

namespace Creation
{
    StringButtonProperty::StringButtonProperty() = default;

    StringButtonProperty::~StringButtonProperty() = default;

    wxString StringButtonProperty::GetName() const
    {
        return "StringButtonEditor";
    }

    wxPGWindowList StringButtonProperty::CreateControls(
        wxPropertyGrid* propGrid,
        wxPGProperty* property,
        const wxPoint& pos,
        const wxSize& size) const
    {
        auto buttons = new wxPGMultiButton(propGrid, size);
        buttons->Add("...");
        auto list = wxPGTextCtrlEditor::CreateControls(propGrid, property, pos, buttons->GetPrimarySize());
        buttons->Finalize(propGrid, pos);
        list.SetSecondary(buttons);
        return list;
    }

    bool StringButtonProperty::OnEvent(
        wxPropertyGrid* propGrid,
        wxPGProperty* property,
        wxWindow* ctrl,
        wxEvent& event) const
    {
        if (event.GetEventType() == wxEVT_BUTTON)
        {
            const auto buttons = static_cast<wxPGMultiButton*>(propGrid->GetEditorControlSecondary());
            if (event.GetId() == buttons->GetButtonId(0))
            {
                StringSelectionDialog dialog(ctrl, "Strings");
                dialog.Set(stringList);
                if (!dialog.ShowModal())
                    return false;

                const auto selected = dialog.GetSelected();
                if (!selected)
                    return false;
            }
        }

        return wxPGTextCtrlEditor::OnEvent(propGrid, property, ctrl, event);
    }

    void StringButtonProperty::AddString(const String& add)
    {
        stringList.push_back(add);
    }

    void StringButtonProperty::AddString(String&& add)
    {
        stringList.push_back(std::move(add));
    }

    void StringButtonProperty::SetStrings(std::vector<String>&& set)
    {
        stringList = std::move(set);
    }

    wxIMPLEMENT_DYNAMIC_CLASS(StringButtonProperty, wxPGTextCtrlEditor)
}