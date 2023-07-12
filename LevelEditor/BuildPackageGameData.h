#pragma once

#include "BuildPackage.h"
#include "BuildPackageList.h"
#include "BuildPackageGeneral.h"

#include <Atmos/ResourceAttribute.h>
#include <Atmos/StatAttribute.h>
#include <Atmos/Element.h>

namespace Creation
{
    namespace Build
    {
        template<>
        class Package<::Atmos::GlobalContext<::Atmos::ResourceAttributeTable>> : public PackageBase
        {
        public:
            typedef ::Atmos::GlobalContext<::Atmos::ResourceAttributeTable> BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Name> health;
            Package<::Atmos::Name> mana;
            Package<::Atmos::Name> acumen;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            void Build() const;
        };

        template<>
        class Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>> : public PackageBase
        {
        public:
            typedef ::Atmos::DataStandard<::Atmos::StatAttributeTable> BuildT;
        public:
            class EntryPackage : public PackageBase
            {
            public:
                typedef ::Atmos::DataStandard<::Atmos::StatAttributeTable>::Entry BuildT;
            private:
                INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
                INSCRIPTION_ACCESS;
            public:
                Package<::Atmos::Name> name;
                Package<::Atmos::Name> niceName;
                Package<::Atmos::Name> opposing;

                BUILD_PACKAGE_DEFAULT_SPECIFIC(EntryPackage);
                EntryPackage(EntryPackage &&arg);
                EntryPackage& operator=(EntryPackage &&arg);
                bool operator==(const EntryPackage &arg) const;
                bool operator!=(const EntryPackage &arg) const;

                BuildT Build() const;
            };
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::RandomAccessSequence<EntryPackage>> entries;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            void Build() const;
        };

        template<>
        class Package<::Atmos::GlobalContext<::Atmos::Element>> : public PackageBase
        {
        public:
            typedef ::Atmos::GlobalContext<::Atmos::Element> BuildT;
        public:
            class EntryPackage : public PackageBase
            {
            public:
                typedef ::Atmos::GlobalContext<::Atmos::Element>::Entry BuildT;
            private:
                INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
                INSCRIPTION_ACCESS;
            public:
                Package<::Atmos::Name> name;
                Package<::Atmos::Name> niceName;
                Package<::Atmos::Element> opposing;
                Package<::Atmos::Name> statName;

                BUILD_PACKAGE_DEFAULT_SPECIFIC(EntryPackage);
                EntryPackage(EntryPackage &&arg);
                EntryPackage& operator=(EntryPackage &&arg);
                bool operator==(const EntryPackage &arg) const;
                bool operator!=(const EntryPackage &arg) const;

                BuildT Build() const;
            };
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Name> neutral;
            Package<::Atmos::RandomAccessSequence<EntryPackage>> entries;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            void Build() const;
        };
    }
}