#include "MoveTool.h"

#include "EditingMode.h"

namespace Creation::Editing
{
    MoveTool::MoveTool(Arca::Reliquary& reliquary) : reliquary(&reliquary)
    {}

    void MoveTool::OnLeftMouseDown(const Atmos::Spatial::Point2D& position, Mode& mode)
    {
        if (movementManager || !mode.IsPointInSelection(position, *reliquary))
            return;

        movementManager = MovementManager(mode.CreateGhosts(), position);
    }

    void MoveTool::OnLeftMouseUp(const Atmos::Spatial::Point2D& position, Mode& mode)
    {
        if (!movementManager)
            return;

        movementManager->Move(position);
        mode.OnMoved(movementManager->Ghosts());
        movementManager.reset();
    }

    void MoveTool::OnMouseMoved(const Atmos::Spatial::Point2D& position, Mode& mode)
    {
        if (!movementManager)
            return;

        movementManager->Move(position);
    }
}