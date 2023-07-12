
#pragma once

#include <wx/stattext.h>
#include <wx/scrolwin.h>

namespace Creation
{
    // Readonly scrolled text window
    class ScrolledTextWindow : public wxScrolledWindow
    {
    private:
        std::string output;
        wxStaticText *text;

        void MakeStaticText();
    public:
        ScrolledTextWindow(wxWindow *parent, wxWindowID id, const wxString &label = wxEmptyString, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxHSCROLL | wxVSCROLL | wxALWAYS_SHOW_SB, const wxString &name = "ScrolledTextWindow");
        void SetText(const std::string &set);
        void AppendText(const std::string &append);
        void ClearText();
    };
}