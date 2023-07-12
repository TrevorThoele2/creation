#pragma once

#include "ViewManager.h"
#include "BuildPackageTile.h"

namespace Creation
{
    // Manages tiles which are empty (have no sprites)
    class TileViewManager : public ViewManager<TileViewManager, Build::Package<::Atmos::Tile>>
    {
    private:
        typedef ViewManager<TileViewManager, Build::Package<::Atmos::Tile>> BaseT;
        friend BaseT;

        PositionPackageT& GetPosition(PackageT &package) override final;
        const PositionPackageT& GetPosition(const PackageT &package) override final;
        Build::Package<::Atmos::RandomAccessSequence<Build::Package<::Atmos::ObjectOffsetHandle<::Atmos::Sprite, ::Atmos::Position3D>>>>* GetSpriteList(PackageT &package) override final;
        const Build::Package<::Atmos::RandomAccessSequence<Build::Package<::Atmos::ObjectOffsetHandle<::Atmos::Sprite, ::Atmos::Position3D>>>>* GetSpriteList(const PackageT &package) override final;
        Build::Package<::Atmos::RandomAccessSequence<PackageT>>& GetFieldList(Build::Package<::Atmos::Field> &field) override final;
        Image GetDefaultVoidImageImpl() override final;

        TileViewManager() = default;
        TileViewManager(const TileViewManager &arg) = delete;
        TileViewManager& operator=(const TileViewManager &arg) = delete;
    };
}