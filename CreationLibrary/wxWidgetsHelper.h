#pragma once

#include <wx/window.h>
#include <wx/statbox.h>
#include <wx/sizer.h>

#include "Direction.h"

namespace Creation
{
    // Creates a static box for the widget
    template<class WindowT>
    WindowT* CreateStaticBox(
        wxWindow* parent,
        wxWindowID id,
        const std::string& label,
        wxSizer* sizerAddBoxTo,
        int proportion = 0,
        int flags = 0,
        int border = 0,
        bool expandWindow = true)
    {
        auto box = new wxStaticBoxSizer(new wxStaticBox(parent, wxID_ANY, label), wxVERTICAL);
        sizerAddBoxTo->Add(box, proportion, flags, border);

        auto newWindow = new WindowT(box->GetStaticBox(), id);
        expandWindow ?  box->Add(newWindow, 1, wxEXPAND) : box->Add(newWindow);
        return newWindow;
    }

    // Creates a static box for the widget
    template<class WindowT, class... Args>
    WindowT* CreateStaticBox(
        wxWindow* parent,
        wxWindowID id,
        const std::string& label,
        wxSizer* sizerAddBoxTo,
        int proportion,
        int flags,
        int border,
        bool expandWindow,
        Args && ... args)
    {
        auto box = new wxStaticBoxSizer(new wxStaticBox(parent, wxID_ANY, label), wxVERTICAL);
        sizerAddBoxTo->Add(box, proportion, flags, border);

        auto newWindow = new WindowT(box->GetStaticBox(), id, std::forward<Args>(args)...);
        expandWindow ? box->Add(newWindow, 1, wxEXPAND) : box->Add(newWindow);
        return newWindow;
    }

    // Allows a window/sizer to expand along the primary direction for box sizers without expanding along the secondary
    // PrimaryDirection must match the direction that you want to expand along
    template<class T>
    void TransverseExpand(Direction primaryDirection, wxSizer* sizer, T* add)
    {
        const auto useDirection = primaryDirection == Direction::Horizontal
            ? wxVERTICAL
            : wxHORIZONTAL;
        auto tempSizer = new wxBoxSizer(useDirection);
        sizer->Add(tempSizer, 1, wxEXPAND);
        tempSizer->Add(add, 0, wxEXPAND);
    }
}