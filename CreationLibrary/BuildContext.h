#pragma once

#include <Arca/Reliquary.h>

namespace Creation::Build
{
    class Context
    {
    public:
        explicit Context(Arca::Reliquary& reliquary);

        Arca::Reliquary& reliquary;
    };
}