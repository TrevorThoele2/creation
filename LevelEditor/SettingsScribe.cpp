
#include "SettingsScribe.h"

#include "Settings.h"

#include "String.h"

namespace Creation
{
    SettingsScribeOut::SettingsScribeOut(const ::Atmos::FilePath &path) : file(path.GetValue())
    {}

    void SettingsScribeOut::Save()
    {
        file << Settings::GetWorldPath() << "\n";
        file << Settings::GetBuildPath() << "\n";
        file << Settings::GetAudioAssetPath() << "\n";
        file << Settings::GetImageAssetPath() << "\n";
        file << Settings::GetScriptAssetPath() << "\n";
        file << Settings::GetShaderAssetPath();
    }

    void SettingsScribeOut::Flush()
    {
        file.Flush();
    }

    SettingsScribeIn::SettingsScribeIn(const ::Atmos::FilePath &path) : file(path.GetValue())
    {}

    void SettingsScribeIn::Load()
    {
        String str;
        file.GetLine(str);
        Settings::SetWorldPath(str);
        file.GetLine(str);
        Settings::SetBuildPath(str);
        file.GetLine(str);
        Settings::SetAudioAssetPath(str);
        file.GetLine(str);
        Settings::SetImageAssetPath(str);
        file.GetLine(str);
        Settings::SetScriptAssetPath(str);
        file.GetLine(str);
        Settings::SetShaderAssetPath(str);
    }
}