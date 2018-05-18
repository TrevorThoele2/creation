#pragma once

#include <Atmos/LoggingSink.h>

#include "OutputView.h"
#include <wx/statusbr.h>

namespace Creation
{
    class LoggingSink final : public Atmos::Logging::Sink
    {
    public:
        LoggingSink(OutputView& outputView, wxStatusBar& statusBar);

        void Log(const Atmos::Logging::Log& log) override;
        void Flush();
    private:
        OutputView* outputView = nullptr;
        wxStatusBar* statusBar = nullptr;
    };
}