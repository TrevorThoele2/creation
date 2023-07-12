
#include "Rectangle.h"

namespace Creation
{
    Rectangle::Rectangle() : left(0), top(0), right(0), bottom(0)
    {}

    Rectangle::Rectangle(ValueT left, ValueT top, ValueT right, ValueT bottom) : left(left), top(top), right(right), bottom(bottom)
    {}

    bool Rectangle::operator==(const Rectangle &arg) const
    {
        return left == arg.left && top == arg.top && right == arg.right && bottom == arg.bottom;
    }

    bool Rectangle::operator!=(const Rectangle &arg) const
    {
        return !(*this == arg);
    }

    void Rectangle::Edit(ValueT left, ValueT top, ValueT right, ValueT bottom)
    {
        this->left = left;
        this->top = top;
        this->right = right;
        this->bottom = bottom;
    }
}