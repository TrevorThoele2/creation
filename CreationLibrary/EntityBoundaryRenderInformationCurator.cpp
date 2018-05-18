#include "EntityBoundaryRenderInformationCurator.h"

namespace Creation
{
    EntityBoundaryRenderInformationCurator::EntityBoundaryRenderInformationCurator(Init init) :
        Curator(init), information(init.owner.Find<EntityBoundaryRenderInformation>())
    {}

    void EntityBoundaryRenderInformationCurator::Handle(const InitializeEntityBoundaryRenderInformation& command)
    {
        auto mutableInformation = MutablePointer().Of(information);
        mutableInformation->standardMaterial = command.standardMaterial;
        mutableInformation->selectedMaterial = command.selectedMaterial;
        mutableInformation->ghostMaterial = command.ghostMaterial;
    }
}