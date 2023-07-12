#pragma once

namespace Creation
{
    template<class Mixin>
    class Singleton
    {
    protected:
        Singleton() = default;
        Singleton(const Singleton &arg) = default;
        Singleton& operator=(const Singleton &arg) = default;
    public:
        static Mixin& Instance()
        {
            static Mixin instance;
            return instance;
        }
    };
}