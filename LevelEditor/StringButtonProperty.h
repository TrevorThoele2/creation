#pragma once

#include <vector>

#include "String.h"
#include "Event.h"

#include <wx/window.h>
#include <wx/propgrid/editors.h>
class wxTextCtrl;

namespace Creation
{
    // Property representing a string that has an additional button for a dialog to open and select a string from a list
    class StringButtonProperty : public wxPGTextCtrlEditor
    {
    public:
        typedef std::vector<String> StringVector;
    private:
        wxDECLARE_DYNAMIC_CLASS(StringButtonProperty);
    private:
        std::vector<String> strings;
    public:
        mutable Event<const String&> onChanged;

        StringButtonProperty() = default;
        virtual ~StringButtonProperty() {}

        wxString GetName() const override final;
        wxPGWindowList CreateControls(wxPropertyGrid *propGrid, wxPGProperty *property, const wxPoint &pos, const wxSize &sz) const override final;
        bool OnEvent(wxPropertyGrid *propGrid, wxPGProperty *property, wxWindow *ctrl, wxEvent &event) const override final;

        void AddString(const String &add);
        void AddString(String &&add);
        void SetStrings(StringVector &&set);
    };
}