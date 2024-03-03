#include "LoggingSink.h"

namespace Creation
{
    LoggingSink::LoggingSink(OutputView& outputView, wxStatusBar& statusBar) :
        outputView(&outputView), statusBar(&statusBar)
    {}

    void LoggingSink::Log(const Atmos::Logging::Log& log)
    {
        const auto outputViewMessage = StandardFormattedLog(log);
        outputView->OutputMessage(outputViewMessage);

        const auto statusBarMessage = log.message;
        statusBar->SetStatusText(statusBarMessage);
    }

    void LoggingSink::Flush()
    {}
}