#pragma once

#include "BuildPackage.h"
#include "BuildPackageList.h"
#include "BuildPackageGeneral.h"

#include <Atmos/AVEffect.h>

namespace Creation
{
    namespace Build
    {
        template<>
        class Package<::Atmos::AVEffect> : public PackageBase
        {
        public:
            typedef ::Atmos::AVEffect BuildT;
        public:
            class NodePackage : public PackageBase
            {
            public:
                typedef ::Atmos::AVEffect::Node BuildT;
            private:
                INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
                INSCRIPTION_ACCESS;
            public:
                Package<std::underlying_type<BuildT::ModulatorEntryType>::type> type;

                BUILD_PACKAGE_DEFAULT_SPECIFIC(NodePackage);
                NodePackage(NodePackage &&arg);
                NodePackage& operator=(NodePackage &&arg);
                bool operator==(const NodePackage &arg) const;
                bool operator!=(const NodePackage &arg) const;

                BuildT Build() const;
            };
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::RandomAccessSequence<NodePackage>> nodes;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };
    }
}