#pragma once

#include "String.h"
#include <Atmos/MaterialAsset.h>
#include <Atmos/ImageAsset.h>

namespace Creation
{
    struct ShaderDefinition
    {
        String inputName;
        String storeName;
    };

    Arca::Index<Atmos::Asset::Image> CreateImage(
        const String& imageName,
        Arca::Reliquary& reliquary);
    Arca::Index<Atmos::Asset::Shader> CreateShader(
        ShaderDefinition definition,
        Arca::Reliquary& reliquary);
    Arca::Index<Atmos::Asset::Material> CreateMaterial(
        ShaderDefinition vertex,
        ShaderDefinition fragment,
        const String& materialName,
        Arca::Reliquary& reliquary);

    inline const String atmosDefaultImageMaterialName = "default_image";
}