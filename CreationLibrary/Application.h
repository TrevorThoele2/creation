#pragma once

#include <wx/wx.h>

#include "MainFrame.h"

namespace Creation
{
    class MainFrame;

    class Application final : public wxApp
    {
    public:
        bool OnInit() override;
        bool OnExceptionInMainLoop() override;
        void OnUnhandledException() override;
    private:
        std::shared_ptr<Atmos::Logging::Logger> logger;
        [[nodiscard]] static std::shared_ptr<Atmos::Logging::Logger> CreateLogger();
    private:
        MainFrame* mainFrame = nullptr;
        MainFrame* CreateMainFrame(const std::shared_ptr<Atmos::Logging::Logger>& logger);
    private:
        static void RegisterProperties();
        static void RegisterImageHandlers();
        static void SetupIdleEvent();
    private:
        void HandleException();
        bool TryCatch(const std::function<void()>& function);
    private:
        void OnMainFrameClose(wxCloseEvent& e);
    };
}