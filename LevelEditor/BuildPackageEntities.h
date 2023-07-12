#pragma once

#include "BuildPackage.h"
#include "BuildPackageList.h"
#include "BuildPackageGeneral.h"
#include "BuildPackageAsset.h"
#include "BuildPackageAction.h"
#include "BuildPackageAVEffect.h"
#include "BuildPackageRegistryReference.h"
#include "BuildPackageRegistries.h"
#include "BuildPackageOffset.h"
#include "BuildPackageModulators.h"

#include <Atmos/ActionComponent.h>
#include <Atmos/AIComponent.h>
#include <Atmos/AvatarComponent.h>
#include <Atmos/BattleComponent.h>
#include <Atmos/CharacterComponent.h>
#include <Atmos/CombatComponent.h>
#include <Atmos/DialogueComponent.h>
#include <Atmos/GeneralComponent.h>
#include <Atmos/InventoryComponent.h>
#include <Atmos/MovementComponent.h>
#include <Atmos/SenseComponent.h>
#include <Atmos/Entity.h>

namespace Creation
{
    namespace Build
    {
        template<>
        class Package<::Atmos::Ent::ActionComponent> : public PackageBase
        {
        public:
            typedef ::Atmos::Ent::ActionComponent BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<std::underlying_type<BuildT::Activator>::type> activator;
            Package<::Atmos::Act::Action> action;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::Ent::AIComponent> : public PackageBase
        {
        public:
            typedef ::Atmos::Ent::AIComponent BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Script::Instance> ai;
            Package<::Atmos::Script::Instance> battleAI;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::Ent::AvatarComponent> : public PackageBase
        {
        public:
            typedef ::Atmos::Ent::AvatarComponent BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<BuildT::Gold> gold;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::Ent::CharacterComponent::ImplMonster> : public PackageBase
        {
        public:
            typedef ::Atmos::Ent::CharacterComponent::ImplMonster BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::Ent::CharacterComponent> : public PackageBase
        {
        public:
            typedef ::Atmos::Ent::CharacterComponent BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<std::underlying_type<BuildT::Type>::type> type;
            Package<::Atmos::Optional<Package<BuildT::ImplMonster>>> monsterImpl;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::Ent::CombatComponent> : public PackageBase
        {
        public:
            typedef ::Atmos::Ent::CombatComponent BuildT;
        public:
            class EntryPackage : public PackageBase
            {
            private:
                INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
                INSCRIPTION_ACCESS;
            public:
                Package<std::underlying_type<::Atmos::EquipSlot>::type> slot;
                Package<::Atmos::RegistryObjectReference<::Atmos::Item>> item;

                BUILD_PACKAGE_DEFAULT_SPECIFIC(EntryPackage);
                EntryPackage(EntryPackage &&arg);
                EntryPackage& operator=(EntryPackage &&arg);
                bool operator==(const EntryPackage &arg) const;
                bool operator!=(const EntryPackage &arg) const;
            };
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::RegistryObjectReference<::Atmos::CharacterClass>> charClass;
            Package<::Atmos::Acumen> acumen;
            Build::Package<::Atmos::RandomAccessSequence<Package<::Atmos::RegistryObjectReference<::Atmos::Item>>>> permanentStash;
            Build::Package<::Atmos::RandomAccessSequence<EntryPackage>> equipment;
            Package<BuildT::Level> level;
            Package<::Atmos::MovementRange> movementRange;
            Build::Package<::Atmos::RandomAccessSequence<Package<::Atmos::RegistryObjectReference<::Atmos::Spell>>>> spells;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::Ent::DialogueComponent> : public PackageBase
        {
        public:
            typedef ::Atmos::Ent::DialogueComponent BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Script::Instance> script;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::Ent::GeneralComponent> : public PackageBase
        {
        public:
            typedef ::Atmos::Ent::GeneralComponent BuildT;
        public:
            class StoragePackage : public PackageBase
            {
            private:
                INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
                INSCRIPTION_ACCESS;
            public:
                Package<::Atmos::Name> name;
                Package<::Atmos::Variant> variant;

                BUILD_PACKAGE_DEFAULT_SPECIFIC(StoragePackage);
                StoragePackage(StoragePackage &&arg);
                StoragePackage& operator=(StoragePackage &&arg);
                bool operator==(const StoragePackage &arg) const;
                bool operator!=(const StoragePackage &arg) const;
            };
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Name> name;
            Package<::Atmos::Name> niceName;
            Package<BuildT::PositionT> position;
            Package<BuildT::DirectionT> direction;
            Package<bool> solid;
            Build::Package<::Atmos::RandomAccessSequence<StoragePackage>> storage;
            Build::Package<::Atmos::RandomAccessSequence<Package<::Atmos::Tag>>> tags;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::Ent::InventoryComponent> : public PackageBase
        {
        public:
            typedef ::Atmos::Ent::InventoryComponent BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Build::Package<::Atmos::RandomAccessSequence<Package<::Atmos::ItemStack>>> items;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::Ent::MovementComponent> : public PackageBase
        {
        public:
            typedef ::Atmos::Ent::MovementComponent BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Name> upMod;
            Package<::Atmos::Name> downMod;
            Package<::Atmos::Name> leftMod;
            Package<::Atmos::Name> rightMod;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::Ent::SenseComponent> : public PackageBase
        {
        public:
            typedef ::Atmos::Ent::SenseComponent BuildT;

            class ModulatorEntryPackage : public PackageBase
            {
            public:
                typedef ::Atmos::Ent::SenseComponent::ModulatorEntry BuildT;
            private:
                INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
                INSCRIPTION_ACCESS;
            public:
                Package<BuildT::ObjectID> objectID;
                Package<std::underlying_type<BuildT::Type>::type> type;
                Package<::Atmos::Modulator::GeneratorRoute> generatorRoute;

                BUILD_PACKAGE_DEFAULT_SPECIFIC(ModulatorEntryPackage);
                ModulatorEntryPackage(ModulatorEntryPackage &&arg);
                ModulatorEntryPackage& operator=(ModulatorEntryPackage &&arg);
                bool operator==(const ModulatorEntryPackage &arg) const;
                bool operator!=(const ModulatorEntryPackage &arg) const;

                BuildT Build() const;
            };

            class ModulatorPackPackage : public PackageBase
            {
            public:
                typedef ::Atmos::Ent::SenseComponent::ModulatorPack BuildT;
            private:
                INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
                INSCRIPTION_ACCESS;
            public:
                Build::Package<::Atmos::Name> name;
                Build::Package<::Atmos::RandomAccessSequence<ModulatorEntryPackage>> entries;

                BUILD_PACKAGE_DEFAULT_SPECIFIC(ModulatorPackPackage);
                ModulatorPackPackage(ModulatorPackPackage &&arg);
                ModulatorPackPackage& operator=(ModulatorPackPackage &&arg);
                bool operator==(const ModulatorPackPackage &arg) const;
                bool operator!=(const ModulatorPackPackage &arg) const;

                BuildT Build() const;
            };
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Build::Package<::Atmos::RandomAccessSequence<Package<BuildT::SpriteHandle>>> sprites;
            Build::Package<::Atmos::RandomAccessSequence<Package<BuildT::SoundHandle>>> sounds;
            Build::Package<::Atmos::RandomAccessSequence<Package<BuildT::AVEffectHandle>>> avEffects;

            Build::Package<::Atmos::RandomAccessSequence<ModulatorPackPackage>> modulatorPacks;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::Ent::Entity> : public PackageBase
        {
        public:
            typedef ::Atmos::Ent::Entity BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Optional<Package<::Atmos::Ent::ActionComponent>>> actionComponent;
            Package<::Atmos::Optional<Package<::Atmos::Ent::AIComponent>>> aiComponent;
            Package<::Atmos::Optional<Package<::Atmos::Ent::AvatarComponent>>> avatarComponent;
            Package<::Atmos::Optional<Package<::Atmos::Ent::CharacterComponent>>> characterComponent;
            Package<::Atmos::Optional<Package<::Atmos::Ent::CombatComponent>>> combatComponent;
            Package<::Atmos::Optional<Package<::Atmos::Ent::DialogueComponent>>> dialogueComponent;
            Package<::Atmos::Ent::GeneralComponent> generalComponent;
            Package<::Atmos::Optional<Package<::Atmos::Ent::InventoryComponent>>> inventoryComponent;
            Package<::Atmos::Optional<Package<::Atmos::Ent::MovementComponent>>> movementComponent;
            Package<::Atmos::Optional<Package<::Atmos::Ent::SenseComponent>>> senseComponent;
            Package<BuildT::ValueT> id;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;
        };
    }
}