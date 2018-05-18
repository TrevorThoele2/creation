#pragma once

#include "DataRoot.h"

#include "ListData.h"
#include "EntityPrototypeData.h"

namespace Creation::Editing::Data
{
    class EntitiesRoot final : public Root
    {
    public:
        struct Input
        {
            std::list<EntityPrototype>* entities;
            Arca::Reliquary* reliquary;
            bool visible;
            const NexusHistory* nexusHistory;
            UI* ui;
        };
    public:
        Nexus<std::list<EntityPrototype>> entities;
    public:
        EntitiesRoot(Input& input);
        EntitiesRoot(const EntitiesRoot& arg) = delete;
        EntitiesRoot(EntitiesRoot&& arg) noexcept = default;
    protected:
        [[nodiscard]] std::vector<SequenceNexusBase*> TopNexi() override;
    };
}