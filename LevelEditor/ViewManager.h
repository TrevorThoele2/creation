#pragma once

#include <memory>
#include <unordered_map>

#include "CurrentWorld.h"

#include "Image.h"
#include <Atmos/Sprite.h>

namespace Creation
{
    template<class Mixin, class Package>
    class ViewManager
    {
    public:
        typedef Package PackageT;
        typedef Build::Package<::Atmos::GridPosition> PositionPackageT;
    protected:
        struct Entry
        {
            virtual ~Entry() = 0 {}
            virtual bool IsVoidImage() const = 0;
            virtual bool IsSpriteVector() const = 0;
        };

        struct VoidImageEntry : public Entry
        {
            Image underlying;
            VoidImageEntry(Image &&underlying);
            ~VoidImageEntry();
            bool IsVoidImage() const override final;
            bool IsSpriteVector() const override final;
        };

        struct SpriteVectorEntry : public Entry
        {
            std::vector<::Atmos::Sprite> underlying;
            SpriteVectorEntry(std::vector<::Atmos::Sprite> &&underlying);
            ~SpriteVectorEntry();
            bool IsVoidImage() const override final;
            bool IsSpriteVector() const override final;
            ::Atmos::Sprite& Add(::Atmos::Sprite &&add);
        };
    private:
        bool viewing;

        typedef std::unique_ptr<Entry> EntryPtr;
        typedef std::unordered_map<Atmos::GridPosition, EntryPtr> Map;
        Map map;

        virtual PositionPackageT& GetPosition(PackageT &package) = 0;
        virtual const PositionPackageT& GetPosition(const PackageT &package) = 0;
        virtual Build::Package<::Atmos::RandomAccessSequence<Build::Package<::Atmos::ObjectOffsetHandle<::Atmos::Sprite, ::Atmos::Position3D>>>>* GetSpriteList(PackageT &package) = 0;
        virtual const Build::Package<::Atmos::RandomAccessSequence<Build::Package<::Atmos::ObjectOffsetHandle<::Atmos::Sprite, ::Atmos::Position3D>>>>* GetSpriteList(const PackageT &package) = 0;
        virtual Build::Package<::Atmos::RandomAccessSequence<PackageT>>& GetFieldList(Build::Package<::Atmos::Field> &field) = 0;
        virtual Image GetDefaultVoidImageImpl() = 0;

        void OnToggled();

        void AddVoidSprite(const PositionPackageT &position);
        void RemoveSprites(const PositionPackageT &position);

        void EvaluateCommon(const PackageT &package);
    protected:
        ViewManager();
        ViewManager(const ViewManager &arg) = delete;
        ViewManager& operator=(const ViewManager &arg) = delete;
    public:
        virtual ~ViewManager() = 0 {}
        static Mixin& Instance();

        static void Clear();
        // If nullptr, will just clear this
        static void BuildFromField(Build::Package<::Atmos::Field> *field);
        static void Evaluate(const PositionPackageT &position);
        static void Evaluate(const PackageT &package);
        static void RecalculateAllSprites();

        static void ToggleView();
        static bool IsViewing();

        static Image GetDefaultVoidImage();
    };

    template<class Mixin, class Package>
    ViewManager<Mixin, Package>::VoidImageEntry::VoidImageEntry(Image &&underlying) : underlying(std::move(underlying))
    {
        GetCurrentRenderFragments()->Add(this->underlying);
    }

    template<class Mixin, class Package>
    ViewManager<Mixin, Package>::VoidImageEntry::~VoidImageEntry()
    {
        GetCurrentRenderFragments()->Remove(underlying);
    }

    template<class Mixin, class Package>
    bool ViewManager<Mixin, Package>::VoidImageEntry::IsVoidImage() const
    {
        return true;
    }

    template<class Mixin, class Package>
    bool ViewManager<Mixin, Package>::VoidImageEntry::IsSpriteVector() const
    {
        return false;
    }

    template<class Mixin, class Package>
    ViewManager<Mixin, Package>::SpriteVectorEntry::SpriteVectorEntry(std::vector<::Atmos::Sprite> &&underlying) : underlying(std::move(underlying))
    {
        for (auto &loop : this->underlying)
            GetCurrentRenderFragments()->Add(loop);
    }

    template<class Mixin, class Package>
    ViewManager<Mixin, Package>::SpriteVectorEntry::~SpriteVectorEntry()
    {
        for (auto &loop : underlying)
            GetCurrentRenderFragments()->Remove(loop);
    }

    template<class Mixin, class Package>
    bool ViewManager<Mixin, Package>::SpriteVectorEntry::IsVoidImage() const
    {
        return false;
    }

    template<class Mixin, class Package>
    bool ViewManager<Mixin, Package>::SpriteVectorEntry::IsSpriteVector() const
    {
        return true;
    }

    template<class Mixin, class Package>
    ::Atmos::Sprite& ViewManager<Mixin, Package>::SpriteVectorEntry::Add(::Atmos::Sprite &&add)
    {
        underlying.push_back(std::move(add));
        GetCurrentRenderFragments()->Add(underlying.back());
        return underlying.back();
    }

    template<class Mixin, class Package>
    void ViewManager<Mixin, Package>::OnToggled()
    {
        bool viewing = IsViewing();
        for (auto &loop : map)
        {
            if (!loop.second->IsVoidImage())
                return;

            static_cast<VoidImageEntry*>(loop.second.get())->underlying.Enable(viewing);
        }
    }

    template<class Mixin, class Package>
    void ViewManager<Mixin, Package>::AddVoidSprite(const PositionPackageT &position)
    {
        auto built = position.Build();
        auto found = map.find(built);
        if (found != map.end())
            return;

        Image image(GetDefaultVoidImage());
        image.SetPosition(built);
        map.emplace(built, EntryPtr(new VoidImageEntry(std::move(image))));
    }

    template<class Mixin, class Package>
    void ViewManager<Mixin, Package>::RemoveSprites(const PositionPackageT &position)
    {
        auto found = map.find(position.Build());
        if (found == map.end())
            return;

        map.erase(found);
    }

    template<class Mixin, class Package>
    void ViewManager<Mixin, Package>::EvaluateCommon(const PackageT &package)
    {
        Build::Package<::Atmos::GridPosition> positionPackage(GetPosition(package));
        ::Atmos::GridPosition gridPosition(positionPackage.Build());
        auto found = map.find(gridPosition);

        auto sprites = GetSpriteList(package);
        // Has no sprites
        if (!sprites || sprites->value.empty())
        {
            // Check for previous entries for this tile
            if (found != map.end())
            {
                if (found->second->IsVoidImage())
                    return;
                else
                    map.erase(found);
            }

            AddVoidSprite(positionPackage);
            return;
        }

        // Has sprites
        bool hasRenderableSprites = false;
        for (auto &loop : sprites->value)
        {
            auto builtMaterial = loop.wrapped.material.Build();
            if (builtMaterial)
            {
                // Can check this to make sure we haven't deleted already
                if (!hasRenderableSprites)
                {
                    // If the entry already exists and is a void image
                    if (found != map.end() && found->second->IsVoidImage())
                    {
                        map.erase(found);
                        found = map.emplace(gridPosition, EntryPtr(new SpriteVectorEntry(std::vector<::Atmos::Sprite>()))).first;
                    }
                    // Else if the entry already exists and are actual images
                    else if (found != map.end() && found->second->IsSpriteVector())
                    {
                        static_cast<SpriteVectorEntry*>(found->second.get())->underlying.clear();
                    }
                    // Must be an empty entry
                    else
                    {
                        found = map.emplace(gridPosition, EntryPtr(new SpriteVectorEntry(std::vector<::Atmos::Sprite>()))).first;
                    }
                }

                ::Atmos::Position3D position3D(gridPosition);
                position3D.IncrementX(loop.xOffset.Build());
                position3D.IncrementY(loop.yOffset.Build());
                position3D.IncrementZ(loop.zOffset.Build());
                static_cast<SpriteVectorEntry*>(found->second.get())->Add(loop.wrapped.Build()).SetPosition(position3D);

                hasRenderableSprites = true;
            }
        }

        // Tile has sprites, but none would be rendered
        if (!hasRenderableSprites && found == map.end())
            AddVoidSprite(positionPackage);
    }

    template<class Mixin, class Package>
    ViewManager<Mixin, Package>::ViewManager() : viewing(true)
    {}

    template<class Mixin, class Package>
    Mixin& ViewManager<Mixin, Package>::Instance()
    {
        static Mixin instance;
        return instance;
    }

    template<class Mixin, class Package>
    void ViewManager<Mixin, Package>::Clear()
    {
        Instance().map.clear();
    }

    template<class Mixin, class Package>
    void ViewManager<Mixin, Package>::BuildFromField(Build::Package<::Atmos::Field> *field)
    {
        Clear();
        if (!field)
            return;

        for (auto &loop : Instance().GetFieldList(*field).value)
            Evaluate(loop);
    }

    template<class Mixin, class Package>
    void ViewManager<Mixin, Package>::Evaluate(const PositionPackageT &position)
    {
        for (auto &loop : Instance().GetFieldList(CurrentWorld::fieldPackage).value)
        {
            if (Instance().GetPosition(loop) == position)
            {
                Instance().EvaluateCommon(loop);
                return;
            }
        }

        // Was not found
        Instance().RemoveSprites(position);
    }

    template<class Mixin, class Package>
    void ViewManager<Mixin, Package>::Evaluate(const PackageT &package)
    {
        for (auto &loop : Instance().GetFieldList(CurrentWorld::fieldPackage).value)
        {
            if (loop == package)
            {
                Instance().EvaluateCommon(loop);
                return;
            }
        }

        // Was not found
        Instance().RemoveSprites(Instance().GetPosition(package));
    }

    template<class Mixin, class Package>
    void ViewManager<Mixin, Package>::RecalculateAllSprites()
    {
        for (auto &loop : Instance().map)
        {
            if (loop.second->IsSpriteVector())
            {
                auto casted = static_cast<SpriteVectorEntry*>(loop.second.get());
                for (auto &castedLoop : casted->underlying)
                    castedLoop.SetMaterial(castedLoop.GetMaterial());
            }
        }
    }

    template<class Mixin, class Package>
    void ViewManager<Mixin, Package>::ToggleView()
    {
        Instance().viewing = !Instance().viewing;
        Instance().OnToggled();
    }

    template<class Mixin, class Package>
    bool ViewManager<Mixin, Package>::IsViewing()
    {
        return Instance().viewing;
    }

    template<class Mixin, class Package>
    Image ViewManager<Mixin, Package>::GetDefaultVoidImage()
    {
        return Instance().GetDefaultVoidImageImpl();
    }

    // Will also deconstruct the internal assets
    void DeconstructAllViewManagers();
    // Will also construct the internal assets
    void ConstructAllViewManagers(Build::Package<Atmos::Field> *field = &CurrentWorld::fieldPackage);
}