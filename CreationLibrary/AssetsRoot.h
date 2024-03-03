#pragma once

#include "DataRoot.h"

#include "ListData.h"
#include "ActionAssetData.h"
#include "AudioAssetData.h"
#include "ImageAssetData.h"
#include "FontAssetData.h"
#include "MaterialAssetData.h"
#include "ScriptAssetData.h"
#include "ShaderAssetData.h"

namespace Creation::Editing::Data
{
    class AssetsRoot final : public Root
    {
    public:
        struct Input
        {
            std::list<ActionAsset>& actionAssets;
            std::list<AudioAsset>& audioAssets;
            std::list<ImageAsset>& imageAssets;
            std::list<FontAsset>& fontAssets;
            std::list<MaterialAsset>& materialAssets;
            std::list<ScriptAsset>& scriptAssets;
            std::list<ShaderAsset>& shaderAssets;
            Arca::Reliquary& reliquary;
            const NexusHistory& nexusHistory;
            UI& ui;
        };
    public:
        Nexus<std::list<ActionAsset>> actionAssets;
        Nexus<std::list<AudioAsset>> audioAssets;
        Nexus<std::list<ImageAsset>> imageAssets;
        Nexus<std::list<FontAsset>> fontAssets;
        Nexus<std::list<MaterialAsset>> materialAssets;
        Nexus<std::list<ScriptAsset>> scriptAssets;
        Nexus<std::list<ShaderAsset>> shaderAssets;
    public:
        AssetsRoot(Input input);
        AssetsRoot(const AssetsRoot& arg) = delete;
        AssetsRoot(AssetsRoot&& arg) noexcept = default;
    protected:
        [[nodiscard]] std::vector<SequenceNexusBase*> TopNexi() override;
    };
}
