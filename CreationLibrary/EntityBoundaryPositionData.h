#pragma once

#include "DataIncludes.h"

#include "DynamicWorldEntityBoundaryPosition.h"
#include "GridPointData.h"

#include <Atmos/Point3D.h>

namespace Creation::Editing
{
    namespace Data
    {
        class EntityBoundaryPosition
        {
        public:
            std::int32_t x;
            std::int32_t y;
        public:
            EntityBoundaryPosition() = default;
            EntityBoundaryPosition(std::int32_t x, std::int32_t y);
            EntityBoundaryPosition(const EntityBoundaryPosition& arg) = default;
            EntityBoundaryPosition& operator=(const EntityBoundaryPosition& arg) = default;

            Atmos::Spatial::Grid::Point Build(Build::Context& context) const;
        private:
            INSCRIPTION_ACCESS;
        };
    }

    template<>
    class GhostWorldElement<Data::EntityBoundaryPosition> final : public GhostWorldElementCommon<Data::EntityBoundaryPosition>
    {
    public:
        GhostWorldElement(Nexus& nexus, Arca::Reliquary& reliquary);
    public:
        [[nodiscard]] DataT CurrentData() const override;
    protected:
        void MoveByImpl(const Atmos::Spatial::Point2D& by) override;
    private:
        DataT data;
    private:
        Atmos::Spatial::Point3D ephemeralPosition;

        DynamicWorldEntityBoundaryPosition position;

        [[nodiscard]] DynamicWorldEntityBoundaryPosition::Data PositionData() const;
    private:
        [[nodiscard]] static Atmos::Spatial::Grid::Point Point3DToGrid(Atmos::Spatial::Point3D point);
        [[nodiscard]] static Atmos::Spatial::Point3D GridToPoint3D(Atmos::Spatial::Grid::Point point);

    };

    template<>
    class WorldElement<Data::EntityBoundaryPosition> final : public WorldElementCommon<Data::EntityBoundaryPosition>
    {
    public:
        WorldElement(Nexus& nexus, Arca::Reliquary& reliquary);
        WorldElement(WorldElement&& arg) noexcept = default;
    protected:
        void OnDataChanged(DataT data) override;

        void DoSelect() override;
        void DoDeselect() override;

        void DoShow() override;
        void DoHide() override;
    private:
        DataT data;

        DynamicWorldEntityBoundaryPosition position;

        bool isSelected = false;

        [[nodiscard]] DynamicWorldEntityBoundaryPosition::Data PositionData() const;
    };

    template<>
    class NexusBatch<Data::EntityBoundaryPosition> final : public NexusBatchCommon<Data::EntityBoundaryPosition>
    {
    public:
        Property<std::int32_t> x, y;
    public:
        NexusBatch(wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui);
        NexusBatch(NexusBatch&& arg) noexcept;
    private:
        void SetupProperties();
    };

    template<>
    class Nexus<Data::EntityBoundaryPosition> final : public EditableNexusCommon<Data::EntityBoundaryPosition>
    {
    public:
        Nexus<std::int32_t> x, y;
    public:
        Nexus(
            DataT& data,
            NexusNode* parent,
            const NexusHistory& nexusHistory,
            UI& ui,
            Arca::Reliquary& reliquary);
        Nexus(Nexus&& arg, NexusNode* parent) noexcept;
        Nexus(Nexus&& arg) noexcept = default;
    private:
        void SetupChildren();

        [[nodiscard]] static String CalculateLabel(const DataT& data);
    };
}

namespace Inscription
{
    template<>
    class Scribe<Creation::Editing::Data::EntityBoundaryPosition> final
    {
    public:
        using ObjectT = Creation::Editing::Data::EntityBoundaryPosition;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            format("x", object.x);
            format("y", object.y);
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Editing::Data::EntityBoundaryPosition, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Editing::Data::EntityBoundaryPosition>;
    };
}