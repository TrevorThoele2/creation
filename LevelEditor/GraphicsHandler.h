#pragma once

#include <Atmos/DXGraphics.h>

#include "ImageAsset.h"

namespace Creation
{
    class GraphicsHandler : public ::Atmos::DX9GraphicsHandler
    {
    private:
        void RenderUnknownFragmentImpl(const ::Atmos::RenderFragment &fragment, float X, float Y) override;
    public:
        GraphicsHandler(HWND hwnd, const ::Atmos::Join2<UINT> &backbuffer, bool fullscreen, bool subscribeEvents = true);

        ImageAsset CreateCreationImageAsset(const ::Atmos::FilePath &filePath);
    };
}