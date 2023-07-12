#include "ScriptAssetData.h"

#include "FilePaths.h"
#include <Atmos/LoadScriptAssetResourceData.h>
#include <Atmos/LoadAssetError.h>
#include <Atmos/JavaScriptPaths.h>
#include <Arca/Create.h>

namespace Creation::Editing
{
    namespace Data
    {
        ScriptAsset::ScriptAsset(const File::Path& filePath) : filePath(filePath)
        {}

        void ScriptAsset::Build(Build::Context& context) const
        {
            try
            {
                const auto useFilePath = CompiledScriptPath(filePath);

                const auto loadedResource = context.reliquary.Do(
                    Atmos::Asset::Resource::LoadData<Atmos::Asset::Resource::Script>{ useFilePath });
                auto resource = context.reliquary.Do(
                    Atmos::Asset::Resource::Create<Atmos::Asset::Resource::Script>{
                        loadedResource.data,
                        useFilePath.filename().string() });
                context.reliquary.Do(Arca::Create<Atmos::Asset::Script> {
                    FileAssetName(useFilePath),
                    std::move(resource) });
            }
            catch (const Atmos::Asset::LoadError&)
            {
            }
        }
    }

    NexusBatch<Data::ScriptAsset>::NexusBatch(
        wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui)
        :
        NexusBatchCommon(grid),
        filePath("FilePath", "File Path", nullptr, grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    NexusBatch<Data::ScriptAsset>::NexusBatch(NexusBatch&& arg) noexcept :
        NexusBatchCommon(std::move(arg)),
        filePath(std::move(arg.filePath))
    {
        SetupProperties();
    }

    void NexusBatch<Data::ScriptAsset>::SetupProperties()
    {
        filePath.SetRelative(settings.scriptAssetPath);
        filePath.SetInitialPath(settings.scriptAssetPath);
        Auto(filePath, &Nexus::filePath);
    }

    Nexus<Data::ScriptAsset>::Nexus(
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

    Nexus<Data::ScriptAsset>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        EditableAssetNexusCommon(std::move(arg), parent),
        filePath(std::move(arg.filePath), this)
    {
        SetupChildren();
    }

    String Nexus<Data::ScriptAsset>::CalculateLabel(const DataT& data) const
    {
        const auto label = File::Path(data.filePath).filename().replace_extension().string();
        return !label.empty() ? label : "Script Asset";
    }

    void Nexus<Data::ScriptAsset>::SetupChildren()
    {
        autoHandler.Auto(*this, filePath, &DataT::filePath);

        eventConnections =
        {
            filePath.onDataChanged.Subscribe([this](const File::Path&) { OnLabelChanged(); })
        };
    }
}