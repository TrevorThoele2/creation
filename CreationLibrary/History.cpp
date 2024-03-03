#include "History.h"

namespace Creation::Editing
{
    void History::Push(const String& message, Function&& function)
    {
        GenerateRecord(message, std::move(function));

        records.back().function(true);
        onDo(HistoryArgs{ message });

        onChanged(this);
    }

    void History::Checkpoint(const String& message, Function&& function)
    {
        GenerateRecord(message, std::move(function));

        onChanged(this);
    }

    void History::Forward()
    {
        if (!CanForward())
            return;

        auto& record = *currentPosition;
        const auto sendMessage = record.message;
        record.function(true);
        ++currentPosition;

        onDo(HistoryArgs{ sendMessage });
        onChanged(this);
    }

    void History::Reverse()
    {
        if (!CanReverse())
            return;

        auto& record = *(currentPosition - 1);
        const auto sendMessage = record.message;
        record.function(false);
        --currentPosition;

        onUndo(HistoryArgs{ sendMessage });
        onChanged(this);
    }

    void History::Clear()
    {
        if (IsEmpty())
            return;

        records.clear();
        currentPosition = records.begin();
        onChanged(this);
    }

    bool History::CanForward() const
    {
        return !IsEmpty() && Position() < records.size();
    }

    bool History::CanReverse() const
    {
        return !IsEmpty() && Position() > 0;
    }

    auto History::Position() const -> size_t
    {
        if (IsEmpty())
            return 0;

        return currentPosition - records.begin();
    }

    void History::GenerateRecord(const String& message, Function&& function)
    {
        if (!records.empty() && currentPosition != records.end())
        {
            auto record = currentPosition;
            while (record != records.end())
                record = records.erase(record);
        }

        records.emplace_back(message, std::move(function));
        currentPosition = records.end();
    }

    bool History::IsEmpty() const
    {
        return records.empty();
    }
}