#pragma once

#include "DataRoot.h"

#include "ListData.h"
#include "EntityBoundaryPositionData.h"

namespace Creation::Editing::Data
{
    class EntityBoundaryRoot final : public Root
    {
    public:
        struct Input
        {
            std::list<EntityBoundaryPosition>* entityBoundary;
            Arca::Reliquary* reliquary;
            bool visible;
            const NexusHistory* nexusHistory;
            UI* ui;
        };
    public:
        Nexus<std::list<EntityBoundaryPosition>> entityBoundary;
    public:
        EntityBoundaryRoot(Input& input);
        EntityBoundaryRoot(const EntityBoundaryRoot& arg) = delete;
        EntityBoundaryRoot(EntityBoundaryRoot&& arg) noexcept = default;
    protected:
        [[nodiscard]] std::vector<SequenceNexusBase*> TopNexi() override;
    };
}
