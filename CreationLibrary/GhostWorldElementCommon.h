#pragma once

#include "GhostWorldElementBase.h"
#include "MutationCurator.h"

namespace Creation::Editing
{
    template<class Data>
    class GhostWorldElementCommon : public GhostWorldElementBase
    {
    public:
        using DataT = Data;

        using Nexus = Nexus<DataT>;
    public:
        virtual ~GhostWorldElementCommon() = 0;
    public:
        [[nodiscard]] virtual DataT CurrentData() const = 0;

        [[nodiscard]] Nexus& UnderlyingNexus();
        [[nodiscard]] const Nexus& UnderlyingNexus() const;
    protected:
        GhostWorldElementCommon(Nexus& nexus, Arca::Reliquary& reliquary);

        [[nodiscard]] Arca::Reliquary& Reliquary() const;

        Arca::MutablePointer MutablePointer();
    private:
        DataT data;

        Nexus* nexus;
    private:
        Arca::Reliquary* reliquary;
    };

    template<class Data>
    GhostWorldElementCommon<Data>::~GhostWorldElementCommon() = default;

    template<class Data>
    auto GhostWorldElementCommon<Data>::UnderlyingNexus() -> Nexus&
    {
        return *nexus;
    }

    template<class Data>
    auto GhostWorldElementCommon<Data>::UnderlyingNexus() const -> const Nexus&
    {
        return *nexus;
    }

    template<class Data>
    GhostWorldElementCommon<Data>::GhostWorldElementCommon(Nexus& nexus, Arca::Reliquary& reliquary) :
        data(nexus.CurrentData()), nexus(&nexus), reliquary(&reliquary)
    {}

    template<class Data>
    Arca::Reliquary& GhostWorldElementCommon<Data>::Reliquary() const
    {
        return *reliquary;
    }

    template<class Data>
    Arca::MutablePointer GhostWorldElementCommon<Data>::MutablePointer()
    {
        return reliquary->Find<Creation::MutationCurator>().RetrieveMutablePointer();
    }
}