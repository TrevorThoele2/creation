#pragma once

#include <wx/treebase.h>

namespace std
{
    template<>
    struct hash<wxTreeItemId>
    {
        using argument_type = wxTreeItemId;
        using result_type = std::size_t;

        result_type operator()(const argument_type& arg) const noexcept
        {
            return std::hash<void*>()(arg.GetID());
        }
    };
}