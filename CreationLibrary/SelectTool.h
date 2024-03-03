#pragma once

#include "EditingTool.h"

#include "EditBox.h"

namespace Creation::Editing
{
    class SelectTool final : public Tool
    {
    public:
        SelectTool(Arca::Reliquary& reliquary);

        void OnLeftMouseDown(const Atmos::Spatial::Point2D& position, Mode& mode) override;
        void OnLeftMouseUp(const Atmos::Spatial::Point2D& position, Mode& mode) override;
        void OnRightMouseUp(const Atmos::Spatial::Point2D& position, Mode& mode) override;
        void OnMouseMoved(const Atmos::Spatial::Point2D& position, Mode& mode) override;
    private:
        std::optional<EditBox> editBox;
    private:
        Arca::Reliquary* reliquary = nullptr;
    };
}