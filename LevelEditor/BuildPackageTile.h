#pragma once

#include "BuildPackage.h"
#include "BuildPackageList.h"
#include "BuildPackageGeneral.h"
#include "BuildPackageOffset.h"

#include <Atmos/Tile.h>

namespace Creation
{
    namespace Build
    {
        template<>
        class Package<::Atmos::Tile> : public PackageBase
        {
        public:
            typedef ::Atmos::Tile BuildT;
            typedef Package<::Atmos::ObjectOffsetHandle<::Atmos::Sprite, ::Atmos::Position3D>> SpritePackageT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::GridPosition> position;
            Package<bool> solid;
            Package<::Atmos::RandomAccessSequence<SpritePackageT>> sprites;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };
    }
}