
#include "DataBreakdownCommonKey.h"

#include "DataBreakdownCommon.h"

namespace Creation
{
    DataBreakdownCommonKey::DataBreakdownCommonKey(const std::type_index &parentTI, const String &parentName, const std::type_index &ti, const String &name, bool ignoreName) : parentTI(parentTI), parentName(parentName), ti(ti), name(name), ignoreName(ignoreName)
    {}

    DataBreakdownCommonKey::DataBreakdownCommonKey(DataBreakdownCommon &from) : DataBreakdownCommonKey((from.GetParent()) ? typeid(*from.GetParent()) : typeid(int), ((from.GetParent()) ? from.GetParent()->GetName() : ""), typeid(from), from.GetName(), from.IgnoreNameForKey())
    {}

    bool DataBreakdownCommonKey::operator==(const DataBreakdownCommonKey &arg) const
    {
        return parentTI == arg.parentTI && parentName == arg.parentName && ti == arg.ti && name == arg.name && ignoreName == arg.ignoreName;
    }

    bool DataBreakdownCommonKey::operator!=(const DataBreakdownCommonKey &arg) const
    {
        return !(*this == arg);
    }

    void DataBreakdownCommonKey::Set(const std::type_index &parentTI, const String &parentName, const std::type_index &ti, const String &name, bool ignoreName)
    {
        this->parentTI = parentTI;
        this->parentName = parentName;
        this->ti = ti;
        this->name = name;
        this->ignoreName = ignoreName;
    }

    void DataBreakdownCommonKey::Set(DataBreakdownCommon &from)
    {
        Set((from.GetParent()) ? typeid(*from.GetParent()) : typeid(int), ((from.GetParent()) ? from.GetParent()->GetName() : ""), typeid(from), from.GetName(), from.IgnoreNameForKey());
    }

    size_t DataBreakdownCommonKeyHasher::operator()(const DataBreakdownCommonKey &k) const
    {
        if (!k.ignoreName)
            return std::hash<std::type_index>()(k.parentTI) ^
                (std::hash<String>()(k.parentName) << 1) ^
                (std::hash<std::type_index>()(k.ti) >> 1) ^
                (std::hash<String>()(k.name) << 1);
        else
            return std::hash<std::type_index>()(k.parentTI) ^
                (std::hash<String>()(k.parentName) << 1) ^
                (std::hash<std::type_index>()(k.ti) >> 1);
    }
}