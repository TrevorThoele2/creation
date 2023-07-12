
#include "Sprite.h"

#include "InternalShaders.h"

#include "Viewport.h"

namespace Creation
{
    void Selectable<Atmos::Sprite>::SelectImpl()
    {
        shader = GetWrapped().GetShaderPatch();
        GetWrapped().SetShaderPatch(spriteSelectionName);
    }

    void Selectable<Atmos::Sprite>::DeselectImpl()
    {
        GetWrapped().SetShaderPatch(shader);
        shader = nullptr;
    }

    Selectable<Atmos::Sprite>::Selectable(WrappedT &wrapped) : SelectableBase(wrapped), shader(nullptr)
    {}

    Selectable<Atmos::Sprite>::Selectable(Selectable &&arg) : SelectableBase(std::move(arg)), shader(arg.shader)
    {}

    Selectable<Atmos::Sprite>& Selectable<Atmos::Sprite>::operator=(Selectable &&arg)
    {
        SelectableBase::operator=(std::move(arg));
        shader = arg.shader;
        return *this;
    }

    bool Selectable<Atmos::Sprite>::operator==(const Selectable &arg) const
    {
        return SelectableBase::operator==(arg);
    }

    bool Selectable<Atmos::Sprite>::operator!=(const Selectable &arg) const
    {
        return !(*this == arg);
    }
}