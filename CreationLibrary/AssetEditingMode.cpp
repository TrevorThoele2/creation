#include "AssetEditingMode.h"

#include "AssetsRoot.h"
#include "EditingUI.h"

namespace Creation::Editing
{
    AssetMode::AssetMode(NexusSelection& nexusSelection, NexusHistory nexusHistory) :
        Mode(nexusSelection, nexusHistory)
    {}

    void AssetMode::ChangeRootImpl(UI& ui)
    {
        ui.ShowRoot<Data::AssetsRoot>();
    }
}