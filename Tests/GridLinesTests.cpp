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
#include <Atmos/CompileScript.h>
#include <Atmos/JavaScriptManager.h>
#include <Arca/Create.h>
#include <Inscription/Plaintext.h>

#include "MockGraphicsManager.h"
#include "MockTextManager.h"
#include "MockWindow.h"

class GridLinesTestsFixture : public GeneralFixture
{
public:
    Arca::Index<Asset::Script> CompileAndCreateBasicMaterialScript(Arca::Reliquary& reliquary);
    [[nodiscard]] static String BasicMaterialScriptSource();

    Arca::Index<Asset::Script> CompileAndCreateScriptAsset(
        const String& name,
        const String& source,
        const std::vector<Scripting::Module>& sharedModules,
        Arca::Reliquary& reliquary);
};

Arca::Index<Asset::Script> GridLinesTestsFixture::CompileAndCreateScriptAsset(
    const String& name,
    const String& source,
    const std::vector<Scripting::Module>& sharedModules,
    Arca::Reliquary& reliquary)
{
    Inscription::Plaintext::ToFile(source, name);
    for (auto& module : sharedModules)
        Inscription::Plaintext::ToFile(module.source, module.name);

    std::vector<Scripting::Module> modules = sharedModules;
    modules.push_back(Scripting::Module{ Inscription::File::Path(name).replace_extension().string(), source });
    const auto compiledModules = reliquary.Do(Scripting::Compile{ modules });

    std::vector<Scripting::CompiledModule>::const_iterator compiledSource;
    for (auto module = compiledModules.begin(); module != compiledModules.end(); ++module)
    {
        if (module->name == Inscription::File::Path(name).replace_extension().string())
        {
            compiledSource = module;
            break;
        }
    }

    auto assetResource = reliquary.Do(Asset::Resource::Create<Asset::Resource::Script>{
        compiledSource->source,
        name });

    return reliquary.Do(Arca::Create<Asset::Script>{
        name, std::move(assetResource)});
}

Arca::Index<Asset::Script> GridLinesTestsFixture::CompileAndCreateBasicMaterialScript(
    Arca::Reliquary& reliquary)
{
    return CompileAndCreateScriptAsset("basic_script.ts", BasicMaterialScriptSource(), {}, reliquary);
}

String GridLinesTestsFixture::BasicMaterialScriptSource()
{
    return R"V0G0N(import { Atmos } from "./atmos";

export const main = (): Atmos.Result => {
    const material = Atmos.Reliquary.find(Atmos.Traits.Render.Raster.ExecutingMaterial.typeName)!;
    
    const shaders = {
        vertex: Atmos.Reliquary.send(Atmos.Traits.Asset.FindByName.Shader.typeName, { name: "vertex" }),
        fragment: Atmos.Reliquary.send(Atmos.Traits.Asset.FindByName.Shader.typeName, { name: "fragment" })    
    };

    Atmos.Reliquary.send(
        Atmos.Traits.Render.Raster.RecordCommands.typeName,
        {
            commands: [
                ...material.images.map(x => ({ shaders, ...x })),
                ...material.lines.map(x => ({ shaders, ...x })),
                ...material.regions.map(x => ({ shaders, ...x })),
                ...material.texts.map(x => ({ shaders, ...x }))
            ]
        });

    return {
        done: true
    };
};)V0G0N";
}

SCENARIO_METHOD(GridLinesTestsFixture, "GridLines")
{
    GIVEN("setup render reliquary and camera")
    {
        auto logger = Logging::Logger(Logging::Severity::Verbose);
        auto assetResourceManager = Asset::Resource::NullManager(logger);
        auto graphics = std::make_unique<MockGraphicsManager>(logger);
        auto text = std::make_unique<MockTextManager>();
        auto window = std::make_unique<MockWindow>(logger);
        auto scripting = std::make_unique<Scripting::JavaScript::Manager>(logger);

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
        Scripting::RegisterTypes(reliquaryOrigin, *scripting);
        Window::RegisterTypes(reliquaryOrigin, *window);

        reliquaryOrigin.Register<Creation::GridLines>();
        reliquaryOrigin.Register<Creation::GridLinesInformation>();

        auto reliquary = reliquaryOrigin.Actualize();

        auto materialScriptAsset = CompileAndCreateBasicMaterialScript(*reliquary);

        auto materialAsset = reliquary->Do(Arca::Create<Asset::Material> {
            String{}, materialScriptAsset, "main", Scripting::Parameters{} });

        reliquary->Do(Creation::ChangeGridLineMaterial{ materialAsset });

        auto camera = reliquary->Find<Camera>();

        WHEN("sending work command")
        {
            reliquary->Do(Work{});

            THEN("all lines rendered")
            {
                auto& commands = graphics->commands;
                REQUIRE(commands.size() == 56);
            }
        }

        WHEN("moving camera beyond the origin and sending work command")
        {
            reliquary->Do(Spatial::MoveBounds{ camera.ID(), Spatial::Point3D { 2048, 0, 0 } });

            reliquary->Do(Work{});

            THEN("all lines rendered")
            {
                auto& commands = graphics->commands;
                REQUIRE(commands.size() == 56);
            }
        }
    }
}