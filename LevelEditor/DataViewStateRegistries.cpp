
#include "DataViewStateRegistries.h"
#include "CurrentWorld.h"
#include "MainFrame.h"
#include <wx/treectrl.h>

namespace Creation
{
    void DataViewStateRegistries::SetupBreakdowns()
    {
        abilities.Setup(CurrentWorld::globals.abilityPackage);
        abilities.SetNiceNameFunctions(AbilityBreakdown::NiceNameExtractorFunction(static_cast<String(*)(AbilityBreakdown::BreakdownT&)>([](AbilityBreakdown::BreakdownT &breakdown) { return breakdown.name.Get()->Build(); })),
            AbilityBreakdown::NiceNameGetEventFunction(static_cast<Event<const DataBreakdownEditArgs&>*(*)(AbilityBreakdown::BreakdownT&)>([](AbilityBreakdown::BreakdownT &breakdown) -> Event<const DataBreakdownEditArgs&>* { return &breakdown.name.edited; })),
            AbilityBreakdown::NameSetFunction(static_cast<void(*)(AbilityBreakdown::BreakdownT&, const String&)>([](AbilityBreakdown::BreakdownT &breakdown, const String &str) { Build::Package<::Atmos::Name> package; package.value = str; breakdown.name.Edit(std::move(package)); })));
        abilities.SetAddChildrenToProperties(false);
        characterClasses.Setup(CurrentWorld::globals.characterClassPackage);
        characterClasses.SetNiceNameFunctions(CharacterClassBreakdown::NiceNameExtractorFunction(static_cast<String(*)(CharacterClassBreakdown::BreakdownT&)>([](CharacterClassBreakdown::BreakdownT &breakdown) { return breakdown.name.Get()->Build(); })),
            CharacterClassBreakdown::NiceNameGetEventFunction(static_cast<Event<const DataBreakdownEditArgs&>*(*)(CharacterClassBreakdown::BreakdownT&)>([](CharacterClassBreakdown::BreakdownT &breakdown) -> Event<const DataBreakdownEditArgs&>* { return &breakdown.name.edited; })),
            CharacterClassBreakdown::NameSetFunction(static_cast<void(*)(CharacterClassBreakdown::BreakdownT&, const String&)>([](CharacterClassBreakdown::BreakdownT &breakdown, const String &str) { Build::Package<::Atmos::Name> package; package.value = str; breakdown.name.Edit(std::move(package)); })));
        characterClasses.SetAddChildrenToProperties(false);
        items.Setup(CurrentWorld::globals.itemPackage);
        items.SetNiceNameFunctions(ItemBreakdown::NiceNameExtractorFunction(static_cast<String(*)(ItemBreakdown::BreakdownT&)>([](ItemBreakdown::BreakdownT &breakdown) { return breakdown.name.Get()->Build(); })),
            ItemBreakdown::NiceNameGetEventFunction(static_cast<Event<const DataBreakdownEditArgs&>*(*)(ItemBreakdown::BreakdownT&)>([](ItemBreakdown::BreakdownT &breakdown) -> Event<const DataBreakdownEditArgs&>* { return &breakdown.name.edited; })),
            ItemBreakdown::NameSetFunction(static_cast<void(*)(ItemBreakdown::BreakdownT&, const String&)>([](ItemBreakdown::BreakdownT &breakdown, const String &str) { Build::Package<::Atmos::Name> package; package.value = str; breakdown.name.Edit(std::move(package)); })));
        items.SetAddChildrenToProperties(false);
        quests.Setup(CurrentWorld::globals.questPackage);
        quests.SetNiceNameFunctions(QuestBreakdown::NiceNameExtractorFunction(static_cast<String(*)(QuestBreakdown::BreakdownT&)>([](QuestBreakdown::BreakdownT &breakdown) { return breakdown.name.Get()->Build(); })),
            QuestBreakdown::NiceNameGetEventFunction(static_cast<Event<const DataBreakdownEditArgs&>*(*)(QuestBreakdown::BreakdownT&)>([](QuestBreakdown::BreakdownT &breakdown) -> Event<const DataBreakdownEditArgs&>* { return &breakdown.name.edited; })),
            QuestBreakdown::NameSetFunction(static_cast<void(*)(QuestBreakdown::BreakdownT&, const String&)>([](QuestBreakdown::BreakdownT &breakdown, const String &str) { Build::Package<::Atmos::Name> package; package.value = str; breakdown.name.Edit(std::move(package)); })));
        quests.SetAddChildrenToProperties(false);
        spells.Setup(CurrentWorld::globals.spellPackage);
        spells.SetNiceNameFunctions(SpellBreakdown::NiceNameExtractorFunction(static_cast<String(*)(SpellBreakdown::BreakdownT&)>([](SpellBreakdown::BreakdownT &breakdown) { return breakdown.name.Get()->Build(); })),
            SpellBreakdown::NiceNameGetEventFunction(static_cast<Event<const DataBreakdownEditArgs&>*(*)(SpellBreakdown::BreakdownT&)>([](SpellBreakdown::BreakdownT &breakdown) -> Event<const DataBreakdownEditArgs&>* { return &breakdown.name.edited; })),
            SpellBreakdown::NameSetFunction(static_cast<void(*)(SpellBreakdown::BreakdownT&, const String&)>([](SpellBreakdown::BreakdownT &breakdown, const String &str) { Build::Package<::Atmos::Name> package; package.value = str; breakdown.name.Edit(std::move(package)); })));
        spells.SetAddChildrenToProperties(false);
        statusEffects.Setup(CurrentWorld::globals.statusEffectPackage);
        statusEffects.SetNiceNameFunctions(StatusEffectBreakdown::NiceNameExtractorFunction(static_cast<String(*)(StatusEffectBreakdown::BreakdownT&)>([](StatusEffectBreakdown::BreakdownT &breakdown) { return breakdown.name.Get()->Build(); })),
            StatusEffectBreakdown::NiceNameGetEventFunction(static_cast<Event<const DataBreakdownEditArgs&>*(*)(StatusEffectBreakdown::BreakdownT&)>([](StatusEffectBreakdown::BreakdownT &breakdown) -> Event<const DataBreakdownEditArgs&>* { return &breakdown.name.edited; })),
            StatusEffectBreakdown::NameSetFunction(static_cast<void(*)(StatusEffectBreakdown::BreakdownT&, const String&)>([](StatusEffectBreakdown::BreakdownT &breakdown, const String &str) { Build::Package<::Atmos::Name> package; package.value = str; breakdown.name.Edit(std::move(package)); })));
        statusEffects.SetAddChildrenToProperties(false);
    }

    void DataViewStateRegistries::StartImpl()
    {
        
    }

    void DataViewStateRegistries::StopImpl()
    {

    }

    void DataViewStateRegistries::SelectImpl(wxTreeItemId id)
    {
        auto data = static_cast<DataBreakdownWXItemData*>(Tree()->GetItemData(id))->data;
        data->CreateEditorProperties(nullptr);
        GetMainFrame()->GetDataView()->PropertyGrid()->FitColumns();
    }

    void DataViewStateRegistries::DeselectImpl(wxTreeItemId id)
    {

    }

    void DataViewStateRegistries::DeselectAllImpl()
    {
        GetMainFrame()->GetDataView()->Deselect(abilities.GetTreeItemID());
        GetMainFrame()->GetDataView()->Deselect(characterClasses.GetTreeItemID());
        GetMainFrame()->GetDataView()->Deselect(items.GetTreeItemID());
        GetMainFrame()->GetDataView()->Deselect(quests.GetTreeItemID());
        GetMainFrame()->GetDataView()->Deselect(spells.GetTreeItemID());
        GetMainFrame()->GetDataView()->Deselect(statusEffects.GetTreeItemID());
    }

    void DataViewStateRegistries::AddImpl()
    {

    }

    void DataViewStateRegistries::RemoveImpl()
    {

    }

    void DataViewStateRegistries::CreateBreakdownsFromScratchImpl()
    {
        abilities.CreateBreakdowns();
        characterClasses.CreateBreakdowns();
        items.CreateBreakdowns();
        quests.CreateBreakdowns();
        spells.CreateBreakdowns();
        statusEffects.CreateBreakdowns();
    }

    void DataViewStateRegistries::DestroyBreakdownsImpl()
    {
        abilities.DestroyBreakdowns();
        characterClasses.DestroyBreakdowns();
        items.DestroyBreakdowns();
        quests.DestroyBreakdowns();
        spells.DestroyBreakdowns();
        statusEffects.DestroyBreakdowns();
    }

    void DataViewStateRegistries::CreateTreePiecesImpl()
    {
        abilities.CreateTreePiece(TreeRootID());
        characterClasses.CreateTreePiece(TreeRootID());
        items.CreateTreePiece(TreeRootID());
        quests.CreateTreePiece(TreeRootID());
        spells.CreateTreePiece(TreeRootID());
        statusEffects.CreateTreePiece(TreeRootID());
    }

    void DataViewStateRegistries::CreateEditorPropertiesImpl()
    {
        abilities.CreateEditorProperties(nullptr);
        characterClasses.CreateEditorProperties(nullptr);
        items.CreateEditorProperties(nullptr);
        quests.CreateEditorProperties(nullptr);
        spells.CreateEditorProperties(nullptr);
        statusEffects.CreateEditorProperties(nullptr);

        GetMainFrame()->GetDataView()->PropertyGrid()->FitColumns();
    }

    void DataViewStateRegistries::DestroyEditorPropertiesImpl(bool destroyTreeItems)
    {
        abilities.DestroyEditorProperties(destroyTreeItems);
        characterClasses.DestroyEditorProperties(destroyTreeItems);
        items.DestroyEditorProperties(destroyTreeItems);
        quests.DestroyEditorProperties(destroyTreeItems);
        spells.DestroyEditorProperties(destroyTreeItems);
        statusEffects.DestroyEditorProperties(destroyTreeItems);
    }

    DataViewStateRegistries::Type DataViewStateRegistries::GetTypeImpl() const
    {
        return type;
    }

    DataViewStateRegistries::DataViewStateRegistries(DataView *dataView) : DataViewState(dataView),
        abilities("Ability Registry", nullptr),
        characterClasses("Character Classes Registry", nullptr),
        items("Item Registry", nullptr),
        quests("Quest Registry", nullptr),
        spells("Spell Registry", nullptr),
        statusEffects("Status Effect Registry", nullptr)
    {
        SetupBreakdowns();
        abilities.SetPrependEntryName("Ability");
        characterClasses.SetPrependEntryName("CharacterClass");
        items.SetPrependEntryName("Item");
        quests.SetPrependEntryName("Quest");
        spells.SetPrependEntryName("Spell");
        statusEffects.SetPrependEntryName("StatusEffect");
    }

    void DataViewStateRegistries::SetAbilities(const AbilityBreakdown::ListT &set)
    {
        abilities.Edit(set);
    }

    void DataViewStateRegistries::SetAbilities(AbilityBreakdown::ListT &&set)
    {
        abilities.Edit(std::move(set));
    }

    void DataViewStateRegistries::SetCharacterClasses(const CharacterClassBreakdown::ListT &set)
    {
        characterClasses.Edit(set);
    }

    void DataViewStateRegistries::SetCharacterClasses(CharacterClassBreakdown::ListT &&set)
    {
        characterClasses.Edit(std::move(set));
    }

    void DataViewStateRegistries::SetItems(const ItemBreakdown::ListT &set)
    {
        items.Edit(set);
    }

    void DataViewStateRegistries::SetItems(ItemBreakdown::ListT &&set)
    {
        items.Edit(std::move(set));
    }

    void DataViewStateRegistries::SetQuests(const QuestBreakdown::ListT &set)
    {
        quests.Edit(set);
    }

    void DataViewStateRegistries::SetQuests(QuestBreakdown::ListT &&set)
    {
        quests.Edit(std::move(set));
    }

    void DataViewStateRegistries::SetSpells(const SpellBreakdown::ListT &set)
    {
        spells.Edit(set);
    }

    void DataViewStateRegistries::SetSpells(SpellBreakdown::ListT &&set)
    {
        spells.Edit(std::move(set));
    }

    void DataViewStateRegistries::SetStatusEffects(const StatusEffectBreakdown::ListT &set)
    {
        statusEffects.Edit(set);
    }

    void DataViewStateRegistries::SetStatusEffects(StatusEffectBreakdown::ListT &&set)
    {
        statusEffects.Edit(std::move(set));
    }

    String DataViewStateRegistries::GetTreeString()
    {
        return "Registries";
    }
}