#include "DynamicWorldImage.h"

#include "MutationCurator.h"

#include <Atmos/ChangeImageCore.h>
#include <Atmos/ChangeColor.h>
#include <Atmos/ChangeMaterialAsset.h>
#include <Atmos/MoveBounds.h>
#include <Atmos/ScaleBounds.h>
#include <Atmos/RotateBounds.h>
#include <Arca/Create.h>
#include <Arca/Destroy.h>

namespace Creation::Editing
{
    DynamicWorldImage::DynamicWorldImage(Arca::Reliquary& reliquary) :
        reliquary(&reliquary)
    {}

    DynamicWorldImage::~DynamicWorldImage()
    {
        Destroy();
    }

    DynamicWorldImage::operator bool() const
    {
        return object;
    }

    void DynamicWorldImage::Create(Data data)
    {
        object = reliquary->Do(Arca::Create<Atmos::Render::DynamicImage> {
            data.asset,
            data.assetIndex,
            data.material,
            data.color,
            data.position,
            data.scalers,
            data.rotation });
    }

    void DynamicWorldImage::Destroy()
    {
        if (reliquary && object)
            reliquary->Do(Arca::Destroy<Atmos::Render::DynamicImage>{ object.ID() });
    }

    void DynamicWorldImage::Refresh(Data data)
    {
        reliquary->Do(Atmos::Render::ChangeImageCore{ object.ID(), data.asset, data.assetIndex });
        reliquary->Do(Atmos::Render::ChangeColor{ object.ID(), data.color });
        reliquary->Do(Atmos::Render::ChangeMaterialAsset{ object.ID(), data.material });
        reliquary->Do(Atmos::Spatial::MoveBounds(object.ID(), data.position));
        reliquary->Do(Atmos::Spatial::ScaleBounds(object.ID(), data.scalers));
        reliquary->Do(Atmos::Spatial::RotateBounds(object.ID(), data.rotation));
    }

    Arca::MutablePointer DynamicWorldImage::MutablePointer()
    {
        return reliquary->Find<Creation::MutationCurator>().RetrieveMutablePointer();
    }
}
