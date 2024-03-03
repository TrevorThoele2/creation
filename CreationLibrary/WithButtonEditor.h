#pragma once

#include <wx/propgrid/editors.h>

namespace Creation::Editing
{
    class WithButtonEditor : public wxPGTextCtrlEditor
    {
    public:
        using OnButton = std::function<void()>;
    public:
        WithButtonEditor() = default;

        void SetOnButton(const OnButton& onButton);
    public:
        wxPGWindowList CreateControls(
            wxPropertyGrid* grid,
            wxPGProperty* property,
            const wxPoint& position,
            const wxSize& size) const override;

        bool OnEvent(
            wxPropertyGrid* grid,
            wxPGProperty* property,
            wxWindow* window,
            wxEvent& event) const override;

        wxString GetName() const override;
    private:
        OnButton onButton;

        wxDECLARE_DYNAMIC_CLASS(WithButtonEditor);
    };
}