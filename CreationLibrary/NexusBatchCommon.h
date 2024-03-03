#pragma once

#include "NexusBatchBase.h"
#include "AutoProperty.h"

#include <wx/propgrid/propgrid.h>

namespace Creation::Editing
{
    template<class Object>
    class NexusBatch;

    template<class Object>
    class NexusBatchCommon : public NexusBatchBase
    {
    public:
        using ObjectT = Object;

        using Nexus = Nexus<ObjectT>;
    public:
        virtual ~NexusBatchCommon() = 0;

        void AttemptAdd(NexusNode& node) final;
        void AttemptRemove(NexusNode& node) final;

        void Add(Nexus& nexus);
        void Remove(Nexus& nexus);
        [[nodiscard]] size_t Size() const final;
    protected:
        explicit NexusBatchCommon(wxPropertyGrid& grid);
        NexusBatchCommon(NexusBatchCommon&& arg) noexcept;
    protected:
        template<class Child>
        void Auto(Child& child, typename Child::Nexus Nexus::* childNexusRetriever);
    private:
        size_t size = 0;

        wxPropertyGrid* grid;
    private:
        std::vector<Data::AutoProperty<ObjectT>> autoProperties;
    };

    template<class Object>
    NexusBatchCommon<Object>::~NexusBatchCommon() = default;

    template<class Object>
    void NexusBatchCommon<Object>::AttemptAdd(NexusNode& node)
    {
        auto casted = dynamic_cast<Nexus*>(&node);
        if (casted)
            Add(*casted);
    }

    template<class Object>
    void NexusBatchCommon<Object>::AttemptRemove(NexusNode& node)
    {
        auto casted = dynamic_cast<Nexus*>(&node);
        if (casted)
            Remove(*casted);
    }

    template<class Object>
    void NexusBatchCommon<Object>::Add(Nexus& nexus)
    {
        for (auto& property : autoProperties)
            property.DecomposeAddNexus(nexus);
        ++size;
    }

    template<class Object>
    void NexusBatchCommon<Object>::Remove(Nexus& nexus)
    {
        for (auto& property : autoProperties)
            property.DecomposeRemoveNexus(nexus);
        --size;
    }

    template<class Object>
    size_t NexusBatchCommon<Object>::Size() const
    {
        return size;
    }

    template<class Object>
    NexusBatchCommon<Object>::NexusBatchCommon(wxPropertyGrid& grid) :
        grid(&grid)
    {}

    template<class Object>
    NexusBatchCommon<Object>::NexusBatchCommon(NexusBatchCommon&& arg) noexcept :
        size(arg.size), grid(arg.grid)
    {}

    template<class Object>
    template<class Child>
    void NexusBatchCommon<Object>::Auto(Child& child, typename Child::Nexus Nexus::* childNexusRetriever)
    {
        autoProperties.emplace_back(child, childNexusRetriever);
    }
}