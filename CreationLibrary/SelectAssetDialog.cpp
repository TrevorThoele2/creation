#include "SelectAssetDialog.h"

#include "String.h"

#include <wx/sizer.h>
#include <wx/statline.h>
#include "ToWxWidgets.h"

namespace Creation
{
    SelectAssetDialog::SelectAssetDialog(
        const std::vector<String>& choices,
        wxWindow* parent,
        const wxString& title,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxString& name)
        :
        wxDialog(parent, wxID_ANY, title, pos, size, style, name)
    {
        SetSizer(new wxBoxSizer(wxVERTICAL));

        const auto wxChoices = WxWidgets::ToStringArray(choices);
        listbox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxChoices, wxLB_SINGLE | wxLB_ALWAYS_SB);
        GetSizer()->Add(listbox, 1, wxEXPAND | wxALL, 5);

        GetSizer()->Add(new wxStaticLine(this), 0, wxEXPAND | wxTOP, 2);

        GetSizer()->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxBOTTOM, 2);
        Layout();
        CentreOnScreen();
    }

    std::optional<String> SelectAssetDialog::Selected() const
    {
        const auto selected = listbox->GetSelection();
        return selected == wxNOT_FOUND ? std::optional<String>{} : String(listbox->GetString(selected));
    }
}