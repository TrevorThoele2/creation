#include "EntityBoundaryEditingMode.h"

#include "EditingUI.h"
#include "World.h"

#include <Atmos/GridCellSize.h>

namespace Creation::Editing
{
    EntityBoundaryMode::EntityBoundaryMode(NexusSelection& nexusSelection, NexusHistory nexusHistory) :
        Mode(nexusSelection, nexusHistory)
    {}

    void EntityBoundaryMode::ChangeRootImpl(UI& ui)
    {
        ui.ShowRoot<Data::EntityBoundaryRoot>();
        root = ui.Root<Data::EntityBoundaryRoot>();
    }
    
    void EntityBoundaryMode::OnPaintImpl(Atmos::Spatial::AxisAlignedBox2D box)
    {
        if (root)
        {
            std::vector<NexusNode*> created;
            OverDifferentiatedBox(
                [this, &created](const Atmos::Spatial::Grid::Point& point)
                {
                    created.push_back(&CreateEntityBoundaryPosition(point));
                },
                box);
            RetrieveNexusHistory().Add(created);
        }
    }

    void EntityBoundaryMode::OnSelectImpl(Atmos::Spatial::AxisAlignedBox2D box)
    {
        if (root)
        {
            NexusSelection::Delta delta;
            OverDifferentiatedBox(
                [this, &delta](const Atmos::Spatial::Grid::Point& point)
                {
                    for (auto& currentPosition : root->entityBoundary)
                    {
                        const auto positionData = currentPosition->CurrentData();
                        if (positionData.x == point.x && positionData.y == point.y)
                        {
                            if (!currentPosition->IsSelected())
                                delta.select.emplace(currentPosition.get());
                            else
                                delta.deselect.emplace(currentPosition.get());
                        }
                    }
                },
                box);
            CurrentNexusSelection().Modify(delta);
        }
    }

    void EntityBoundaryMode::OnMovedImpl(const std::vector<GhostWorldElementBase*>& ghosts)
    {
        if (root)
        {
            std::vector<NexusHistory::Delta<Data::EntityBoundaryPosition>> nexusChanges;
            for (auto& ghost : ghosts)
            {
                auto casted = dynamic_cast<GhostWorldElement<Data::EntityBoundaryPosition>*>(ghost);
                nexusChanges.emplace_back(&casted->UnderlyingNexus(), casted->CurrentData());
            }
            RetrieveNexusHistory().ChangeData(nexusChanges);
        }
    }

    auto EntityBoundaryMode::OnCopyImpl() -> PaintAction
    {
        if (root)
        {
            auto& nexusSelection = CurrentNexusSelection();
            std::vector<Data::EntityBoundaryPosition> copiedData;
            copiedData.reserve(nexusSelection.size());
            for (auto& nexus : nexusSelection)
            {
                auto entityBoundary = dynamic_cast<Nexus<Data::EntityBoundaryPosition>*>(nexus);
                copiedData.push_back(entityBoundary->CurrentData());
            }

            return PaintAction([root = this->root,
                nexusHistory = this->RetrieveNexusHistory(),
                &nexusSelection,
                copiedData]() mutable
            {
                std::vector<NexusNode*> created;
                NexusSelection::Nodes select;
                for (auto& data : copiedData)
                {
                    created.push_back(&root->entityBoundary.Add(data));
                    select.emplace(created.back());
                }
                nexusHistory.Add(created);
                nexusSelection.Modify({ select, {} });
            });
        }
        else
            return {};
    }

    std::vector<std::unique_ptr<GhostWorldElementBase>> EntityBoundaryMode::CreateGhostsImpl() const
    {
        if (root)
        {
            std::vector<std::unique_ptr<GhostWorldElementBase>> ghosts;
            for (auto& nexus : CurrentNexusSelection())
            {
                auto entityBoundary = dynamic_cast<Nexus<Data::EntityBoundaryPosition>*>(nexus);
                const auto worldElement = entityBoundary->WorldElement();

                if (worldElement)
                    ghosts.push_back(worldElement->CreateGhost());
            }
            return ghosts;
        }
        else
            return {};
    }

    bool EntityBoundaryMode::IsPointInSelectionImpl(Atmos::Spatial::Point2D position, Arca::Reliquary& reliquary) const
    {
        if (root)
        {
            const auto cellSize = Atmos::Spatial::Grid::CellSize<float>;
            const auto gridSize = Atmos::Spatial::Size2D{ cellSize, cellSize };

            for (auto& nexus : CurrentNexusSelection())
            {
                auto entityBoundary = dynamic_cast<Nexus<Data::EntityBoundaryPosition>*>(nexus);

                const auto data = entityBoundary->CurrentData();
                const auto worldPosition = Atmos::Spatial::Point2D
                {
                    data.x * cellSize + cellSize / 2,
                    data.y * cellSize + cellSize / 2
                };

                const auto worldBox = Atmos::Spatial::AxisAlignedBox2D
                {
                    worldPosition,
                    gridSize
                };

                if (Contains(worldBox, position))
                    return true;
            }

            return false;
        }
        else
            return false;
    }

    NexusNode& EntityBoundaryMode::CreateEntityBoundaryPosition(const Atmos::Spatial::Grid::Point& position)
    {
        Data::EntityBoundaryPosition data;
        data.x = position.x;
        data.y = position.y;
        return root->entityBoundary.Add(data);
    }
}