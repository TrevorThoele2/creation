
#include "Application.h"
#include "MainFrame.h"
#include "CommandStack.h"
#include "Command.h"

namespace Creation
{
    namespace Command
    {
        Stack::Stack() : curPos(0)
        {}

        void Stack::UpdateStatus(ICommand &command, bool forward)
        {
            MainFrame *mainFrame = GetMainFrame();
            auto outputMessage = command.GetOutputMessage();
            if(forward)
                mainFrame->SetStatusText(outputMessage + " done");
            else
                mainFrame->SetStatusText(outputMessage + " undone");
        }

        Stack& Stack::Instance()
        {
            static Stack instance;
            return instance;
        }

        void Stack::Push(ICommand &add)
        {
            auto &curPos = Instance().curPos;
            auto &stack = Instance().stack;

            if (!stack.empty() && curPos != stack.size())
            {
                Commands::iterator loop = stack.begin() + curPos;
                while (loop != stack.end())
                    loop = stack.erase(loop);
            }

            auto movePos = stack.empty();
            if (!movePos)
                movePos = (curPos == stack.size());

            stack.push_back(CommandPtr(&add));
            stack.back()->Do();
            UpdateStatus(*stack.back(), true);

            if (movePos)
                curPos = stack.size();

            Instance().onChanged();
        }

        void Stack::Undo(Count count)
        {
            auto &stack = Instance().stack;
            auto &curPos = Instance().curPos;
            if (stack.empty() || curPos == 0)
                return;

            if (count == 0)
                count = 1;

            auto loop = stack.begin() + (curPos - 1);
            auto countLeft = count;
            while (countLeft > 0)
            {
                (*loop)->Undo();
                UpdateStatus(**loop, false);
                --curPos;
                if (loop == stack.begin())
                    break;

                --loop;
                --countLeft;
            }

            Instance().onChanged();
        }

        void Stack::Redo(Count count)
        {
            auto &stack = Instance().stack;
            auto &curPos = Instance().curPos;
            if (stack.empty() || curPos == stack.size())
                return;

            if (count == 0)
                count = 1;

            auto loop = stack.begin() + curPos;
            auto countLeft = count;
            while (countLeft > 0)
            {
                (*loop)->Do();
                UpdateStatus(**loop, true);
                ++curPos;
                if (loop == stack.end())
                    break;

                ++loop;
                --countLeft;
            }

            Instance().onChanged();
        }

        void Stack::Clear()
        {
            Instance().stack.clear();
            Instance().curPos = 0;
        }
    }
}