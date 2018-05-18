#include "MovementManager.h"

#include <Atmos/SpatialAlgorithms.h>

namespace Creation::Editing
{
    MovementManager::MovementManager(
        GhostWorldElements&& ghostWorldElements,
        Atmos::Spatial::Point2D mousePosition)
        :
        ghostWorldElements(std::move(ghostWorldElements)),
        previousMousePosition(mousePosition)
    {}

    void MovementManager::Move(const Atmos::Spatial::Point2D& position)
    {
        const auto deltaPosition = position - previousMousePosition;
        for (auto& ghost : ghostWorldElements)
            ghost->MoveBy(deltaPosition);
        previousMousePosition = position;
    }

    std::vector<GhostWorldElementBase*> MovementManager::Ghosts() const
    {
        std::vector<GhostWorldElementBase*> returnValue;
        for (auto& ghost : ghostWorldElements)
            returnValue.push_back(ghost.get());
        return returnValue;
    }
}