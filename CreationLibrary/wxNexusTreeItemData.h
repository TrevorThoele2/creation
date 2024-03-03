#pragma once

#include <wx/treebase.h>
#include "NexusNode.h"

namespace Creation::Editing
{
    class wxNexusTreeItemData final : public wxClientData
    {
    public:
        NexusNode* node;
        explicit wxNexusTreeItemData(NexusNode& node) : node(&node)
        {}
    };
}