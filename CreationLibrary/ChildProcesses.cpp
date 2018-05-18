#include "ChildProcesses.h"

#include "Application.h"
#include "MainFrame.h"

#include <Chroma/StringUtility.h>

namespace Creation
{
    ChildProcesses::ChildProcesses(Atmos::Logging::Logger& logger) : logger(&logger)
    {}

    void ChildProcesses::Create(const File::Path& execute, std::vector<String> commands, OnExit onExit)
    {
        auto startDirectory = execute;
        startDirectory.remove_filename();

        boost::process::ipstream outStream;
        boost::process::ipstream errorStream;

        children.emplace_back(
            boost::process::child(
                execute.string(),
                commands,
                boost::process::start_dir(startDirectory.string()),
                boost::process::std_out > outStream,
                boost::process::std_err > errorStream),
            std::move(onExit));

        logger->Log(Atmos::Logging::Log{
            "Child process started.",
            {{ "ID", Chroma::ToString(children.back().process.id()) }} });
    }

    void ChildProcesses::Work()
    {
        for (auto child = children.begin(); child != children.end();)
        {
            if (!child->process.running())
            {
                if (child->onExit)
                    child->onExit();

                logger->Log(Atmos::Logging::Log{
                    "Child process exited.",
                    {
                        { "ID", Chroma::ToString(child->process.id()) },
                        { "Exit Code", Chroma::ToString(child->process.exit_code()) },
                        { "Native Exit Code", Chroma::ToString(child->process.native_exit_code()) }
                    } });

                child = children.erase(child);
            }
            else
                ++child;
        }
    }

    ChildProcesses::Child::Child(boost::process::child&& process, OnExit&& onExit) :
        process(std::move(process)), onExit(std::move(onExit))
    {}
}