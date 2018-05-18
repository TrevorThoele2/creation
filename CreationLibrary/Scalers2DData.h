#pragma once

#include "DataIncludes.h"
#include <Atmos/Scalers2D.h>

#include "FloatData.h"

namespace Creation::Editing
{
    template<>
    class Property<Atmos::Spatial::Scalers2D> final : public CategoryProperty<Atmos::Spatial::Scalers2D>
    {
    public:
        Property<float> x, y;
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
    class Nexus<Atmos::Spatial::Scalers2D> final : public NexusCommon<Atmos::Spatial::Scalers2D>
    {
    public:
        Nexus<float> x, y;
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