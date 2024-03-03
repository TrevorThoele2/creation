#include "GhostWorldElementBase.h"

namespace Creation::Editing
{
    GhostWorldElementBase::~GhostWorldElementBase() = default;

    void GhostWorldElementBase::MoveBy(const Atmos::Spatial::Point2D& to)
    {
        MoveByImpl(to);
    }
}