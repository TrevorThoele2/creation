
#include "Point.h"

namespace Creation
{
    Point::Point() : x(0), y(0)
    {}

    Point::Point(ValueT x, ValueT y) : x(x), y(y)
    {}

    Point::Point(const wxPoint &point) : x(point.x), y(point.y)
    {}

    Point::Point(const Atmos::Position2D &pos) : x(pos.GetX()), y(pos.GetY())
    {}

    bool Point::operator==(const Point &arg) const
    {
        return x == arg.x && y == arg.y;
    }

    bool Point::operator!=(const Point &arg) const
    {
        return !(*this == arg);
    }

    Point::operator wxPoint() const
    {
        return ToWxwidgets();
    }

    Point::operator Atmos::Position2D() const
    {
        return ToAtmos();
    }

    wxPoint Point::ToWxwidgets() const
    {
        return wxPoint(x, y);
    }

    Atmos::Position2D Point::ToAtmos() const
    {
        return Atmos::Position2D(x, y);
    }
}