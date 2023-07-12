#pragma once

#include <wx/dialog.h>
#include <Atmos/FieldID.h>

class wxTextCtrl;
namespace Creation
{
    class WorldStartDialog : public wxDialog
    {
    private:
        wxTextCtrl *fieldText;
    public:
        WorldStartDialog(::Atmos::FieldID fieldID, wxWindow *parent, wxWindowID windowID);
        ::Atmos::FieldID GetFieldID() const;
    };
}