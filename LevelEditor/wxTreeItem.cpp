
#include "wxTreeItem.h"

namespace Creation
{
    size_t wxTreeItemIDHasher::operator()(const wxTreeItemId &k) const
    {
        return std::hash<void*>()(k.GetID());
    }
}