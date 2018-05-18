#pragma once

#include "Settings.h"

#include "FilePath.h"
#include <Inscription/InputTextArchive.h>
#include <Inscription/InputJsonFormat.h>

namespace Creation
{
    class InputSettingsFile
    {
    public:
        explicit InputSettingsFile(const File::Path& path);

        Settings Load();
    private:
        Inscription::File::InputText file;
        Inscription::Archive::InputText archive;
    };
}