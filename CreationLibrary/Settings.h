#pragma once

#include "FilePath.h"

#include <Inscription/Scribe.h>
#include <Inscription/CompositeScribeCategory.h>

namespace Creation
{
    struct Settings
    {
        File::Path worldPath;
        File::Path buildPath;
        File::Path audioAssetPath;
        File::Path imageAssetPath;
        File::Path fontAssetPath;
        File::Path scriptAssetPath;
        File::Path compiledScriptAssetPath;
        File::Path shaderAssetPath;
        File::Path compiledShaderAssetPath;

        bool viewTerrain = true;
        bool viewEntityBoundary = true;
        bool viewEntities = true;
    };

    inline Settings settings;
}

namespace Inscription
{
    template<>
    class Scribe<Creation::Settings> final
    {
    public:
        using ObjectT = Creation::Settings;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format);
    };

    template<class Format>
    struct ScribeTraits<Creation::Settings, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Settings>;
    };

    template<class Format>
    void Scribe<Creation::Settings>::Scriven(ObjectT& object, Format& format)
    {
        format("worldPath", object.worldPath);
        format("buildPath", object.buildPath);
        format("audioAssetPath", object.audioAssetPath);
        format("imageAssetPath", object.imageAssetPath);
        format("fontAssetPath", object.fontAssetPath);
        format("scriptAssetPath", object.scriptAssetPath);
        format("compiledScriptAssetPath", object.compiledScriptAssetPath);
        format("shaderAssetPath", object.shaderAssetPath);
        format("compiledShaderAssetPath", object.compiledShaderAssetPath);
        format("viewTerrain", object.viewTerrain);
        format("viewEntityBoundary", object.viewEntityBoundary);
        format("viewEntities", object.viewEntities);
    }
}