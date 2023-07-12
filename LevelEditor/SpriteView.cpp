
#include "SpriteView.h"

namespace Creation
{
    void Selectable<SpriteViewImmutable>::SelectImpl()
    {
        //shader = GetWrapped()->sprite.GetShader();
        //GetWrapped()->sprite.SetShader("SpriteSelection.fx");
    }

    void Selectable<SpriteViewImmutable>::DeselectImpl()
    {
        //GetWrapped()->sprite.SetShader(shader);
        shader = nullptr;
    }

    Selectable<SpriteViewImmutable>::Selectable(WrappedT &wrapped) : SelectableBase(wrapped), shader(nullptr)
    {}

    Selectable<SpriteViewImmutable>::Selectable(Selectable &&arg) : SelectableBase(std::move(arg)), shader(arg.shader)
    {}

    Selectable<SpriteViewImmutable>& Selectable<SpriteViewImmutable>::operator=(Selectable &&arg)
    {
        SelectableBase::operator=(std::move(arg));
        shader = arg.shader;
        return *this;
    }

    bool Selectable<SpriteViewImmutable>::operator==(const Selectable &arg) const
    {
        return SelectableBase::operator==(arg);
    }

    bool Selectable<SpriteViewImmutable>::operator!=(const Selectable &arg) const
    {
        return !(*this == arg);
    }

    SpriteViewHolder::SpriteViewHolder(wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &smallestSize, const wxString &name) : RenderWindow(parent, winid, pos, smallestSize, name), smallestSize(smallestSize)
    {}

    void SpriteViewHolder::Set(const SpriteT &set)
    {
        int width = 0;
        int height = 0;
        (set.GetSize().GetWidth() < smallestSize.GetWidth()) ? width = smallestSize.GetWidth() : width = set.GetSize().GetWidth();
        (set.GetSize().GetHeight() < smallestSize.GetHeight()) ? height = smallestSize.GetHeight() : height = set.GetSize().GetHeight();
        SetSize(wxSize(width, height));

        sprite.Set(set);
        Refresh();
    }

    void SpriteViewHolder::Set(const SpriteT *set)
    {
        if (!set)
        {
            Reset();
            return;
        }

        Set(*set);
    }

    void SpriteViewHolder::Set(SpriteT &&set)
    {
        int width = 0;
        int height = 0;
        (set.GetSize().GetWidth() < smallestSize.GetWidth()) ? width = smallestSize.GetWidth() : width = set.GetSize().GetWidth();
        (set.GetSize().GetHeight() < smallestSize.GetHeight()) ? height = smallestSize.GetHeight() : height = set.GetSize().GetHeight();
        SetSize(wxSize(width, height));

        sprite.Set(std::move(set));
        Refresh();
    }

    void SpriteViewHolder::Reset()
    {
        sprite.Reset();
        Refresh();
    }

    bool SpriteViewHolder::IsSet() const
    {
        return sprite.IsValid();
    }

    SpriteViewHolder::SpriteT* SpriteViewHolder::GetSprite()
    {
        if (sprite.IsValid())
            return &*sprite;
        else
            return nullptr;
    }

    std::unordered_set<const Atmos::Sprite*> SpriteViewHolder::GetSprites() const
    {
        std::unordered_set<const Atmos::Sprite*> ret;
        if (!sprite)
            return ret;

        ret.emplace(&sprite.Get());
        return ret;
    }
}