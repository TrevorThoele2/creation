
#include "Settings.h"

namespace Creation
{
    Settings& Settings::Instance()
    {
        static Settings instance;
        return instance;
    }

    void Settings::SetWorldPath(const ::Atmos::FilePath &set)
    {
        Instance().worldPath = set;
    }

    const ::Atmos::FilePath& Settings::GetWorldPath()
    {
        return Instance().worldPath;
    }

    void Settings::SetBuildPath(const ::Atmos::FilePath &set)
    {
        Instance().buildPath = set;
    }

    const ::Atmos::FilePath& Settings::GetBuildPath()
    {
        return Instance().buildPath;
    }

    void Settings::SetAudioAssetPath(const ::Atmos::FilePath &set)
    {
        Instance().audioAssetPath = set;
    }

    const ::Atmos::FilePath& Settings::GetAudioAssetPath()
    {
        return Instance().audioAssetPath;
    }

    void Settings::SetImageAssetPath(const ::Atmos::FilePath &set)
    {
        Instance().imageAssetPath = set;
    }

    const ::Atmos::FilePath& Settings::GetImageAssetPath()
    {
        return Instance().imageAssetPath;
    }

    void Settings::SetScriptAssetPath(const ::Atmos::FilePath &set)
    {
        Instance().scriptAssetPath = set;
    }

    const ::Atmos::FilePath& Settings::GetScriptAssetPath()
    {
        return Instance().scriptAssetPath;
    }

    void Settings::SetShaderAssetPath(const ::Atmos::FilePath &set)
    {
        Instance().shaderAssetPath = set;
    }

    const ::Atmos::FilePath& Settings::GetShaderAssetPath()
    {
        return Instance().shaderAssetPath;
    }
}