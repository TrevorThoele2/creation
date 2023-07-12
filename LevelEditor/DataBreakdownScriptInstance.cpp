
#include "DataBreakdownScriptInstance.h"

namespace Creation
{
    void DataBreakdown<Build::Package<::Atmos::Script::Instance>>::AddAllChildren()
    {
        AddChild(asset);
        AddChild(globalItems);
        AddChild(executeName);
        AddChild(parameters);
    }

    void DataBreakdown<Build::Package<::Atmos::Script::Instance>>::SetupImpl()
    {
        asset.Setup(Get()->asset);
        globalItems.Setup(Get()->globalItems);
        executeName.Setup(Get()->executeName);
        parameters.Setup(Get()->parameters);
    }

    DataBreakdown<Build::Package<::Atmos::Script::Instance>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        asset("Asset", this),
        globalItems("Global Items", this),
        executeName("Execute Name", this),
        parameters("Parameters", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Script::Instance>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        asset(std::move(arg.asset), this),
        globalItems(std::move(arg.globalItems), this),
        executeName(std::move(arg.executeName), this),
        parameters(std::move(arg.parameters), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Script::Instance>>& DataBreakdown<Build::Package<::Atmos::Script::Instance>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        asset = std::move(arg.asset);
        globalItems = std::move(arg.globalItems);
        executeName = std::move(arg.executeName);
        parameters = std::move(arg.parameters);
        return *this;
    }
}