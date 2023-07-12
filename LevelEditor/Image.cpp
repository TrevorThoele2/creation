
#include "Image.h"
#include "ImageRegistry.h"

#include <Atmos/Environment.h>
#include <Atmos/GridSize.h>

namespace Creation
{
    void Image::CalculateSize()
    {
        if (!asset)
        {
            SetWidth(0.0f);
            SetHeight(0.0f);
            return;
        }

        SetWidth(static_cast<::Atmos::Size3D::ValueT>(asset->GetWidth()));
        SetHeight(static_cast<::Atmos::Size3D::ValueT>(asset->GetHeight()));
    }

    void Image::DrawImpl() const
    {
        ::Atmos::Environment::GetGraphics()->RenderUnknownFragment(*this);
    }

    ::Atmos::AxisBoundingBox3D::Coordinate Image::GetZHeight() const
    {
        return ::Atmos::GRID_SIZE<::Atmos::AxisBoundingBox3D::Coordinate>;
    }

    Image::Image(const ImageAsset::FileName &name, const ::Atmos::Color &color) : RenderFragment(true), asset(ImageRegistry::Find(name)), color(color)
    {
        CalculateSize();
    }

    Image::Image(const ImageAsset *asset, const ::Atmos::Color &color) : RenderFragment(true), asset(asset), color(color)
    {
        CalculateSize();
    }

    Image::Image(const Image &arg) : RenderFragment(arg), asset(arg.asset), color(arg.color)
    {
        CalculateSize();
    }

    Image::Image(Image &&arg) : RenderFragment(std::move(arg)), asset(std::move(arg.asset)), color(std::move(arg.color))
    {}

    Image& Image::operator=(const Image &arg)
    {
        RenderFragment::operator=(arg);
        asset = arg.asset;
        color = arg.color;
        CalculateSize();
        return *this;
    }

    Image& Image::operator=(Image &&arg)
    {
        RenderFragment::operator=(std::move(arg));
        asset = std::move(arg.asset);
        color = std::move(arg.color);
        return *this;
    }

    void Image::SetAsset(const ImageAsset::FileName &name)
    {
        SetAsset(ImageRegistry::Find(name));
    }

    void Image::SetAsset(const ImageAsset *set)
    {
        asset = set;
        CalculateSize();
    }

    const ImageAsset* Image::GetAsset() const
    {
        return asset;
    }

    void Image::SetXScaler(::Atmos::Size3D::ValueT set)
    {
        RenderFragment::SetXScaler(set);
    }

    void Image::SetYScaler(::Atmos::Size3D::ValueT set)
    {
        RenderFragment::SetYScaler(set);
    }

    void Image::SetZScaler(::Atmos::Size3D::ValueT set)
    {
        RenderFragment::SetZScaler(set);
    }

    void Image::SetScalers(const ::Atmos::Join3<::Atmos::Size3D::ValueT> &set)
    {
        RenderFragment::SetScalers(set);
    }
}