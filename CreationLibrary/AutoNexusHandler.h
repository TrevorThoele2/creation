#pragma once

#include <vector>
#include <list>
#include "AutoNexus.h"

namespace Creation::Editing
{
    template<class Data>
    class Nexus;

    template<class Data>
    class AutoNexusHandler
    {
    public:
        AutoNexusHandler() = default;
        AutoNexusHandler(AutoNexusHandler&& arg) noexcept = default;
        AutoNexusHandler& operator=(AutoNexusHandler&& arg) noexcept = default;
    public:
        template<class Child>
        void Auto(Nexus<Data>& parent, Child& child, typename Child::DataT Data::* childDataRetriever);

        void DecomposeChangeData(Data& data);

        [[nodiscard]] std::vector<NexusNode*> AllAutoNexi() const;
    private:
        std::list<AutoNexus<Data>> autoNexi;
    };

    template<class Data>
    template<class Child>
    void AutoNexusHandler<Data>::Auto(Nexus<Data>& parent, Child& child, typename Child::DataT Data::* childDataRetriever)
    {
        autoNexi.emplace_back(parent, child, childDataRetriever);
    }

    template<class Data>
    void AutoNexusHandler<Data>::DecomposeChangeData(Data& data)
    {
        for (auto& nexus : autoNexi)
            nexus.DecomposeChangeData(data);
    }

    template<class Data>
    std::vector<NexusNode*> AutoNexusHandler<Data>::AllAutoNexi() const
    {
        std::vector<NexusNode*> returnValue;
        returnValue.reserve(autoNexi.size());
        for (auto& nexus : autoNexi)
            returnValue.push_back(nexus.Node());
        return returnValue;
    }

    template<class Data>
    class NullAutoNexusHandler
    {
    public:
        NullAutoNexusHandler() = default;
        NullAutoNexusHandler(NullAutoNexusHandler&& arg) noexcept = default;
        NullAutoNexusHandler& operator=(NullAutoNexusHandler&& arg) noexcept = default;
    public:
        void DecomposeChangeData(Data& data);

        [[nodiscard]] std::vector<NexusNode*> AllAutoNexi() const;
    };

    template<class Data>
    void NullAutoNexusHandler<Data>::DecomposeChangeData(Data& data)
    {}

    template<class Data>
    std::vector<NexusNode*> NullAutoNexusHandler<Data>::AllAutoNexi() const
    {
        return {};
    }
}