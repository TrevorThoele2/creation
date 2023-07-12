#pragma once

#include "BuildPackage.h"
#include "BuildPackageGeneral.h"

#include <Atmos/WorldStart.h>

namespace Creation
{
    namespace Build
    {
        template<>
        class Package<::Atmos::WorldStart> : public PackageBase
        {
        public:
            typedef ::Atmos::WorldStart BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::FieldID> id;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };
    }
}