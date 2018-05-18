#include "AtmosRender.h"

#include <Atmos/LoadImageAssetResourceData.h>
#include <Atmos/CreateImageAssetResource.h>
#include <Atmos/CreateShaderAssetResource.h>
#include <Atmos/CompileShader.h>
#include <Atmos/InputSimpleFile.h>
#include <Arca/Create.h>

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
        ShaderDefinition vertex,
        ShaderDefinition fragment,
        const String& materialName,
        Arca::Reliquary& reliquary)
    {
        const auto vertexShader = CreateShader(vertex, reliquary);
        const auto fragmentShader = CreateShader(fragment, reliquary);
        return reliquary.Do(Arca::Create<Atmos::Asset::Material>(
            materialName, std::vector<Atmos::Asset::Material::Pass>{ {vertexShader, fragmentShader} }));
    }
}