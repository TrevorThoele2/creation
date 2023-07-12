#include "World.h"

#include "WorldException.h"
#include "OutputBuildFile.h"
#include "FilePaths.h"

#include "AtmosAsset.h"

#include <Atmos/InvalidSignature.h>
#include <Atmos/OutputWorldFile.h>
#include <Atmos/InputSimpleFile.h>
#include <Atmos/AssetsFileExtension.h>
#include <Atmos/TypeRegistration.h>
#include <Arca/ReliquaryOrigin.h>
#include <Atmos/Camera.h>
#include <Atmos/GraphicsCurator.h>
#include <Atmos/TextCurator.h>
#include <Atmos/ScriptCurator.h>
#include <Atmos/AudioCurator.h>

namespace Creation
{
    World::World(const File::Path& buildFilePath, const File::Path& worldFilePath, Atmos::Logging::Logger& logger) :
        buildFilePath(buildFilePath),
        worldFilePath(worldFilePath),
        logger(&logger)
    {}

    void World::InsertDefaults()
    {
        assets.scriptAssets.emplace_back(
            Inscription::File::Path{ std::filesystem::current_path() / "scripts" / (defaultMaterialScript + ".ts") });
        assets.shaderAssets.emplace_back(
            Inscription::File::Path{ std::filesystem::current_path() / "shaders" / (defaultVertexShader + ".vert") });
        assets.shaderAssets.emplace_back(
            Inscription::File::Path{ std::filesystem::current_path() / "shaders" / (defaultFragmentShader + ".frag") });
        assets.materialAssets.emplace_back(
            atmosDefaultMaterialName,
            defaultMaterialScript,
            String("main"),
            std::list
            {
                Editing::Data::Variant
                {
                    Editing::Data::VariantType::String,
                    defaultVertexShader,
                },
                Editing::Data::Variant
                {
                    Editing::Data::VariantType::String,
                    defaultFragmentShader
                }
            });
    }

    void World::ChangeField(Atmos::World::FieldID fieldID)
    {
        auto file = Build::InputFile(buildFilePath);
        auto field = file.Field(fieldID);
        if (!field)
            throw WorldLoadFailure(buildFilePath, fieldID);

        currentField = *field;
    }

    void World::CreateAndChangeField(Atmos::World::FieldID fieldID)
    {
        currentField = Field();
        currentField.id = fieldID;
        DoSave();
    }

    void World::DestroyField(Atmos::World::FieldID fieldID)
    {
        if (currentField.id == fieldID)
        {
            const auto allFieldIDs = AllFieldIDs();
            std::optional<Atmos::World::FieldID> lowerFieldID;
            std::optional<Atmos::World::FieldID> upperFieldID;
            for(auto& checkFieldID : allFieldIDs)
            {
                if (checkFieldID < fieldID && lowerFieldID && lowerFieldID < checkFieldID)
                    lowerFieldID = checkFieldID;

                if (checkFieldID > fieldID && upperFieldID && upperFieldID > checkFieldID)
                    upperFieldID = checkFieldID;
            }

            if (lowerFieldID)
                ChangeField(*lowerFieldID);
            else if (upperFieldID)
                ChangeField(*upperFieldID);
        }

        DoSave(fieldID);
    }

    bool World::HasField(Atmos::World::FieldID fieldID) const
    {
        auto allIDs = AllFieldIDs();
        return std::any_of(
            allIDs.begin(),
            allIDs.end(),
            [fieldID](Atmos::World::FieldID currentID)
            {
                return fieldID == currentID;
            });
    }

    std::vector<Atmos::World::FieldID> World::AllFieldIDs() const
    {
        const auto file = Build::InputFile(buildFilePath);
        return file.AllIDs();
    }

    Field& World::CurrentField()
    {
        return currentField;
    }

    const Field& World::CurrentField() const
    {
        return currentField;
    }

    Assets& World::CurrentAssets()
    {
        return assets;
    }

    const Assets& World::CurrentAssets() const
    {
        return assets;
    }

    void World::Save()
    {
        DoSave();
    }

    void World::Build(
        Atmos::Audio::Manager& audioManager,
        Atmos::Render::GraphicsManager& graphicsManager,
        Atmos::Render::TextManager& textManager,
        Atmos::Asset::Resource::Manager& assetResourceManager,
        Atmos::Scripting::Manager& scriptingManager,
        Atmos::Logging::Logger& logger)
    {
        std::vector<Atmos::World::Field> fields;
        File::Path temporaryAssetsFile;
        File::Path temporaryWorldFile;

        {
            auto inputFile = Build::InputFile(buildFilePath);

            auto fieldIDs = inputFile.AllIDs();

            auto assets = this->assets;

            {
                auto reliquary = CreateReliquary(
                    audioManager,
                    graphicsManager,
                    textManager,
                    assetResourceManager,
                    scriptingManager,
                    logger);
                scriptingManager.SetReliquary(reliquary.get());
                BuildAssets(graphicsManager, scriptingManager, assets);
            }

            fields.reserve(fieldIDs.size());
            for (auto fieldID : fieldIDs)
            {
                auto reliquary = CreateReliquary(
                    audioManager,
                    graphicsManager,
                    textManager,
                    assetResourceManager,
                    scriptingManager,
                    logger);
                scriptingManager.SetReliquary(reliquary.get());
                auto buildContext = Build::Context(*reliquary);
                auto field = *inputFile.Field(fieldID);
                BuildField(field, assets, buildContext);

                fields.emplace_back(fieldID, std::move(reliquary));
            }

            temporaryAssetsFile = BuildAssetsFile(worldFilePath, assets);
            temporaryWorldFile = BuildWorldFile(worldFilePath, fields);
        }
        
        auto assetsFilePath = worldFilePath;
        assetsFilePath.replace_extension(Atmos::World::Serialization::assetsFileExtension);
        std::filesystem::rename(temporaryAssetsFile, assetsFilePath);

        std::filesystem::rename(temporaryWorldFile, worldFilePath);
    }

    void World::LoadAssets()
    {
        auto file = Build::InputFile(buildFilePath);
        assets = file.Assets();
    }

    void World::BuildFilePath(const File::Path& path)
    {
        buildFilePath = path;
    }

    File::Path World::BuildFilePath() const
    {
        return buildFilePath;
    }

    void World::WorldFilePath(const File::Path& path)
    {
        worldFilePath = path;
    }

    File::Path World::WorldFilePath() const
    {
        return worldFilePath;
    }

    void World::DoSave()
    {
        const auto temporarySaveFilePath = std::filesystem::temp_directory_path() / buildFilePath.filename();

        {
            auto outputFile = Build::OutputFile(temporarySaveFilePath);

            outputFile.Set(assets);
            outputFile.Add(currentField);

            std::vector<Field> fields;
            try
            {
                if (exists(buildFilePath))
                {
                    auto inputFile = Build::InputFile(buildFilePath);

                    for (const auto& id : inputFile.AllIDs())
                    {
                        if (currentField.id != id)
                        {
                            fields.push_back(*inputFile.Field(id));
                            outputFile.Add(fields.back());
                        }
                    }
                }
            }
            catch (const Atmos::InvalidSignature&)
            { }
            catch (const Inscription::JsonParseError&)
            { }

            outputFile.Save();
        }

        std::filesystem::rename(temporarySaveFilePath, buildFilePath);
    }

    void World::DoSave(Atmos::World::FieldID withoutID)
    {
        const auto temporarySaveFilePath = std::filesystem::temp_directory_path() / buildFilePath.filename();

        {
            auto outputFile = Build::OutputFile(temporarySaveFilePath);

            outputFile.Set(assets);

            std::vector<Field> fields;
            try
            {
                auto inputFile = Build::InputFile(buildFilePath);

                for (auto& id : inputFile.AllIDs())
                {
                    if (currentField.id == id)
                        outputFile.Add(currentField);
                    else if (withoutID != id)
                    {
                        fields.push_back(*inputFile.Field(id));
                        outputFile.Add(fields.back());
                    }
                }
            }
            catch (const Atmos::InvalidSignature&)
            {
                outputFile.Add(currentField);
            }
            catch (const Inscription::JsonParseError&)
            {
                outputFile.Add(currentField);
            }

            outputFile.Save();
        }

        std::filesystem::rename(temporarySaveFilePath, buildFilePath);
    }

    void World::BuildAssets(
        Atmos::Render::GraphicsManager& graphicsManager,
        Atmos::Scripting::Manager& scriptingManager,
        Assets& assets)
    {
        BuildShaderAssets(graphicsManager, assets);
        BuildScriptAssets(scriptingManager, assets);
    }

    void World::BuildShaderAssets(
        Atmos::Render::GraphicsManager& graphicsManager,
        Assets& assets)
    {
        for (auto& [filePath] : assets.shaderAssets)
            OutputBinary(
                CompiledShaderPath(filePath),
                graphicsManager.CompileShader(filePath));
    }

    void World::BuildScriptAssets(
        Atmos::Scripting::Manager& scriptingManager,
        Assets& assets)
    {
        const auto createModule = [](File::Path filePath)
        {
        };

        std::vector<Atmos::Scripting::Module> modules;
        modules.reserve(assets.scriptAssets.size());
        for (auto& [filePath] : assets.scriptAssets)
        {
            String fileData;
            {
                auto inputFile = Inscription::File::InputText(filePath);
                while (!inputFile.IsAtEnd())
                    fileData += inputFile.ReadUntil('\n') + "\n";
            }
            modules.push_back(Atmos::Scripting::Module{ filePath.string(), fileData });
        }

        auto compiledModules = scriptingManager.Compile(modules);

        for (auto& module : compiledModules)
            OutputBinary(CompiledScriptPath(module.name), std::move(module.source));
    }

    void World::BuildField(
        Field field,
        Assets& assets,
        Build::Context& buildContext)
    {
        const auto pushData = [&buildContext](auto& data)
        {
            for (auto& element : data)
                element.Build(buildContext);
        };

        pushData(assets.actionAssets);
        pushData(assets.audioAssets);
        pushData(assets.imageAssets);
        pushData(assets.fontAssets);
        pushData(assets.shaderAssets);
        pushData(assets.materialAssets);
        pushData(assets.scriptAssets);
        pushData(field.terrain);
        pushData(field.entities);
        pushData(field.entityBoundary);
    }
    
    File::Path World::BuildAssetsFile(const File::Path& worldFilePath, Assets& assets)
    {
        const auto sameFilePath = [](const File::Path& filePath)
        {
            return filePath;
        };

        Saves saves;
        FillFromFiles(assets.imageAssets, saves.images, sameFilePath);
        FillFromFiles(assets.fontAssets, saves.fonts, sameFilePath);
        FillFromFiles(assets.audioAssets, saves.audio, sameFilePath);
        FillFromFiles(assets.shaderAssets, saves.shaders, &CompiledShaderPath);
        FillFromFiles(assets.scriptAssets, saves.scripts, &CompiledScriptPath);

        Validate(saves);

        auto temporarySaveFilePath = std::filesystem::temp_directory_path() / worldFilePath.filename();
        temporarySaveFilePath.replace_extension(Atmos::World::Serialization::assetsFileExtension);

        auto outputFile = Atmos::World::Serialization::OutputAssetsFile(temporarySaveFilePath);
        outputFile.Save(saves);

        return temporarySaveFilePath;
    }
    
    File::Path World::BuildWorldFile(const File::Path& worldFilePath, std::vector<Atmos::World::Field>& fields)
    {
        const auto temporarySaveFilePath = std::filesystem::temp_directory_path() / worldFilePath.filename();

        auto outputFile = Atmos::World::Serialization::OutputWorldFile(temporarySaveFilePath);
        outputFile.Save(fields, {});

        return temporarySaveFilePath;
    }

    void World::OutputBinary(const File::Path& filePath, Atmos::Buffer&& buffer)
    {
        Inscription::File::OutputBinary outputFile(filePath);
        Inscription::Archive::OutputBinary outputArchive(outputFile);
        Inscription::Format::OutputBinary outputFormat(outputArchive);
        for (auto& byte : buffer)
            outputFormat.Write(byte);
    }

    Atmos::Buffer World::InputBinary(const File::Path& filePath)
    {
        auto assetInputArchive = Atmos::InputSimpleFile(filePath);
        return assetInputArchive.ReadBuffer();
    }

    std::unique_ptr<Arca::Reliquary> World::CreateReliquary(
        Atmos::Audio::Manager& audioManager,
        Atmos::Render::GraphicsManager& graphicsManager,
        Atmos::Render::TextManager& textManager,
        Atmos::Asset::Resource::Manager& assetResourceManager,
        Atmos::Scripting::Manager& scriptingManager,
        Atmos::Logging::Logger& logger)
    {
        auto origin = Arca::ReliquaryOrigin();
        Atmos::Audio::RegisterTypes(origin);
        Atmos::Input::RegisterTypes(origin);
        Atmos::Render::RegisterTypes(origin);
        Atmos::Scripting::RegisterTypes(origin);
        Atmos::RegisterCommonTypes(origin, assetResourceManager, logger);
        origin
            .Register<Atmos::Audio::Curator>(std::ref(audioManager))
            .Register<Atmos::Render::GraphicsCurator>(std::ref(graphicsManager))
            .Register<Atmos::Render::TextCurator>(std::ref(textManager))
            .Register<Atmos::Render::Camera>(Atmos::Spatial::Size2D{ 1024, 768 })
            .Register<Atmos::Scripting::Curator>(std::ref(scriptingManager))
            .Register<MutationCurator>();
        return origin.Actualize();
    }

    void World::Validate(Saves& saves)
    {
        Validate(saves.audio, "Audio");
        Validate(saves.images, "Image");
        Validate(saves.fonts, "Font");
        Validate(saves.scripts, "Script");
        Validate(saves.shaders, "Shader");
    }

    void World::Validate(SaveAssets& saves, const String& assetType)
    {
        for (auto& save : saves)
            if (save.memory.empty())
                logger->Log(
                    "Saving empty file.",
                    Atmos::Logging::Severity::Warning,
                    { { {"FileName", save.name}, {"AssetType", assetType} } });
    }
}
