
#include "DataBreakdownGameData.h"

#include <Atmos/CharacterClass.h>

#include "ActionData.h"

#include <wx/stattext.h>
#include <wx/statline.h>

namespace Creation
{
    void DataBreakdown<Build::Package<::Atmos::Direction>>::AddAllChildren()
    {
        AddChild(value);
    }

    void DataBreakdown<Build::Package<::Atmos::Direction>>::SetupImpl()
    {
        value.Setup(Get()->value);
    }

    DataBreakdown<Build::Package<::Atmos::Direction>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        value(name, this)
    {
        SetAddCategory(false);
        SetAddTreePiece(false);
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Direction>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        value(std::move(arg.value), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Direction>>& DataBreakdown<Build::Package<::Atmos::Direction>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        value = std::move(arg.value);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::CharacterClassGroup>>::AddAllChildren()
    {
        AddChild(classes);
    }

    void DataBreakdown<Build::Package<::Atmos::CharacterClassGroup>>::SetupImpl()
    {
        classes.Setup(Get()->classes);
    }

    DataBreakdown<Build::Package<::Atmos::CharacterClassGroup>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        classes(name, this)
    {
        classes.SetMakeChildrenCategory(false);
        classes.SetPrependEntryName("Class");
        SetAddCategory(false);
        SetAddTreePiece(false);
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::CharacterClassGroup>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        classes(std::move(arg.classes), parent)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::CharacterClassGroup>>& DataBreakdown<Build::Package<::Atmos::CharacterClassGroup>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        classes = std::move(arg.classes);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Acumen>>::AddAllChildren()
    {
        AddChild(value);
    }

    void DataBreakdown<Build::Package<::Atmos::Acumen>>::SetupImpl()
    {
        value.Setup(Get()->value);
    }

    DataBreakdown<Build::Package<::Atmos::Acumen>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        value(name, this)
    {
        SetAddCategory(false);
        SetAddTreePiece(false);
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Acumen>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        value(std::move(arg.value), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Acumen>>& DataBreakdown<Build::Package<::Atmos::Acumen>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        value = std::move(arg.value);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Act::Parameter>>::AddAllChildren()
    {
        AddChild(variant);
    }

    void DataBreakdown<Build::Package<::Atmos::Act::Parameter>>::SetupImpl()
    {
        variant.Setup(Get()->variant);
    }

    DataBreakdown<Build::Package<::Atmos::Act::Parameter>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        variant("Variant", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Act::Parameter>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        variant(std::move(arg.variant), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Act::Parameter>>& DataBreakdown<Build::Package<::Atmos::Act::Parameter>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        variant = std::move(arg.variant);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Act::Action>>::AddAllChildren()
    {
        AddChild(id);
        AddChild(parameters);
    }

    void DataBreakdown<Build::Package<::Atmos::Act::Action>>::SetupImpl()
    {
        id.Setup(Get()->id);
        parameters.Setup(Get()->parameters);
    }

    DataBreakdown<Build::Package<::Atmos::Act::Action>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        id("ID", this),
        parameters("Parameters", this)
    {
        AddAllChildren();
        parameters.SetPrependEntryName("Parameter");
    }

    DataBreakdown<Build::Package<::Atmos::Act::Action>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        id(std::move(arg.id), this),
        parameters(std::move(arg.parameters), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Act::Action>>& DataBreakdown<Build::Package<::Atmos::Act::Action>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        id = std::move(arg.id);
        parameters = std::move(arg.parameters);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::ResourceAttributeTable>>>::AddAllChildren()
    {
        AddChild(health);
        AddChild(mana);
        AddChild(acumen);
    }

    void DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::ResourceAttributeTable>>>::SetupImpl()
    {
        health.Setup(Get()->health);
        mana.Setup(Get()->mana);
        acumen.Setup(Get()->acumen);
    }

    DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::ResourceAttributeTable>>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        health("Health", this),
        mana("Mana", this),
        acumen("Acumen", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::ResourceAttributeTable>>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        health(std::move(arg.health), this),
        mana(std::move(arg.mana), this),
        acumen(std::move(arg.acumen), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::ResourceAttributeTable>>>& DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::ResourceAttributeTable>>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        health = std::move(arg.health);
        mana = std::move(arg.mana);
        acumen = std::move(arg.acumen);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::EntryPackage>::AddAllChildren()
    {
        AddChild(name);
        AddChild(niceName);
        AddChild(opposing);
    }

    void DataBreakdown<Build::Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::EntryPackage>::SetupImpl()
    {
        name.Setup(Get()->name);
        niceName.Setup(Get()->niceName);
        opposing.Setup(Get()->opposing);
    }

    DataBreakdown<Build::Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::EntryPackage>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        name("Name", this),
        niceName("Nice Name", this),
        opposing("Opposing", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::EntryPackage>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        name(std::move(arg.name), this),
        niceName(std::move(arg.niceName), this),
        opposing(std::move(arg.opposing), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::EntryPackage>& DataBreakdown<Build::Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::EntryPackage>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        name = std::move(arg.name);
        niceName = std::move(arg.niceName);
        opposing = std::move(arg.opposing);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>>::AddAllChildren()
    {
        AddChild(entries);
    }

    void DataBreakdown<Build::Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>>::SetupImpl()
    {
        entries.Setup(Get()->entries);
    }

    DataBreakdown<Build::Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        entries("Entries", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        entries(std::move(arg.entries), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>>& DataBreakdown<Build::Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        entries = std::move(arg.entries);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::Element>>::EntryPackage>::AddAllChildren()
    {
        AddChild(name);
        AddChild(niceName);
        AddChild(opposing);
        AddChild(statName);
    }

    void DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::Element>>::EntryPackage>::SetupImpl()
    {
        name.Setup(Get()->name);
        niceName.Setup(Get()->niceName);
        opposing.Setup(Get()->opposing);
        statName.Setup(Get()->statName);
    }

    DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::Element>>::EntryPackage>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        name("Name", this),
        niceName("Nice Name", this),
        opposing("Opposing", this),
        statName("Stat Name", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::Element>>::EntryPackage>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        name(std::move(arg.name), this),
        niceName(std::move(arg.niceName), this),
        opposing(std::move(arg.opposing), this),
        statName(std::move(arg.statName), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::Element>>::EntryPackage>& DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::Element>>::EntryPackage>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        name = std::move(arg.name);
        niceName = std::move(arg.niceName);
        opposing = std::move(arg.opposing);
        statName = std::move(arg.statName);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::Element>>>::AddAllChildren()
    {
        AddChild(neutral);
        AddChild(entries);
    }

    void DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::Element>>>::SetupImpl()
    {
        neutral.Setup(Get()->neutral);
        entries.Setup(Get()->entries);
    }

    DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::Element>>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        neutral("Neutral", this),
        entries("Entries", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::Element>>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        neutral(std::move(arg.neutral), this),
        entries(std::move(arg.entries), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::Element>>>& DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::Element>>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        neutral = std::move(arg.neutral);
        entries = std::move(arg.entries);
        return *this;
    }
}