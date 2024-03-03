#pragma once

#include "Exception.h"

namespace Creation::Editing
{
    class ModifyHasNodeInSelectAndDeselect final : public Exception
    {
    public:
        ModifyHasNodeInSelectAndDeselect();
    };
}