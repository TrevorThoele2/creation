
#include "ViewManager.h"

#include "Selection.h"
#include "TileViewManager.h"
#include "EntityViewManager.h"
#include "InternalShaders.h"

namespace Creation
{
    void DeconstructAllViewManagers()
    {
        SelectionHandler::TemporaryDeconstruct();
        TileViewManager::Clear();
        EntityViewManager::Clear();
    }

    void ConstructAllViewManagers(Build::Package<Atmos::Field> *field)
    {
        TileViewManager::BuildFromField(field);
        EntityViewManager::BuildFromField(field);
        SelectionHandler::Reconstruct();
    }
}