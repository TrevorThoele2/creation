#pragma once

#include "EditingMode.h"

namespace Creation::Editing
{
    class AssetMode final : public Mode
    {
    public:
        AssetMode(NexusSelection& nexusSelection, NexusHistory nexusHistory);
    protected:
        void ChangeRootImpl(UI& ui) override;
    };
}