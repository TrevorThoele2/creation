#pragma once

#include <Atmos/DynamicImage.h>

namespace Creation::Editing
{
    class DynamicWorldImage final
    {
    public:
        struct Data
        {
            Arca::Index<Atmos::Asset::Image> asset;
            Arca::Index<Atmos::Asset::Material> material;
            Atmos::Render::Color color;
            int32_t assetIndex;
            Atmos::Spatial::Point3D position;
            Atmos::Spatial::Scalers2D scalers;
            Atmos::Spatial::Angle2D rotation;
        };
    public:
        DynamicWorldImage(Arca::Reliquary& reliquary);
        DynamicWorldImage(DynamicWorldImage&& arg) noexcept = default;
        ~DynamicWorldImage();

        [[nodiscard]] operator bool() const;

        void Create(Data data);
        void Destroy();
        void Refresh(Data data);
    private:
        using Object = Atmos::Render::DynamicImage;
        using Index = Arca::Index<Object>;

        Index object;
    private:
        Arca::Reliquary* reliquary;

        Arca::MutablePointer MutablePointer();
    };
}