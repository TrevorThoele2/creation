#pragma once

#include <unordered_map>
#include "ViewManager.h"

#include "Image.h"

#include "BuildPackage.h"
#include "BuildPackageEntities.h"

#include <Atmos\Entity.h>
#include <Atmos\Field.h>

namespace Creation
{
    // Manages entities which do not have a sense component, or do not have any sprites in there
    class EntityViewManager : public ViewManager<EntityViewManager, Build::Package<::Atmos::Entity>>
    {
    private:
        typedef ViewManager<EntityViewManager, Build::Package<::Atmos::Entity>> BaseT;
        friend BaseT;

        PositionPackageT& GetPosition(PackageT &package) override final;
        const PositionPackageT& GetPosition(const PackageT &package) override final;
        Build::Package<::Atmos::RandomAccessSequence<Build::Package<::Atmos::ObjectOffsetHandle<::Atmos::Sprite, ::Atmos::Position3D>>>>* GetSpriteList(PackageT &package) override final;
        const Build::Package<::Atmos::RandomAccessSequence<Build::Package<::Atmos::ObjectOffsetHandle<::Atmos::Sprite, ::Atmos::Position3D>>>>* GetSpriteList(const PackageT &package) override final;
        Build::Package<::Atmos::RandomAccessSequence<PackageT>>& GetFieldList(Build::Package<::Atmos::Field> &field) override final;
        Image GetDefaultVoidImageImpl() override final;

        EntityViewManager() = default;
        EntityViewManager(const EntityViewManager &arg) = delete;
        EntityViewManager& operator=(const EntityViewManager &arg) = delete;
    };
}