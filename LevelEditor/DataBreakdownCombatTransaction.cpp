
#include "DataBreakdownCombatTransaction.h"

namespace Creation
{
    void DataBreakdown<Build::Package<::Atmos::CombatTransactionGenerator>>::AddAllChildren()
    {
        AddChild(resourceName);
        AddChild(statName);
        AddChild(element);
        AddChild(proficiencyName);
    }

    void DataBreakdown<Build::Package<::Atmos::CombatTransactionGenerator>>::SetupImpl()
    {
        resourceName.Setup(Get()->resourceName);
        statName.Setup(Get()->statName);
        element.Setup(Get()->element);
        proficiencyName.Setup(Get()->proficiencyName);
    }

    DataBreakdown<Build::Package<::Atmos::CombatTransactionGenerator>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        resourceName("Resource", this),
        statName("Stat", this),
        element("Element", this),
        proficiencyName("Proficiency", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::CombatTransactionGenerator>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        resourceName(std::move(arg.resourceName), this),
        statName(std::move(arg.statName), this),
        element(std::move(arg.element), this),
        proficiencyName(std::move(arg.proficiencyName), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::CombatTransactionGenerator>>& DataBreakdown<Build::Package<::Atmos::CombatTransactionGenerator>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        resourceName = std::move(arg.resourceName);
        statName = std::move(arg.statName);
        element = std::move(arg.element);
        proficiencyName = std::move(arg.proficiencyName);
        return *this;
    }
}