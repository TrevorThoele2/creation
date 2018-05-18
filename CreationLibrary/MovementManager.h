#pragma once

#include "GhostWorldElementBase.h"

namespace Creation::Editing
{
    class MovementManager
    {
    public:
        using GhostWorldElementPtr = std::unique_ptr<GhostWorldElementBase>;
        using GhostWorldElements = std::vector<GhostWorldElementPtr>;
    public:
        MovementManager(GhostWorldElements&& ghostWorldElements, Atmos::Spatial::Point2D mousePosition);

        void Move(const Atmos::Spatial::Point2D& position);

        [[nodiscard]] std::vector<GhostWorldElementBase*> Ghosts() const;
    private:
        std::vector<GhostWorldElementPtr> ghostWorldElements;
        Atmos::Spatial::Point2D previousMousePosition;
    };
}