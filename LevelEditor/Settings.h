#pragma once

#include <Atmos/FilePath.h>

namespace Creation
{
    class Settings
    {
    private:
        ::Atmos::FilePath worldPath;
        ::Atmos::FilePath buildPath;
        ::Atmos::FilePath audioAssetPath;
        ::Atmos::FilePath imageAssetPath;
        ::Atmos::FilePath scriptAssetPath;
        ::Atmos::FilePath shaderAssetPath;

        Settings() = default;
        Settings(const Settings &arg) = delete;
        Settings& operator=(const Settings &arg) = delete;
    public:
        static Settings& Instance();

        static void SetWorldPath(const ::Atmos::FilePath &set);
        static const ::Atmos::FilePath& GetWorldPath();
        static void SetBuildPath(const ::Atmos::FilePath &set);
        static const ::Atmos::FilePath& GetBuildPath();
        static void SetAudioAssetPath(const ::Atmos::FilePath &set);
        static const ::Atmos::FilePath& GetAudioAssetPath();
        static void SetImageAssetPath(const ::Atmos::FilePath &set);
        static const ::Atmos::FilePath& GetImageAssetPath();
        static void SetScriptAssetPath(const ::Atmos::FilePath &set);
        static const ::Atmos::FilePath& GetScriptAssetPath();
        static void SetShaderAssetPath(const ::Atmos::FilePath &set);
        static const ::Atmos::FilePath& GetShaderAssetPath();
    };
}