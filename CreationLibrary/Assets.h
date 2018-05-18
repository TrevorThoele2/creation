#pragma once

#include "ActionAssetData.h"
#include "AudioAssetData.h"
#include "ImageAssetData.h"
#include "FontAssetData.h"
#include "MaterialAssetData.h"
#include "ScriptAssetData.h"
#include "ShaderAssetData.h"

#include <Inscription/ListScribe.h>

namespace Creation
{
    struct Assets
    {
        std::list<Editing::Data::ActionAsset> actionAssets;
        std::list<Editing::Data::AudioAsset> audioAssets;
        std::list<Editing::Data::ImageAsset> imageAssets;
        std::list<Editing::Data::FontAsset> fontAssets;
        std::list<Editing::Data::MaterialAsset> materialAssets;
        std::list<Editing::Data::ScriptAsset> scriptAssets;
        std::list<Editing::Data::ShaderAsset> shaderAssets;
    };
}

namespace Inscription
{
    template<>
    class Scribe<Creation::Assets> final
    {
    public:
        using ObjectT = Creation::Assets;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            format("actionAssets", object.actionAssets);
            format("audioAssets", object.audioAssets);
            format("imageAssets", object.imageAssets);
            format("fontAssets", object.fontAssets);
            format("materialAssets", object.materialAssets);
            format("scriptAssets", object.scriptAssets);
            format("shaderAssets", object.shaderAssets);
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Assets, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Assets>;
    };
}