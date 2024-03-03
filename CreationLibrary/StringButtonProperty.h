#pragma once

#include <vector>

#include "String.h"

#include <wx/window.h>
#include <wx/propgrid/editors.h>

namespace Creation
{
    class StringButtonProperty final : public wxPGTextCtrlEditor
    {
    public:
        StringButtonProperty();
        virtual ~StringButtonProperty();

        [[nodiscard]] wxString GetName() const override;
        wxPGWindowList CreateControls(
            wxPropertyGrid* propGrid,
            wxPGProperty* property,
            const wxPoint& pos,
            const wxSize& size) const override;
        bool OnEvent(
            wxPropertyGrid* propGrid,
            wxPGProperty* property,
            wxWindow* ctrl,
            wxEvent& event) const override;

        void AddString(const String& add);
        void AddString(String&& add);
        void SetStrings(std::vector<String>&& set);
    private:
        std::vector<String> stringList;
    private:
        wxDECLARE_DYNAMIC_CLASS(StringButtonProperty);
    };
}