#pragma once

#include <wx/dialog.h>
#include <wx/listbox.h>
#include "String.h"
#include "Optional.h"

namespace Creation
{
    class StringSelectionDialog : public wxDialog
    {
    public:
        typedef std::vector<String> StringVector;
    private:
        wxListBox *list;

        void CreateWidgets();
        void SetWidgets(const StringVector &set);
    public:
        StringSelectionDialog(wxWindow *parent, const wxString &title, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxSize(400, 300), long style = wxCAPTION | wxCLOSE_BOX | wxSTAY_ON_TOP, const wxString &name = wxDialogNameStr);
    
        void Set(const StringVector &set);

        Optional<String> GetSelected() const;
    };
}