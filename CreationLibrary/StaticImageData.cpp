#include "StaticImageData.h"

#include "DefaultImageMaterials.h"

#include <Atmos/FindAssetByName.h>
#include <Atmos/SpatialAlgorithms.h>

#include <Arca/Create.h>

namespace Creation::Editing
{
    namespace Data
    {
        void StaticImage::Build(Build::Context& context) const
        {
            auto builtRenderCore = renderCore.Build(context);
            auto builtCore = imageCore.Build(context);
            auto builtBounds = bounds.Build(context);

            const auto asset = builtCore.asset;
            if (asset)
                builtBounds.BaseSize(asset->SliceSize());

            context.reliquary.Do(Arca::Create<Atmos::Render::StaticImage> {
                builtCore.asset,
                builtCore.assetIndex,
                builtRenderCore.material,
                builtRenderCore.color,
                builtBounds.Position(),
                builtBounds.Scalers(),
                builtBounds.Rotation() });
        }
    }

    Property<Data::StaticImage>::Property(
        const String& name,
        const String& label,
        wxPGProperty* parentProperty,
        wxPropertyGrid& grid,
        const NexusHistory& nexusHistory,
        UI& ui)
        :
        CategoryProperty(name, label, parentProperty, grid, ui),
        renderCore("Render Core", "Render Core", WxProperty(), grid, nexusHistory, ui),
        imageCore("Core", "Core", WxProperty(), grid, nexusHistory, ui),
        bounds("Bounds", "Bounds", WxProperty(), grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    Property<Data::StaticImage>::Property(Property&& arg) noexcept :
        CategoryProperty(std::move(arg)),
        renderCore(std::move(arg.renderCore)),
        imageCore(std::move(arg.imageCore)),
        bounds(std::move(arg.bounds))
    {
        SetupProperties();
    }

    void Property<Data::StaticImage>::SetupProperties()
    {
        Auto(renderCore, &Nexus::renderCore);
        Auto(imageCore, &Nexus::imageCore);
        Auto(bounds, &Nexus::bounds);
    }

    NexusBatch<Data::StaticImage>::NexusBatch(
        wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui)
        :
        NexusBatchCommon(grid),
        renderCore("Render Core", "Render Core", nullptr, grid, nexusHistory, ui),
        imageCore("Core", "Core", nullptr, grid, nexusHistory, ui),
        bounds("Bounds", "Bounds", nullptr, grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    NexusBatch<Data::StaticImage>::NexusBatch(NexusBatch&& arg) noexcept :
        NexusBatchCommon(std::move(arg)),
        renderCore(std::move(arg.renderCore)),
        imageCore(std::move(arg.imageCore)),
        bounds(std::move(arg.bounds))
    {
        SetupProperties();
    }

    void NexusBatch<Data::StaticImage>::SetupProperties()
    {
        Auto(renderCore, &Nexus::renderCore);
        Auto(imageCore, &Nexus::imageCore);
        Auto(bounds, &Nexus::bounds);
    }

    GhostWorldElement<Data::StaticImage>::GhostWorldElement(Nexus& nexus, Arca::Reliquary& reliquary) :
        GhostWorldElementCommon(nexus, reliquary),
        data(nexus.CurrentData()),
        image(reliquary),
        imageData
        {
            reliquary.Do(Atmos::Asset::FindByName<Atmos::Asset::Image> { data.imageCore.asset }),
            reliquary.Find<DefaultImageMaterials>()->ghost,
            Atmos::Render::Color { 255, 255, 255, 255 },
            data.imageCore.assetIndex,
            data.bounds.position,
            data.bounds.scalers,
            data.bounds.rotation
        }
    {
        image.Create(imageData);
    }

    auto GhostWorldElement<Data::StaticImage>::CurrentData() const -> DataT
    {
        auto returnData = data;
        returnData.bounds.position = imageData.position;
        return returnData;
    }

    void GhostWorldElement<Data::StaticImage>::MoveByImpl(const Atmos::Spatial::Point2D& by)
    {
        if (!image)
            return;

        const auto fromReliquary = Reliquary().Do(Atmos::Asset::FindByName<Atmos::Asset::Image> { data.imageCore.asset });
        const auto assetSliceSize = fromReliquary
            ? fromReliquary->SliceSize()
            : Atmos::Spatial::Size2D { 1, 1 };
        const auto z = data.bounds.position.z;

        const Atmos::Spatial::Point3D newPosition
        {
            data.bounds.position.x + by.x,
            data.bounds.position.y + by.y,
            z
        };
        data.bounds.position = newPosition;

        const auto gridPosition = Atmos::Spatial::ToPoint3D(Atmos::Spatial::Grid::ToPoint(newPosition), z);
        const auto normalizedNewPosition = Atmos::Spatial::Point3D
        {
            gridPosition.x + assetSliceSize.width / 2,
            gridPosition.y + assetSliceSize.height / 2,
            gridPosition.z
        };
        imageData.position = normalizedNewPosition;
        image.Refresh(imageData);
    }

    WorldElement<Data::StaticImage>::WorldElement(Nexus& nexus, Arca::Reliquary& reliquary) :
        WorldElementCommon(nexus, reliquary),
        image(reliquary)
    {
        data = nexus.CurrentData();
        image.Create(ImageData(data));
    }

    WorldElement<Data::StaticImage>::WorldElement(WorldElement&& arg) noexcept :
        WorldElementCommon(std::move(arg)),
        data(std::move(arg.data)),
        image(std::move(arg.image)),
        isSelected(arg.isSelected)
    {}

    void WorldElement<Data::StaticImage>::OnDataChanged(DataT data)
    {
        this->data = data;
        if (image)
            image.Refresh(ImageData(data));
    }

    void WorldElement<Data::StaticImage>::DoSelect()
    {
        isSelected = true;
        image.Refresh(ImageData(data));
    }

    void WorldElement<Data::StaticImage>::DoDeselect()
    {
        isSelected = false;
        image.Refresh(ImageData(data));
    }

    void WorldElement<Data::StaticImage>::DoShow()
    {
        if (image)
            image.Refresh(ImageData(data));
    }

    void WorldElement<Data::StaticImage>::DoHide()
    {
        if (image)
            image.Refresh(ImageData(data));
    }

    DynamicWorldImage::Data WorldElement<Data::StaticImage>::ImageData(DataT data) const
    {
        return DynamicWorldImage::Data
        {
            Reliquary().Do(Atmos::Asset::FindByName<Atmos::Asset::Image> { data.imageCore.asset }),
            MaterialFor(data),
            ColorFor(data),
            data.imageCore.assetIndex,
            data.bounds.position,
            data.bounds.scalers,
            data.bounds.rotation
        };
    }

    Atmos::Render::Color WorldElement<Data::StaticImage>::ColorFor(DataT data) const
    {
        return IsShown()
            ? data.renderCore.color
            : Atmos::Render::Color{ 0, 0, 0, 0 };
    }

    Arca::Index<Atmos::Asset::Material> WorldElement<Data::StaticImage>::MaterialFor(DataT data) const
    {
        auto& reliquary = Reliquary();
        if (isSelected)
            return reliquary.Find<DefaultImageMaterials>()->selected;

        if (data.renderCore.material.empty())
            return Arca::Index<Atmos::Asset::Material>();

        const auto dataMaterial = reliquary.Do(
            Atmos::Asset::FindByName<Atmos::Asset::Material> { data.renderCore.material });
        return dataMaterial
            ? dataMaterial
            : reliquary.Find<DefaultImageMaterials>()->material;
    }

    Nexus<Data::StaticImage>::Nexus(
        DataT& data,
        NexusNode* parent,
        const NexusHistory& nexusHistory,
        UI& ui,
        Arca::Reliquary& reliquary)
        :
        EditableNexusCommon(
            data,
            parent,
            nexusHistory,
            ui,
            reliquary,
            CalculateLabel(data)),
        renderCore(data.renderCore, this, nexusHistory, ui, reliquary, "Render Core"),
        imageCore(data.imageCore, this, nexusHistory, ui, reliquary, "Core"),
        bounds(data.bounds, this, nexusHistory, ui, reliquary, "Bounds")
    {
        SetupChildren();
    }

    Nexus<Data::StaticImage>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        EditableNexusCommon(std::move(arg), parent),
        renderCore(std::move(arg.renderCore), this),
        imageCore(std::move(arg.imageCore), this),
        bounds(std::move(arg.bounds), this)
    {
        SetupChildren();
    }

    void Nexus<Data::StaticImage>::SetupChildren()
    {
        autoHandler.Auto(*this, renderCore, &DataT::renderCore);
        autoHandler.Auto(*this, imageCore, &DataT::imageCore);
        autoHandler.Auto(*this, bounds, &DataT::bounds);

        const auto onLabelComponentChanged = [this](auto)
        {
            const auto label = CalculateLabel(CurrentData());
            ChangeLabel(label);
        };

        eventConnections =
        {
            bounds.position.x.onDataChanged.Subscribe(onLabelComponentChanged),
            bounds.position.y.onDataChanged.Subscribe(onLabelComponentChanged),
            bounds.position.z.onDataChanged.Subscribe(onLabelComponentChanged)
        };
    }

    String Nexus<Data::StaticImage>::CalculateLabel(const DataT& data)
    {
        return
            "("
            + Chroma::ToString(data.bounds.position.x)
            + ", "
            + Chroma::ToString(data.bounds.position.y)
            + ", "
            + Chroma::ToString(data.bounds.position.z)
            + ")";
    }
}