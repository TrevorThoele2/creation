#pragma once

#include <Atmos/DynamicImage.h>

namespace Creation::Editing
{
    class EditBox
    {
    public:
        EditBox(
            Arca::Index<Atmos::Asset::Image> imageAsset,
            Atmos::Spatial::Point2D position,
            Atmos::Render::Color color,
            Arca::Reliquary& reliquary);
        EditBox(const EditBox& arg) = delete;
        EditBox(EditBox&& arg) = default;
        ~EditBox();

        EditBox& operator=(const EditBox& arg) = delete;
        EditBox& operator=(EditBox&& arg) = default;

        void DynamicPositionMoved(Atmos::Spatial::Point2D otherPosition);

        [[nodiscard]] Atmos::Spatial::AxisAlignedBox2D CompleteBox(Atmos::Spatial::Point2D otherPosition) const;
    private:
        Atmos::Spatial::Point2D position;

        Arca::Index<Atmos::Render::DynamicImage> image;

        Arca::Reliquary* reliquary = nullptr;
    private:
        static constexpr Atmos::Spatial::Point2D::Value z =
            std::numeric_limits<Atmos::Spatial::Point2D::Value>::max() / 2 - 1;
    };
}