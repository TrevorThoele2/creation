#pragma once

#include <vector>

#include "String.h"

#include <Atmos/Event.h>

#include <function2/function2.hpp>

namespace Creation::Editing
{
    struct HistoryArgs
    {
        const String message;
    };

    class History
    {
    public:
        using Function = fu2::unique_function<void(bool)>;
    public:
        Atmos::Event<HistoryArgs> onDo;
        Atmos::Event<HistoryArgs> onUndo;
        Atmos::Event<History*> onChanged;
    public:
        History() = default;
        History(const History& arg) = delete;
        History& operator=(const History& arg) = delete;

        void Push(const String& message, Function&& function);
        void Checkpoint(const String& message, Function&& function);
        void Forward();
        void Reverse();
        void Clear();

        [[nodiscard]] bool CanForward() const;
        [[nodiscard]] bool CanReverse() const;

        [[nodiscard]] size_t Position() const;
    private:
        struct Record
        {
            String message;
            Function function;
            Record(const String& message, Function&& function) :
                message(message), function(std::move(function))
            {}
        };

        using Records = std::vector<Record>;
        Records records;
        Records::iterator currentPosition;

        void GenerateRecord(const String& message, Function&& function);

        [[nodiscard]] bool IsEmpty() const;
    };
}