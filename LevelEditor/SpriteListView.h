#pragma once

#include "RenderWindow.h"

namespace Creation
{
    /*
    // Holds only one spritelist node
    template<class T>
    class SpriteListViewImmutableTemplate : public RenderWindow
    {
    public:
        T &sprite;
        SpriteListViewImmutableTemplate(T &sprite, wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size, const wxString &name = "SpriteListWindowImmutable");
        std::unordered_set<const Atmos::Sprite*> GetSprites() const override;
    };

    template<class T>
    SpriteListViewImmutableTemplate<T>::SpriteListViewImmutableTemplate(T &sprite, wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size, const wxString &name) : RenderWindow(parent, winid, pos, size, name), sprite(sprite)
    {}

    template<class T>
    std::unordered_set<const Atmos::Sprite*> SpriteListViewImmutableTemplate<T>::GetSprites() const
    {
        std::unordered_set<const Atmos::Sprite*> ret;
        ret.emplace(&sprite);
        return ret;
    }

    typedef SpriteListViewImmutableTemplate<Atmos::SpriteList::VisibleNode> SpriteListViewImmutable;
    typedef SpriteListViewImmutableTemplate<const Atmos::SpriteList::VisibleNode> ConstSpriteViewImmutable;
    */
}