#include "Rectangle.h"

namespace Creation
{
    bool Rectangle::operator==(const Rectangle &arg) const
    {
        return left == arg.left && top == arg.top && right == arg.right && bottom == arg.bottom;
    }

    bool Rectangle::operator!=(const Rectangle &arg) const
    {
        return !(*this == arg);
    }
}