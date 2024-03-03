#include "SelectTool.h"

#include "EditingMode.h"

#include <Atmos/FindAssetByName.h>

namespace Creation::Editing
{
    SelectTool::SelectTool(Arca::Reliquary& reliquary) : reliquary(&reliquary)
    {}

    void SelectTool::OnLeftMouseDown(const Atmos::Spatial::Point2D& position, Mode& mode)
    {
        editBox =
        {
            reliquary->Do(Atmos::Asset::FindByName<Atmos::Asset::Image>("pixel.png")),
            position,
            Atmos::Render::Color{80, 255, 255, 255},
            *reliquary
        };
    }

    void SelectTool::OnLeftMouseUp(const Atmos::Spatial::Point2D& position, Mode& mode)
    {
        if (!editBox)
            return;

        const auto box = editBox->CompleteBox(position);
        editBox.reset();

        mode.OnSelect(box);
    }

    void SelectTool::OnRightMouseUp(const Atmos::Spatial::Point2D& position, Mode& mode)
    {
        if (editBox)
            return;

        const auto minimumSizeValue = std::numeric_limits<Atmos::Spatial::Size2D::Value>::min();
        const auto box = Atmos::Spatial::AxisAlignedBox2D{ position, {minimumSizeValue, minimumSizeValue} };

        mode.OnSelect(box);
    }

    void SelectTool::OnMouseMoved(const Atmos::Spatial::Point2D& position, Mode& mode)
    {
        if (!editBox)
            return;

        editBox->DynamicPositionMoved(position);
    }
}