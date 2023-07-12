
#include "Viewport.h"

#include "EntityViewManager.h"
#include "CurrentWorld.h"
#include <Atmos\SenseComponent.h>

namespace Creation
{
    EntityViewManager::PositionPackageT& EntityViewManager::GetPosition(PackageT &package)
    {
        return package.generalComponent.position;
    }

    const EntityViewManager::PositionPackageT& EntityViewManager::GetPosition(const PackageT &package)
    {
        return package.generalComponent.position;
    }

    Build::Package<::Atmos::RandomAccessSequence<Build::Package<::Atmos::ObjectOffsetHandle<::Atmos::Sprite, ::Atmos::Position3D>>>>* EntityViewManager::GetSpriteList(PackageT &package)
    {
        auto built = package.senseComponent.valid.Build();
        if (!built)
            return nullptr;
        else
            return &package.senseComponent.value.sprites;
    }

    const Build::Package<::Atmos::RandomAccessSequence<Build::Package<::Atmos::ObjectOffsetHandle<::Atmos::Sprite, ::Atmos::Position3D>>>>* EntityViewManager::GetSpriteList(const PackageT &package)
    {
        auto built = package.senseComponent.valid.Build();
        if (!built)
            return nullptr;
        else
            return &package.senseComponent.value.sprites;
    }

    Build::Package<::Atmos::RandomAccessSequence<EntityViewManager::PackageT>>& EntityViewManager::GetFieldList(Build::Package<::Atmos::Field> &field)
    {
        return field.entities;
    }

    Image EntityViewManager::GetDefaultVoidImageImpl()
    {
        return Image(voidEntityImageName, Atmos::Color(255, 255, 255, 255));
    }
}