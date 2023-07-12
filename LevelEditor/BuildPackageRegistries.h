#pragma once

#include "BuildPackage.h"
#include "BuildPackageBattlePattern.h"
#include "BuildPackageCharacterClassGroup.h"
#include "BuildPackageAsset.h"

#include <Atmos/Ability.h>
#include <Atmos/CharacterClass.h>
#include <Atmos/Item.h>
#include <Atmos/Quest.h>
#include <Atmos/Spell.h>
#include <Atmos/StatusEffect.h>

namespace Creation
{
    namespace Build
    {
        template<>
        class Package<::Atmos::Ability> : public PackageBase
        {
        public:
            typedef ::Atmos::Ability BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Name> name;
            Package<::Atmos::Name> niceName;
            Package<BuildT::Description> description;
            Package<BuildT::ID> id;

            Package<::Atmos::BattlePatternHolder> pattern;
            Package<::Atmos::AttackRange> range;
            Package<::Atmos::Acumen> cost;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            ::Atmos::RegistryObjectReference<BuildT> Build() const;
        };

        template<>
        class Package<::Atmos::CharacterClass> : public PackageBase
        {
        public:
            typedef ::Atmos::CharacterClass BuildT;
        public:
            class AttributePackage : public PackageBase
            {
            public:
                typedef ::Atmos::CharacterClass::AttributeEntry BuildT;
            private:
                INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
                INSCRIPTION_ACCESS;
            public:
                Package<::Atmos::Name> name;
                Package<BuildT::AttributeEntry::ValueT> base;
                Package<BuildT::AttributeEntry::ValueT> growth;

                BUILD_PACKAGE_DEFAULT_SPECIFIC(AttributePackage);
                AttributePackage(AttributePackage &&arg);
                AttributePackage& operator=(AttributePackage &&arg);
                bool operator==(const AttributePackage &arg) const;
                bool operator!=(const AttributePackage &arg) const;

                BuildT Build() const;
            };

            class ProficiencyPackage : public PackageBase
            {
            private:
                INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
                INSCRIPTION_ACCESS;
            public:
                Package<::Atmos::Name> name;
                Package<::Atmos::Proficiencies::Rating> rating;

                BUILD_PACKAGE_DEFAULT_SPECIFIC(ProficiencyPackage);
                ProficiencyPackage(ProficiencyPackage &&arg);
                ProficiencyPackage& operator=(ProficiencyPackage &&arg);
                bool operator==(const ProficiencyPackage &arg) const;
                bool operator!=(const ProficiencyPackage &arg) const;
            };
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Name> name;
            Package<::Atmos::Name> niceName;
            Package<BuildT::Description> description;
            Package<BuildT::ID> id;

            Package<::Atmos::RandomAccessSequence<AttributePackage>> resources;
            Package<::Atmos::RandomAccessSequence<AttributePackage>> stats;
            Package<::Atmos::RandomAccessSequence<ProficiencyPackage>> proficiencies;
            Package<::Atmos::ItemStashSize> permanentStashSize;
            Package<::Atmos::ItemStashSize> temporaryStashSize;

            Package();
            Package(const Package &arg) = default;
            Package(Package &&arg);
            Package& operator=(const Package &arg) = default;
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            ::Atmos::RegistryObjectReference<BuildT> Build() const;
            BUILD_PACKAGE_DEFAULT_CLONE;
        };

        template<>
        class Package<::Atmos::ConsumableAspect> : public PackageBase
        {
        public:
            typedef ::Atmos::ConsumableAspect BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::AssetReference<::Atmos::ScriptModuleBase>> script;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::EquippableAspect> : public PackageBase
        {
        public:
            typedef ::Atmos::EquippableAspect BuildT;
        public:
            class AmmoAdditionalPackage : public PackageBase
            {
            public:
                typedef ::Atmos::EquippableAspect::AmmoAdditional BuildT;
            private:
                INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
                INSCRIPTION_ACCESS;
            public:
                Package<::Atmos::Tag> ammoType;

                BUILD_PACKAGE_DEFAULT_SPECIFIC(AmmoAdditionalPackage);
                AmmoAdditionalPackage(AmmoAdditionalPackage &&arg);
                AmmoAdditionalPackage& operator=(AmmoAdditionalPackage &&arg);
                bool operator==(const AmmoAdditionalPackage &arg) const;
                bool operator!=(const AmmoAdditionalPackage &arg) const;

                BuildT Build() const;
            };

            class AttackAdditionalPackage : public PackageBase
            {
            public:
                typedef ::Atmos::EquippableAspect::AttackAdditional BuildT;
            public:
                class UsesAmmoPackage : public PackageBase
                {
                public:
                    typedef ::Atmos::EquippableAspect::AttackAdditional::UsesAmmoAdditional BuildT;
                private:
                    INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
                    INSCRIPTION_ACCESS;
                public:
                    BUILD_PACKAGE_DEFAULT_SPECIFIC(UsesAmmoPackage);
                    UsesAmmoPackage(UsesAmmoPackage &&arg);
                    UsesAmmoPackage& operator=(UsesAmmoPackage &&arg);
                    bool operator==(const UsesAmmoPackage &arg) const;
                    bool operator!=(const UsesAmmoPackage &arg) const;

                    BuildT Build() const;
                };
            private:
                INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
                INSCRIPTION_ACCESS;
            public:
                Package<BuildT::Power> power;
                Package<::Atmos::BattlePatternHolder> pattern;
                Package<::Atmos::AttackRange> range;
                Package<::Atmos::CharacterClassGroup> allowedClasses;
                Package<::Atmos::Name> proficiencyName;
                UsesAmmoPackage usesAmmo;

                BUILD_PACKAGE_DEFAULT_SPECIFIC(AttackAdditionalPackage);
                AttackAdditionalPackage(AttackAdditionalPackage &&arg);
                AttackAdditionalPackage& operator=(AttackAdditionalPackage &&arg);
                bool operator==(const AttackAdditionalPackage &arg) const;
                bool operator!=(const AttackAdditionalPackage &arg) const;

                BuildT Build() const;
            };
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::EquipRegion> equipRegion;
            Package<::Atmos::Defense> defense;
            Package<::Atmos::Optional<AmmoAdditionalPackage>> ammoAdditional;
            Package<::Atmos::Optional<AttackAdditionalPackage>> attackAdditional;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::Item> : public PackageBase
        {
        public:
            typedef ::Atmos::Item BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Name> name;
            Package<::Atmos::Name> niceName;
            Package<BuildT::Description> description;
            Package<BuildT::ID> id;

            Package<::Atmos::Flags<BuildT::Flag>> flags;
            Package<::Atmos::Optional<Package<::Atmos::ConsumableAspect>>> consumableAspect;
            Package<::Atmos::Optional<Package<::Atmos::EquippableAspect>>> equippableAspect;
            Package<BuildT::Price> buyingPrice;
            Package<BuildT::Price> sellingPrice;
            Package<::Atmos::Sprite> portrait;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            ::Atmos::RegistryObjectReference<BuildT> Build() const;
        };

        template<>
        class Package<::Atmos::Quest::Part> : public PackageBase
        {
        public:
            typedef ::Atmos::Quest::Part BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Name> name;
            Package<BuildT::Description> description;
            Package<std::underlying_type<BuildT::Type>::type> type;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::Quest> : public PackageBase
        {
        public:
            typedef ::Atmos::Quest BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Name> name;
            Package<::Atmos::Name> niceName;
            Package<BuildT::Description> description;
            Package<BuildT::ID> id;

            Package<::Atmos::RandomAccessSequence<Package<BuildT::Part>>> parts;
            Package<::Atmos::Script::Instance> script;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            ::Atmos::RegistryObjectReference<BuildT> Build() const;
        };

        template<>
        class Package<::Atmos::Spell> : public PackageBase
        {
        public:
            typedef ::Atmos::Spell BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Name> name;
            Package<::Atmos::Name> niceName;
            Package<BuildT::Description> description;
            Package<BuildT::ID> id;

            Package<::Atmos::BattlePatternHolder> attackPattern;
            Package<::Atmos::BattlePatternHolder::Piece> pieceOverworld;
            Package<::Atmos::AttackRange> range;
            Package<::Atmos::Attribute> resourceCost;
            Package<::Atmos::CharacterClassGroup> allowedClasses;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            ::Atmos::RegistryObjectReference<BuildT> Build() const;
        };

        template<>
        class Package<::Atmos::StatusEffect> : public PackageBase
        {
        public:
            typedef ::Atmos::StatusEffect BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Name> name;
            Package<::Atmos::Name> niceName;
            Package<BuildT::Description> description;
            Package<BuildT::ID> id;

            Package<::Atmos::AssetReference<::Atmos::ScriptModuleBase>> script;
            Package<BuildT::ApplicationCount> applicationCount;
            Package<::Atmos::Name> proficiencyName;
            Package<BuildT::Accuracy> accuracy;
            Package<bool> positive;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            ::Atmos::RegistryObjectReference<BuildT> Build() const;
        };

        template<>
        class Package<::Atmos::ItemStack> : public PackageBase
        {
        public:
            typedef ::Atmos::ItemStack BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::RegistryObjectReference<::Atmos::Item>> wrapped;
            Package<BuildT::CountT> count;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };
    }
}