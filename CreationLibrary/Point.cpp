#include "Point.h"

namespace Creation
{
    bool Point::operator==(const Point& arg) const
    {
        return x == arg.x && y == arg.y;
    }

    bool Point::operator!=(const Point& arg) const
    {
        return !(*this == arg);
    }

    Point::operator wxPoint() const
    {
        return ToWxwidgets();
    }

    Point::operator Atmos::Spatial::Point2D() const
    {
        return ToAtmos();
    }

    wxPoint Point::ToWxwidgets() const
    {
        return wxPoint(x, y);
    }

    Atmos::Spatial::Point2D Point::ToAtmos() const
    {
        return Atmos::Spatial::Point2D
        {
            static_cast<Atmos::Spatial::Point2D::Value>(x),
            static_cast<Atmos::Spatial::Point2D::Value>(y)
        };
    }
}