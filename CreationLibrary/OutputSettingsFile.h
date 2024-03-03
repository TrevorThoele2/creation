#pragma once

#include "Settings.h"

#include "FilePath.h"
#include <Inscription/OutputTextArchive.h>
#include <Inscription/OutputJsonFormat.h>

namespace Creation
{
    class OutputSettingsFile
    {
    public:
        explicit OutputSettingsFile(const File::Path& path);

        void Save(const Settings& settings);
    private:
        Inscription::File::OutputText file;
        Inscription::Archive::OutputText archive;
    };
}