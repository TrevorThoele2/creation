#pragma once

#include <typeindex>

#include "String.h"

namespace Creation
{
    class DataBreakdownCommon;
    struct DataBreakdownCommonKey
    {
        std::type_index parentTI;
        String parentName;
        std::type_index ti;
        String name;
        bool ignoreName;
        DataBreakdownCommonKey() = default;
        DataBreakdownCommonKey(const std::type_index &parentTI, const String &parentName, const std::type_index &ti, const String &name, bool ignoreName);
        DataBreakdownCommonKey(DataBreakdownCommon &from);
        bool operator==(const DataBreakdownCommonKey &arg) const;
        bool operator!=(const DataBreakdownCommonKey &arg) const;

        void Set(const std::type_index &parentTI, const String &parentName, const std::type_index &ti, const String &name, bool ignoreName);
        void Set(DataBreakdownCommon &from);
    };

    struct DataBreakdownCommonKeyHasher
    {
        size_t operator()(const DataBreakdownCommonKey &k) const;
    };
}