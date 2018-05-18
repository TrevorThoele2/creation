#pragma once

#include <Atmos/Point2D.h>

namespace Creation::Editing
{
    class GhostWorldElementBase
    {
    public:
        virtual ~GhostWorldElementBase() = 0;

        void MoveBy(const Atmos::Spatial::Point2D& to);
    protected:
        virtual void MoveByImpl(const Atmos::Spatial::Point2D& by) = 0;
    };
}