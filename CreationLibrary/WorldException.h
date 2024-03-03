#pragma once

#include <Atmos/Exception.h>
#include <Atmos/FieldID.h>
#include "FilePath.h"

namespace Creation
{
    class WorldLoadFailure final : public Atmos::Exception
    {
    public:
        WorldLoadFailure(const File::Path& filePath, Atmos::World::FieldID fieldID);
    };
}