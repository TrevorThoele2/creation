#include "EntityRenderInformationCurator.h"

namespace Creation
{
    EntityRenderInformationCurator::EntityRenderInformationCurator(Init init) :
        Curator(init), rendering(init.owner.Find<EntityRenderInformation>())
    {}

    void EntityRenderInformationCurator::Handle(const InitializeEntityRenderInformation& command)
    {
        MutablePointer().Of(rendering)->asset = command.asset;
    }
}