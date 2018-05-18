#include "EntityPrototypeData.h"

#include "EntityRenderInformation.h"
#include "DefaultImageMaterials.h"

#include <Atmos/EntityPrototype.h>
#include <Atmos/SpatialAlgorithms.h>
#include <Atmos/GridCellSize.h>
#include <Atmos/FindAssetByName.h>
#include <Arca/Create.h>

namespace Creation::Editing
{
    namespace Data
    {
        void EntityPrototype::Build(Build::Context& context) const
        {
            const auto builtConstructor = constructor.Build(context);
            context.reliquary.Do(Arca::Create<Atmos::Entity::Prototype>(
                builtConstructor,
                name,
                position,
                solid));
        }
    }

    NexusBatch<Data::EntityPrototype>::NexusBatch(
        wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui)
        :
        NexusBatchCommon(grid),
        name("Name", "Name", nullptr, grid, nexusHistory, ui),
        position("Position", "Position", nullptr, grid, nexusHistory, ui),
        solid("Solid", "Solid", nullptr, grid, nexusHistory, ui),
        constructor("Constructor", "Constructor", nullptr, grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    NexusBatch<Data::EntityPrototype>::NexusBatch(NexusBatch&& arg) noexcept :
        NexusBatchCommon(std::move(arg)),
        name(std::move(arg.name)),
        position(std::move(arg.position)),
        solid(std::move(arg.solid)),
        constructor(std::move(arg.constructor))
    {
        SetupProperties();
    }

    void NexusBatch<Data::EntityPrototype>::SetupProperties()
    {
        Auto(name, &Nexus::name);
        Auto(position, &Nexus::position);
        Auto(solid, &Nexus::solid);
        Auto(constructor, &Nexus::constructor);
    }

    GhostWorldElement<Data::EntityPrototype>::GhostWorldElement(Nexus& nexus, Arca::Reliquary& reliquary) :
        GhostWorldElementCommon(nexus, reliquary),
        data(nexus.CurrentData()),
        image(reliquary),
        imageData(ImageData(data, reliquary)),
        ephemeralPosition(imageData.position)
    {
        image.Create(imageData);
    }

    auto GhostWorldElement<Data::EntityPrototype>::CurrentData() const -> DataT
    {
        auto returnData = data;
        returnData.position = Atmos::Spatial::Grid::ToPoint(ephemeralPosition);
        return returnData;
    }

    void GhostWorldElement<Data::EntityPrototype>::MoveByImpl(const Atmos::Spatial::Point2D& by)
    {
        if (!image)
            return;

        const auto assetSliceSize = imageData.asset->SliceSize();

        const Atmos::Spatial::Point3D newPosition
        {
            ephemeralPosition.x + by.x,
            ephemeralPosition.y + by.y,
            0
        };
        ephemeralPosition = newPosition;

        const auto gridPosition = Atmos::Spatial::ToPoint3D(Atmos::Spatial::Grid::ToPoint(newPosition), 0);
        const auto normalizedNewPosition = Atmos::Spatial::Point3D
        {
            gridPosition.x + assetSliceSize.width / 2,
            gridPosition.y + assetSliceSize.height / 2,
            gridPosition.z
        };
        imageData.position = normalizedNewPosition;
        image.Refresh(imageData);
    }

    DynamicWorldImage::Data GhostWorldElement<Data::EntityPrototype>::ImageData(DataT data, Arca::Reliquary& reliquary)
    {
        const auto asset = reliquary.Find<EntityRenderInformation>()->asset;
        const auto assetSize = asset->SliceSize();

        return
        {
            reliquary.Find<EntityRenderInformation>()->asset,
            reliquary.Find<DefaultImageMaterials>()->ghost,
            Atmos::Render::Color { 255, 255, 255, 255 },
            0,
            Atmos::Spatial::Point3D
            {
                data.position.x * Atmos::Spatial::Grid::CellSize<float> + assetSize.width / 2,
                data.position.y * Atmos::Spatial::Grid::CellSize<float> + assetSize.height / 2,
                0
            },
            Atmos::Spatial::Scalers2D{ 1.0f, 1.0f },
            0.0f
        };
    }

    WorldElement<Data::EntityPrototype>::WorldElement(Nexus& nexus, Arca::Reliquary& reliquary) :
        WorldElementCommon(nexus, reliquary),
        image(reliquary),
        asset(reliquary.Find<EntityRenderInformation>()->asset)
    {
        data = nexus.CurrentData();
        image.Create(ImageData(data));
    }

    WorldElement<Data::EntityPrototype>::WorldElement(WorldElement&& arg) noexcept :
        WorldElementCommon(std::move(arg)),
        data(arg.data),
        image(std::move(arg.image)),
        isSelected(arg.isSelected),
        asset(std::move(arg.asset))
    {}

    void WorldElement<Data::EntityPrototype>::OnDataChanged(DataT data)
    {
        this->data = data;
        if (image)
            image.Refresh(ImageData(data));
    }

    void WorldElement<Data::EntityPrototype>::DoSelect()
    {
        isSelected = true;
        image.Refresh(ImageData(data));
    }

    void WorldElement<Data::EntityPrototype>::DoDeselect()
    {
        isSelected = false;
        image.Refresh(ImageData(data));
    }

    void WorldElement<Data::EntityPrototype>::DoShow()
    {
        if (image)
            image.Refresh(ImageData(data));
    }

    void WorldElement<Data::EntityPrototype>::DoHide()
    {
        if (image)
            image.Refresh(ImageData(data));
    }

    DynamicWorldImage::Data WorldElement<Data::EntityPrototype>::ImageData(DataT data) const
    {
        return DynamicWorldImage::Data
        {
            asset,
            MaterialFor(data),
            ColorFor(data),
            0,
            PositionFor(data),
            Atmos::Spatial::Scalers2D{ 1.0f, 1.0f },
            0.0f
        };
    }

    Atmos::Spatial::Point3D WorldElement<Data::EntityPrototype>::PositionFor(DataT data) const
    {
        return Atmos::Spatial::ToPoint3D(data.position, 1.0f)
            + Atmos::Spatial::Point3D
            {
                asset->SliceSize().width / 2,
                asset->SliceSize().height / 2,
                0
            };
    }

    Atmos::Render::Color WorldElement<Data::EntityPrototype>::ColorFor(DataT data) const
    {
        return IsShown()
            ? Atmos::Render::Color{ 255, 255, 255, 255 }
            : Atmos::Render::Color{ 0, 0, 0, 0 };
    }

    Arca::Index<Atmos::Asset::Material> WorldElement<Data::EntityPrototype>::MaterialFor(DataT data) const
    {
        const auto defaultImageMaterials = Reliquary().Find<DefaultImageMaterials>();
        return isSelected
            ? defaultImageMaterials->selected
            : defaultImageMaterials->material;
    }

    Nexus<Data::EntityPrototype>::Nexus(
        DataT& data,
        NexusNode* parent,
        NexusHistory nexusHistory,
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
        name(data.name, this, nexusHistory, ui, reliquary, "Name"),
        position(data.position, this, nexusHistory, ui, reliquary, "Position"),
        solid(data.solid, this, nexusHistory, ui, reliquary, "Solid"),
        constructor(data.constructor, this, nexusHistory, ui, reliquary, "Constructor")
    {
        SetupChildren();
    }

    Nexus<Data::EntityPrototype>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        EditableNexusCommon(std::move(arg), parent),
        name(std::move(arg.name), this),
        position(std::move(arg.position), this),
        solid(std::move(arg.solid), this),
        constructor(std::move(arg.constructor), this)
    {
        SetupChildren();
    }

    void Nexus<Data::EntityPrototype>::SetupChildren()
    {
        autoHandler.Auto(*this, name, &DataT::name);
        autoHandler.Auto(*this, position, &DataT::position);
        autoHandler.Auto(*this, solid, &DataT::solid);
        autoHandler.Auto(*this, constructor, &DataT::constructor);

        const auto onLabelComponentChanged = [this](auto)
        {
            const auto label = CalculateLabel(CurrentData());
            ChangeLabel(label);
        };

        eventConnections =
        {
            name.onDataChanged.Subscribe(onLabelComponentChanged)
        };
    }

    String Nexus<Data::EntityPrototype>::CalculateLabel(const DataT& data)
    {
        const auto label = data.name;
        return !label.empty() ? label : "Entity";
    }
}