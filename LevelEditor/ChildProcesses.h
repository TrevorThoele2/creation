#pragma once

#include <vector>
#include <Atmos/WindowsInclude.h>

namespace Creation
{
    class ChildProcesses
    {
    private:
        class Process
        {
        public:
            bool reenableFrame;
            PROCESS_INFORMATION processInfo;
            Process(bool reenableFrame, const PROCESS_INFORMATION &processInfo);
        };
    private:
        std::vector<Process> processes;

        ChildProcesses() = default;
        ChildProcesses(const ChildProcesses &arg) = delete;
        ChildProcesses& operator=(const ChildProcesses &arg) = delete;
    public:
        static ChildProcesses& Instance();
        static void Work();
        static void Manage(bool reenableFrame, const PROCESS_INFORMATION &processInfo);
    };
}