#include "EditingUI.h"

namespace Creation::Editing
{
    UI::UI(
        PropertiesEditor& editor,
        PropertiesTree& tree,
        Arca::Reliquary& renderReliquary,
        const NexusHistory& nexusHistory)
        :
        tree(&tree),
        editor(&editor),
        renderReliquary(&renderReliquary),
        nexusHistory(nexusHistory)
    {}

    void UI::HideRoot()
    {
        if (shownRoot)
        {
            shownRoot->DestroyTreeElements();
            shownRoot = nullptr;
        }
    }

    void UI::CommitChanges()
    {
        editor->CommitChanges();
    }

    void UI::WorldChanged(World* world)
    {
        if (world)
        {
            auto& assets = world->CurrentAssets();
            assetsRoot = std::make_unique<Data::AssetsRoot>(
                Data::AssetsRoot::Input
                {
                    assets.actionAssets,
                    assets.audioAssets,
                    assets.imageAssets,
                    assets.fontAssets,
                    assets.materialAssets,
                    assets.scriptAssets,
                    assets.shaderAssets,
                    *renderReliquary,
                    nexusHistory,
                    *this
                });
        }
        else
        {
            HideRoot();

            assetsRoot.reset();
            fieldRoots.reset();
        }
    }

    void UI::FieldChanging()
    {
        fieldRoots.reset();
        shownRoot = nullptr;
    }

    void UI::FieldChanged(Field& field)
    {
        auto entities = Data::EntitiesRoot::Input
        {
            &field.entities,
            renderReliquary,
            viewEntities,
            &nexusHistory,
            this
        };

        auto entityBoundaries = Data::EntityBoundaryRoot::Input
        {
            &field.entityBoundary,
            renderReliquary,
            viewEntityBoundary,
            &nexusHistory,
            this
        };

        auto terrain = Data::TerrainRoot::Input
        {
            &field.terrain,
            renderReliquary,
            viewTerrain,
            &nexusHistory,
            this
        };

        fieldRoots = std::make_unique<FieldRoots>(entities, entityBoundaries, terrain);
    }

    void UI::ViewTerrain(bool value)
    {
        ChangeVisibility<Data::TerrainRoot>(value, viewTerrain);
    }

    void UI::ViewEntityBoundary(bool value)
    {
        ChangeVisibility<Data::EntityBoundaryRoot>(value, viewEntityBoundary);
    }

    void UI::ViewEntities(bool value)
    {
        ChangeVisibility<Data::EntitiesRoot>(value, viewEntities);
    }

    void UI::Freeze()
    {
        tree->Freeze();
        editor->Freeze();
    }

    void UI::Thaw()
    {
        tree->Thaw();
        editor->Thaw();
    }

    void UI::RefreshTree()
    {
        tree->Refresh();
    }

    Data::AssetsRoot* UI::AssetsRoot()
    {
        return assetsRoot.get();
    }

    UI::FieldRoots::FieldRoots(
        Data::EntitiesRoot::Input& entities,
        Data::EntityBoundaryRoot::Input& entityBoundary,
        Data::TerrainRoot::Input& terrain)
        :
        entities(entities),
        entityBoundary(entityBoundary),
        terrain(terrain)
    {}
}