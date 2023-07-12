
#include "DataBreakdownCombatChain.h"

namespace Creation
{
    void DataBreakdown<Build::Package<::Atmos::CombatChain::Node>>::AddAllChildren()
    {
        AddChild(transaction);
        AddChild(statusEffect);
    }

    void DataBreakdown<Build::Package<::Atmos::CombatChain::Node>>::SetupImpl()
    {
        transaction.Setup(Get()->transaction);
        statusEffect.Setup(Get()->statusEffect);
    }

    DataBreakdown<Build::Package<::Atmos::CombatChain::Node>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        transaction("Transaction", this),
        statusEffect("Status Effect", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::CombatChain::Node>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        transaction(std::move(arg.transaction), this),
        statusEffect(std::move(arg.statusEffect), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::CombatChain::Node>>& DataBreakdown<Build::Package<::Atmos::CombatChain::Node>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        transaction = std::move(arg.transaction);
        statusEffect = std::move(arg.statusEffect);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::CombatChain>>::AddAllChildren()
    {
        AddChild(nodes);
    }

    void DataBreakdown<Build::Package<::Atmos::CombatChain>>::SetupImpl()
    {
        nodes.Setup(Get()->nodes);
    }

    DataBreakdown<Build::Package<::Atmos::CombatChain>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        nodes("Nodes", this)
    {
        AddAllChildren();
        nodes.SetPrependEntryName("Node");
    }

    DataBreakdown<Build::Package<::Atmos::CombatChain>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        nodes(std::move(arg.nodes), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::CombatChain>>& DataBreakdown<Build::Package<::Atmos::CombatChain>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        nodes = std::move(arg.nodes);
        return *this;
    }
}