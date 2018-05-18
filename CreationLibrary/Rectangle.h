#pragma once

namespace Creation
{
    struct Rectangle
    {
        using Value = int;
        Value left, top, right, bottom;

        bool operator==(const Rectangle &arg) const;
        bool operator!=(const Rectangle &arg) const;
    };
}