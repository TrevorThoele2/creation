#pragma once

#include <Atmos/RenderFragment.h>
#include "ImageAsset.h"
#include <Atmos/Color.h>

namespace Creation
{
    class Image : public ::Atmos::RenderFragment
    {
    private:
        const ImageAsset *asset;

        void CalculateSize();

        void DrawImpl() const override final;
        ::Atmos::AxisBoundingBox3D::Coordinate GetZHeight() const override final;
    public:
        ::Atmos::Color color;

        Image(const ImageAsset::FileName &name, const ::Atmos::Color &color);
        Image(const ImageAsset *asset, const ::Atmos::Color &color);
        Image(const Image &arg);
        Image(Image &&arg);
        Image& operator=(const Image &arg);
        Image& operator=(Image &&arg);

        void SetAsset(const ImageAsset::FileName &name);
        void SetAsset(const ImageAsset *set);
        const ImageAsset* GetAsset() const;

        void SetXScaler(::Atmos::Size3D::ValueT set);
        void SetYScaler(::Atmos::Size3D::ValueT set);
        void SetZScaler(::Atmos::Size3D::ValueT set);
        void SetScalers(const ::Atmos::Join3<::Atmos::Size3D::ValueT> &set);
    };
}