#include "AtmosAsset.h"

#include <Atmos/LoadImageAssetResourceData.h>
#include <Atmos/CreateImageAssetResource.h>
#include <Atmos/CreateShaderAssetResource.h>
#include <Atmos/CompileShader.h>
#include <Atmos/CompileScript.h>
#include <Arca/Create.h>
#include <Inscription/Plaintext.h>

namespace Creation
{
    Arca::Index<Atmos::Asset::Image> CreateImage(
        const String& imageName,
        Arca::Reliquary& reliquary)
    {
        const auto filePath = std::filesystem::current_path() / "images" / imageName;

        const auto loaded = reliquary.Do(
            Atmos::Asset::Resource::LoadData<Atmos::Asset::Resource::Image>{ filePath });

        using Resource = Atmos::Asset::Resource::Image;
        auto resource = reliquary.Do(
            Atmos::Asset::Resource::Create<Resource> { loaded.buffer, imageName, loaded.size });

        return reliquary.Do(Arca::Create<Atmos::Asset::Image>(
            imageName,
            std::move(resource),
            Atmos::Asset::ImageGridSize{ 1, 1 }));
    }

    Arca::Index<Atmos::Asset::Shader> CreateShader(
        ShaderDefinition definition,
        Arca::Reliquary& reliquary)
    {
        const auto inputFilePath = std::filesystem::current_path() / "shaders" / definition.inputName;
        const auto buffer = reliquary.Do(Atmos::Render::CompileShader{ inputFilePath });
        
        using Resource = Atmos::Asset::Resource::Shader;
        auto resource = reliquary.Do(
            Atmos::Asset::Resource::Create<Resource> { buffer, definition.storeName });
        return reliquary.Do(Arca::Create<Atmos::Asset::Shader>(
            definition.storeName, std::move(resource)));
    }

    Arca::Index<Atmos::Asset::Material> CreateMaterial(
        const String& materialName,
        const Arca::Index<Atmos::Asset::Script>& asset,
        const String& executeName,
        const Atmos::Scripting::Parameters& parameters,
        Arca::Reliquary& reliquary)
    {
        return reliquary.Do(Arca::Create<Atmos::Asset::Material>(
            materialName, asset, executeName, parameters));
    }

    Arca::Index<Atmos::Asset::Script> CreateScript(const String& scriptName, Arca::Reliquary& reliquary)
    {
        const auto source = Inscription::Plaintext::FromFile(Inscription::File::Path("scripts/" + scriptName));

        const auto compiledModules = reliquary.Do(Atmos::Scripting::Compile{ {Atmos::Scripting::Module{ "scripts/" + scriptName, source }} });

        const auto scriptNameWithoutExtension = Inscription::File::Path(scriptName).replace_extension().string();

        std::vector<Atmos::Scripting::CompiledModule>::const_iterator compiledSource;
        for (const auto& compiledModule : compiledModules)
        {
            if (compiledModule.name == scriptNameWithoutExtension)
            {
                auto resource = reliquary.Do(Atmos::Asset::Resource::Create<Atmos::Asset::Resource::Script>(
                    compiledModule.source, compiledModule.name));
                return reliquary.Do(Arca::Create<Atmos::Asset::Script>{scriptNameWithoutExtension, std::move(resource)});
            }
        }

        throw std::runtime_error("Could not find module.");
    }
}
