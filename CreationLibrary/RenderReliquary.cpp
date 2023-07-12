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
#include "AtmosAsset.h"
#include "EntityRenderInformationCurator.h"
#include <Atmos/TypeRegistration.h>
#include <Atmos/FrameInformation.h>
#include <Atmos/MainSurface.h>
#include <Atmos/ChangeSurfaceBackgroundColor.h>
#include <Atmos/FileCurator.h>
#include <Atmos/LoggingCurator.h>
#include <Atmos/LoggingInformation.h>
#include <Inscription/Plaintext.h>

namespace Creation
{
    std::unique_ptr<Arca::Reliquary> CreateRenderReliquary(
        Atmos::Render::GraphicsManager& graphicsManager,
        Atmos::Render::TextManager& textManager,
        Atmos::Asset::Resource::Manager& assetResourceManager,
        Atmos::Scripting::Manager& scriptManager,
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
        RegisterTypes(reliquaryOrigin, scriptManager);
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
        
        const auto basicMaterial = CreateScript("basic_material_script.ts", *reliquary);

        const auto createBasicMaterial = [&](
            const String& name, const ShaderDefinition& vertexDefinition, const ShaderDefinition& fragmentDefinition)
        {
            CreateShader(vertexDefinition, *reliquary);
            CreateShader(fragmentDefinition, *reliquary);

            return CreateMaterial(
                name,
                basicMaterial,
                "main",
                { vertexDefinition.storeName, fragmentDefinition.storeName },
                *reliquary);
        };
        
        reliquary->Do(ChangeDefaultImageMaterials
            {
                .material = createBasicMaterial(
                    "creation_internal_image",
                    ShaderDefinition{ "vertex.vert", "creation_internal_vertex" },
                    ShaderDefinition{ "fragment.frag", "creation_internal_fragment" }),
                .selected = createBasicMaterial(
                    "creation_internal_selected_image",
                    ShaderDefinition{ "selected_image_vertex.vert", "creation_internal_selected_image_vertex" },
                    ShaderDefinition{ "selected_image_fragment.frag", "creation_internal_selected_image_fragment" }),
                .ghost = createBasicMaterial(
                    "creation_internal_ghost_image",
                    ShaderDefinition{ "ghost_image_vertex.vert", "creation_internal_ghost_image_vertex" },
                    ShaderDefinition{ "ghost_image_fragment.frag", "creation_internal_ghost_image_fragment" })
            });
        
        reliquary->Do(ChangeGridLineMaterial
            {
                .material = createBasicMaterial(
                    "creation_internal_line",
                    ShaderDefinition{ "line_vertex.vert", "creation_internal_line_vertex" },
                    ShaderDefinition{ "line_fragment.frag", "creation_internal_line_fragment" })
            });
        
        reliquary->Do(InitializeEntityBoundaryRenderInformation
            {
                .standardMaterial = createBasicMaterial(
                    "creation_internal_crosshatch",
                    ShaderDefinition{ "crosshatch_vertex.vert", "creation_internal_crosshatch_vertex" },
                    ShaderDefinition{ "crosshatch_fragment.frag", "creation_internal_crosshatch_fragment" }),
                .selectedMaterial = createBasicMaterial(
                    "creation_internal_selected_crosshatch",
                    ShaderDefinition{ "selected_crosshatch_vertex.vert", "creation_internal_selected_crosshatch_vertex" },
                    ShaderDefinition{ "selected_crosshatch_fragment.frag", "creation_internal_selected_crosshatch_fragment" }),
                .ghostMaterial = createBasicMaterial(
                    "creation_internal_ghost_crosshatch",
                    ShaderDefinition{ "ghost_crosshatch_vertex.vert", "creation_internal_ghost_crosshatch_vertex" },
                    ShaderDefinition{ "ghost_crosshatch_fragment.frag", "creation_internal_ghost_crosshatch_fragment" })
            });

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