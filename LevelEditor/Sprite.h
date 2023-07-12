#pragma once

#include <cstddef>
#include <Atmos\Sprite.h>
#include <Atmos\AssetReference.h>
#include <Atmos\ShaderAsset.h>
#include "Selectable.h"

namespace Creation
{
    template<>
    class Selectable<Atmos::Sprite> : public SelectableBase<Atmos::Sprite>
    {
    private:
        ::Atmos::AssetReference<::Atmos::ShaderAsset> shader;
        void SelectImpl() override;
        void DeselectImpl() override;
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

DEFINE_SELECTABLE_HASH_REF(Atmos::Sprite)