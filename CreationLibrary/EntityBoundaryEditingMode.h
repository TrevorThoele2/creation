#pragma once

#include "EditingMode.h"

#include "EntityBoundaryRoot.h"

namespace Creation::Editing
{
    class EntityBoundaryMode final : public Mode
    {
    public:
        EntityBoundaryMode(NexusSelection& nexusSelection, NexusHistory nexusHistory);
    protected:
        void ChangeRootImpl(UI& ui) override;
        
        void OnPaintImpl(Atmos::Spatial::AxisAlignedBox2D box) override;
        void OnSelectImpl(Atmos::Spatial::AxisAlignedBox2D box) override;

        void OnMovedImpl(const std::vector<GhostWorldElementBase*>& ghosts) override;

        PaintAction OnCopyImpl() override;
        
        [[nodiscard]] std::vector<std::unique_ptr<GhostWorldElementBase>> CreateGhostsImpl() const override;
        [[nodiscard]] bool IsPointInSelectionImpl(Atmos::Spatial::Point2D position, Arca::Reliquary& reliquary) const override;
    private:
        Data::EntityBoundaryRoot* root = nullptr;

        NexusNode& CreateEntityBoundaryPosition(const Atmos::Spatial::Grid::Point& position);
    };
}