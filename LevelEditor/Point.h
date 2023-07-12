#pragma once

#include <wx/gdicmn.h> // For wxPoint
#include <Atmos/Position2D.h> // For Atmos::Position2D

namespace Creation
{
    class Point
    {
    public:
        typedef double ValueT;
    public:
        ValueT x, y;
        Point();
        Point(ValueT x, ValueT y);
        Point(const wxPoint &point);
        Point(const Atmos::Position2D &pos);
        Point(const Point &arg) = default;
        Point& operator=(const Point &arg) = default;
        bool operator==(const Point &arg) const;
        bool operator!=(const Point &arg) const;
        explicit operator wxPoint() const;
        explicit operator Atmos::Position2D() const;

        wxPoint ToWxwidgets() const;
        Atmos::Position2D ToAtmos() const;
    };
}