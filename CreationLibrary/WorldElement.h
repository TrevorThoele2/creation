#pragma once

#include "WorldElementBase.h"
#include <Arca/Reliquary.h>

namespace Creation::Editing
{
    template<class Data>
    class WorldElement final : public WorldElementBase
    {
    public:
        using DataT = Data;
        using Nexus = Editing::Nexus<DataT>;
    public:
        WorldElement(Nexus& nexus, Arca::Reliquary& reliquary);
        WorldElement(WorldElement&& arg) noexcept = default;
    public:
        [[nodiscard]] NexusNode& UnderlyingNexusNode() override;
        [[nodiscard]] const NexusNode& UnderlyingNexusNode() const override;
    protected:
        [[nodiscard]] std::unique_ptr<GhostWorldElementBase> CreateGhostImpl() const override;
    private:
        Nexus* nexus;
    };

    template<class Data>
    WorldElement<Data>::WorldElement(Nexus& nexus, Arca::Reliquary&) : nexus(&nexus)
    {}

    template<class Data>
    NexusNode& WorldElement<Data>::UnderlyingNexusNode()
    {
        return *nexus;
    }

    template<class Data>
    const NexusNode& WorldElement<Data>::UnderlyingNexusNode() const
    {
        return *nexus;
    }

    template<class Data>
    std::unique_ptr<GhostWorldElementBase> WorldElement<Data>::CreateGhostImpl() const
    {
        return {};
    }
}