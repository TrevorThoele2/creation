#pragma once

#include <Atmos/Point2D.h>

namespace Creation::Editing
{
    class Mode;

    class Tool
    {
    public:
        virtual ~Tool() = 0;

        virtual void OnLeftMouseDown(const Atmos::Spatial::Point2D& position, Mode& mode);
        virtual void OnLeftMouseUp(const Atmos::Spatial::Point2D& position, Mode& mode);
        virtual void OnRightMouseDown(const Atmos::Spatial::Point2D& position, Mode& mode);
        virtual void OnRightMouseUp(const Atmos::Spatial::Point2D& position, Mode& mode);
        virtual void OnMouseMoved(const Atmos::Spatial::Point2D& position, Mode& mode);
    };
}