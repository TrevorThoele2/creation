#pragma once

#include <wx/dialog.h>
#include <wx/listbox.h>

#include <optional>
#include "String.h"

namespace Creation
{
    class SelectAssetDialog final : public wxDialog
    {
    public:
        SelectAssetDialog(
            const std::vector<String>& choices,
            wxWindow* parent,
            const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxSize(400, 300),
            long style = wxCAPTION | wxCLOSE_BOX | wxSTAY_ON_TOP,
            const wxString& name = wxDialogNameStr);

        [[nodiscard]] std::optional<String> Selected() const;
    private:
        wxListBox* listbox;
    };
}