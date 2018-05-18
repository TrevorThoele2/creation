#pragma once

#include "EditingMode.h"

namespace Creation::Editing
{
    class NullMode final : public Mode
    {
    public:
        NullMode(NexusSelection& nexusSelection, NexusHistory nexusHistory);
    };
}