#pragma once

#include "GhostWorldElementCommon.h"

namespace Creation::Editing
{
    template<class Data>
    class GhostWorldElement final : public GhostWorldElementCommon<Data>
    {
    private:
        using BaseT = GhostWorldElementCommon<Data>;
    public:
        using DataT = typename BaseT::DataT;

        using Nexus = typename BaseT::Nexus;
    public:
        GhostWorldElement(Nexus& nexus, Arca::Reliquary& reliquary);
    public:
        [[nodiscard]] DataT CurrentData() const override;
    protected:
        void MoveByImpl(const Atmos::Spatial::Point2D& by) override;
    private:
        DataT data;
    };

    template<class Data>
    GhostWorldElement<Data>::GhostWorldElement(Nexus& nexus, Arca::Reliquary& reliquary) :
        GhostWorldElementCommon<Data>(nexus, reliquary),
        data(nexus.CurrentData())
    {}

    template<class Data>
    auto GhostWorldElement<Data>::CurrentData() const -> DataT
    {
        return data;
    }

    template<class Data>
    void GhostWorldElement<Data>::MoveByImpl(const Atmos::Spatial::Point2D& by)
    {}
}