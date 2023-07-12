#pragma once

namespace Creation
{
    template<class T>
    class Vector2
    {
    public:
        T first, second;
        Vector2(T first, T second) : first(first), second(second) {}
    };
}