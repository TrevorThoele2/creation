#pragma once

#include <Atmos/GridPosition.h>

#include <wx/dialog.h>
#include <wx/textctrl.h>

namespace Creation
{
    class GridPositionDialog : public wxDialog
    {
    public:
        typedef ::Atmos::GridPosition ValueT;
    private:
        typedef ValueT::ValueT DimensionT;

        wxTextCtrl *x;
        wxTextCtrl *y;
        wxTextCtrl *z;
        void CreateWidgets();
        void SetWidgets(DimensionT setX, DimensionT setY, DimensionT setZ);
    public:
        GridPositionDialog(wxWindow *parent, const wxString &title, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxSize(200, 50), long style = wxCAPTION | wxCLOSE_BOX | wxSTAY_ON_TOP, const wxString &name = wxDialogNameStr);
        GridPositionDialog(wxWindow *parent, const ValueT &position, const wxString &title, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxCAPTION | wxCLOSE_BOX | wxSTAY_ON_TOP, const wxString &name = wxDialogNameStr);

        void Set(const ValueT &set);

        ValueT GetValue() const;
    };
}