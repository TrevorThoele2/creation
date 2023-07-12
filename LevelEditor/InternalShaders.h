#pragma once

#include <vector>

#include <Atmos/FilePath.h>
#include <Atmos/ShaderAsset.h>

namespace Creation
{
    // Defines a registry of shader file names that are internal to the editor
    class InternalShaders
    {
    public:
        typedef Atmos::ShaderAsset AssetT;

        typedef Atmos::FilePath FilePath;
    private:
        typedef AssetT::ID ID;
        static const ID startID = 50000;

        static std::vector<FilePath> filePaths;

        InternalShaders() = default;
        InternalShaders(const InternalShaders &arg) = delete;
        InternalShaders& operator=(const InternalShaders &arg) = delete;
    public:
        static InternalShaders& Instance();

        static void Add(FilePath &&path);

        static void ConstructAll();
        static void DeconstructAll();
    };
}