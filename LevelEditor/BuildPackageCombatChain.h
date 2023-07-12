#pragma once

#include "BuildPackage.h"
#include "BuildPackageList.h"
#include "BuildPackageGeneral.h"
#include "BuildPackageAsset.h"
#include "BuildPackageRegistryReference.h"

#include <Atmos/CombatChain.h>

namespace Creation
{
    namespace Build
    {
        template<>
        class Package<::Atmos::CombatChain::Node> : public PackageBase
        {
        public:
            typedef ::Atmos::CombatChain::Node BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::CombatTransactionGenerator> transaction;
            Package<::Atmos::RegistryObjectReference<::Atmos::StatusEffect>> statusEffect;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::CombatChain> : public PackageBase
        {
        public:
            typedef ::Atmos::CombatChain BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::RandomAccessSequence<Package<BuildT::Node>>> nodes;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };
    }
}