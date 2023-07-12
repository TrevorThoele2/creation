
#include "DataBreakdownNameValuePair.h"

namespace Creation
{
    void DataBreakdown<Build::Package<::Atmos::NameValuePair>>::AddAllChildren()
    {
        AddChild(variant);
        AddChild(name);
    }

    void DataBreakdown<Build::Package<::Atmos::NameValuePair>>::SetupImpl()
    {
        variant.Setup(Get()->variant);
        name.Setup(Get()->name);
    }

    DataBreakdown<Build::Package<::Atmos::NameValuePair>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        variant("Value", this),
        name("Name", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::NameValuePair>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        variant(std::move(arg.variant), this), name(std::move(arg.name), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::NameValuePair>>& DataBreakdown<Build::Package<::Atmos::NameValuePair>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        variant = std::move(arg.variant);
        name = std::move(arg.name);
        return *this;
    }
}