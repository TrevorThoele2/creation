#include <catch.hpp>
#include "GeneralFixture.h"

#include <CreationLibrary/GridLines.h>
#include <CreationLibrary/GridLinesInformation.h>

#include <Atmos/TypeRegistration.h>
#include <Atmos/MainSurface.h>
#include <Atmos/MoveBounds.h>
#include <Atmos/GraphicsCurator.h>
#include <Atmos/Camera.h>
#include <Atmos/Work.h>
#include <Atmos/NullAssetResourceManager.h>

#include <Arca/Create.h>

#include "MockGraphicsManager.h"
#include "MockTextManager.h"
#include "MockSurfaceResource.h"
#include "MockWindow.h"

class GridLinesTestsFixture : public GeneralFixture
{
public:

};

SCENARIO_METHOD(GridLinesTestsFixture, "GridLines")
{
    GIVEN("setup render reliquary and camera")
    {
        auto logger = Atmos::Logging::Logger(Atmos::Logging::Severity::Verbose);
        auto assetResourceManager = Atmos::Asset::Resource::NullManager(logger);
        auto graphics = std::make_unique<MockGraphicsManager>(logger);
        auto text = std::make_unique<MockTextManager>();
        auto window = std::make_unique<MockWindow>(logger);

        Arca::ReliquaryOrigin reliquaryOrigin;
        RegisterTypes(
            reliquaryOrigin,
            *graphics,
            *text,
            Spatial::Size2D{ 1024, 768 },
            nullptr);
        Asset::RegisterTypes(reliquaryOrigin, assetResourceManager);
        Spatial::RegisterTypes(reliquaryOrigin);
        Diagnostics::RegisterTypes(reliquaryOrigin);
        Frame::RegisterTypes(reliquaryOrigin);
        Window::RegisterTypes(reliquaryOrigin, *window);

        reliquaryOrigin.Register<Creation::GridLines>();
        reliquaryOrigin.Register<Creation::GridLinesInformation>();

        auto reliquary = reliquaryOrigin.Actualize();

        const auto mainSurface = reliquary->Find<MainSurface>();
        auto mainSurfaceImplementation = mainSurface->Resource<MockSurfaceDataImplementation>();

        const auto material = reliquary->Do(Arca::Create<Asset::Material>(
            String{},
            std::vector<Asset::Material::Pass>{ {Arca::Index<Asset::Shader>{}, Arca::Index<Asset::Shader>{} } }));

        reliquary->Do(Creation::ChangeGridLineMaterial{ material });

        auto camera = reliquary->Find<Camera>();

        WHEN("sending work command")
        {
            reliquary->Do(Work{});

            THEN("all lines rendered")
            {
                auto& lineRenders = graphics->lineRenders;
                REQUIRE(lineRenders.size() == 56);
            }
        }

        WHEN("moving camera beyond the origin and sending work command")
        {
            reliquary->Do(Spatial::MoveBounds{ camera.ID(), Spatial::Point3D { 2048, 0, 0 } });

            reliquary->Do(Work{});

            THEN("all lines rendered")
            {
                auto& lineRenders = graphics->lineRenders;
                REQUIRE(lineRenders.size() == 56);
            }
        }
    }
}