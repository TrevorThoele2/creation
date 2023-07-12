
#include "Application.h"
#include "MainFrame.h"

//#include <vld.h>

namespace Creation
{
    bool Application::OnInit()
    {
        new MainFrame(wxPoint(), wxSize(1024, 768));
        auto mainFrame = GetMainFrame();
        SetTopWindow(mainFrame);
        mainFrame->SetMinClientSize(wxSize(640, 480));
        mainFrame->Show(true);
        mainFrame->Center();
        return true;
    }

    bool Application::OnExceptionInMainLoop()
    {
        try
        {
            std::rethrow_exception(std::current_exception());
        }
        catch (const std::exception& e)
        {
            GetMainFrame()->OutputMessage(String("Exception.\n") + e.what());
        }
        catch (...)
        {
            GetMainFrame()->OutputMessage("Exception.");
        }

        return true;
    }

    Application* GetApplication()
    {
        return static_cast<Application*>(wxApp::GetInstance());
    }
}