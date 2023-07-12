
#include "Viewport.h"

#include "TileViewManager.h"
#include "CurrentWorld.h"
#include "ImageRegistry.h"

namespace Creation
{
    TileViewManager::PositionPackageT& TileViewManager::GetPosition(PackageT &package)
    {
        return package.position;
    }

    const TileViewManager::PositionPackageT& TileViewManager::GetPosition(const PackageT &package)
    {
        return package.position;
    }

    Build::Package<::Atmos::RandomAccessSequence<Build::Package<::Atmos::ObjectOffsetHandle<::Atmos::Sprite, ::Atmos::Position3D>>>>* TileViewManager::GetSpriteList(PackageT &package)
    {
        return &package.sprites;
    }

    const Build::Package<::Atmos::RandomAccessSequence<Build::Package<::Atmos::ObjectOffsetHandle<::Atmos::Sprite, ::Atmos::Position3D>>>>* TileViewManager::GetSpriteList(const PackageT &package)
    {
        return &package.sprites;
    }

    Build::Package<::Atmos::RandomAccessSequence<TileViewManager::PackageT>>& TileViewManager::GetFieldList(Build::Package<::Atmos::Field> &field)
    {
        return field.tiles;
    }

    Image TileViewManager::GetDefaultVoidImageImpl()
    {
        return Image(voidTileImageName, ::Atmos::Color(255, 255, 255, 255));
    }
}