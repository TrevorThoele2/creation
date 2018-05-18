#include "EditingTool.h"

namespace Creation::Editing
{
    Tool::~Tool() = default;

    void Tool::OnLeftMouseDown(const Atmos::Spatial::Point2D& position, Mode& mode)
    {}

    void Tool::OnLeftMouseUp(const Atmos::Spatial::Point2D& position, Mode& mode)
    {}

    void Tool::OnRightMouseDown(const Atmos::Spatial::Point2D& position, Mode& mode)
    {}

    void Tool::OnRightMouseUp(const Atmos::Spatial::Point2D& position, Mode& mode)
    {}

    void Tool::OnMouseMoved(const Atmos::Spatial::Point2D& position, Mode& mode)
    {}
}