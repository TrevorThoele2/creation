#pragma once

#include <vector>
#include <memory>
#include <Atmos/Event.h>

namespace Creation
{
    namespace Command
    {
        class ICommand;
        class Stack
        {
        public: typedef unsigned int Count;
        private:
            typedef std::unique_ptr<ICommand> CommandPtr;
            typedef std::vector<CommandPtr> Commands;
            Commands stack;
            // 0 is one before the first element
            Commands::size_type curPos;

            Stack();
            Stack(const Stack &arg) = delete;
            Stack& operator=(const Stack &arg) = delete;
            static void UpdateStatus(ICommand &command, bool forward);
        public:
            Atmos::NullEvent onChanged;

            static Stack& Instance();
            template<class CommandT, class... Args>
            static void Create(Args && ... args);
            // Expects heap memory
            // Will execute the command
            static void Push(ICommand &add);
            // 0 counts as 1
            static void Undo(Count count = 1);
            // 0 counts as 1
            static void Redo(Count count = 1);
            static void Clear();
        };

        template<class CommandT, class... Args>
        void Stack::Create(Args && ... args)
        {
            Push(*new CommandT(std::forward<Args>(args)...));
        }
    }
}