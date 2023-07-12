
#include "Tile.h"

#include "CurrentWorld.h"
#include "Viewport.h"

namespace Creation
{
    void CreateImage(Optional<Image> &image, Build::Package<Atmos::Tile> &tile, const ::Atmos::FileName &assetName, const Atmos::Color &color)
    {
        image.Set(assetName, color);
        image->SetPosition(tile.position.Build());
        image->SetZ(::Atmos::GridPosition::DimensionToPosition(tile.position.z.Build()) + 1.0f);
    }

    void Selectable<Build::Package<Atmos::Tile>>::SelectImpl()
    {
        if (selectedRender)
            return;

        CreateImage(selectedRender, GetWrapped(), pixelImageName, Atmos::Color(127, 255, 255, 255));
        selectedRender->SetXScaler(32.0f);
        selectedRender->SetYScaler(32.0f);
        PublishSprite();
    }

    void Selectable<Build::Package<Atmos::Tile>>::DeselectImpl()
    {
        selectedRender.Reset();
    }

    void Selectable<Build::Package<Atmos::Tile>>::PublishSprite()
    {
        if(selectedRender.IsValid())
            CurrentWorld::GetCurrentField()->renderFragments.Add(*selectedRender);
    }

    void Selectable<Build::Package<Atmos::Tile>>::UnpublishSprite()
    {
        if (selectedRender.IsValid())
            CurrentWorld::GetCurrentField()->renderFragments.Remove(*selectedRender);
    }

    void Selectable<Build::Package<Atmos::Tile>>::OnMove(Selectable &&arg)
    {
        arg.UnpublishSprite();
        selectedRender = std::move(arg.selectedRender);
        PublishSprite();
    }

    Selectable<Build::Package<Atmos::Tile>>::Selectable(WrappedT &wrapped) : SelectableBase(wrapped)
    {}

    Selectable<Build::Package<Atmos::Tile>>::Selectable(Selectable &&arg) : SelectableBase(std::move(arg))
    {
        OnMove(std::move(arg));
    }

    Selectable<Build::Package<Atmos::Tile>>& Selectable<Build::Package<Atmos::Tile>>::operator=(Selectable &&arg)
    {
        SelectableBase::operator=(std::move(arg));

        OnMove(std::move(arg));
        return *this;
    }

    bool Selectable<Build::Package<Atmos::Tile>>::operator==(const Selectable &arg) const
    {
        return SelectableBase::operator==(arg);
    }

    bool Selectable<Build::Package<Atmos::Tile>>::operator!=(const Selectable &arg) const
    {
        return !(*this == arg);
    }
}