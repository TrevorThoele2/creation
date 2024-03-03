#include "EntityBoundaryPositionCurator.h"

#include <Atmos/RenderRegion.h>
#include <Atmos/RenderAlgorithms.h>
#include <Atmos/StagedRenders.h>

namespace Creation::Editing
{
    EntityBoundaryPositionCurator::EntityBoundaryPositionCurator(Init init) :
        ObjectCurator(init), information(init.owner.Find<EntityBoundaryRenderInformation>())
    {
        Owner().On<Arca::CreatedKnown<EntityBoundaryPosition>>(
            [this](const Arca::CreatedKnown<EntityBoundaryPosition>& signal)
            {
                OnCreated(signal);
            });

        Owner().On<Arca::DestroyingKnown<EntityBoundaryPosition>>(
            [this](const Arca::DestroyingKnown<EntityBoundaryPosition>& signal)
            {
                OnDestroying(signal);
            });
    }

    void EntityBoundaryPositionCurator::WorkImpl(
        Atmos::Spatial::AxisAlignedBox3D cameraBox,
        Atmos::Spatial::Point2D cameraTopLeft,
        const Atmos::Render::MainSurface& mainSurface)
    {
        Region standard(information->standardMaterial);
        Region selected(information->selectedMaterial);
        Region ghost(information->ghostMaterial);

        auto indices = octree.AllWithin(cameraBox);

        for (auto& index : indices)
        {
            const auto& value = *index->value;

            const auto point = Atmos::Spatial::Grid::Point{ value.x, value.y };

            Points* points;
            if (value.status == EntityBoundaryPosition::Status::Selected)
                points = &selected.points;
            else if (value.status == EntityBoundaryPosition::Status::Ghost)
                points = &ghost.points;
            else
                points = &standard.points;
            points->emplace(point);
        }

        const auto stagedRenders = MutablePointer().Of<Atmos::Render::StagedRenders>();
        stagedRenders->regions.push_back(RenderOf(standard, cameraTopLeft, mainSurface));
        stagedRenders->regions.push_back(RenderOf(selected, cameraTopLeft, mainSurface));
        stagedRenders->regions.push_back(RenderOf(ghost, cameraTopLeft, mainSurface));
    }

    Atmos::Render::RenderRegion EntityBoundaryPositionCurator::RenderOf(
        const Region& region,
        Atmos::Spatial::Point2D cameraTopLeft,
        const Atmos::Render::MainSurface& mainSurface)
    {
        const auto points = std::vector<Atmos::Spatial::Grid::Point>
        {
            region.points.begin(),
            region.points.end()
        };
        auto mesh = Atmos::Render::ConvertToMesh(Atmos::Render::Triangulate(points));
        for (auto& vertex : mesh.vertices)
        {
            vertex.x -= cameraTopLeft.x;
            vertex.y -= cameraTopLeft.y;
        }

        constexpr auto z = std::numeric_limits<Atmos::Spatial::Grid::Point::Value>::max() - 1 / 2;

        return Atmos::Render::RenderRegion
        {
            mesh,
            static_cast<float>(z),
            region.material,
            ToRenderSpace(Atmos::Spatial::Space::World),
            mainSurface.Resource()
        };
    }

    void EntityBoundaryPositionCurator::OnCreated(const Arca::CreatedKnown<EntityBoundaryPosition>& signal)
    {
        octree.Add(signal.index.ID(), signal.index, BoxFor(signal.index));
    }

    void EntityBoundaryPositionCurator::OnDestroying(const Arca::DestroyingKnown<EntityBoundaryPosition>& signal)
    {
        octree.Remove(signal.index.ID(), BoxFor(signal.index));
    }

    Atmos::Spatial::AxisAlignedBox3D EntityBoundaryPositionCurator::BoxFor(
        const Index& index)
    {
        const auto cellSize = Atmos::Spatial::Grid::CellSize<float>;
        return Atmos::Spatial::AxisAlignedBox3D
        {
            {
                index->x * cellSize,
                index->y * cellSize,
                0
            },
            {
                cellSize,
                cellSize,
                cellSize
            }
        };
    }
}