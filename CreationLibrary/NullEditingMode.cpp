#include "NullEditingMode.h"

namespace Creation::Editing
{
    NullMode::NullMode(NexusSelection& nexusSelection, NexusHistory nexusHistory) :
        Mode(nexusSelection, nexusHistory)
    {}
}