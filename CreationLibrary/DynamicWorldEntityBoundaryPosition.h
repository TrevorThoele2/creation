#pragma once

#include "EntityBoundaryPosition.h"

namespace Creation::Editing
{
    class DynamicWorldEntityBoundaryPosition final
    {
    public:
        using Value = EntityBoundaryPosition::Value;
        using Status = EntityBoundaryPosition::Status;

        struct Data
        {
            Value x;
            Value y;

            std::optional<Status> status;

            Data(Value x, Value y, std::optional<Status> status = {}) : x(x), y(y), status(status)
            {}
        };
    public:
        DynamicWorldEntityBoundaryPosition(Arca::Reliquary& reliquary);
        DynamicWorldEntityBoundaryPosition(DynamicWorldEntityBoundaryPosition&& arg) noexcept = default;
        ~DynamicWorldEntityBoundaryPosition();
        DynamicWorldEntityBoundaryPosition& operator=(DynamicWorldEntityBoundaryPosition&& arg) noexcept = default;

        [[nodiscard]] operator bool() const;

        void Create(Data data);
        void Destroy();
        void Refresh(Data data);
    private:
        using Object = EntityBoundaryPosition;
        using Index = Arca::Index<Object>;

        Index object;
    private:
        Arca::Reliquary* reliquary;

        Arca::MutablePointer MutablePointer();
    };
}