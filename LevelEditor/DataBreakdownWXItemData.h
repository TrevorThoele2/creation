#pragma once

#include "DataBreakdownCommon.h"
#include <wx/treebase.h>

namespace Creation
{
    class DataBreakdownWXItemData : public wxTreeItemData
    {
    public:
        DataBreakdownCommon *data;
        DataBreakdownWXItemData(DataBreakdownCommon *data);
    };
}