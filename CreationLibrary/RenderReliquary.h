#pragma once

#include <Arca/Reliquary.h>
#include <Atmos/GraphicsManager.h>
#include <Atmos/TextManager.h>
#include <Atmos/AssetResourceManager.h>

namespace Creation
{
    std::unique_ptr<Arca::Reliquary> CreateRenderReliquary(
        Atmos::Render::GraphicsManager& graphicsManager,
        Atmos::Render::TextManager& textManager,
        Atmos::Asset::Resource::Manager& assetResourceManager,
        Atmos::Spatial::Size2D clientSize,
        Atmos::Logging::Logger& logger,
        void* hwnd);
}