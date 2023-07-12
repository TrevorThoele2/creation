
#include "DataBreakdownAVEffect.h"

namespace Creation
{
    DataBreakdown<Build::Package<::Atmos::AVEffect>::NodePackage>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent)
    {}

    DataBreakdown<Build::Package<::Atmos::AVEffect>::NodePackage>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent)
    {}

    DataBreakdown<Build::Package<::Atmos::AVEffect>::NodePackage>& DataBreakdown<Build::Package<::Atmos::AVEffect>::NodePackage>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::AVEffect>>::AddAllChildren()
    {
        AddChild(nodes);
    }

    void DataBreakdown<Build::Package<::Atmos::AVEffect>>::SetupImpl()
    {
        nodes.Setup(Get()->nodes);
    }

    DataBreakdown<Build::Package<::Atmos::AVEffect>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        nodes("Nodes", this)
    {
        AddAllChildren();
        nodes.SetPrependEntryName("Node");
    }

    DataBreakdown<Build::Package<::Atmos::AVEffect>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        nodes(std::move(arg.nodes), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::AVEffect>>& DataBreakdown<Build::Package<::Atmos::AVEffect>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        nodes = std::move(arg.nodes);
        return *this;
    }
}