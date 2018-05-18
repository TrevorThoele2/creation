#include "EntityBoundaryPosition.h"

namespace Creation::Editing
{
    EntityBoundaryPosition::EntityBoundaryPosition(
        Value x, Value y, std::optional<Status> status)
        :
        x(x),
        y(y),
        status(status)
    {}

    EntityBoundaryPosition::operator Atmos::Spatial::Grid::Point() const
    {
        return Atmos::Spatial::Grid::Point{ x, y };
    }
}