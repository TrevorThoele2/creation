#include "EntityBoundaryPositionCurator.h"

#include <Atmos/RenderAlgorithms.h>
#include <Atmos/StagedRasters.h>

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

        const auto stagedRasters = MutablePointer().Of<Atmos::Render::Raster::Staged>();
        stagedRasters->regions.push_back(Raster(standard, cameraTopLeft, mainSurface));
        stagedRasters->regions.push_back(Raster(selected, cameraTopLeft, mainSurface));
        stagedRasters->regions.push_back(Raster(ghost, cameraTopLeft, mainSurface));
    }

    Atmos::Render::Raster::Prepared<Atmos::Render::Raster::Region> EntityBoundaryPositionCurator::Raster(
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

        return std::tuple
        {
            Atmos::Render::Raster::Region
            {
                .material = region.material,
                .mesh = mesh
            },
            mainSurface.Resource(),
            Atmos::Render::Raster::Order
            {
                .space = Atmos::Render::Ordering(Atmos::Spatial::Space::World),
                .z = static_cast<float>(z)
            }
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
        constexpr auto cellSize = Atmos::Spatial::Grid::CellSize<float>;
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