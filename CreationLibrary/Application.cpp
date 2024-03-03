#include "Application.h"

#include "MainFrame.h"

#include "StringButtonProperty.h"

#include <Atmos/FileLoggingSink.h>
#include <Chroma/DetailedException.h>

#ifdef CREATION_DEBUG
    #include <vld.h>
#endif

namespace Creation
{
    bool Application::OnInit()
    {
        const auto result = TryCatch(
            [this]
            {
                logger = CreateLogger();
                RegisterProperties();
                RegisterImageHandlers();
                mainFrame = CreateMainFrame(logger);
                mainFrame->Bind(wxEVT_CLOSE_WINDOW, &Application::OnMainFrameClose, this);
            });

        return !result;
    }

    bool Application::OnExceptionInMainLoop()
    {
        HandleException();
        return true;
    }

    void Application::OnUnhandledException()
    {
        HandleException();
    }

    std::shared_ptr<Atmos::Logging::Logger> Application::CreateLogger()
    {
        auto created = std::make_shared<Atmos::Logging::Logger>(Atmos::Logging::Severity::Verbose);
        created->AddSink<Atmos::Logging::FileSink>();
        return created;
    }

    MainFrame* Application::CreateMainFrame(const std::shared_ptr<Atmos::Logging::Logger>& logger)
    {
        auto mainFrame = new MainFrame(wxPoint(), wxSize(1024, 768), logger);
        mainFrame->SetMinClientSize(wxSize(640, 480));
        mainFrame->Show(true);
        mainFrame->Center();
        return mainFrame;
    }

    void Application::RegisterProperties()
    {
        wxPGEditor* stringButtonProperty = new StringButtonProperty();
        wxPropertyGrid::RegisterEditorClass(stringButtonProperty);
    }

    void Application::RegisterImageHandlers()
    {
        wxImage::AddHandler(new wxPNGHandler);
    }

    void Application::SetupIdleEvent()
    {
        wxIdleEvent::SetMode(wxIDLE_PROCESS_SPECIFIED);
    }

    void Application::HandleException()
    {
        TryCatch([] { std::rethrow_exception(std::current_exception()); });
    }

    bool Application::TryCatch(const std::function<void()>& function)
    {
        try
        {
            function();
        }
        catch (const Chroma::DetailedException& e)
        {
            logger->Log(
                e.what(),
                Atmos::Logging::Severity::Error,
                e.Details());
            return true;
        }
        catch (const std::exception& e)
        {
            logger->Log(
                e.what(),
                Atmos::Logging::Severity::Error);
            return true;
        }
        catch (...)
        {
            logger->Log(
                "Unknown error.",
                Atmos::Logging::Severity::Error);
            return true;
        }

        return false;
    }

    void Application::OnMainFrameClose(wxCloseEvent& e)
    {
        logger.reset();
        mainFrame->Destroy();
    }
}