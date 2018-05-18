#pragma once

#include "EditingMode.h"

#include "TerrainRoot.h"

#include "MovementManager.h"

namespace Creation::Editing
{
    class TerrainMode final : public Mode
    {
    public:
        TerrainMode(NexusSelection& nexusSelection, NexusHistory nexusHistory);
    protected:
        void ChangeRootImpl(UI& ui) override;
        
        void OnPaintImpl(Atmos::Spatial::AxisAlignedBox2D box) override;
        void OnSelectImpl(Atmos::Spatial::AxisAlignedBox2D box) override;

        void OnMovedImpl(const std::vector<GhostWorldElementBase*>& ghosts) override;

        PaintAction OnCopyImpl() override;

        [[nodiscard]] std::vector<std::unique_ptr<GhostWorldElementBase>> CreateGhostsImpl() const override;
        [[nodiscard]] bool IsPointInSelectionImpl(Atmos::Spatial::Point2D position, Arca::Reliquary& reliquary) const override;
    private:
        Data::TerrainRoot* root = nullptr;

        NexusNode& CreateTerrainImage(const Atmos::Spatial::Grid::Point& position);

        Atmos::Spatial::Point3D NormalizedPoint(const Atmos::Spatial::Grid::Point& point);
    };
}