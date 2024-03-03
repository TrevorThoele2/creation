#include "EntityBoundaryPositionData.h"

#include "EntityBoundaryRenderInformation.h"

#include <Atmos/GridCellSize.h>
#include <Atmos/SpatialAlgorithms.h>

namespace Creation::Editing
{
    namespace Data
    {
        EntityBoundaryPosition::EntityBoundaryPosition(std::int32_t x, std::int32_t y) : x(x), y(y)
        {}

        Atmos::Spatial::Grid::Point EntityBoundaryPosition::Build(Build::Context& context) const
        {
            return {};
        }
    }

    GhostWorldElement<Data::EntityBoundaryPosition>::GhostWorldElement(Nexus& nexus, Arca::Reliquary& reliquary) :
        GhostWorldElementCommon(nexus, reliquary),
        data(nexus.CurrentData()),
        ephemeralPosition(GridToPoint3D(Atmos::Spatial::Grid::Point { data.x, data.y })),
        position(reliquary)
    {
        position.Create(PositionData());
    }

    auto GhostWorldElement<Data::EntityBoundaryPosition>::CurrentData() const -> DataT
    {
        const auto gridPoint = Point3DToGrid(ephemeralPosition);

        return
        {
            gridPoint.x,
            gridPoint.y
        };
    }

    void GhostWorldElement<Data::EntityBoundaryPosition>::MoveByImpl(const Atmos::Spatial::Point2D& by)
    {
        ephemeralPosition.x += by.x;
        ephemeralPosition.y += by.y;
        const auto newPosition = Point3DToGrid(ephemeralPosition);
        data.x = newPosition.x;
        data.y = newPosition.y;

        position.Refresh(PositionData());
    }

    DynamicWorldEntityBoundaryPosition::Data GhostWorldElement<Data::EntityBoundaryPosition>::PositionData() const
    {
        return DynamicWorldEntityBoundaryPosition::Data
        {
            data.x,
            data.y,
            DynamicWorldEntityBoundaryPosition::Status::Ghost
        };
    }

    Atmos::Spatial::Grid::Point GhostWorldElement<Data::EntityBoundaryPosition>::Point3DToGrid(Atmos::Spatial::Point3D point)
    {
        const auto cellSize = Atmos::Spatial::Grid::CellSize<float>;
        return
        {
            static_cast<int32_t>(floor(point.x / cellSize)),
            static_cast<int32_t>(floor(point.y / cellSize))
        };
    }

    Atmos::Spatial::Point3D GhostWorldElement<Data::EntityBoundaryPosition>::GridToPoint3D(Atmos::Spatial::Grid::Point point)
    {
        const auto cellSize = Atmos::Spatial::Grid::CellSize<float>;
        return
        {
            static_cast<float>(point.x * cellSize + cellSize / 2),
            static_cast<float>(point.y * cellSize + cellSize / 2),
            0
        };
    }

    WorldElement<Data::EntityBoundaryPosition>::WorldElement(Nexus& nexus, Arca::Reliquary& reliquary) :
        WorldElementCommon(nexus, reliquary),
        position(reliquary)
    {
        data = nexus.CurrentData();
        position.Create(PositionData());
    }

    void WorldElement<Data::EntityBoundaryPosition>::OnDataChanged(DataT data)
    {
        this->data = data;
        position.Refresh(PositionData());
    }

    void WorldElement<Data::EntityBoundaryPosition>::DoSelect()
    {
        isSelected = true;
        position.Refresh(PositionData());
    }

    void WorldElement<Data::EntityBoundaryPosition>::DoDeselect()
    {
        isSelected = false;
        position.Refresh(PositionData());
    }

    void WorldElement<Data::EntityBoundaryPosition>::DoShow()
    {
        position.Create(PositionData());
    }

    void WorldElement<Data::EntityBoundaryPosition>::DoHide()
    {
        position.Destroy();
    }

    DynamicWorldEntityBoundaryPosition::Data WorldElement<Data::EntityBoundaryPosition>::PositionData() const
    {
        std::optional<DynamicWorldEntityBoundaryPosition::Status> status;
        if (isSelected)
            status = DynamicWorldEntityBoundaryPosition::Status::Selected;

        return DynamicWorldEntityBoundaryPosition::Data
        {
            data.x,
            data.y,
            status
        };
    }

    NexusBatch<Data::EntityBoundaryPosition>::NexusBatch(
        wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui)
        :
        NexusBatchCommon(grid),
        x("X", "X", nullptr, grid, nexusHistory, ui),
        y("Y", "Y", nullptr, grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    NexusBatch<Data::EntityBoundaryPosition>::NexusBatch(NexusBatch&& arg) noexcept :
        NexusBatchCommon(std::move(arg)),
        x(std::move(arg.x)),
        y(std::move(arg.y))
    {
        SetupProperties();
    }

    void NexusBatch<Data::EntityBoundaryPosition>::SetupProperties()
    {
        Auto(x, &Nexus::x);
        Auto(y, &Nexus::y);
    }

    Nexus<Data::EntityBoundaryPosition>::Nexus(
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
        x(data.x, this, nexusHistory, ui, reliquary, "X"),
        y(data.y, this, nexusHistory, ui, reliquary, "Y")
    {
        SetupChildren();
    }

    Nexus<Data::EntityBoundaryPosition>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        EditableNexusCommon(std::move(arg), parent),
        x(std::move(arg.x), this),
        y(std::move(arg.y), this)
    {
        SetupChildren();
    }

    void Nexus<Data::EntityBoundaryPosition>::SetupChildren()
    {
        autoHandler.Auto(*this, x, &DataT::x);
        autoHandler.Auto(*this, y, &DataT::y);

        const auto onLabelComponentChanged = [this](auto)
        {
            const auto label = CalculateLabel(CurrentData());
            ChangeLabel(label);
        };

        eventConnections =
        {
            x.onDataChanged.Subscribe(onLabelComponentChanged),
            y.onDataChanged.Subscribe(onLabelComponentChanged)
        };
    }

    String Nexus<Data::EntityBoundaryPosition>::CalculateLabel(const DataT& data)
    {
        return
            "("
            + Chroma::ToString(data.x)
            + ", "
            + Chroma::ToString(data.y)
            + ")";
    }
}