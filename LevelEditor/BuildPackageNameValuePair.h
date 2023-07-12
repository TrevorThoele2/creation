#pragma once

#include "BuildPackage.h"
#include "BuildPackageGeneral.h"
#include "BuildPackageVariant.h"

#include <Atmos/NameValuePair.h>

namespace Creation
{
    namespace Build
    {
        template<>
        class Package<::Atmos::NameValuePair> : public PackageBase
        {
        public:
            typedef ::Atmos::NameValuePair BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Variant> variant;
            Package<::Atmos::Name> name;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };
    }
}