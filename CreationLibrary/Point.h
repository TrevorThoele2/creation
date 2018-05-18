#pragma once

#include <wx/gdicmn.h>
#include <Atmos/Point2D.h>

namespace Creation
{
    struct Point
    {
        using Value = double;
        Value x = 0, y = 0;

        bool operator==(const Point& arg) const;
        bool operator!=(const Point& arg) const;

        explicit operator wxPoint() const;
        explicit operator Atmos::Spatial::Point2D() const;

        [[nodiscard]] wxPoint ToWxwidgets() const;
        [[nodiscard]] Atmos::Spatial::Point2D ToAtmos() const;
    };
}