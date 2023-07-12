
#include "Application.h"
#include "MainFrame.h"
#include "ChildProcesses.h"

namespace Creation
{
    ChildProcesses::Process::Process(bool reenableFrame, const PROCESS_INFORMATION &processInfo) : reenableFrame(reenableFrame), processInfo(processInfo)
    {}

    ChildProcesses& ChildProcesses::Instance()
    {
        static ChildProcesses instance;
        return instance;
    }

    void ChildProcesses::Work()
    {
        bool attemptFocus(!Instance().processes.empty());

        for (auto loop = Instance().processes.begin(); loop != Instance().processes.end();)
        {
            DWORD result = WaitForSingleObject(loop->processInfo.hProcess, 0);
            if (result == WAIT_OBJECT_0)
            {
                if (loop->reenableFrame)
                    GetMainFrame()->Enable();

                CloseHandle(loop->processInfo.hProcess);
                CloseHandle(loop->processInfo.hThread);
                loop = Instance().processes.erase(loop);
            }
            else
                ++loop;
        }

        if (attemptFocus && Instance().processes.empty())
            GetMainFrame()->Raise();
    }

    void ChildProcesses::Manage(bool reenableFrame, const PROCESS_INFORMATION &processInfo)
    {
        Instance().processes.push_back(Process(reenableFrame, processInfo));
    }
}