#pragma once

#include "WorldElementBase.h"
#include "Nexus.h"
#include "MutationCurator.h"
#include "GhostWorldElement.h"

namespace Creation::Editing
{
    template<class Data>
    class WorldElementCommon : public WorldElementBase
    {
    public:
        using DataT = Data;

        using Nexus = Editing::Nexus<DataT>;
    public:
        [[nodiscard]] NexusNode& UnderlyingNexusNode() final;
        [[nodiscard]] const NexusNode& UnderlyingNexusNode() const final;
    public:
        [[nodiscard]] Nexus& UnderlyingNexus();
        [[nodiscard]] const Nexus& UnderlyingNexus() const;
    protected:
        WorldElementCommon(Nexus& nexus, Arca::Reliquary& reliquary);
        WorldElementCommon(WorldElementCommon&& arg) noexcept;
        WorldElementCommon& operator=(WorldElementCommon&& arg) noexcept;

        [[nodiscard]] Arca::Reliquary& Reliquary() const;

        Arca::MutablePointer MutablePointer();

        [[nodiscard]] std::unique_ptr<GhostWorldElementBase> CreateGhostImpl() const final;
    protected:
        virtual void OnDataChanged(DataT data) = 0;
    private:
        Nexus* nexus;
        Arca::Reliquary* reliquary;
    private:
        std::vector<ScopedEventConnection> eventConnections;

        void SubscribeEvents();
    };

    template<class Data>
    NexusNode& WorldElementCommon<Data>::UnderlyingNexusNode()
    {
        return *nexus;
    }

    template<class Data>
    const NexusNode& WorldElementCommon<Data>::UnderlyingNexusNode() const
    {
        return *nexus;
    }

    template<class Data>
    auto WorldElementCommon<Data>::UnderlyingNexus() -> Nexus&
    {
        return *nexus;
    }

    template<class Data>
    auto WorldElementCommon<Data>::UnderlyingNexus() const -> const Nexus&
    {
        return *nexus;
    }

    template<class Data>
    WorldElementCommon<Data>::WorldElementCommon(Nexus& nexus, Arca::Reliquary& reliquary) :
        nexus(&nexus),
        reliquary(&reliquary)
    {
        SubscribeEvents();
    }

    template<class Data>
    WorldElementCommon<Data>::WorldElementCommon(WorldElementCommon&& arg) noexcept :
        nexus(std::move(arg.nexus)),
        reliquary(std::move(arg.reliquary))
    {
        SubscribeEvents();
    }

    template<class Data>
    WorldElementCommon<Data>& WorldElementCommon<Data>::operator=(WorldElementCommon&& arg) noexcept
    {
        nexus = std::move(arg.nexus);
        reliquary = std::move(arg.reliquary);
        arg.eventConnections.clear();
        SubscribeEvents();
        return *this;
    }

    template<class Data>
    Arca::Reliquary& WorldElementCommon<Data>::Reliquary() const
    {
        return *reliquary;
    }

    template<class Data>
    Arca::MutablePointer WorldElementCommon<Data>::MutablePointer()
    {
        return reliquary->Find<Creation::MutationCurator>().RetrieveMutablePointer();
    }

    template<class Data>
    std::unique_ptr<GhostWorldElementBase> WorldElementCommon<Data>::CreateGhostImpl() const
    {
        return std::make_unique<GhostWorldElement<Data>>(*nexus, *reliquary);
    }

    template<class Data>
    void WorldElementCommon<Data>::SubscribeEvents()
    {
        eventConnections.push_back(
            this->nexus->onDataChanged.Subscribe([this](DataT data)
                {
                    OnDataChanged(data);
                }));
    }
}