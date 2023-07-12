#pragma once

#include "BuildPackage.h"

#include <Atmos/Variant.h>

namespace Creation
{
    namespace Build
    {
        template<>
        class Package<::Atmos::Variant> : public PackageBase
        {
        public:
            typedef ::Atmos::Variant BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            BuildT value;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };
    }
}