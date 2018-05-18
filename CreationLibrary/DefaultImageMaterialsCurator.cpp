#include "DefaultImageMaterialsCurator.h"

#include "DefaultImageMaterials.h"

namespace Creation
{
    DefaultImageMaterialsCurator::DefaultImageMaterialsCurator(Init init) : Curator(init)
    {}

    void DefaultImageMaterialsCurator::Handle(const ChangeDefaultImageMaterials& command)
    {
        auto change = MutablePointer().Of<DefaultImageMaterials>();
        change->material = command.material;
        change->selected = command.selected;
        change->ghost = command.ghost;
    }
}