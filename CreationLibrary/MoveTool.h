#pragma once

#include "EditingTool.h"

#include "MovementManager.h"

#include <Arca/Reliquary.h>

namespace Creation::Editing
{
    class MoveTool final : public Tool
    {
    public:
        MoveTool(Arca::Reliquary& reliquary);

        void OnLeftMouseDown(const Atmos::Spatial::Point2D& position, Mode& mode) override;
        void OnLeftMouseUp(const Atmos::Spatial::Point2D& position, Mode& mode) override;
        void OnMouseMoved(const Atmos::Spatial::Point2D& position, Mode& mode) override;
    private:
        std::optional<MovementManager> movementManager;
    private:
        Arca::Reliquary* reliquary = nullptr;
    };
}