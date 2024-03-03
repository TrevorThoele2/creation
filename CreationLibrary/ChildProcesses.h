#pragma once

#include <SDKDDKVer.h>
#include <boost/process.hpp>

#include "String.h"
#include "FilePath.h"
#include <list>

#include <Atmos/Logger.h>

namespace Creation
{
    class ChildProcesses
    {
    public:
        using OnExit = std::function<void()>;
    public:
        ChildProcesses(Atmos::Logging::Logger& logger);
        ChildProcesses(const ChildProcesses& arg) = delete;
        ChildProcesses(ChildProcesses&& arg) noexcept = default;

        void Create(const File::Path& execute, std::vector<String> commands, OnExit onExit);
        void Work();
    private:
        struct Child
        {
            boost::process::child process;
            OnExit onExit;
            Child(boost::process::child&& process, OnExit&& onExit);
        };

        std::list<Child> children {};
    private:
        Atmos::Logging::Logger* logger;
    };
}