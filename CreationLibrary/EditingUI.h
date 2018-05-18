#pragma once

#include <memory>

#include "DataRoot.h"

#include "PropertiesEditor.h"
#include "PropertiesTree.h"

#include "AssetsRoot.h"
#include "EntitiesRoot.h"
#include "EntityBoundaryRoot.h"
#include "TerrainRoot.h"

#include "World.h"

namespace Creation::Editing
{
    class UI
    {
    public:
        UI(
            PropertiesEditor& editor,
            PropertiesTree& tree,
            Arca::Reliquary& renderReliquary,
            const NexusHistory& nexusHistory);

        template<class RootT, std::enable_if_t<std::is_base_of_v<Data::Root, RootT>, int> = 0>
        void ShowRoot();
        void HideRoot();
        template<class RootT, std::enable_if_t<std::is_base_of_v<Data::Root, RootT>, int> = 0>
        RootT* Root();

        void CommitChanges();

        void WorldChanged(World* world);
        void FieldChanging();
        void FieldChanged(Field& field);

        void ViewTerrain(bool value);
        void ViewEntityBoundary(bool value);
        void ViewEntities(bool value);

        void Freeze();
        void Thaw();

        void RefreshTree();

        [[nodiscard]] Data::AssetsRoot* AssetsRoot();
    private:
        std::unique_ptr<Data::AssetsRoot> assetsRoot;
        struct FieldRoots
        {
            Data::EntitiesRoot entities;
            Data::EntityBoundaryRoot entityBoundary;
            Data::TerrainRoot terrain;
            FieldRoots(
                Data::EntitiesRoot::Input& entities,
                Data::EntityBoundaryRoot::Input& entityBoundary,
                Data::TerrainRoot::Input& terrain);
        };
        std::unique_ptr<FieldRoots> fieldRoots;

        Data::Root* shownRoot = nullptr;

        template<class RootT, std::enable_if_t<std::is_base_of_v<Data::Root, RootT>, int> = 0>
        RootT* TypeToRoot();
    private:
        PropertiesTree* tree = nullptr;
        PropertiesEditor* editor = nullptr;
        Arca::Reliquary* renderReliquary = nullptr;
    private:
        bool viewTerrain = true;
        bool viewEntityBoundary = true;
        bool viewEntities = true;
        template<class RootT>
        void ChangeVisibility(bool to, bool& of);
    private:
        NexusHistory nexusHistory;
    };

    template<class RootT, std::enable_if_t<std::is_base_of_v<Data::Root, RootT>, int>>
    void UI::ShowRoot()
    {
        HideRoot();
        shownRoot = TypeToRoot<RootT>();
        shownRoot->CreateTreeElements(*tree);
    }

    template<class RootT, std::enable_if_t<std::is_base_of_v<Data::Root, RootT>, int>>
    RootT* UI::Root()
    {
        return TypeToRoot<RootT>();
    }

    template<class RootT, std::enable_if_t<std::is_base_of_v<Data::Root, RootT>, int>>
    RootT* UI::TypeToRoot()
    {
        if constexpr (std::is_same_v<RootT, Data::AssetsRoot>)
            return assetsRoot ? &*assetsRoot : nullptr;
        else if constexpr (std::is_same_v<RootT, Data::EntitiesRoot>)
            return fieldRoots ? &fieldRoots->entities : nullptr;
        else if constexpr (std::is_same_v<RootT, Data::EntityBoundaryRoot>)
            return fieldRoots ? &fieldRoots->entityBoundary : nullptr;
        else if constexpr (std::is_same_v<RootT, Data::TerrainRoot>)
            return fieldRoots ? &fieldRoots->terrain : nullptr;
        else
            return nullptr;
    }

    template<class RootT>
    void UI::ChangeVisibility(bool to, bool& of)
    {
        if (of != to)
        {
            of = to;
            if (fieldRoots)
            {
                auto& root = *TypeToRoot<RootT>();
                if (to)
                    root.Show();
                else
                    root.Hide();
            }
        }
    }
}