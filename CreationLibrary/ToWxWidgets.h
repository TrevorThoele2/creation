#pragma once

#include <wx/arrstr.h>
#include <vector>
#include <Chroma/StringUtility.h>

namespace Creation::WxWidgets
{
    template<class T>
    [[nodiscard]] wxArrayString ToStringArray(const std::vector<T>& values)
    {
        wxArrayString returnValue;
        for (auto& value : values)
            returnValue.Add(Chroma::ToString(value));
        return returnValue;
    }
}