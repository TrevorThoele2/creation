#include "TerrainRoot.h"

namespace Creation::Editing::Data
{
    TerrainRoot::TerrainRoot(Input& input) :
        Root(input.visible, *input.nexusHistory),
        terrain(*input.terrain, nullptr, *input.nexusHistory, *input.ui, *input.reliquary, "Terrain")
    {}

    std::vector<SequenceNexusBase*> TerrainRoot::TopNexi()
    {
        return std::vector<SequenceNexusBase*>
        {
            &terrain
        };
    }
}