#pragma once

#include "DataBreakdownGeneral.h"
#include "DataBreakdownScriptInstance.h"
#include "DataBreakdownSenses.h"
#include "DataBreakdownGameData.h"
#include "DataBreakdownBattlePattern.h"

#include "EquipSlotData.h"
#include "ItemData.h"
#include "QuestData.h"

namespace Creation
{
    template<>
    class DataBreakdown<Build::Package<::Atmos::ItemStack>> : public DataBreakdownBase<Build::Package<::Atmos::ItemStack>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::RegistryObjectReference<::Atmos::Item>>> wrapped;
        DataBreakdown<Build::Package<BuildT::CountT>> count;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Ability>> : public DataBreakdownBase<Build::Package<::Atmos::Ability>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> name;
        DataBreakdown<Build::Package<::Atmos::Name>> niceName;
        DataBreakdown<Build::Package<::Atmos::String>> description;
        DataBreakdown<Build::Package<BuildT::ID>> id;

        DataBreakdown<Build::Package<::Atmos::BattlePatternHolder>> pattern;
        DataBreakdown<Build::Package<::Atmos::AttackRange>> range;
        DataBreakdown<Build::Package<::Atmos::Acumen>> cost;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::CharacterClass>::AttributePackage> : public DataBreakdownBase<Build::Package<::Atmos::CharacterClass>::AttributePackage>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> name;
        DataBreakdown<Build::Package<BuildT::AttributeEntry::ValueT>> base;
        DataBreakdown<Build::Package<BuildT::AttributeEntry::ValueT>> growth;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::CharacterClass>::ProficiencyPackage> : public DataBreakdownBase<Build::Package<::Atmos::CharacterClass>::ProficiencyPackage>
    {
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> name;
        DataBreakdown<Build::Package<::Atmos::Proficiencies::Rating>> rating;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::CharacterClass>> : public DataBreakdownBase<Build::Package<::Atmos::CharacterClass>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> name;
        DataBreakdown<Build::Package<::Atmos::Name>> niceName;
        DataBreakdown<Build::Package<::Atmos::String>> description;
        DataBreakdown<Build::Package<BuildT::ID>> id;

        DataBreakdownList<PackageT::AttributePackage> resources;
        DataBreakdownList<PackageT::AttributePackage> stats;
        DataBreakdownList<PackageT::ProficiencyPackage> proficiencies;
        DataBreakdown<Build::Package<::Atmos::ItemStashSize>> permanentStashSize;
        DataBreakdown<Build::Package<::Atmos::ItemStashSize>> temporaryStashSize;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::ConsumableAspect>> : public DataBreakdownBase<Build::Package<::Atmos::ConsumableAspect>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::AssetReference<::Atmos::ScriptModuleBase>>> script;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AmmoAdditionalPackage> : public DataBreakdownBase<Build::Package<::Atmos::EquippableAspect>::AmmoAdditionalPackage>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Tag>> ammoType;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::UsesAmmoPackage> : public DataBreakdownBase<Build::Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::UsesAmmoPackage>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AttackAdditionalPackage> : public DataBreakdownBase<Build::Package<::Atmos::EquippableAspect>::AttackAdditionalPackage>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<BuildT::AttackAdditional::Power>> power;
        DataBreakdown<Build::Package<::Atmos::BattlePatternHolder>> pattern;
        DataBreakdown<Build::Package<::Atmos::AttackRange>> range;
        DataBreakdown<Build::Package<::Atmos::CharacterClassGroup>> allowedClasses;
        DataBreakdown<Build::Package<::Atmos::Name>> proficiencyName;
        DataBreakdown<PackageT::UsesAmmoPackage> usesAmmo;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::EquippableAspect>> : public DataBreakdownBase<Build::Package<::Atmos::EquippableAspect>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::EquipRegion>> equipRegion;
        DataBreakdown<Build::Package<::Atmos::Defense>> defense;
        DataBreakdown<Build::Package<::Atmos::Optional<PackageT::AmmoAdditionalPackage>>> ammoAdditional;
        DataBreakdown<Build::Package<::Atmos::Optional<PackageT::AttackAdditionalPackage>>> attackAdditional;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Item>> : public DataBreakdownBase<Build::Package<::Atmos::Item>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> name;
        DataBreakdown<Build::Package<::Atmos::Name>> niceName;
        DataBreakdown<Build::Package<::Atmos::String>> description;
        DataBreakdown<Build::Package<BuildT::ID>> id;

        DataBreakdown<Build::Package<::Atmos::Flags<BuildT::Flag>>> flags;
        DataBreakdown<Build::Package<::Atmos::Optional<Build::Package<::Atmos::ConsumableAspect>>>> consumableAspect;
        DataBreakdown<Build::Package<::Atmos::Optional<Build::Package<::Atmos::EquippableAspect>>>> equippableAspect;
        DataBreakdown<Build::Package<BuildT::Price>> buyingPrice;
        DataBreakdown<Build::Package<BuildT::Price>> sellingPrice;
        DataBreakdown<Build::Package<::Atmos::Sprite>> portrait;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Quest::Part>> : public DataBreakdownBase<Build::Package<::Atmos::Quest::Part>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> name;
        DataBreakdown<Build::Package<BuildT::Description>> description;
        DataBreakdownEnum<BuildT::Type> type;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Quest>> : public DataBreakdownBase<Build::Package<::Atmos::Quest>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> name;
        DataBreakdown<Build::Package<::Atmos::Name>> niceName;
        DataBreakdown<Build::Package<::Atmos::String>> description;
        DataBreakdown<Build::Package<BuildT::ID>> id;

        DataBreakdownList<Build::Package<BuildT::Part>> parts;
        DataBreakdown<Build::Package<::Atmos::Script::Instance>> script;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Spell>> : public DataBreakdownBase<Build::Package<::Atmos::Spell>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> name;
        DataBreakdown<Build::Package<::Atmos::Name>> niceName;
        DataBreakdown<Build::Package<::Atmos::String>> description;
        DataBreakdown<Build::Package<BuildT::ID>> id;

        DataBreakdown<Build::Package<::Atmos::BattlePatternHolder>> attackPattern;
        DataBreakdown<Build::Package<::Atmos::BattlePatternHolder::Piece>> pieceOverworld;
        DataBreakdown<Build::Package<::Atmos::AttackRange>> range;
        DataBreakdown<Build::Package<::Atmos::Attribute>> resourceCost;
        DataBreakdown<Build::Package<::Atmos::CharacterClassGroup>> allowedClasses;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::StatusEffect>> : public DataBreakdownBase<Build::Package<::Atmos::StatusEffect>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> name;
        DataBreakdown<Build::Package<::Atmos::Name>> niceName;
        DataBreakdown<Build::Package<::Atmos::String>> description;
        DataBreakdown<Build::Package<BuildT::ID>> id;

        DataBreakdown<Build::Package<::Atmos::AssetReference<::Atmos::ScriptModuleBase>>> script;
        DataBreakdown<Build::Package<BuildT::ApplicationCount>> applicationCount;
        DataBreakdown<Build::Package<::Atmos::Name>> proficiencyName;
        DataBreakdown<Build::Package<BuildT::Accuracy>> accuracy;
        DataBreakdown<Build::Package<bool>> positive;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };
}