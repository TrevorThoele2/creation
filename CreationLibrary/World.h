#pragma once

#include "Field.h"
#include <Atmos/FieldID.h>
#include "Assets.h"

#include "FilePath.h"

#include "InputBuildFile.h"

#include <Atmos/AudioManager.h>
#include <Atmos/GraphicsManager.h>
#include <Atmos/TextManager.h>
#include <Atmos/AssetResourceManager.h>
#include <Atmos/ScriptManager.h>
#include <Atmos/OutputAssetsFile.h>

namespace Creation
{
    class World
    {
    public:
        explicit World(const File::Path& buildFilePath, const File::Path& worldFilePath, Atmos::Logging::Logger& logger);

        void InsertDefaults();
        void ChangeField(Atmos::World::FieldID fieldID);
        void CreateAndChangeField(Atmos::World::FieldID fieldID);
        void DestroyField(Atmos::World::FieldID fieldID);
        [[nodiscard]] bool HasField(Atmos::World::FieldID fieldID) const;
        [[nodiscard]] std::vector<Atmos::World::FieldID> AllFieldIDs() const;
        [[nodiscard]] Field& CurrentField();
        [[nodiscard]] const Field& CurrentField() const;
        [[nodiscard]] Assets& CurrentAssets();
        [[nodiscard]] const Assets& CurrentAssets() const;

        void Save();
        void Build(
            Atmos::Audio::Manager& audioManager,
            Atmos::Render::GraphicsManager& graphicsManager,
            Atmos::Render::TextManager& textManager,
            Atmos::Asset::Resource::Manager& assetResourceManager,
            Atmos::Scripting::Manager& scriptingManager,
            Atmos::Logging::Logger& logger);
        void LoadAssets();

        void BuildFilePath(const File::Path& path);
        [[nodiscard]] File::Path BuildFilePath() const;
        void WorldFilePath(const File::Path& path);
        [[nodiscard]] File::Path WorldFilePath() const;
    private:
        File::Path buildFilePath;
        File::Path worldFilePath;
        Field currentField;
        Assets assets;

        Atmos::Logging::Logger* logger;
    private:
        void DoSave();
        void DoSave(Atmos::World::FieldID withoutID);
    private:
        void BuildAssets(
            Atmos::Render::GraphicsManager& graphicsManager,
            Atmos::Scripting::Manager& scriptingManager,
            Assets& assets);
        void BuildShaderAssets(
            Atmos::Render::GraphicsManager& graphicsManager,
            Assets& assets);
        void BuildScriptAssets(
            Atmos::Scripting::Manager& scriptingManager,
            Assets& assets);

        void BuildField(
            Field field,
            Assets& assets,
            Build::Context& buildContext);
    private:
        using SaveAsset = Atmos::World::Serialization::OutputAssetsFile::SaveAsset;
        using SaveAssets = Atmos::World::Serialization::OutputAssetsFile::SaveAssets;
        using Saves = Atmos::World::Serialization::OutputAssetsFile::Saves;

        File::Path BuildAssetsFile(const File::Path& worldFilePath, Assets& assets);
        template<class T>
        void FillFromFiles(
            const T& inputAssets,
            SaveAssets& outputAssets,
            const std::function<File::Path(const File::Path&)>& transformPath);

        File::Path BuildWorldFile(const File::Path& worldFilePath, std::vector<Atmos::World::Field>& fields);
    private:
        void OutputBinary(const File::Path& filePath, Atmos::Buffer&& buffer);
        [[nodiscard]] Atmos::Buffer InputBinary(const File::Path& filePath);

    private:
        std::unique_ptr<Arca::Reliquary> CreateReliquary(
            Atmos::Audio::Manager& audioManager,
            Atmos::Render::GraphicsManager& graphicsManager,
            Atmos::Render::TextManager& textManager,
            Atmos::Asset::Resource::Manager& assetResourceManager,
            Atmos::Scripting::Manager& scriptingManager,
            Atmos::Logging::Logger& logger);
    private:
        void Validate(Saves& saves);
        void Validate(SaveAssets& saves, const String& assetType);
    private:
        static inline const String defaultVertexShader = "vertex";
        static inline const String defaultFragmentShader = "fragment";
        static inline const String defaultMaterialScript = "basic_material_script";
    };
    
    template<class T>
    void World::FillFromFiles(
        const T& inputAssets,
        SaveAssets& outputAssets,
        const std::function<File::Path(const File::Path&)>& transformPath)
    {
        outputAssets.reserve(inputAssets.size());
        for (auto& asset : inputAssets)
        {
            const auto filePath = transformPath(asset.filePath);
            outputAssets.push_back(SaveAsset{
                Atmos::Name(filePath.filename().string()),
                InputBinary(filePath) });
        }
    }
}
