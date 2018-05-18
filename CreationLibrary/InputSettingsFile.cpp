#include "InputSettingsFile.h"

#include "Settings.h"

#include <Inscription/FilePathScribe.h>
#include <Inscription/NumericScribe.h>

namespace Creation
{
    InputSettingsFile::InputSettingsFile(const File::Path& path) : file(path), archive(file)
    {}

    Settings InputSettingsFile::Load()
    {
        Settings settings;

        Inscription::Format::InputJson format(settings, archive);

        return settings;
    }
}