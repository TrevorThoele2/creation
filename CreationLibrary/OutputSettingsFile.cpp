#include "OutputSettingsFile.h"

#include "Settings.h"

#include <Inscription/FilePathScribe.h>
#include <Inscription/NumericScribe.h>

namespace Creation
{
    OutputSettingsFile::OutputSettingsFile(const File::Path& path) : file(path), archive(file)
    {}

    void OutputSettingsFile::Save(const Settings& settings)
    {
        Settings useSettings = settings;
        Inscription::Format::OutputJson format(useSettings, archive);
    }
}