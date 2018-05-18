#pragma once

#include <list>
#include "SequenceNexusCommon.h"

namespace Creation::Editing
{
    template<class T>
    class Nexus<std::list<T>> final : public SequenceNexusCommon<T>
    {
    public:
        using SequenceNexusCommon<T>::SequenceNexusCommon;
    };
}