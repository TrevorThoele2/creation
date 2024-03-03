#include "WorldException.h"

#include <Atmos/StringUtility.h>

namespace Creation
{
    std::string FilePathMessage(const File::Path& filePath)
    {
        return "File Path: " + filePath.string();
    }

    std::string FieldIDMessage(Atmos::World::FieldID fieldID)
    {
        return "Field ID: " + Atmos::ToString(fieldID);
    }

    WorldLoadFailure::WorldLoadFailure(const File::Path& filePath, Atmos::World::FieldID fieldID) :
        Exception(
            "Loading part of the world has failed. \n    "
            + FilePathMessage(filePath)
            + "\n    "
            + FieldIDMessage(fieldID))
    {}
}