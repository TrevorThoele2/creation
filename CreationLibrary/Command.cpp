#include "Command.h"

namespace Creation
{
    Command<>::Command() : alterState([](){})
    {}

    Command<>::Command(AlterState alterState) : alterState(std::move(alterState))
    {}

    void Command<>::operator()()
    {
        alterState();
        event();
    }

    void Command<>::On(std::function<void()> function)
    {
        event.Subscribe(function);
    }
}