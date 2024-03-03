#include "EntityBoundaryRoot.h"

namespace Creation::Editing::Data
{
    EntityBoundaryRoot::EntityBoundaryRoot(Input& input) :
        Root(input.visible, *input.nexusHistory),
        entityBoundary(*input.entityBoundary, nullptr, *input.nexusHistory, *input.ui, *input.reliquary, "Entity Boundary")
    {}

    std::vector<SequenceNexusBase*> EntityBoundaryRoot::TopNexi()
    {
        return std::vector<SequenceNexusBase*>
        {
            &entityBoundary
        };
    }
}