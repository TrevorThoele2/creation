#include "EntitiesRoot.h"

namespace Creation::Editing::Data
{
    EntitiesRoot::EntitiesRoot(Input& input) :
        Root(input.visible, *input.nexusHistory),
        entities(*input.entities, nullptr, *input.nexusHistory, *input.ui, *input.reliquary, "Entities")
    {}

    std::vector<SequenceNexusBase*> EntitiesRoot::TopNexi()
    {
        return std::vector<SequenceNexusBase*>
        {
            &entities
        };
    }
}