#include "EditBox.h"

#include <Atmos/MoveBounds.h>
#include <Atmos/ScaleBounds.h>
#include "DefaultImageMaterials.h"

#include <Atmos/SpatialAlgorithms.h>
#include <Arca/Create.h>
#include <Arca/Destroy.h>

namespace Creation::Editing
{
    EditBox::EditBox(
        Arca::Index<Atmos::Asset::Image> imageAsset,
        Atmos::Spatial::Point2D position,
        Atmos::Render::Color color,
        Arca::Reliquary& reliquary)
        :
        position(position),
        image(reliquary.Do(Arca::Create<Atmos::Render::DynamicImage>(
            imageAsset,
            1,
            reliquary.Find<DefaultImageMaterials>()->material,
            color,
            Atmos::Spatial::Point3D
            {
                position.x,
                position.y,
                z
            },
            Atmos::Spatial::Scalers2D{ 1, 1 },
            Atmos::Spatial::Angle2D(0)))),
        reliquary(&reliquary)
    {}

    EditBox::~EditBox()
    {
        if (image)
            reliquary->Do(Arca::Destroy<Atmos::Render::DynamicImage>(image.ID()));
    }

    void EditBox::DynamicPositionMoved(Atmos::Spatial::Point2D otherPosition)
    {
        if (image)
        {
            const auto box = CompleteBox(otherPosition);

            image.Owner()->Do(Atmos::Spatial::MoveBounds(
                image.ID(),
                Atmos::Spatial::Point3D
                {
                    box.center.x,
                    box.center.y,
                    z
                }));

            image.Owner()->Do(Atmos::Spatial::ScaleBounds(
                image.ID(),
                Atmos::Spatial::Scalers2D
                {
                    box.size.width,
                    box.size.height
                }));
        }
    }

    Atmos::Spatial::AxisAlignedBox2D EditBox::CompleteBox(Atmos::Spatial::Point2D otherPosition) const
    {
        const auto left = position.x < otherPosition.x
            ? position.x
            : otherPosition.x;

        const auto top = position.y < otherPosition.y
            ? position.y
            : otherPosition.y;

        const auto right = position.x > otherPosition.x
            ? position.x
            : otherPosition.x;

        const auto bottom = position.y > otherPosition.y
            ? position.y
            : otherPosition.y;

        return Atmos::Spatial::ToAxisAlignedBox2D(left, top, right, bottom);
    }
}