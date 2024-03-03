#include "PaintTool.h"

#include "EditingMode.h"

#include <Atmos/FindAssetByName.h>

namespace Creation::Editing
{
    PaintTool::PaintTool(Arca::Reliquary& reliquary) : reliquary(&reliquary)
    {}

    void PaintTool::OnLeftMouseDown(const Atmos::Spatial::Point2D& position, Mode& mode)
    {
        editBox =
        {
            reliquary->Do(Atmos::Asset::FindByName<Atmos::Asset::Image>("pixel.png")),
            position,
            Atmos::Render::Color{80, 0, 255, 0},
            *reliquary
        };
    }

    void PaintTool::OnLeftMouseUp(const Atmos::Spatial::Point2D& position, Mode& mode)
    {
        if (!editBox)
            return;

        const auto box = editBox->CompleteBox(position);
        editBox.reset();

        mode.OnPaint(box);
    }

    void PaintTool::OnRightMouseUp(const Atmos::Spatial::Point2D& position, Mode& mode)
    {
        if (editBox)
            return;

        const auto minimumSizeValue = std::numeric_limits<Atmos::Spatial::Size2D::Value>::min();
        const auto box = Atmos::Spatial::AxisAlignedBox2D{ position, {minimumSizeValue, minimumSizeValue} };

        mode.OnPaint(box);
    }

    void PaintTool::OnMouseMoved(const Atmos::Spatial::Point2D& position, Mode& mode)
    {
        if (!editBox)
            return;

        editBox->DynamicPositionMoved(position);
    }
}