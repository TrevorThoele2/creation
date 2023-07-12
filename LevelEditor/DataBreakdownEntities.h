#pragma once

#include "DataBreakdownGameData.h"
#include "DataBreakdownAVEffect.h"
#include "DataBreakdownRegistries.h"
#include "DataBreakdownScriptInstance.h"
#include "DataBreakdownOffset.h"
#include "DataBreakdownModulators.h"

#include "BuildPackageEntities.h"
#include "EntityData.h"

#include <Atmos/Event.h>

namespace Creation
{
    template<>
    class DataBreakdown<Build::Package<::Atmos::Ent::ActionComponent>> : public DataBreakdownBase<Build::Package<::Atmos::Ent::ActionComponent>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdownEnum<BuildT::Activator> activator;
        DataBreakdown<Build::Package<::Atmos::Act::Action>> action;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Ent::AIComponent>> : public DataBreakdownBase<Build::Package<::Atmos::Ent::AIComponent>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Script::Instance>> ai;
        DataBreakdown<Build::Package<::Atmos::Script::Instance>> battleAI;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Ent::AvatarComponent>> : public DataBreakdownBase<Build::Package<::Atmos::Ent::AvatarComponent>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<BuildT::Gold>> gold;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Ent::CharacterComponent::ImplMonster>> : public DataBreakdownBase<Build::Package<::Atmos::Ent::CharacterComponent::ImplMonster>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Ent::CharacterComponent>> : public DataBreakdownBase<Build::Package<::Atmos::Ent::CharacterComponent>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdownEnum<BuildT::Type> type;
        DataBreakdown<Build::Package<::Atmos::Optional<Build::Package<BuildT::ImplMonster>>>> monsterImpl;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Ent::CombatComponent>::EntryPackage> : public DataBreakdownBase<Build::Package<::Atmos::Ent::CombatComponent>::EntryPackage>
    {
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<std::underlying_type<::Atmos::EquipSlot>::type>> slot;
        DataBreakdown<Build::Package<::Atmos::RegistryObjectReference<::Atmos::Item>>> item;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Ent::CombatComponent>> : public DataBreakdownBase<Build::Package<::Atmos::Ent::CombatComponent>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::RegistryObjectReference<::Atmos::CharacterClass>>> charClass;
        DataBreakdown<Build::Package<::Atmos::Acumen>> acumen;
        DataBreakdownList<Build::Package<::Atmos::RegistryObjectReference<::Atmos::Item>>> permanentStash;
        DataBreakdownList<PackageT::EntryPackage> equipment;
        DataBreakdown<Build::Package<BuildT::Level>> level;
        DataBreakdown<Build::Package<::Atmos::MovementRange>> movementRange;
        DataBreakdownList<Build::Package<::Atmos::RegistryObjectReference<::Atmos::Spell>>> spells;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Ent::DialogueComponent>> : public DataBreakdownBase<Build::Package<::Atmos::Ent::DialogueComponent>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Script::Instance>> script;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Ent::GeneralComponent>::StoragePackage> : public DataBreakdownBase<Build::Package<::Atmos::Ent::GeneralComponent>::StoragePackage>
    {
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> name;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Ent::GeneralComponent>> : public DataBreakdownBase<Build::Package<::Atmos::Ent::GeneralComponent>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> name;
        DataBreakdown<Build::Package<::Atmos::Name>> niceName;
        DataBreakdown<Build::Package<BuildT::PositionT>> position;
        DataBreakdown<Build::Package<BuildT::DirectionT>> direction;
        DataBreakdown<Build::Package<bool>> solid;
        DataBreakdownList<PackageT::StoragePackage> storage;
        DataBreakdownList<Build::Package<::Atmos::Tag>> tags;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Ent::InventoryComponent>> : public DataBreakdownBase<Build::Package<::Atmos::Ent::InventoryComponent>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdownList<Build::Package<::Atmos::ItemStack>> items;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Ent::MovementComponent>> : public DataBreakdownBase<Build::Package<::Atmos::Ent::MovementComponent>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> upMod;
        DataBreakdown<Build::Package<::Atmos::Name>> downMod;
        DataBreakdown<Build::Package<::Atmos::Name>> leftMod;
        DataBreakdown<Build::Package<::Atmos::Name>> rightMod;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage> : public DataBreakdownBase<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void OnTypeChanged(const DataBreakdownEditArgs &args);

        void AddAllChildren();
        void SubscribeEvents();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<BuildT::ObjectID>> objectID;
        DataBreakdownEnum<BuildT::Type> type;
        DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>> generatorRoute;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorPackPackage> : public DataBreakdownBase<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorPackPackage>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> name;
        DataBreakdownList<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage> entries;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>> : public DataBreakdownBase<Build::Package<::Atmos::Ent::SenseComponent>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdownList<Build::Package<BuildT::SpriteHandle>> sprites;
        DataBreakdownList<Build::Package<BuildT::SoundHandle>> sounds;
        DataBreakdownList<Build::Package<BuildT::AVEffectHandle>> avEffects;

        DataBreakdownList<PackageT::ModulatorPackPackage> modulatorPacks;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Ent::Entity>> : public DataBreakdownBase<Build::Package<::Atmos::Ent::Entity>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        ::Atmos::EventScopedConnectionManager senseConnections;

        void AddAllChildren();
        void SubscribeEvents();
        void CheckSenseComponentSubscribe();

        void OnSenseComponentValid(const DataBreakdownEditArgs &args);
        void OnSpriteAdded(const DataBreakdownAddArgs &args);
        void OnSpriteRemoved(const DataBreakdownPostRemoveArgs &args);
        void OnSpriteEdited(const DataBreakdownEditArgs &args);

        void SetupImpl() override final;
        bool IgnoreNameForKeyImpl() const override final;
    public:
        DataBreakdown<Build::Package<Optional<Build::Package<::Atmos::Ent::ActionComponent>>>> actionComponent;
        DataBreakdown<Build::Package<Optional<Build::Package<::Atmos::Ent::AIComponent>>>> aiComponent;
        DataBreakdown<Build::Package<Optional<Build::Package<::Atmos::Ent::AvatarComponent>>>> avatarComponent;
        DataBreakdown<Build::Package<Optional<Build::Package<::Atmos::Ent::CharacterComponent>>>> characterComponent;
        DataBreakdown<Build::Package<Optional<Build::Package<::Atmos::Ent::CombatComponent>>>> combatComponent;
        DataBreakdown<Build::Package<Optional<Build::Package<::Atmos::Ent::DialogueComponent>>>> dialogueComponent;
        DataBreakdown<Build::Package<::Atmos::Ent::GeneralComponent>> generalComponent;
        DataBreakdown<Build::Package<Optional<Build::Package<::Atmos::Ent::InventoryComponent>>>> inventoryComponent;
        DataBreakdown<Build::Package<Optional<Build::Package<::Atmos::Ent::MovementComponent>>>> movementComponent;
        DataBreakdown<Build::Package<Optional<Build::Package<::Atmos::Ent::SenseComponent>>>> senseComponent;

        DataBreakdown<Build::Package<BuildT::ValueT>> id;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };
}