#pragma once

#include <wx/treebase.h>

namespace Creation
{
    struct wxTreeItemIDHasher
    {
        size_t operator()(const wxTreeItemId &k) const;
    };
}