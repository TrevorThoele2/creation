
#include "GraphicsHandler.h"
#include "Image.h"

namespace Creation
{
    class ImageAssetData : public ImageAsset::Data
    {
    public:
        LPDIRECT3DTEXTURE9 tex;

        ImageAssetData(LPDIRECT3DTEXTURE9 tex) : tex(tex)
        {}

        ~ImageAssetData()
        {
            tex->Release();
        }
    };

    void GraphicsHandler::RenderUnknownFragmentImpl(const ::Atmos::RenderFragment &fragment, float X, float Y)
    {
        const Image& real = static_cast<const Image&>(fragment);
        ::Atmos::Size2D size(real.GetSize().GetWidth(), real.GetSize().GetHeight());
        RenderObject(
            real.GetAsset()->GetData<ImageAssetData>()->tex,
            nullptr,
            X,
            Y,
            fragment.GetZ(),
            ::Atmos::AxisBoundingBox2D(0.0f, 0.0f, 1.0f, 1.0f),
            size,
            ::Atmos::Position2D(size.GetWidth() / 2.0f, size.GetHeight() / 2.0f),
            ::Atmos::Join2<float>(real.GetScalers().first, real.GetScalers().second),
            real.GetXRotation(),
            real.color);
    }

    GraphicsHandler::GraphicsHandler(HWND hwnd, const ::Atmos::Join2<UINT> &backbuffer, bool fullscreen, bool subscribeEvents) : DX9GraphicsHandler(hwnd, backbuffer, fullscreen, subscribeEvents)
    {}

    ImageAsset GraphicsHandler::CreateCreationImageAsset(const ::Atmos::FilePath &filePath)
    {
        D3DXIMAGE_INFO info;
        D3DXGetImageInfoFromFile(filePath.c_str(), &info);

        LPDIRECT3DTEXTURE9 tex;
        D3DXCreateTextureFromFileEx(GetDevice(), filePath.c_str(), info.Width, info.Height, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, nullptr, nullptr, &tex);

        return ImageAsset(new ImageAssetData(tex), filePath.GetFileName(), info.Width, info.Height);
    }
}