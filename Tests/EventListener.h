#pragma once

#include <Chroma/Event.h>

template<class... Args>
class EventListener
{
public:
    using Execution = std::tuple<Args...>;
    using ExecutionList = std::vector<Execution>;
public:
    explicit EventListener(Chroma::Event<Args...>& event);

    [[nodiscard]] const ExecutionList& Executions() const;
private:
    ExecutionList executions;

    void On(Args&& ... args);
};

template<class... Args>
EventListener<Args...>::EventListener(Chroma::Event<Args...>& event)
{
    event.Subscribe([this](Args&& ... args) { this->On(std::forward<Args>(args)...); });
}

template<class... Args>
auto EventListener<Args...>::Executions() const -> const ExecutionList&
{
    return executions;
}

template<class... Args>
void EventListener<Args...>::On(Args&& ... args)
{
    executions.push_back(std::forward_as_tuple(std::forward<Args>(args)...));
}