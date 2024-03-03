#include "AssetsRoot.h"

namespace Creation::Editing::Data
{
    AssetsRoot::AssetsRoot(Input input) :
        Root(false, input.nexusHistory),
        actionAssets(input.actionAssets, nullptr, input.nexusHistory, input.ui, input.reliquary, "Action Assets"),
        audioAssets(input.audioAssets, nullptr, input.nexusHistory, input.ui, input.reliquary, "Audio Assets"),
        imageAssets(input.imageAssets, nullptr, input.nexusHistory, input.ui, input.reliquary, "Image Assets"),
        fontAssets(input.fontAssets, nullptr, input.nexusHistory, input.ui, input.reliquary, "Font Assets"),
        materialAssets(input.materialAssets, nullptr, input.nexusHistory, input.ui, input.reliquary, "Material Assets"),
        scriptAssets(input.scriptAssets, nullptr, input.nexusHistory, input.ui, input.reliquary, "Script Assets"),
        shaderAssets(input.shaderAssets, nullptr, input.nexusHistory, input.ui, input.reliquary, "Shader Assets")
    {}

    std::vector<SequenceNexusBase*> AssetsRoot::TopNexi()
    {
        return std::vector<SequenceNexusBase*>
        {
            &actionAssets,
            &audioAssets,
            &imageAssets,
            &fontAssets,
            &materialAssets,
            &scriptAssets,
            &shaderAssets
        };
    }
}