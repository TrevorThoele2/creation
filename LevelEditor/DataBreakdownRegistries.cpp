
#include "DataBreakdownRegistries.h"

#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/artprov.h>
#include <wx/textdlg.h>

namespace Creation
{
    void DataBreakdown<Build::Package<::Atmos::ItemStack>>::AddAllChildren()
    {
        AddChild(wrapped);
        AddChild(count);
    }

    void DataBreakdown<Build::Package<::Atmos::ItemStack>>::SetupImpl()
    {
        wrapped.Setup(Get()->wrapped);
        count.Setup(Get()->count);
    }

    DataBreakdown<Build::Package<::Atmos::ItemStack>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        wrapped("Wrapped", this),
        count("Count", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::ItemStack>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        wrapped(std::move(arg.wrapped), this),
        count(std::move(arg.count), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::ItemStack>>& DataBreakdown<Build::Package<::Atmos::ItemStack>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        wrapped = std::move(arg.wrapped);
        count = std::move(arg.count);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Ability>>::AddAllChildren()
    {
        AddChild(name);
        AddChild(niceName);
        AddChild(description);
        AddChild(id);

        AddChild(pattern);
        AddChild(range);
        AddChild(cost);
    }

    void DataBreakdown<Build::Package<::Atmos::Ability>>::SetupImpl()
    {
        name.Setup(Get()->name);
        niceName.Setup(Get()->niceName);
        description.Setup(Get()->description);
        id.Setup(Get()->id);

        pattern.Setup(Get()->pattern);
        range.Setup(Get()->range);
        cost.Setup(Get()->cost);
    }

    DataBreakdown<Build::Package<::Atmos::Ability>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        name("Name", this),
        niceName("Nice Name", this),
        description("Description", this),
        id("ID", this),
        pattern("Pattern", this),
        range("Range", this),
        cost("Cost", this)
    {
        SetAddChildrenToProperties(false);
        SetAddChildrenToTree(false);
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ability>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        name(std::move(arg.name), this),
        niceName(std::move(arg.niceName), this),
        description(std::move(arg.description), this),
        id(std::move(arg.id), this),
        pattern(std::move(arg.pattern), this),
        range(std::move(arg.range), this),
        cost(std::move(arg.cost), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ability>>& DataBreakdown<Build::Package<::Atmos::Ability>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        name = std::move(arg.name);
        niceName = std::move(arg.niceName);
        description = std::move(arg.description);
        id = std::move(arg.id);
        pattern = std::move(arg.pattern);
        range = std::move(arg.range);
        cost = std::move(arg.cost);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::CharacterClass>::AttributePackage>::AddAllChildren()
    {
        AddChild(name);
        AddChild(base);
        AddChild(growth);
    }

    void DataBreakdown<Build::Package<::Atmos::CharacterClass>::AttributePackage>::SetupImpl()
    {
        name.Setup(Get()->name);
        base.Setup(Get()->base);
        growth.Setup(Get()->growth);
    }

    DataBreakdown<Build::Package<::Atmos::CharacterClass>::AttributePackage>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        name("Name", this),
        base("Base", this),
        growth("Growth", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::CharacterClass>::AttributePackage>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        name(std::move(arg.name), this),
        base(std::move(arg.base), this),
        growth(std::move(arg.growth), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::CharacterClass>::AttributePackage>& DataBreakdown<Build::Package<::Atmos::CharacterClass>::AttributePackage>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        name = std::move(arg.name);
        base = std::move(arg.base);
        growth = std::move(arg.growth);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::CharacterClass>::ProficiencyPackage>::AddAllChildren()
    {
        AddChild(name);
        AddChild(rating);
    }

    void DataBreakdown<Build::Package<::Atmos::CharacterClass>::ProficiencyPackage>::SetupImpl()
    {
        name.Setup(Get()->name);
        rating.Setup(Get()->rating);
    }

    DataBreakdown<Build::Package<::Atmos::CharacterClass>::ProficiencyPackage>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        name("Name", this),
        rating("Rating", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::CharacterClass>::ProficiencyPackage>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        name(std::move(arg.name), this),
        rating(std::move(arg.rating), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::CharacterClass>::ProficiencyPackage>& DataBreakdown<Build::Package<::Atmos::CharacterClass>::ProficiencyPackage>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        name = std::move(arg.name);
        rating = std::move(arg.rating);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::CharacterClass>>::AddAllChildren()
    {
        AddChild(name);
        AddChild(niceName);
        AddChild(description);
        AddChild(id);

        AddChild(resources);
        AddChild(stats);
        AddChild(proficiencies);
        AddChild(permanentStashSize);
        AddChild(temporaryStashSize);
    }

    void DataBreakdown<Build::Package<::Atmos::CharacterClass>>::SetupImpl()
    {
        name.Setup(Get()->name);
        niceName.Setup(Get()->niceName);
        description.Setup(Get()->description);
        id.Setup(Get()->id);

        resources.Setup(Get()->resources);
        stats.Setup(Get()->stats);
        proficiencies.Setup(Get()->proficiencies);
        permanentStashSize.Setup(Get()->permanentStashSize);
        temporaryStashSize.Setup(Get()->temporaryStashSize);
    }

    DataBreakdown<Build::Package<::Atmos::CharacterClass>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        name("Name", this),
        niceName("Nice Name", this),
        description("Description", this),
        id("ID", this),
        resources("Resources", this),
        stats("Stats", this),
        proficiencies("Proficiencies", this),
        permanentStashSize("Permanent Stash Size", this),
        temporaryStashSize("Temporary Stash Size", this)
    {
        SetAddChildrenToProperties(false);
        SetAddChildrenToTree(false);
        AddAllChildren();
        resources.SetPrependEntryName("Resource");
        stats.SetPrependEntryName("Stat");
        proficiencies.SetPrependEntryName("Proficiency");
    }

    DataBreakdown<Build::Package<::Atmos::CharacterClass>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        name(std::move(arg.name), this),
        niceName(std::move(arg.niceName), this),
        description(std::move(arg.description), this),
        id(std::move(arg.id), this),
        resources(std::move(arg.resources), this),
        stats(std::move(arg.stats), this),
        proficiencies(std::move(arg.proficiencies), this),
        permanentStashSize(std::move(arg.permanentStashSize), this),
        temporaryStashSize(std::move(arg.temporaryStashSize), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::CharacterClass>>& DataBreakdown<Build::Package<::Atmos::CharacterClass>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        name = std::move(arg.name);
        niceName = std::move(arg.niceName);
        description = std::move(arg.description);
        id = std::move(arg.id);
        resources = std::move(arg.resources);
        stats = std::move(arg.stats);
        proficiencies = std::move(arg.proficiencies);
        permanentStashSize = std::move(arg.permanentStashSize);
        temporaryStashSize = std::move(arg.temporaryStashSize);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::ConsumableAspect>>::AddAllChildren()
    {
        AddChild(script);
    }

    void DataBreakdown<Build::Package<::Atmos::ConsumableAspect>>::SetupImpl()
    {
        script.Setup(Get()->script);
    }

    DataBreakdown<Build::Package<::Atmos::ConsumableAspect>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        script("Script", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::ConsumableAspect>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        script(std::move(arg.script), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::ConsumableAspect>>& DataBreakdown<Build::Package<::Atmos::ConsumableAspect>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        script = std::move(arg.script);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AmmoAdditionalPackage>::AddAllChildren()
    {
        AddChild(ammoType);
    }

    void DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AmmoAdditionalPackage>::SetupImpl()
    {
        ammoType.Setup(Get()->ammoType);
    }

    DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AmmoAdditionalPackage>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        ammoType("Ammo Type", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AmmoAdditionalPackage>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        ammoType(std::move(arg.ammoType), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AmmoAdditionalPackage>& DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AmmoAdditionalPackage>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        ammoType = std::move(arg.ammoType);
        return *this;
    }

    DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::UsesAmmoPackage>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent)
    {}

    DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::UsesAmmoPackage>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent)
    {}

    DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::UsesAmmoPackage>& DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::UsesAmmoPackage>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AttackAdditionalPackage>::AddAllChildren()
    {
        AddChild(power);
        AddChild(range);
        AddChild(proficiencyName);
        AddChild(pattern);
        AddChild(allowedClasses);
        AddChild(usesAmmo);
    }

    void DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AttackAdditionalPackage>::SetupImpl()
    {
        power.Setup(Get()->power);
        pattern.Setup(Get()->pattern);
        range.Setup(Get()->range);
        allowedClasses.Setup(Get()->allowedClasses);
        proficiencyName.Setup(Get()->proficiencyName);
        usesAmmo.Setup(Get()->usesAmmo);
    }

    DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AttackAdditionalPackage>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        power("Power", this),
        pattern("Pattern", this),
        range("Range", this),
        allowedClasses("Allowed Classes", this),
        proficiencyName("Proficiency", this),
        usesAmmo("Uses Ammo", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AttackAdditionalPackage>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        power(std::move(arg.power), this),
        pattern(std::move(arg.pattern), this),
        range(std::move(arg.range), this),
        allowedClasses(std::move(arg.allowedClasses), this),
        proficiencyName(std::move(arg.proficiencyName), this),
        usesAmmo(std::move(arg.usesAmmo), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AttackAdditionalPackage>& DataBreakdown<Build::Package<::Atmos::EquippableAspect>::AttackAdditionalPackage>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        power = std::move(arg.power);
        pattern = std::move(arg.pattern);
        range = std::move(arg.range);
        allowedClasses = std::move(arg.allowedClasses);
        proficiencyName = std::move(arg.proficiencyName);
        usesAmmo = std::move(arg.usesAmmo);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::EquippableAspect>>::AddAllChildren()
    {
        AddChild(defense);
        AddChild(equipRegion);
        AddChild(ammoAdditional);
        AddChild(attackAdditional);
    }

    void DataBreakdown<Build::Package<::Atmos::EquippableAspect>>::SetupImpl()
    {
        equipRegion.Setup(Get()->equipRegion);
        defense.Setup(Get()->defense);
        ammoAdditional.Setup(Get()->ammoAdditional);
        attackAdditional.Setup(Get()->attackAdditional);
    }

    DataBreakdown<Build::Package<::Atmos::EquippableAspect>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        equipRegion("Equip Region", this),
        defense("Defense", this),
        ammoAdditional("Ammo Additional", this),
        attackAdditional("Attack Additional", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::EquippableAspect>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        equipRegion(std::move(arg.equipRegion), this),
        defense(std::move(arg.defense), this),
        ammoAdditional(std::move(arg.ammoAdditional), this),
        attackAdditional(std::move(arg.attackAdditional), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::EquippableAspect>>& DataBreakdown<Build::Package<::Atmos::EquippableAspect>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        equipRegion = std::move(arg.equipRegion);
        defense = std::move(arg.defense);
        ammoAdditional = std::move(arg.ammoAdditional);
        attackAdditional = std::move(arg.attackAdditional);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Item>>::AddAllChildren()
    {
        AddChild(name);
        AddChild(niceName);
        AddChild(description);
        AddChild(id);

        AddChild(flags);
        AddChild(consumableAspect);
        AddChild(equippableAspect);
        AddChild(buyingPrice);
        AddChild(sellingPrice);
        AddChild(portrait);
    }

    void DataBreakdown<Build::Package<::Atmos::Item>>::SetupImpl()
    {
        name.Setup(Get()->name);
        niceName.Setup(Get()->niceName);
        description.Setup(Get()->description);
        id.Setup(Get()->id);

        flags.Setup(Get()->flags);
        consumableAspect.Setup(Get()->consumableAspect);
        equippableAspect.Setup(Get()->equippableAspect);
        buyingPrice.Setup(Get()->buyingPrice);
        sellingPrice.Setup(Get()->sellingPrice);
        portrait.Setup(Get()->portrait);
    }

    DataBreakdown<Build::Package<::Atmos::Item>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        name("Name", this),
        niceName("Nice Name", this),
        description("Description", this),
        id("ID", this),
        flags("Flags", this),
        consumableAspect("Consumable Aspect", this),
        equippableAspect("Equippable Aspect", this),
        buyingPrice("Buying Price", this),
        sellingPrice("Selling Price", this),
        portrait("Portrait", this)
    {
        SetAddChildrenToProperties(false);
        SetAddChildrenToTree(false);
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Item>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        name(std::move(arg.name), this),
        niceName(std::move(arg.niceName), this),
        description(std::move(arg.description), this),
        id(std::move(arg.id), this),
        flags(std::move(arg.flags), this),
        consumableAspect(std::move(arg.consumableAspect), this),
        equippableAspect(std::move(arg.equippableAspect), this),
        buyingPrice(std::move(arg.buyingPrice), this),
        sellingPrice(std::move(arg.sellingPrice), this),
        portrait(std::move(arg.portrait), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Item>>& DataBreakdown<Build::Package<::Atmos::Item>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        name = std::move(arg.name);
        niceName = std::move(arg.niceName);
        description = std::move(arg.description);
        id = std::move(arg.id);
        flags = std::move(arg.flags);
        consumableAspect = std::move(arg.consumableAspect);
        equippableAspect = std::move(arg.equippableAspect);
        buyingPrice = std::move(arg.buyingPrice);
        sellingPrice = std::move(arg.sellingPrice);
        portrait = std::move(arg.portrait);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Quest::Part>>::AddAllChildren()
    {
        AddChild(name);
        AddChild(description);
        AddChild(type);
    }

    void DataBreakdown<Build::Package<::Atmos::Quest::Part>>::SetupImpl()
    {
        name.Setup(Get()->name);
        description.Setup(Get()->description);
        type.Setup(Get()->type);
    }

    DataBreakdown<Build::Package<::Atmos::Quest::Part>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        name("Name", this),
        description("Description", this),
        type("Type", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Quest::Part>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        name(std::move(arg.name), this),
        description(std::move(arg.description), this),
        type(std::move(arg.type), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Quest::Part>>& DataBreakdown<Build::Package<::Atmos::Quest::Part>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        name = std::move(arg.name);
        description = std::move(arg.description);
        type = std::move(arg.type);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Quest>>::AddAllChildren()
    {
        AddChild(name);
        AddChild(niceName);
        AddChild(description);
        AddChild(id);

        AddChild(parts);
        AddChild(script);
    }

    void DataBreakdown<Build::Package<::Atmos::Quest>>::SetupImpl()
    {
        name.Setup(Get()->name);
        niceName.Setup(Get()->niceName);
        description.Setup(Get()->description);
        id.Setup(Get()->id);

        typedef decltype(parts) PartsBreakdownT;
        parts.Setup(Get()->parts);
        parts.SetNiceNameFunctions(PartsBreakdownT::NiceNameExtractorFunction(static_cast<String(*)(PartsBreakdownT::BreakdownT&)>([](PartsBreakdownT::BreakdownT &breakdown) { return breakdown.name.Get()->Build(); })),
            PartsBreakdownT::NiceNameGetEventFunction(static_cast<Event<const DataBreakdownEditArgs&>*(*)(PartsBreakdownT::BreakdownT&)>([](PartsBreakdownT::BreakdownT &breakdown) -> Event<const DataBreakdownEditArgs&>* { return &breakdown.name.edited; })),
            PartsBreakdownT::NameSetFunction(static_cast<void(*)(PartsBreakdownT::BreakdownT&, const String&)>([](PartsBreakdownT::BreakdownT &breakdown, const String &str) { Build::Package<::Atmos::Name> package; package.value = str; breakdown.name.Edit(std::move(package)); })));
        script.Setup(Get()->script);
    }

    DataBreakdown<Build::Package<::Atmos::Quest>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        name("Name", this),
        niceName("Nice Name", this),
        description("Description", this),
        id("ID", this),
        parts("Parts", this),
        script("Script", this)
    {
        AddAllChildren();
        parts.SetPrependEntryName("Part");
    }

    DataBreakdown<Build::Package<::Atmos::Quest>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        name(std::move(arg.name), this),
        niceName(std::move(arg.niceName), this),
        description(std::move(arg.description), this),
        id(std::move(arg.id), this),
        parts(std::move(arg.parts), this),
        script(std::move(arg.script), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Quest>>& DataBreakdown<Build::Package<::Atmos::Quest>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        name = std::move(arg.name);
        niceName = std::move(arg.niceName);
        description = std::move(arg.description);
        id = std::move(arg.id);
        parts = std::move(arg.parts);
        script = std::move(arg.script);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Spell>>::AddAllChildren()
    {
        AddChild(name);
        AddChild(niceName);
        AddChild(description);
        AddChild(id);

        AddChild(attackPattern);
        AddChild(pieceOverworld);
        AddChild(range);
        AddChild(resourceCost);
        AddChild(allowedClasses);
    }

    void DataBreakdown<Build::Package<::Atmos::Spell>>::SetupImpl()
    {
        name.Setup(Get()->name);
        niceName.Setup(Get()->niceName);
        description.Setup(Get()->description);
        id.Setup(Get()->id);

        attackPattern.Setup(Get()->attackPattern);
        pieceOverworld.Setup(Get()->pieceOverworld);
        range.Setup(Get()->range);
        resourceCost.Setup(Get()->resourceCost);
        allowedClasses.Setup(Get()->allowedClasses);
    }

    DataBreakdown<Build::Package<::Atmos::Spell>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        name("Name", this),
        niceName("Nice Name", this),
        description("Description", this),
        id("ID", this),
        attackPattern("Attack Pattern", this),
        pieceOverworld("Piece Overworld", this),
        range("Range", this),
        resourceCost("Resource Cost", this),
        allowedClasses("Allowed Classes", this)
    {
        SetAddChildrenToProperties(false);
        SetAddChildrenToTree(false);
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Spell>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        name(std::move(arg.name), this),
        niceName(std::move(arg.niceName), this),
        description(std::move(arg.description), this),
        id(std::move(arg.id), this),
        attackPattern(std::move(arg.attackPattern), this),
        pieceOverworld(std::move(arg.pieceOverworld), this),
        range(std::move(arg.range), this),
        resourceCost(std::move(arg.resourceCost), this),
        allowedClasses(std::move(arg.allowedClasses), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Spell>>& DataBreakdown<Build::Package<::Atmos::Spell>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        name = std::move(arg.name);
        niceName = std::move(arg.niceName);
        description = std::move(arg.description);
        id = std::move(arg.id);
        attackPattern = std::move(arg.attackPattern);
        pieceOverworld = std::move(arg.pieceOverworld);
        range = std::move(arg.range);
        resourceCost = std::move(arg.resourceCost);
        allowedClasses = std::move(arg.allowedClasses);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::StatusEffect>>::AddAllChildren()
    {
        AddChild(name);
        AddChild(niceName);
        AddChild(description);
        AddChild(id);

        AddChild(script);
        AddChild(applicationCount);
        AddChild(proficiencyName);
        AddChild(accuracy);
        AddChild(positive);
    }

    void DataBreakdown<Build::Package<::Atmos::StatusEffect>>::SetupImpl()
    {
        name.Setup(Get()->name);
        niceName.Setup(Get()->niceName);
        description.Setup(Get()->description);
        id.Setup(Get()->id);

        script.Setup(Get()->script);
        applicationCount.Setup(Get()->applicationCount);
        proficiencyName.Setup(Get()->proficiencyName);
        accuracy.Setup(Get()->accuracy);
        positive.Setup(Get()->positive);
    }

    DataBreakdown<Build::Package<::Atmos::StatusEffect>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        name("Name", this),
        niceName("Nice Name", this),
        description("Description", this),
        id("ID", this),
        script("Script", this),
        applicationCount("Application Count", this),
        proficiencyName("Proficiency", this),
        accuracy("Accuracy", this),
        positive("Positive", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::StatusEffect>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        name(std::move(arg.name), this),
        niceName(std::move(arg.niceName), this),
        description(std::move(arg.description), this),
        id(std::move(arg.id), this),
        script(std::move(arg.script), this),
        applicationCount(std::move(arg.applicationCount), this),
        proficiencyName(std::move(arg.proficiencyName), this),
        accuracy(std::move(arg.accuracy), this),
        positive(std::move(arg.positive), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::StatusEffect>>& DataBreakdown<Build::Package<::Atmos::StatusEffect>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        name = std::move(arg.name);
        niceName = std::move(arg.niceName);
        description = std::move(arg.description);
        id = std::move(arg.id);
        script = std::move(arg.script);
        applicationCount = std::move(arg.applicationCount);
        proficiencyName = std::move(arg.proficiencyName);
        accuracy = std::move(arg.accuracy);
        positive = std::move(arg.positive);
        return *this;
    }
}