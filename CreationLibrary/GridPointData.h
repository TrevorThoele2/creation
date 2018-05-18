#pragma once

#include "DataIncludes.h"
#include <Atmos/GridPoint.h>

#include "IntegerData.h"

namespace Creation::Editing
{
    template<>
    class Property<Atmos::Spatial::Grid::Point> final : public CategoryProperty<Atmos::Spatial::Grid::Point>
    {
    public:
        Property<std::int32_t> x, y;
    public:
        Property(
            const String& name,
            const String& label,
            wxPGProperty* parentProperty,
            wxPropertyGrid& grid,
            const NexusHistory& nexusHistory,
            UI& ui);
        Property(Property&& arg) noexcept;
    private:
        void SetupProperties();
    };

    template<>
    class Nexus<Atmos::Spatial::Grid::Point> final : public NexusCommon<Atmos::Spatial::Grid::Point>
    {
    public:
        Nexus<std::int32_t> x, y;
    public:
        Nexus(
            DataT& data,
            NexusNode* parent,
            const NexusHistory& nexusHistory,
            UI& ui,
            Arca::Reliquary& reliquary,
            const String& label);
        Nexus(Nexus&& arg, NexusNode* parent) noexcept;
        Nexus(Nexus&& arg) noexcept = default;
    private:
        void SetupChildren();
    };
}