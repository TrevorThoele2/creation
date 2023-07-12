
#include "GridPositionDialog.h"

#include <Atmos/StringUtility.h>

#include <wx/stattext.h>
#include <wx/sizer.h>

namespace Creation
{
    void GridPositionDialog::CreateWidgets()
    {
        wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
        SetSizer(mainSizer);

        wxGridSizer *gridSizer = new wxGridSizer(3, 0, 0);
        mainSizer->Add(gridSizer, 0, wxEXPAND);

        gridSizer->Add(new wxStaticText(this, wxID_ANY, "X"), 0, wxALIGN_CENTER);
        gridSizer->Add(new wxStaticText(this, wxID_ANY, "Y"), 0, wxALIGN_CENTER);
        gridSizer->Add(new wxStaticText(this, wxID_ANY, "Z"), 0, wxALIGN_CENTER);

        x = new wxTextCtrl(this, wxID_ANY);
        gridSizer->Add(x);
        y = new wxTextCtrl(this, wxID_ANY);
        gridSizer->Add(y);
        z = new wxTextCtrl(this, wxID_ANY);
        gridSizer->Add(z);

        mainSizer->Add(CreateSeparatedButtonSizer(wxOK | wxCANCEL), 0, wxEXPAND);
        DoLayoutAdaptation();
        CenterOnScreen();
    }

    void GridPositionDialog::SetWidgets(DimensionT setX, DimensionT setY, DimensionT setZ)
    {
        x->SetValue(::Atmos::ToString(setX));
        y->SetValue(::Atmos::ToString(setY));
        z->SetValue(::Atmos::ToString(setZ));
    }

    GridPositionDialog::GridPositionDialog(wxWindow *parent, const wxString &title, const wxPoint &pos, const wxSize &size, long style, const wxString &name) : wxDialog(parent, wxID_ANY, title, pos, size, style, name)
    {
        CreateWidgets();
        SetWidgets(0, 0, 0);
    }

    GridPositionDialog::GridPositionDialog(wxWindow *parent, const ValueT &position, const wxString &title, const wxPoint &pos, const wxSize &size, long style, const wxString &name) : wxDialog(parent, wxID_ANY, title, pos, size, style, name)
    {
        CreateWidgets();
        Set(position);
    }

    void GridPositionDialog::Set(const ValueT &set)
    {
        SetWidgets(set.x, set.y, set.z);
    }

    GridPositionDialog::ValueT GridPositionDialog::GetValue() const
    {
        return ValueT(::Atmos::FromString<::Atmos::GridPosition::ValueT>(x->GetValue().ToStdString()), ::Atmos::FromString<::Atmos::GridPosition::ValueT>(y->GetValue().ToStdString()), ::Atmos::FromString<::Atmos::GridPosition::ValueT>(z->GetValue().ToStdString()));
    }
}