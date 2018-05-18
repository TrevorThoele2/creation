#include "ImageAssetData.h"

#include <Atmos/LoadImageAssetResourceData.h>
#include <Atmos/CreateImageAssetResource.h>
#include <Atmos/PruneGraphicsResources.h>
#include <Atmos/LoadAssetError.h>
#include <Arca/Create.h>
#include <Arca/Assign.h>
#include <Arca/Destroy.h>

namespace Creation::Editing
{
    namespace Data
    {
        void ImageAsset::Build(Build::Context& context) const
        {
            try
            {
                const auto loadedResource = context.reliquary.Do(
                    Atmos::Asset::Resource::LoadData<Atmos::Asset::Resource::Image>{ filePath });
                auto resource = context.reliquary.Do(
                    Atmos::Asset::Resource::Create<Atmos::Asset::Resource::Image>{
                        loadedResource.buffer,
                        filePath.filename().string(),
                        loadedResource.size });
                context.reliquary.Do(Arca::Create<Atmos::Asset::Image> {
                    FileAssetName(filePath),
                    std::move(resource),
                    Atmos::Asset::ImageGridSize{ columns, rows } });
            }
            catch (const Atmos::Asset::LoadError&)
            { }
        }
    }

    NexusBatch<Data::ImageAsset>::NexusBatch(
        wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui)
        :
        NexusBatchCommon(grid),
        filePath("FilePath", "File Path", nullptr, grid, nexusHistory, ui),
        columns("Columns", "Columns", nullptr, grid, nexusHistory, ui),
        rows("Rows", "Rows", nullptr, grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    NexusBatch<Data::ImageAsset>::NexusBatch(NexusBatch&& arg) noexcept :
        NexusBatchCommon(std::move(arg)),
        filePath(std::move(arg.filePath)),
        columns(std::move(arg.columns)),
        rows(std::move(arg.rows))
    {
        SetupProperties();
    }

    void NexusBatch<Data::ImageAsset>::SetupProperties()
    {
        filePath.SetRelative(settings.imageAssetPath);
        filePath.SetInitialPath(settings.imageAssetPath);
        columns.SetMin(1);
        rows.SetMin(1);
        Auto(filePath, &Nexus::filePath);
        Auto(columns, &Nexus::columns);
        Auto(rows, &Nexus::rows);
    }

    WorldElement<Data::ImageAsset>::WorldElement(Nexus& nexus, Arca::Reliquary& reliquary) :
        WorldElementCommon(nexus, reliquary)
    {
        object = CreateObject(nexus.CurrentData());
    }

    WorldElement<Data::ImageAsset>::~WorldElement()
    {
        DestroyObject(object);
    }

    void WorldElement<Data::ImageAsset>::OnDataChanged(DataT data)
    {
        try
        {
            auto [fileName, resource, gridSize] = ObjectConstructorArgsFor(data, Reliquary());
            Reliquary().Do(Arca::AssignMove<Object> {
                object.ID(),
                fileName,
                std::move(resource),
                gridSize });
        }
        catch(const Atmos::Asset::LoadError&)
        { }
    }

    auto WorldElement<Data::ImageAsset>::CreateObject(DataT data) -> Index
    {
        return CreateAtmos(data, Reliquary());
    }

    void WorldElement<Data::ImageAsset>::DestroyObject(Index index)
    {
        auto& reliquary = Reliquary();
        reliquary.Do(Arca::Destroy<Object>{ index.ID() });
        reliquary.Do(Atmos::Render::PruneGraphicsResources{});
    }

    auto WorldElement<Data::ImageAsset>::ObjectConstructorArgsFor(Data::ImageAsset data, Arca::Reliquary& reliquary)
        -> ObjectConstructorArgs
    {
        const auto emptyObject = []()
        {
            return ObjectConstructorArgs(
                "",
                std::unique_ptr<Atmos::Asset::Resource::Image>{},
                Atmos::Asset::ImageGridSize{ 0, 0 });
        };

        const auto filePath = data.filePath;
        if (filePath.string().empty())
            return emptyObject();

        const auto name = filePath.filename().replace_extension().string();

        const auto columns = data.columns;
        const auto rows = data.rows;

        const auto useFilePath = settings.imageAssetPath / data.filePath;
        const auto loadedResource = reliquary.Do(
            Atmos::Asset::Resource::LoadData<Atmos::Asset::Resource::Image> {useFilePath});
        auto imageData = reliquary.Do(
            Atmos::Asset::Resource::Create<Atmos::Asset::Resource::Image>{
            loadedResource.buffer,
                name,
                loadedResource.size });
        return ObjectConstructorArgs(
            name,
            std::move(imageData),
            Atmos::Asset::ImageGridSize{ columns, rows });
    }

    Arca::Index<Atmos::Asset::Image> WorldElement<Data::ImageAsset>::CreateAtmos(
        Data::ImageAsset data, Arca::Reliquary& reliquary)
    {
        try
        {
            auto [name, resource, gridSize] = ObjectConstructorArgsFor(data, reliquary);
            auto created = reliquary.Do(Arca::Create<Atmos::Asset::Image> {
                name,
                std::move(resource),
                gridSize });
            return created;
        }
        catch (const Atmos::Asset::LoadError&)
        {
            return Arca::Index<Atmos::Asset::Image>{};
        }
    }

    Nexus<Data::ImageAsset>::Nexus(
        DataT& data, NexusNode* parent, NexusHistory nexusHistory, UI& ui, Arca::Reliquary& reliquary)
        :
        EditableAssetNexusCommon(
            data,
            parent,
            nexusHistory,
            ui,
            reliquary,
            CalculateLabel(data)),
        filePath(data.filePath, this, nexusHistory, ui, reliquary, "File Path"),
        columns(data.columns, this, nexusHistory, ui, reliquary, "Columns"),
        rows(data.rows, this, nexusHistory, ui, reliquary, "Rows")
    {
        SetupChildren();
    }

    Nexus<Data::ImageAsset>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        EditableAssetNexusCommon(std::move(arg), parent),
        filePath(std::move(arg.filePath), this),
        columns(std::move(arg.columns), this),
        rows(std::move(arg.rows), this)
    {
        SetupChildren();
    }

    String Nexus<Data::ImageAsset>::CalculateLabel(const DataT& data) const
    {
        const auto label = File::Path(data.filePath).filename().replace_extension().string();
        return !label.empty() ? label : "Image Asset";
    }

    void Nexus<Data::ImageAsset>::SetupChildren()
    {
        autoHandler.Auto(*this, filePath, &DataT::filePath);
        autoHandler.Auto(*this, columns, &DataT::columns);
        autoHandler.Auto(*this, rows, &DataT::rows);

        eventConnections =
        {
            filePath.onDataChanged.Subscribe([this](const File::Path&) { OnLabelChanged(); })
        };
    }
}