#include "AudioAssetData.h"

#include <Atmos/LoadAssetError.h>
#include <Arca/Create.h>

namespace Creation::Editing
{
    namespace Data
    {
        void AudioAsset::Build(Build::Context& context) const
        {
            try
            {
                const auto loadedResource = context.reliquary.Do(
                    Atmos::Asset::Resource::LoadData<Atmos::Asset::Resource::Audio>{ filePath });
                auto resource = context.reliquary.Do(
                    Atmos::Asset::Resource::Create<Atmos::Asset::Resource::Audio>{
                    loadedResource.buffer,
                        filePath.filename().string() });
                context.reliquary.Do(Arca::Create<Atmos::Asset::Audio> {
                    FileAssetName(filePath),
                    std::move(resource) });
            }
            catch (const Atmos::Asset::LoadError&)
            {
            }
        }
    }

    NexusBatch<Data::AudioAsset>::NexusBatch(wxPropertyGrid& grid, NexusHistory nexusHistory, UI& ui) :
        NexusBatchCommon(grid),
        filePath("FilePath", "File Path", nullptr, grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    NexusBatch<Data::AudioAsset>::NexusBatch(NexusBatch&& arg) noexcept :
        NexusBatchCommon(std::move(arg)),
        filePath(std::move(arg.filePath))
    {
        SetupProperties();
    }

    void NexusBatch<Data::AudioAsset>::SetupProperties()
    {
        filePath.SetRelative(settings.audioAssetPath);
        filePath.SetInitialPath(settings.audioAssetPath);
        Auto(filePath, &Nexus::filePath);
    }

    Nexus<Data::AudioAsset>::Nexus(
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

    Nexus<Data::AudioAsset>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        EditableAssetNexusCommon(std::move(arg), parent),
        filePath(std::move(arg.filePath), this)
    {
        SetupChildren();
    }

    String Nexus<Data::AudioAsset>::CalculateLabel(const DataT& data) const
    {
        const auto label = File::Path(data.filePath).filename().replace_extension().string();
        return !label.empty() ? label : "Audio Asset";
    }

    void Nexus<Data::AudioAsset>::SetupChildren()
    {
        autoHandler.Auto(*this, filePath, &DataT::filePath);

        eventConnections =
        {
            filePath.onDataChanged.Subscribe([this](const File::Path&) { OnLabelChanged(); })
        };
    }
}
