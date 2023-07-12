#pragma once

#include "BuildPackage.h"
#include "BuildPackageList.h"
#include "BuildPackageGeneral.h"
#include "BuildPackageAction.h"
#include "BuildPackageVariant.h"

namespace Creation
{
    namespace Build
    {
        template<>
        class Package<::Atmos::Act::Parameter> : public PackageBase
        {
        public:
            typedef ::Atmos::Act::Parameter BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Variant> variant;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::Act::Action> : public PackageBase
        {
        public:
            typedef ::Atmos::Act::Action BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<BuildT::ID> id;
            Package<::Atmos::RandomAccessSequence<Package<BuildT::Parameter>>> parameters;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };
    }
}