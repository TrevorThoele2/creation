#include "RenderReliquary.h"

#include "MutationCurator.h"
#include "GridLines.h"
#include "GridLinesInformation.h"
#include "EntityBoundaryPosition.h"
#include "EntityBoundaryPositionCurator.h"
#include "DefaultImageMaterials.h"
#include "DefaultImageMaterialsCurator.h"
#include "EntityBoundaryRenderInformation.h"
#include "EntityBoundaryRenderInformationCurator.h"
#include "EntityRenderInformation.h"
#include "AtmosRender.h"
#include "EntityRenderInformationCurator.h"
#include <Atmos/TypeRegistration.h>
#include <Atmos/FrameInformation.h>
#include <Atmos/MainSurface.h>
#include <Atmos/ChangeSurfaceBackgroundColor.h>
#include <Atmos/FileCurator.h>
#include <Atmos/LoggingCurator.h>
#include <Atmos/LoggingInformation.h>

namespace Creation
{
    std::unique_ptr<Arca::Reliquary> CreateRenderReliquary(
        Atmos::Render::GraphicsManager& graphicsManager,
        Atmos::Render::TextManager& textManager,
        Atmos::Asset::Resource::Manager& assetResourceManager,
        Atmos::Spatial::Size2D clientSize,
        Atmos::Logging::Logger& logger,
        void* hwnd)
    {
        Arca::ReliquaryOrigin reliquaryOrigin;
        Atmos::Render::RegisterTypes(
            reliquaryOrigin,
            graphicsManager,
            textManager,
            clientSize,
            hwnd);

        Atmos::Asset::RegisterTypes(reliquaryOrigin, assetResourceManager);
        Atmos::Spatial::RegisterTypes(reliquaryOrigin);
        Atmos::Diagnostics::RegisterTypes(reliquaryOrigin);
        
        reliquaryOrigin.Register<Atmos::Frame::Information>();

        reliquaryOrigin.Register<DefaultImageMaterials>();
        reliquaryOrigin.Register<DefaultImageMaterialsCurator>();

        reliquaryOrigin.Register<EntityBoundaryRenderInformation>();
        reliquaryOrigin.Register<EntityBoundaryRenderInformationCurator>();

        reliquaryOrigin.Register<EntityRenderInformation>();
        reliquaryOrigin.Register<EntityRenderInformationCurator>();

        reliquaryOrigin.Register<GridLines>();
        reliquaryOrigin.Register<GridLinesInformation>();
        Arca::Stage gridLinesStage;
        gridLinesStage.Add<GridLines>();

        reliquaryOrigin.Register<Editing::EntityBoundaryPosition>();
        reliquaryOrigin.Register<Editing::EntityBoundaryPositionCurator>();
        Arca::Stage entityBoundaryStage;
        entityBoundaryStage.Add<Editing::EntityBoundaryPositionCurator>();

        reliquaryOrigin.Register<Atmos::File::Curator>();
        reliquaryOrigin.Register<MutationCurator>();

        reliquaryOrigin.Register<Atmos::Logging::Curator>();
        reliquaryOrigin.Register<Atmos::Logging::Information>(std::ref(logger));

        auto constructionPipeline = Arca::Pipeline();
        constructionPipeline.push_back(Atmos::Render::Stage());
        constructionPipeline.push_back(gridLinesStage);
        constructionPipeline.push_back(entityBoundaryStage);

        auto workPipeline = Arca::Pipeline();
        workPipeline.push_back(Atmos::Render::Stage());
        workPipeline.push_back(entityBoundaryStage);

        reliquaryOrigin
            .CuratorConstructionPipeline(constructionPipeline)
            .CuratorCommandPipeline<Atmos::Work>(workPipeline);

        auto reliquary = reliquaryOrigin.Actualize();

        const auto imageMaterial = CreateMaterial(
            ShaderDefinition{ "image_vertex.vert", "creation_internal_image_vertex" },
            ShaderDefinition{ "image_fragment.frag", "creation_internal_image_fragment" },
            "creation_internal_image",
            *reliquary);
        const auto selectedImageMaterial = CreateMaterial(
            ShaderDefinition{ "selected_image_vertex.vert", "creation_internal_selected_image_vertex" },
            ShaderDefinition{ "selected_image_fragment.frag", "creation_internal_selected_image_fragment" },
            "creation_internal_selected_image",
            *reliquary);
        const auto ghostImageMaterial = CreateMaterial(
            ShaderDefinition{ "ghost_image_vertex.vert", "creation_internal_ghost_image_vertex" },
            ShaderDefinition{ "ghost_image_fragment.frag", "creation_internal_ghost_image_fragment" },
            "creation_internal_ghost_image",
            *reliquary);
        reliquary->Do(ChangeDefaultImageMaterials
            {
                imageMaterial,
                selectedImageMaterial,
                ghostImageMaterial
            });

        const auto lineMaterial = CreateMaterial(
            ShaderDefinition{ "line_vertex.vert", "creation_internal_line_vertex" },
            ShaderDefinition{ "line_fragment.frag", "creation_internal_line_fragment" },
            "creation_internal_line",
            *reliquary);
        reliquary->Do(ChangeGridLineMaterial{ lineMaterial });

        const auto entityBoundaryMaterial = CreateMaterial(
            ShaderDefinition{ "crosshatch_vertex.vert", "creation_internal_crosshatch_vertex" },
            ShaderDefinition{ "crosshatch_fragment.frag", "creation_internal_crosshatch_fragment" },
            "creation_internal_crosshatch",
            *reliquary);
        const auto selectedEntityBoundaryMaterial = CreateMaterial(
            ShaderDefinition{ "selected_crosshatch_vertex.vert", "creation_internal_selected_crosshatch_vertex" },
            ShaderDefinition{ "selected_crosshatch_fragment.frag", "creation_internal_selected_crosshatch_fragment" },
            "creation_internal_selected_crosshatch",
            *reliquary);
        const auto ghostEntityBoundaryMaterial = CreateMaterial(
            ShaderDefinition{ "ghost_crosshatch_vertex.vert", "creation_internal_ghost_crosshatch_vertex" },
            ShaderDefinition{ "ghost_crosshatch_fragment.frag", "creation_internal_ghost_crosshatch_fragment" },
            "creation_internal_ghost_crosshatch",
            *reliquary);
        reliquary->Do(InitializeEntityBoundaryRenderInformation{
            entityBoundaryMaterial, selectedEntityBoundaryMaterial, ghostEntityBoundaryMaterial });

        const auto entityAsset = CreateImage(
            "entity.png",
            *reliquary);
        reliquary->Do(InitializeEntityRenderInformation{ entityAsset });

        const auto mainSurface = reliquary->Find<Atmos::Render::MainSurface>();
        reliquary->Do(Atmos::Render::ChangeMainSurfaceBackgroundColor{
            mainSurface.ID(),
            Atmos::Render::Color{ 255, 0, 0, 0 } });

        return reliquary;
    }
}