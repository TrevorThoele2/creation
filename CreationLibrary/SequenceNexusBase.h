#pragma once

#include "NexusNode.h"
#include "PackagedData.h"

namespace Creation::Editing
{
    class SequenceNexusBase : public NexusNode
    {
    public:
        virtual ~SequenceNexusBase() = 0;

        virtual NexusNode* Add() = 0;
        virtual void Remove(NexusNode& nexus) = 0;

        virtual NexusNode* Reinstate(PackagedData&& data) = 0;
        [[nodiscard]] virtual PackagedData Release(NexusNode& data) = 0;

        [[nodiscard]] virtual String Label() const = 0;
    };
}