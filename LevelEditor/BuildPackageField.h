#pragma once

#include "BuildPackage.h"
#include "BuildPackageTile.h"
#include "BuildPackageEntities.h"

#include <Atmos/Field.h>

namespace Creation
{
    namespace Build
    {
        template<>
        class Package<::Atmos::Field> : public PackageBase
        {
        public:
            typedef ::Atmos::Field BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<BuildT::ID> id;

            Build::Package<::Atmos::RandomAccessSequence<Package<::Atmos::Tile>>> tiles;
            Build::Package<::Atmos::RandomAccessSequence<Package<::Atmos::Entity>>> entities;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };
    }
}