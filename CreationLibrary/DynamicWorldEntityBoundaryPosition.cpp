#include "DynamicWorldEntityBoundaryPosition.h"

#include "MutationCurator.h"

#include <Arca/Create.h>
#include <Arca/Destroy.h>

namespace Creation::Editing
{
    DynamicWorldEntityBoundaryPosition::DynamicWorldEntityBoundaryPosition(Arca::Reliquary& reliquary) :
        reliquary(&reliquary)
    {}

    DynamicWorldEntityBoundaryPosition::~DynamicWorldEntityBoundaryPosition()
    {
        Destroy();
    }

    DynamicWorldEntityBoundaryPosition::operator bool() const
    {
        return object;
    }

    void DynamicWorldEntityBoundaryPosition::Create(Data data)
    {
        object = reliquary->Do(Arca::Create<EntityBoundaryPosition> { data.x, data.y, data.status });
    }

    void DynamicWorldEntityBoundaryPosition::Destroy()
    {
        if (reliquary && object)
            reliquary->Do(Arca::Destroy<EntityBoundaryPosition> { object.ID() });
    }

    void DynamicWorldEntityBoundaryPosition::Refresh(Data data)
    {
        const auto mutableObject = MutablePointer().Of(object);
        mutableObject->x = data.x;
        mutableObject->y = data.y;
        mutableObject->status = data.status;
    }

    Arca::MutablePointer DynamicWorldEntityBoundaryPosition::MutablePointer()
    {
        return reliquary->Find<Creation::MutationCurator>().RetrieveMutablePointer();
    }
}