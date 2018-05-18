#pragma once

#include <Atmos/RenderObjectCurator.h>

#include "EntityBoundaryPosition.h"

#include <Atmos/Octree.h>
#include <Atmos/Camera.h>
#include <Atmos/GridPoint.h>
#include <Atmos/AxisAlignedBox3D.h>

#include "EntityBoundaryRenderInformation.h"

namespace Creation::Editing
{
    class EntityBoundaryPositionCurator final : public Atmos::Render::ObjectCurator
    {
    public:
        EntityBoundaryPositionCurator(Init init);
    protected:
        void WorkImpl(
            Atmos::Spatial::AxisAlignedBox3D cameraBox,
            Atmos::Spatial::Point2D cameraTopLeft,
            const Atmos::Render::MainSurface& mainSurface) override;
    private:
        using Index = Arca::Index<EntityBoundaryPosition>;

        Atmos::Spatial::Grid::Octree<Arca::RelicID, Index> octree;

        Arca::Index<Atmos::Render::Camera> camera;
    private:
        using Points = std::unordered_set<Atmos::Spatial::Grid::Point>;

        struct Region
        {
            Points points;
            Arca::Index<Atmos::Asset::Material> material;
            explicit Region(Arca::Index<Atmos::Asset::Material> material) : material(material)
            {}
        };

        [[nodiscard]] Atmos::Render::RenderRegion RenderOf(
            const Region& region,
            Atmos::Spatial::Point2D cameraTopLeft,
            const Atmos::Render::MainSurface& mainSurface);

        void OnCreated(const Arca::CreatedKnown<EntityBoundaryPosition>& signal);
        void OnDestroying(const Arca::DestroyingKnown<EntityBoundaryPosition>& signal);
    private:
        Arca::Index<EntityBoundaryRenderInformation> information;
    private:
        static Atmos::Spatial::AxisAlignedBox3D BoxFor(const Index& index);
    };
}

namespace Arca
{
    template<>
    struct Traits<Creation::Editing::EntityBoundaryPositionCurator>
    {
        static constexpr ObjectType objectType = ObjectType::Curator;
        static const inline TypeName typeName = "Creation::Editing::EntityBoundaryPositionCurator";
        using HandledCommands = HandledCommands<Atmos::Work>;
    };
}

namespace Inscription
{
    template<class Format>
    struct ScribeTraits<Creation::Editing::EntityBoundaryPositionCurator, Format> final
    {
        using Category = ArcaNullScribeCategory<Creation::Editing::EntityBoundaryPositionCurator>;
    };
}