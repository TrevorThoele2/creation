#pragma once

#include "BuildPackage.h"
#include "BuildPackageList.h"
#include "BuildPackageGeneral.h"
#include "BuildPackageRegistryReference.h"

namespace Creation
{
    namespace Build
    {
        template<>
        class Package<::Atmos::CharacterClassGroup> : public PackageBase
        {
        public:
            typedef ::Atmos::CharacterClassGroup BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::RandomAccessSequence<Package<::Atmos::RegistryObjectReference<::Atmos::CharacterClass>>>> classes;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };
    }
}