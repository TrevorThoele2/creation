#pragma once

#include <optional>
#include <wx/dialog.h>
#include <wx/listbox.h>
#include "String.h"

namespace Creation
{
    class StringSelectionDialog final : public wxDialog
    {
    public:
        StringSelectionDialog(
            wxWindow* parent,
            const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxSize(400, 300),
            long style = wxCAPTION | wxCLOSE_BOX | wxSTAY_ON_TOP,
            const wxString& name = wxDialogNameStr);
    
        void Set(const std::vector<String>& set);

        [[nodiscard]] std::optional<String> GetSelected() const;
    private:
        wxListBox* list;

        void CreateWidgets();
        void SetWidgets(const std::vector<String>& set);
    };
}