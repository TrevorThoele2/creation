#pragma once

#include "RenderWindow.h"
#include "Selectable.h"

#include "Optional.h"

namespace Creation
{
	// Holds only one sprite
    template<class T>
    class SpriteViewImmutableTemplate : public RenderWindow
    {
    public:
		T &sprite;
        SpriteViewImmutableTemplate(T &sprite, wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size, const wxString &name = "SpriteWindowImmutable");
        std::unordered_set<const Atmos::Sprite*> GetSprites() const override;
    };

    template<class T>
    SpriteViewImmutableTemplate<T>::SpriteViewImmutableTemplate(T &sprite, wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size, const wxString &name) : RenderWindow(parent, winid, pos, size, name), sprite(sprite)
    {}

    template<class T>
    std::unordered_set<const Atmos::Sprite*> SpriteViewImmutableTemplate<T>::GetSprites() const
    {
        std::unordered_set<const Atmos::Sprite*> ret;
        ret.emplace(&sprite);
        return ret;
    }

    typedef SpriteViewImmutableTemplate<Atmos::Sprite> SpriteViewImmutable;
    typedef SpriteViewImmutableTemplate<const Atmos::Sprite> ConstSpriteViewImmutable;

    template<>
    class Selectable<SpriteViewImmutable> : public SelectableBase<SpriteViewImmutable>
    {
    private:
        const Atmos::ShaderAsset *shader;

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

    template<class T>
    class SpriteViewTemplate : public RenderWindow
    {
    private:
        T *sprite;
        wxSize smallestSize;
    public:
        SpriteViewTemplate(wxWindow *parent, wxWindowID winid, const wxPoint &pos = wxDefaultPosition, const wxSize &smallestSize = wxDefaultSize, const wxString &name = "SpriteWindow");
        void Set(T *sprite);
        void Reset();
        bool IsSet() const;
        T* GetSprite();

        std::unordered_set<const Atmos::Sprite*> GetSprites() const override;
    };

    template<class T>
    SpriteViewTemplate<T>::SpriteViewTemplate(wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &smallestSize, const wxString &name) : RenderWindow(parent, winid, pos, smallestSize, name), smallestSize(smallestSize), sprite(nullptr)
    {}

    template<class T>
    void SpriteViewTemplate<T>::Set(T *sprite)
    {
        if (!sprite)
        {
            Reset();
            return;
        }

        int width = 0;
        int height = 0;
        (sprite->GetSize().GetWidth() < smallestSize.GetWidth()) ? width = smallestSize.GetWidth() : width = sprite->GetSize().GetWidth();
        (sprite->GetSize().GetHeight() < smallestSize.GetHeight()) ? height = smallestSize.GetHeight() : height = sprite->GetSize().GetHeight();
        SetSize(wxSize(width, height));

        this->sprite = sprite;
        Refresh();
    }

    template<class T>
    void SpriteViewTemplate<T>::Reset()
    {
        SetSize(smallestSize);
        sprite = nullptr;
        Refresh();
    }

    template<class T>
    bool SpriteViewTemplate<T>::IsSet() const
    {
        return sprite != nullptr;
    }

    template<class T>
    T* SpriteViewTemplate<T>::GetSprite()
    {
        return sprite;
    }

    template<class T>
    std::unordered_set<const Atmos::Sprite*> SpriteViewTemplate<T>::GetSprites() const
    {
        std::unordered_set<const Atmos::Sprite*> set;
        if (!sprite)
            return set;

        set.emplace(sprite);
        return set;
    }

    typedef SpriteViewTemplate<Atmos::Sprite> SpriteView;
    typedef SpriteViewTemplate<const Atmos::Sprite> ConstSpriteView;

    // This owns the sprite that it displays
    class SpriteViewHolder : public RenderWindow
    {
    public:
        typedef Atmos::Sprite SpriteT;
    private:
        Optional<SpriteT> sprite;
        wxSize smallestSize;
    public:
        SpriteViewHolder(wxWindow *parent, wxWindowID winid, const wxPoint &pos = wxDefaultPosition, const wxSize &smallestSize = wxDefaultSize, const wxString &name = "SpriteWindowHolder");
        void Set(const SpriteT &set);
        void Set(const SpriteT *set);
        void Set(SpriteT &&set);
        void Reset();
        bool IsSet() const;
        SpriteT* GetSprite();

        std::unordered_set<const Atmos::Sprite*> GetSprites() const override;
    };
}

DEFINE_SELECTABLE_HASH_REF(Creation::SpriteViewImmutable)