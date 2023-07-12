
#include "DataBreakdownElement.h"

namespace Creation
{
    void DataBreakdown<Build::Package<::Atmos::Element>>::AddAllChildren()
    {
        AddChild(name);
    }

    void DataBreakdown<Build::Package<::Atmos::Element>>::SetupImpl()
    {
        name.Setup(Get()->name);
    }

    DataBreakdown<Build::Package<::Atmos::Element>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        name(name, this)
    {
        SetAddCategory(false);
        SetAddTreePiece(false);
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Element>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        name(std::move(arg.name), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Element>>& DataBreakdown<Build::Package<::Atmos::Element>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        name = std::move(arg.name);
        return *this;
    }
}