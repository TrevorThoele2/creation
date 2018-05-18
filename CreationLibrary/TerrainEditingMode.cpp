#include "TerrainEditingMode.h"

#include "EditingUI.h"
#include "World.h"

#include <Atmos/GridCellSize.h>
#include <Atmos/FindAssetByName.h>

namespace Creation::Editing
{
    TerrainMode::TerrainMode(NexusSelection& nexusSelection, NexusHistory nexusHistory) :
        Mode(nexusSelection, nexusHistory)
    {}

    void TerrainMode::ChangeRootImpl(UI& ui)
    {
        ui.ShowRoot<Data::TerrainRoot>();
        root = ui.Root<Data::TerrainRoot>();
    }
    
    void TerrainMode::OnPaintImpl(Atmos::Spatial::AxisAlignedBox2D box)
    {
        if (root)
        {
            std::vector<NexusNode*> created;
            OverDifferentiatedBox(
                [this, &created](const Atmos::Spatial::Grid::Point& point)
                {
                    created.push_back(&CreateTerrainImage(point));
                },
                box);
            RetrieveNexusHistory().Add(created);
        }
    }

    void TerrainMode::OnSelectImpl(Atmos::Spatial::AxisAlignedBox2D box)
    {
        if (root)
        {
            NexusSelection::Delta delta;
            OverDifferentiatedBox(
                [this, &delta](const Atmos::Spatial::Grid::Point& point)
                {
                    for (auto& terrain : root->terrain)
                    {
                        if (Atmos::Spatial::Grid::ToPoint(terrain->bounds.position.CurrentData()) == point)
                        {
                            if (!terrain->IsSelected())
                                delta.select.emplace(terrain.get());
                            else
                                delta.deselect.emplace(terrain.get());
                        }
                    }
                },
                box);
            CurrentNexusSelection().Modify(delta);
        }
    }

    void TerrainMode::OnMovedImpl(const std::vector<GhostWorldElementBase*>& ghosts)
    {
        if (root)
        {
            std::vector<NexusHistory::Delta<Data::StaticImage>> nexusChanges;
            for (auto& ghost : ghosts)
            {
                auto casted = dynamic_cast<GhostWorldElement<Data::StaticImage>*>(ghost);
                nexusChanges.emplace_back(&casted->UnderlyingNexus(), casted->CurrentData());
            }
            RetrieveNexusHistory().ChangeData(nexusChanges);
        }
    }

    auto TerrainMode::OnCopyImpl() -> PaintAction
    {
        if (root)
        {
            auto& nexusSelection = CurrentNexusSelection();
            std::vector<Data::StaticImage> copiedData;
            copiedData.reserve(nexusSelection.size());
            for (auto& nexus : nexusSelection)
            {
                auto terrain = dynamic_cast<Nexus<Data::StaticImage>*>(nexus);
                copiedData.push_back(terrain->CurrentData());
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
                    created.push_back(&root->terrain.Add(data));
                    select.emplace(created.back());
                }
                nexusHistory.Add(created);
                nexusSelection.Modify({ select, {} });
            });
        }
        else
            return {};
    }

    std::vector<std::unique_ptr<GhostWorldElementBase>> TerrainMode::CreateGhostsImpl() const
    {
        if (root)
        {
            std::vector<std::unique_ptr<GhostWorldElementBase>> ghosts;
            for (auto& nexus : CurrentNexusSelection())
            {
                auto terrain = dynamic_cast<Nexus<Data::StaticImage>*>(nexus);
                const auto worldElement = terrain->WorldElement();

                if (worldElement)
                    ghosts.push_back(worldElement->CreateGhost());
            }
            return ghosts;
        }
        else
            return {};
    }

    bool TerrainMode::IsPointInSelectionImpl(Atmos::Spatial::Point2D position, Arca::Reliquary& reliquary) const
    {
        if (root)
        {
            std::unordered_map<String, Atmos::Spatial::Size2D> assetSize;

            const auto retrieveAssetSize = [&assetSize, &reliquary](const String& assetName)
            {
                const auto fromMap = assetSize.find(assetName);
                if (fromMap != assetSize.end())
                    return fromMap->second;

                const auto fromReliquary = reliquary.Do(Atmos::Asset::FindByName<Atmos::Asset::Image> { assetName });
                if (!fromReliquary)
                    return Atmos::Spatial::Size2D{};

                auto size = fromReliquary->SliceSize();
                assetSize.emplace(assetName, size);
                return size;
            };

            for (auto& nexus : CurrentNexusSelection())
            {
                auto terrain = dynamic_cast<Nexus<Data::StaticImage>*>(nexus);
                if (!terrain)
                    continue;

                const auto worldPosition = ToPoint2D(terrain->bounds.position.CurrentData());
                const auto worldScalers = terrain->bounds.scalers.CurrentData();

                const auto imageAssetSliceSize = retrieveAssetSize(terrain->imageCore.asset.CurrentData());
                const auto worldSize = Atmos::Spatial::Size2D
                {
                    worldScalers.x * imageAssetSliceSize.width,
                    worldScalers.y * imageAssetSliceSize.height
                };

                const auto worldBox = Atmos::Spatial::AxisAlignedBox2D
                {
                    worldPosition,
                    worldSize
                };

                if (Contains(worldBox, position))
                    return true;
            }

            return false;
        }
        else
            return false;
    }

    NexusNode& TerrainMode::CreateTerrainImage(const Atmos::Spatial::Grid::Point& position)
    {
        const auto normalizedPoint = NormalizedPoint(position);
        Data::StaticImage data;
        data.bounds.position = normalizedPoint;
        return root->terrain.Add(data);
    }
    
    Atmos::Spatial::Point3D TerrainMode::NormalizedPoint(const Atmos::Spatial::Grid::Point& point)
    {
        const auto cellSize = Atmos::Spatial::Grid::CellSize<float>;
        return
        {
            point.x * cellSize + cellSize / 2,
            point.y * cellSize + cellSize / 2,
            0
        };
    }
}