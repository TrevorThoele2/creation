#pragma once

#include <Atmos/FilePath.h>
#include <Inscription/TextFile.h>

namespace Creation
{
    class SettingsScribeOut
    {
    private:
        ::inscription::TextOutFile file;
    public:
        SettingsScribeOut(const ::Atmos::FilePath &path);
        void Save();
        void Flush();
    };

    class SettingsScribeIn
    {
    private:
        ::inscription::TextInFile file;
    public:
        SettingsScribeIn(const ::Atmos::FilePath &path);
        void Load();
    };
}