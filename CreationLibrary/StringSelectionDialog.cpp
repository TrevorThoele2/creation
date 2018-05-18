#include "StringSelectionDialog.h"
#include <wx/sizer.h>

namespace Creation
{
    StringSelectionDialog::StringSelectionDialog(
        wxWindow* parent,
        const wxString& title,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxString& name)
        :
        wxDialog(parent, wxID_ANY, title, pos, size, style, name)
    {
        CreateWidgets();
    }

    void StringSelectionDialog::Set(const std::vector<String>& set)
    {
        SetWidgets(set);
    }

    std::optional<String> StringSelectionDialog::GetSelected() const
    {
        auto selection = list->GetSelection();
        if (selection == wxNOT_FOUND)
            return {};

        return list->GetString(selection).ToStdString();
    }

    void StringSelectionDialog::CreateWidgets()
    {
        SetSizer(new wxBoxSizer(wxVERTICAL));
        auto sizer = GetSizer();

        list = new wxListBox(
            this,
            wxID_ANY,
            wxDefaultPosition,
            wxDefaultSize,
            0,
            nullptr,
            wxLB_SINGLE | wxLB_ALWAYS_SB | wxLB_HSCROLL);
        sizer->Add(list, 1, wxEXPAND);

        sizer->Add(CreateSeparatedButtonSizer(wxOK | wxCANCEL), 0, wxEXPAND);
        Layout();
        CenterOnScreen();
    }

    void StringSelectionDialog::SetWidgets(const std::vector<String>& set)
    {
        for (auto& loop : set)
            if (loop != "")
                list->Append(loop);
    }
}