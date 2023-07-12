#pragma once

namespace Creation
{
    class Rectangle
    {
    public: typedef int ValueT;
    public:
        ValueT left, top, right, bottom;
        Rectangle();
        Rectangle(ValueT left, ValueT top, ValueT right, ValueT bottom);
        bool operator==(const Rectangle &arg) const;
        bool operator!=(const Rectangle &arg) const;
        void Edit(ValueT left, ValueT top, ValueT right, ValueT bottom);
    };
}