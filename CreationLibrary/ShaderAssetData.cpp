#include "ShaderAssetData.h"

#include "FilePaths.h"
#include <Atmos/CompileShader.h>
#include <Atmos/InputSimpleFile.h>
#include <Atmos/CreateShaderAssetResource.h>
#include <Arca/Create.h>
#include <Arca/Destroy.h>

namespace Creation::Editing
{
    namespace Data
    {
        ShaderAsset::ShaderAsset(const File::Path& filePath) : filePath(filePath)
        {}

        void ShaderAsset::Build(Build::Context& context) const
        {
            const auto useFilePath = CompiledShaderPath(filePath);
            context.reliquary.Do(Arca::Create<Atmos::Asset::Shader>(
                FileAssetName(useFilePath),
                std::unique_ptr<Atmos::Asset::Resource::Shader>()));
        }
    }

    NexusBatch<Data::ShaderAsset>::NexusBatch(
        wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui)
        :
        NexusBatchCommon(grid),
        filePath("FilePath", "File Path", nullptr, grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    NexusBatch<Data::ShaderAsset>::NexusBatch(NexusBatch&& arg) noexcept :
        NexusBatchCommon(std::move(arg)),
        filePath(std::move(arg.filePath))
    {
        SetupProperties();
    }

    void NexusBatch<Data::ShaderAsset>::SetupProperties()
    {
        filePath.SetRelative(settings.shaderAssetPath);
        filePath.SetInitialPath(settings.shaderAssetPath);
        Auto(filePath, &Nexus::filePath);
    }

    WorldElement<Data::ShaderAsset>::WorldElement(Nexus& nexus, Arca::Reliquary& reliquary) :
        WorldElementCommon(nexus, reliquary)
    {
        object = CreateObject(nexus.CurrentData());
    }

    WorldElement<Data::ShaderAsset>::~WorldElement()
    {
        DestroyObject(object);
    }

    void WorldElement<Data::ShaderAsset>::OnDataChanged(DataT data)
    {
        DestroyObject(object);
        object = CreateObject(data);
    }

    auto WorldElement<Data::ShaderAsset>::CreateObject(DataT data) -> Index
    {
        return CreateAtmos(data, Reliquary());
    }

    void WorldElement<Data::ShaderAsset>::DestroyObject(Index index)
    {
        Reliquary().Do(Arca::Destroy<Object> { index.ID() });
    }

    Arca::Index<Atmos::Asset::Shader> WorldElement<Data::ShaderAsset>::CreateAtmos(
        Data::ShaderAsset data, Arca::Reliquary& reliquary)
    {
        try
        {
            const auto inputFilePath = std::filesystem::current_path() / "Shaders" / data.filePath;
            const auto buffer = reliquary.Do(Atmos::Render::CompileShader{ inputFilePath });
            
            const auto name = File::Path(data.filePath).filename().replace_extension().string();

            using Resource = Atmos::Asset::Resource::Shader;
            auto resource = reliquary.Do(
                Atmos::Asset::Resource::Create<Resource> { buffer, name });
            return reliquary.Do(Arca::Create<Atmos::Asset::Shader>(name, std::move(resource)));
        }
        catch (...)
        {
            return {};
        }
    }

    Nexus<Data::ShaderAsset>::Nexus(
        DataT& data, NexusNode* parent, NexusHistory nexusHistory, UI& ui, Arca::Reliquary& reliquary)
        :
        EditableAssetNexusCommon(
            data,
            parent,
            nexusHistory,
            ui,
            reliquary,
            CalculateLabel(data)),
        filePath(data.filePath, this, nexusHistory, ui, reliquary, "File Path")
    {
        SetupChildren();
    }

    Nexus<Data::ShaderAsset>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        EditableAssetNexusCommon(std::move(arg), parent),
        filePath(std::move(arg.filePath), this)
    {
        SetupChildren();
    }

    String Nexus<Data::ShaderAsset>::CalculateLabel(const DataT& data) const
    {
        const auto label = File::Path(data.filePath).filename().replace_extension().string();
        return !label.empty() ? label : "Shader Asset";
    }

    void Nexus<Data::ShaderAsset>::SetupChildren()
    {
        autoHandler.Auto(*this, filePath, &DataT::filePath);

        eventConnections =
        {
            filePath.onDataChanged.Subscribe([this](const File::Path&) { OnLabelChanged(); })
        };
    }
}