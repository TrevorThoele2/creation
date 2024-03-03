#include "Editor.h"

#include "AssetEditingMode.h"
#include "TerrainEditingMode.h"
#include "EntityBoundaryEditingMode.h"
#include "EntityEditingMode.h"

#include "PaintTool.h"
#include "SelectTool.h"
#include "MoveTool.h"

#include <Atmos/CreateImageAssetResource.h>
#include <Atmos/LoadImageAssetResourceData.h>
#include <Arca/Create.h>

namespace Creation::Editing
{
    Editor::Editor(
        ViewportStack& viewportStack,
        PropertiesEditor& editor,
        PropertiesTree& tree,
        Arca::Reliquary& renderReliquary,
        History& history,
        NexusSelection& nexusSelection)
        :
        viewportStack(&viewportStack),
        ui(editor, tree, renderReliquary, NexusHistory(history, nexusSelection)),
        renderReliquary(&renderReliquary),
        nexusSelection(&nexusSelection),
        nexusHistory(history, nexusSelection)
    {
        viewportStack.commands.mouseLeftDown.OnArguments(std::bind(&Editor::OnViewportMouseLeftDown, this, std::placeholders::_1));
        viewportStack.commands.mouseLeftUp.OnArguments(std::bind(&Editor::OnViewportMouseLeftUp, this, std::placeholders::_1));
        viewportStack.commands.mouseRightDown.OnArguments(std::bind(&Editor::OnViewportMouseRightDown, this, std::placeholders::_1));
        viewportStack.commands.mouseRightUp.OnArguments(std::bind(&Editor::OnViewportMouseRightUp, this, std::placeholders::_1));
        viewportStack.commands.mouseMoved.OnArguments(std::bind(&Editor::OnViewportMouseMoved, this, std::placeholders::_1));

        const auto pixelName = "pixel.png";
        const auto pixelFilePath = std::filesystem::current_path() / "images" / pixelName;

        const auto loadedPixel = renderReliquary.Do(
            Atmos::Asset::Resource::LoadData<Atmos::Asset::Resource::Image>{ pixelFilePath });

        auto pixelData = renderReliquary.Do(Atmos::Asset::Resource::Create<Atmos::Asset::Resource::Image>{
            loadedPixel.buffer,
                pixelName,
                loadedPixel.size });

        renderReliquary.Do(Arca::Create<Atmos::Asset::Image>(
            pixelName, std::move(pixelData), Atmos::Asset::ImageGridSize{ 1, 1 }));
    }

    void Editor::HideRoot()
    {
        ui.HideRoot();
    }

    void Editor::CommitChanges()
    {
        ui.CommitChanges();
    }

    void Editor::ChangeMode(std::optional<std::type_index> modeType)
    {
        if (!modeType.has_value())
            ResetMode();
        else if (modeType == typeid(AssetMode))
            ChangeMode<AssetMode>();
        else if (modeType == typeid(TerrainMode))
            ChangeMode<TerrainMode>();
        else if (modeType == typeid(EntityBoundaryMode))
            ChangeMode<EntityBoundaryMode>();
        else if (modeType == typeid(EntityMode))
            ChangeMode<EntityMode>();
        else
            throw std::runtime_error("Attempted to change to non-enumerated editing mode.");
    }

    void Editor::ResetMode()
    {
        UIFreezer freezer(ui);
        nexusSelection->Set({});
        ui.HideRoot();
        mode.reset();
    }

    Mode* Editor::CurrentMode()
    {
        return mode.get();
    }

    const Mode* Editor::CurrentMode() const
    {
        return mode.get();
    }

    std::optional<std::type_index> Editor::ModeType() const
    {
        return !mode ? std::optional<std::type_index>{} : std::type_index(typeid(*mode));
    }

    void Editor::ChangeTool(std::optional<std::type_index> toolType)
    {
        if (!toolType.has_value())
            ResetTool();
        else if (toolType == typeid(PaintTool))
            ChangeTool<PaintTool>();
        else if (toolType == typeid(SelectTool))
            ChangeTool<SelectTool>();
        else if (toolType == typeid(MoveTool))
            ChangeTool<MoveTool>();
        else
            throw std::runtime_error("Attempted to change to non-enumerated editing tool.");
    }

    void Editor::ResetTool()
    {
        UIFreezer freezer(ui);
        tool.reset();
    }

    Tool* Editor::CurrentTool()
    {
        return tool.get();
    }

    const Tool* Editor::CurrentTool() const
    {
        return tool.get();
    }

    std::optional<std::type_index> Editor::ToolType() const
    {
        return !tool ? std::optional<std::type_index>{} : std::type_index(typeid(*tool));
    }

    void Editor::WorldChanged(World* world)
    {
        ui.WorldChanged(world);
    }

    void Editor::FieldChanging()
    {
        ui.FieldChanging();
    }

    void Editor::FieldChanged(Field& field)
    {
        ui.FieldChanged(field);
    }

    void Editor::ViewTerrain(bool value)
    {
        ui.ViewTerrain(value);
    }

    void Editor::ViewEntityBoundary(bool value)
    {
        ui.ViewEntityBoundary(value);
    }

    void Editor::ViewEntities(bool value)
    {
        ui.ViewEntities(value);
    }

    void Editor::Activate()
    {
        viewportStack->commands.activate();
    }

    void Editor::Deactivate()
    {
        viewportStack->commands.deactivate();
    }

    void Editor::OnViewportMouseLeftDown(Atmos::Spatial::Point2D position)
    {
        if (mode && tool)
        {
            UIFreezer freezer(ui);
            tool->OnLeftMouseDown(position, *mode);
        }
    }

    void Editor::OnViewportMouseLeftUp(Atmos::Spatial::Point2D position)
    {
        if (mode && tool)
        {
            UIFreezer freezer(ui);
            tool->OnLeftMouseUp(position, *mode);
            ui.RefreshTree();
        }
    }

    void Editor::OnViewportMouseRightDown(Atmos::Spatial::Point2D position)
    {
        if (mode && tool)
        {
            UIFreezer freezer(ui);
            tool->OnRightMouseDown(position, *mode);
        }
    }

    void Editor::OnViewportMouseRightUp(Atmos::Spatial::Point2D position)
    {
        if (mode && tool)
        {
            UIFreezer freezer(ui);
            tool->OnRightMouseUp(position, *mode);
            ui.RefreshTree();
        }
    }

    void Editor::OnViewportMouseMoved(Atmos::Spatial::Point2D position)
    {
        if (mode && tool)
            tool->OnMouseMoved(position, *mode);
    }

    Editor::UIFreezer::UIFreezer(UI& ui) : ui(&ui)
    {
        this->ui->Freeze();
    }

    Editor::UIFreezer::~UIFreezer()
    {
        ui->Thaw();
    }
}