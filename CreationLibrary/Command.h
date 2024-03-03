#pragma once

#include "Event.h"

namespace Creation
{
    template<class... OutputArguments>
    class Command
    {
    public:
        using AlterState = std::function<void(OutputArguments...)>;
    public:
        Command();
        Command(AlterState alterState);

        void operator()(OutputArguments... arguments);

        void On(std::function<void()> function);
        void OnArguments(std::function<void(OutputArguments...)> function);
    private:
        AlterState alterState;
        Event<OutputArguments...> event;
    public:
        template<class... InputArguments>
        class Conversion
        {
        public:
            using Converter = std::function<std::tuple<OutputArguments...>(InputArguments...)>;
            using AlterState = std::function<void(OutputArguments...)>;
        public:
            Conversion(Converter converter);
            Conversion(Converter converter, AlterState alterState);

            void operator()(OutputArguments... arguments);

            void On(std::function<void()> function);
            void OnArguments(std::function<void(OutputArguments...)> function);
        private:
            Converter converter;
            AlterState alterState;
            Event<OutputArguments...> event;
        };
    };

    template<class... OutputArguments>
    Command<OutputArguments...>::Command() :
        alterState([](OutputArguments...) {})
    {}

    template<class... OutputArguments>
    Command<OutputArguments...>::Command(AlterState alterState) :
        alterState(alterState)
    {}

    template<class... OutputArguments>
    void Command<OutputArguments...>::operator()(OutputArguments... arguments)
    {
        alterState(arguments...);
        event(arguments...);
    }

    template<class... OutputArguments>
    void Command<OutputArguments...>::On(std::function<void()> function)
    {
        const auto subscriptionFunction = [function](OutputArguments...)
        {
            function();
        };

        event.Subscribe(subscriptionFunction);
    }

    template<class... OutputArguments>
    void Command<OutputArguments...>::OnArguments(std::function<void(OutputArguments...)> function)
    {
        event.Subscribe(function);
    }

    template<class... OutputArguments>
    template<class... InputArguments>
    Command<OutputArguments...>::Conversion<InputArguments...>::Conversion(Converter converter) :
        converter(converter), alterState([](OutputArguments...){})
    {}
    
    template<class... OutputArguments>
    template<class... InputArguments>
    Command<OutputArguments...>::Conversion<InputArguments...>::Conversion(Converter converter, AlterState alterState) :
        converter(converter), alterState(alterState)
    {}

    template<class... OutputArguments>
    template<class... InputArguments>
    void Command<OutputArguments...>::Conversion<InputArguments...>::operator()(OutputArguments ... arguments)
    {
        auto converted = converter(arguments...);
        std::apply(
            [this](auto&& ... convertedArgs)
            {
                alterState(convertedArgs...);
                event(convertedArgs...);
            }, std::move(converted));
    }

    template<class... OutputArguments>
    template<class... InputArguments>
    void Command<OutputArguments...>::Conversion<InputArguments...>::On(std::function<void()> function)
    {
        const auto subscriptionFunction = [function](OutputArguments...)
        {
            function();
        };

        event.Subscribe(subscriptionFunction);
    }

    template<class... OutputArguments>
    template<class... InputArguments>
    void Command<OutputArguments...>::Conversion<InputArguments...>::OnArguments(std::function<void(OutputArguments...)> function)
    {
        event.Subscribe(function);
    }

    template<>
    class Command<>
    {
    public:
        using AlterState = std::function<void()>;
    public:
        Command();
        Command(AlterState alterState);

        void operator()();

        void On(std::function<void()> function);
    private:
        AlterState alterState;
        Event<> event;
    };
}