#pragma once

#include "String.h"
#include <Atmos/ImageAsset.h>
#include <Atmos/ShaderAsset.h>
#include <Atmos/MaterialAsset.h>

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
        const String& materialName,
        const Arca::Index<Atmos::Asset::Script>& asset,
        const String& executeName,
        const Atmos::Scripting::Parameters& parameters,
        Arca::Reliquary& reliquary);
    Arca::Index<Atmos::Asset::Script> CreateScript(
        const String& scriptName,
        Arca::Reliquary& reliquary);

    inline const String atmosDefaultMaterialName = "default_material";
}