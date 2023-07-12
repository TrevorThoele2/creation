
#include <wx/sizer.h>
#include "ScrolledTextWindow.h"

namespace Creation
{
    void ScrolledTextWindow::MakeStaticText()
    {
        auto sizer = GetSizer();
        sizer->Clear(true);

        text = new wxStaticText(this, wxID_ANY, output);
        sizer->Add(text, 1, wxEXPAND);

        SetScrollRate(5, 5);
        FitInside();
    }

    ScrolledTextWindow::ScrolledTextWindow(wxWindow *parent, wxWindowID id, const wxString &label, const wxPoint &pos, const wxSize &size, long style, const wxString &name) : wxScrolledWindow(parent, id, pos, size, style, name)
    {
        SetSizer(new wxBoxSizer(wxVERTICAL));
        if (label != wxEmptyString)
        {
            output = label;
            MakeStaticText();
        }

        SetScrollRate(5, 5);
        FitInside();
    }

    void ScrolledTextWindow::SetText(const std::string &set)
    {
        output = set;
        MakeStaticText();
    }

    void ScrolledTextWindow::AppendText(const std::string &append)
    {
        output += append;
        MakeStaticText();
    }

    void ScrolledTextWindow::ClearText()
    {
        output.clear();
        GetSizer()->Clear(true);
        text = nullptr;
    }
}