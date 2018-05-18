#include "FontAssetData.h"

#include <Atmos/LoadFontAssetResourceData.h>
#include <Atmos/CreateFontAssetResource.h>
#include <Atmos/PruneGraphicsResources.h>
#include <Atmos/LoadAssetError.h>
#include <Arca/Create.h>
#include <Arca/Assign.h>
#include <Arca/Destroy.h>

namespace Creation::Editing
{
    namespace Data
    {
        void FontAsset::Build(Build::Context& context) const
        {
            try
            {
                const auto loadedResource = context.reliquary.Do(
                    Atmos::Asset::Resource::LoadData<Atmos::Asset::Resource::Font>{ filePath });
                auto resource = context.reliquary.Do(
                    Atmos::Asset::Resource::Create<Atmos::Asset::Resource::Font>{
                        loadedResource.buffer});
                context.reliquary.Do(Arca::Create<Atmos::Asset::Font> {
                    FileAssetName(filePath),
                    std::move(resource) });
            }
            catch (const Atmos::Asset::LoadError&)
            {
            }
        }
    }

    NexusBatch<Data::FontAsset>::NexusBatch(
        wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui)
        :
        NexusBatchCommon(grid),
        filePath("FilePath", "File Path", nullptr, grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    NexusBatch<Data::FontAsset>::NexusBatch(NexusBatch&& arg) noexcept :
        NexusBatchCommon(std::move(arg)),
        filePath(std::move(arg.filePath))
    {
        SetupProperties();
    }

    void NexusBatch<Data::FontAsset>::SetupProperties()
    {
        filePath.SetRelative(settings.fontAssetPath);
        filePath.SetInitialPath(settings.fontAssetPath);
        Auto(filePath, &Nexus::filePath);
    }

    WorldElement<Data::FontAsset>::WorldElement(Nexus& nexus, Arca::Reliquary& reliquary) :
        WorldElementCommon(nexus, reliquary)
    {
        object = CreateObject(nexus.CurrentData());
    }

    WorldElement<Data::FontAsset>::~WorldElement()
    {
        DestroyObject(object);
    }

    void WorldElement<Data::FontAsset>::OnDataChanged(DataT data)
    {
        try
        {
            auto [fileName, resource] = ObjectConstructorArgsFor(data, Reliquary());
            Reliquary().Do(Arca::AssignMove<Object> {
                object.ID(),
                fileName,
                std::move(resource) });
        }
        catch (const Atmos::Asset::LoadError&)
        {
        }
    }

    auto WorldElement<Data::FontAsset>::CreateObject(DataT data) -> Index
    {
        return CreateAtmos(data, Reliquary());
    }

    void WorldElement<Data::FontAsset>::DestroyObject(Index index)
    {
        auto& reliquary = Reliquary();
        reliquary.Do(Arca::Destroy<Object>{ index.ID() });
        reliquary.Do(Atmos::Render::PruneGraphicsResources{});
    }

    auto WorldElement<Data::FontAsset>::ObjectConstructorArgsFor(Data::FontAsset data, Arca::Reliquary& reliquary)
        -> ObjectConstructorArgs
    {
        const auto emptyObject = []()
        {
            return ObjectConstructorArgs(
                "",
                std::unique_ptr<Atmos::Asset::Resource::Font>{});
        };

        const auto filePath = data.filePath;
        if (filePath.string().empty())
            return emptyObject();

        const auto name = filePath.filename().replace_extension().string();
        
        const auto useFilePath = settings.imageAssetPath / data.filePath;
        const auto loadedResource = reliquary.Do(
            Atmos::Asset::Resource::LoadData<Atmos::Asset::Resource::Font> {useFilePath});
        auto imageData = reliquary.Do(
            Atmos::Asset::Resource::Create<Atmos::Asset::Resource::Font>{
                loadedResource.buffer,
                name });
        return ObjectConstructorArgs(
            name,
            std::move(imageData));
    }

    Arca::Index<Atmos::Asset::Font> WorldElement<Data::FontAsset>::CreateAtmos(
        Data::FontAsset data, Arca::Reliquary& reliquary)
    {
        try
        {
            auto [name, resource] = ObjectConstructorArgsFor(data, reliquary);
            auto created = reliquary.Do(Arca::Create<Atmos::Asset::Font> {
                name,
                std::move(resource) });
            return created;
        }
        catch (const Atmos::Asset::LoadError&)
        {
            return Arca::Index<Atmos::Asset::Font>{};
        }
    }

    Nexus<Data::FontAsset>::Nexus(
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

    Nexus<Data::FontAsset>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        EditableAssetNexusCommon(std::move(arg), parent),
        filePath(std::move(arg.filePath), this)
    {
        SetupChildren();
    }

    String Nexus<Data::FontAsset>::CalculateLabel(const DataT& data) const
    {
        const auto label = File::Path(data.filePath).filename().replace_extension().string();
        return !label.empty() ? label : "Font Asset";
    }

    void Nexus<Data::FontAsset>::SetupChildren()
    {
        autoHandler.Auto(*this, filePath, &DataT::filePath);

        eventConnections =
        {
            filePath.onDataChanged.Subscribe([this](const File::Path&) { OnLabelChanged(); })
        };
    }
}