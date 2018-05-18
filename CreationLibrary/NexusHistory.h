#pragma once

#include "History.h"

#include "NexusNode.h"
#include "Nexus.h"
#include "SequenceNexusBase.h"
#include "PackagedData.h"

namespace Creation::Editing
{
    class NexusSelection;

    class NexusHistory
    {
    public:
        using Function = History::Function;

        template<class Data>
        struct Delta
        {
            Nexus<Data>* nexus;
            Data to;
            Delta(Nexus<Data>* nexus, Data to) : nexus(nexus), to(to)
            {}
        };
    public:
        explicit NexusHistory(History& history, NexusSelection& selection);
        NexusHistory(const NexusHistory& arg) = default;
        NexusHistory& operator=(const NexusHistory& arg) = default;

        template<class Data>
        void ChangeData(const std::vector<Delta<Data>>& nexusDeltas);
        void Add(const std::vector<NexusNode*>& children);
        void Remove(const std::vector<NexusNode*>& children);
    private:
        History* history;
        NexusSelection* selection;

        template<class Data>
        [[nodiscard]] static String NameFrom(const std::vector<Delta<Data>>& nexusDeltas);
        [[nodiscard]] static String NameFrom(const std::vector<NexusNode*>& children);
    private:
        struct MappedNexus
        {
            SequenceNexusBase* parent;
            NexusNode* child;
            MappedNexus(SequenceNexusBase* parent, NexusNode* child) :
                parent(parent), child(child)
            {}

            MappedNexus(const MappedNexus& arg) = delete;
            MappedNexus(MappedNexus&& arg) noexcept = default;
            MappedNexus& operator=(const MappedNexus& arg) = delete;
            MappedNexus& operator=(MappedNexus&& arg) noexcept = default;
        };

        struct StoredNexus
        {
            SequenceNexusBase* parent;
            PackagedData child;
            StoredNexus(SequenceNexusBase* parent, PackagedData&& child) :
                parent(parent), child(std::move(child))
            {}

            StoredNexus(const StoredNexus& arg) = delete;
            StoredNexus(StoredNexus&& arg) noexcept = default;
            StoredNexus& operator=(const StoredNexus& arg) = delete;
            StoredNexus& operator=(StoredNexus&& arg) noexcept = default;
        };
    };

    template<class Data>
    void NexusHistory::ChangeData(const std::vector<Delta<Data>>& nexusDeltas)
    {
        const auto name = NameFrom(nexusDeltas);

        std::vector<Delta<Data>> previousNexusDeltas;
        for (auto& delta : nexusDeltas)
            previousNexusDeltas.emplace_back(delta.nexus, delta.nexus->CurrentData());

        history->Push(
            "Changed " + name,
            [nexusDeltas, previousNexusDeltas](bool forward) mutable
            {
                auto& useDeltas = forward
                    ? nexusDeltas
                    : previousNexusDeltas;

                for(auto& nexusDelta : useDeltas)
                    nexusDelta.nexus->ChangeData(nexusDelta.to);
            });
    }

    template<class Data>
    String NexusHistory::NameFrom(const std::vector<Delta<Data>>& nexusDeltas)
    {
        return nexusDeltas.size() == 1
            ? nexusDeltas[0].nexus->Label()
            : "Group";
    }
}