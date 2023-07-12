#pragma once

#include <wx/wx.h>

namespace Creation
{
    class Application : public wxApp
    {
    public:
        bool OnInit() override;
        bool OnExceptionInMainLoop() override;
    };

    Application* GetApplication();
}