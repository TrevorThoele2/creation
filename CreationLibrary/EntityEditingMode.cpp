#include "EntityEditingMode.h"

#include "EntitiesRoot.h"

#include "EntityRenderInformation.h"
#include "EditingUI.h"
#include "World.h"

#include <Atmos/SpatialAlgorithms.h>

namespace Creation::Editing
{
    EntityMode::EntityMode(NexusSelection& nexusSelection, NexusHistory nexusHistory) :
        Mode(nexusSelection, nexusHistory)
    {}

    void EntityMode::ChangeRootImpl(UI& ui)
    {
        ui.ShowRoot<Data::EntitiesRoot>();
        root = ui.Root<Data::EntitiesRoot>();
    }
    
    void EntityMode::OnPaintImpl(Atmos::Spatial::AxisAlignedBox2D box)
    {
        if (root)
        {
            std::vector<NexusNode*> created;
            OverDifferentiatedBox(
                [this, &created](const Atmos::Spatial::Grid::Point& point)
                {
                    created.push_back(&CreateEntity(point));
                },
                box);
            RetrieveNexusHistory().Add(created);
        }
    }

    void EntityMode::OnSelectImpl(Atmos::Spatial::AxisAlignedBox2D box)
    {
        if (root)
        {
            NexusSelection::Delta delta;
            OverDifferentiatedBox(
                [this, &delta](const Atmos::Spatial::Grid::Point& point)
                {
                    for (auto& entity : root->entities)
                    {
                        if (entity->position.CurrentData() == point)
                        {
                            if (!entity->IsSelected())
                                delta.select.emplace(entity.get());
                            else
                                delta.deselect.emplace(entity.get());
                        }
                    }
                },
                box);
            CurrentNexusSelection().Modify(delta);
        }
    }

    void EntityMode::OnMovedImpl(const std::vector<GhostWorldElementBase*>& ghosts)
    {
        if (root)
        {
            std::vector<NexusHistory::Delta<Data::EntityPrototype>> nexusChanges;
            for (auto& ghost : ghosts)
            {
                auto casted = dynamic_cast<GhostWorldElement<Data::EntityPrototype>*>(ghost);
                nexusChanges.emplace_back(&casted->UnderlyingNexus(), casted->CurrentData());
            }
            RetrieveNexusHistory().ChangeData(nexusChanges);
        }
    }

    auto EntityMode::OnCopyImpl() -> PaintAction
    {
        if (root)
        {
            auto& nexusSelection = CurrentNexusSelection();
            std::vector<Data::EntityPrototype> copiedData;
            copiedData.reserve(nexusSelection.size());
            for (auto& nexus : nexusSelection)
            {
                auto entity = dynamic_cast<Nexus<Data::EntityPrototype>*>(nexus);
                copiedData.push_back(entity->CurrentData());
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
                    created.push_back(&root->entities.Add(data));
                    select.emplace(created.back());
                }
                nexusHistory.Add(created);
                nexusSelection.Modify({ select, {} });
            });
        }
        else
            return {};
    }

    std::vector<std::unique_ptr<GhostWorldElementBase>> EntityMode::CreateGhostsImpl() const
    {
        if (root)
        {
            std::vector<std::unique_ptr<GhostWorldElementBase>> ghosts;
            for (auto& nexus : CurrentNexusSelection())
            {
                auto entity = dynamic_cast<Nexus<Data::EntityPrototype>*>(nexus);
                const auto worldElement = entity->WorldElement();

                if (worldElement)
                    ghosts.push_back(worldElement->CreateGhost());
            }
            return ghosts;
        }
        else
            return {};
    }

    bool EntityMode::IsPointInSelectionImpl(Atmos::Spatial::Point2D position, Arca::Reliquary& reliquary) const
    {
        if (root)
        {
            const auto asset = reliquary.Find<EntityRenderInformation>()->asset;
            const auto imageAssetSliceSize = asset->SliceSize();

            for (auto& nexus : CurrentNexusSelection())
            {
                auto entity = dynamic_cast<Nexus<Data::EntityPrototype>*>(nexus);

                const auto worldPosition = Atmos::Spatial::ToPoint2D(entity->position.CurrentData());

                const auto worldBox = Atmos::Spatial::AxisAlignedBox2D
                {
                    worldPosition,
                    imageAssetSliceSize
                };

                if (Contains(worldBox, position))
                    return true;
            }

            return false;
        }
        else
            return false;
    }

    NexusNode& EntityMode::CreateEntity(const Atmos::Spatial::Grid::Point& position)
    {
        Data::EntityPrototype data;
        data.position = position;
        return root->entities.Add(data);
    }
}
