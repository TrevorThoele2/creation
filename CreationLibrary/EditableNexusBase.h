#pragma once

#include <memory>
#include "NexusBatchBase.h"

class wxPropertyGrid;

namespace Creation::Editing
{
    class EditableNexusBase
    {
    public:
        virtual ~EditableNexusBase() = 0;

        virtual std::unique_ptr<NexusBatchBase> StartEditingBatch(wxPropertyGrid& grid) = 0;
    };
}