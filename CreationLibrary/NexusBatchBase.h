#pragma once

#include "NexusNode.h"

namespace Creation::Editing
{
    class NexusBatchBase
    {
    public:
        virtual ~NexusBatchBase() = 0;

        virtual void AttemptAdd(NexusNode& node) = 0;
        virtual void AttemptRemove(NexusNode& node) = 0;

        [[nodiscard]] virtual size_t Size() const = 0;
    };
}