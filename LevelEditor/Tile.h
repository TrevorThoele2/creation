#pragma once

#include "Selectable.h"

#include "BuildPackageTile.h"
#include "Optional.h"
#include "Image.h"

namespace Creation
{
    template<>
    class Selectable<Build::Package<Atmos::Tile>> : public SelectableBase<Build::Package<Atmos::Tile>>
    {
    private:
        Optional<Image> selectedRender;

        void SelectImpl() override;
        void DeselectImpl() override;

        void PublishSprite();
        void UnpublishSprite();
        void OnMove(Selectable &&arg);
    public:
        Selectable(WrappedT &wrapped);
        Selectable(const Selectable &arg) = delete;
        Selectable& operator=(const Selectable &arg) = delete;
        Selectable(Selectable &&arg);
        Selectable& operator=(Selectable &&arg);
        bool operator==(const Selectable &arg) const;
        bool operator!=(const Selectable &arg) const;
    };
}

DEFINE_SELECTABLE_HASH_REF(Creation::Build::Package<Atmos::Tile>)