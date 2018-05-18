#pragma once

#include "EditingUI.h"
#include "EditingMode.h"
#include "EditingTool.h"
#include "ViewportStack.h"

namespace Creation::Editing
{
    class Editor
    {
    public:
        Editor(
            ViewportStack& viewportStack,
            PropertiesEditor& editor,
            PropertiesTree& tree,
            Arca::Reliquary& renderReliquary,
            History& history,
            NexusSelection& nexusSelection);

        void HideRoot();
        void CommitChanges();

        template<class ModeT, std::enable_if_t<std::is_base_of_v<Mode, ModeT>, int> = 0>
        void ChangeMode();
        void ChangeMode(std::optional<std::type_index> modeType);
        void ResetMode();
        [[nodiscard]] Mode* CurrentMode();
        [[nodiscard]] const Mode* CurrentMode() const;
        [[nodiscard]] std::optional<std::type_index> ModeType() const;

        template<class ToolT, std::enable_if_t<std::is_base_of_v<Tool, ToolT>, int> = 0>
        void ChangeTool();
        void ChangeTool(std::optional<std::type_index> toolType);
        void ResetTool();
        [[nodiscard]] Tool* CurrentTool();
        [[nodiscard]] const Tool* CurrentTool() const;
        [[nodiscard]] std::optional<std::type_index> ToolType() const;
    public:
        void WorldChanged(World* world);
        void FieldChanging();
        void FieldChanged(Field& field);
    public:
        void ViewTerrain(bool value);
        void ViewEntityBoundary(bool value);
        void ViewEntities(bool value);
    public:
        void Activate();
        void Deactivate();
    private:
        ViewportStack* viewportStack;
    private:
        UI ui;
        std::unique_ptr<Mode> mode;
        std::unique_ptr<Tool> tool;
        Arca::Reliquary* renderReliquary;
    private:
        NexusSelection* nexusSelection;
        NexusHistory nexusHistory;
    private:
        void OnViewportMouseLeftDown(Atmos::Spatial::Point2D position);
        void OnViewportMouseLeftUp(Atmos::Spatial::Point2D position);
        void OnViewportMouseRightDown(Atmos::Spatial::Point2D position);
        void OnViewportMouseRightUp(Atmos::Spatial::Point2D position);
        void OnViewportMouseMoved(Atmos::Spatial::Point2D position);
    private:
        class UIFreezer
        {
        public:
            UIFreezer(UI& ui);
            ~UIFreezer();
        private:
            UI* ui;
        };
    };

    template<class ModeT, std::enable_if_t<std::is_base_of_v<Mode, ModeT>, int>>
    void Editor::ChangeMode()
    {
        UIFreezer freezer(ui);
        nexusSelection->Set({});
        mode = std::make_unique<ModeT>(*nexusSelection, nexusHistory);
        mode->ChangeRoot(ui);
    }

    template<class ToolT, std::enable_if_t<std::is_base_of_v<Tool, ToolT>, int>>
    void Editor::ChangeTool()
    {
        UIFreezer freezer(ui);
        tool = std::make_unique<ToolT>(*renderReliquary);
    }
}