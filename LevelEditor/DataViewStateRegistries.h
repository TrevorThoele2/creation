#pragma once

#include "DataViewState.h"
#include "DataBreakdownRegistries.h"

namespace Creation
{
    class DataViewStateRegistries : public DataViewState
    {
    public:
        static constexpr const Type type = Type::REGISTRIES;
    private:
        typedef DataBreakdownList<Build::Package<::Atmos::Ability>> AbilityBreakdown;
        typedef DataBreakdownList<Build::Package<::Atmos::CharacterClass>> CharacterClassBreakdown;
        typedef DataBreakdownList<Build::Package<::Atmos::Item>> ItemBreakdown;
        typedef DataBreakdownList<Build::Package<::Atmos::Quest>> QuestBreakdown;
        typedef DataBreakdownList<Build::Package<::Atmos::Spell>> SpellBreakdown;
        typedef DataBreakdownList<Build::Package<::Atmos::StatusEffect>> StatusEffectBreakdown;

        AbilityBreakdown abilities;
        CharacterClassBreakdown characterClasses;
        ItemBreakdown items;
        QuestBreakdown quests;
        SpellBreakdown spells;
        StatusEffectBreakdown statusEffects;

        void SetupBreakdowns();

        void StartImpl() override final;
        void StopImpl() override final;

        void SelectImpl(wxTreeItemId id) override final;
        void DeselectImpl(wxTreeItemId id) override final;
        void DeselectAllImpl() override final;
        void AddImpl() override final;
        void RemoveImpl() override final;

        void CreateBreakdownsFromScratchImpl() override final;
        void DestroyBreakdownsImpl() override final;
        void CreateTreePiecesImpl() override final;
        void CreateEditorPropertiesImpl() override final;
        void DestroyEditorPropertiesImpl(bool destroyTreeItems) override final;

        Type GetTypeImpl() const override final;
    public:
        DataViewStateRegistries(DataView *dataView);

        void SetAbilities(const AbilityBreakdown::ListT &set);
        void SetAbilities(AbilityBreakdown::ListT &&set);
        void SetCharacterClasses(const CharacterClassBreakdown::ListT &set);
        void SetCharacterClasses(CharacterClassBreakdown::ListT &&set);
        void SetItems(const ItemBreakdown::ListT &set);
        void SetItems(ItemBreakdown::ListT &&set);
        void SetQuests(const QuestBreakdown::ListT &set);
        void SetQuests(QuestBreakdown::ListT &&set);
        void SetSpells(const SpellBreakdown::ListT &set);
        void SetSpells(SpellBreakdown::ListT &&set);
        void SetStatusEffects(const StatusEffectBreakdown::ListT &set);
        void SetStatusEffects(StatusEffectBreakdown::ListT &&set);

        static String GetTreeString();
    };
}