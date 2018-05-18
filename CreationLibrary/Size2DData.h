#pragma once

#include "DataIncludes.h"
#include <Atmos/Size2D.h>

#include "FloatData.h"

namespace Creation::Editing
{
    template<>
    class Property<Atmos::Spatial::Size2D> final : public CategoryProperty<Atmos::Spatial::Size2D>
    {
    public:
        Property<float> width, height;
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
    class Nexus<Atmos::Spatial::Size2D> final : public NexusCommon<Atmos::Spatial::Size2D>
    {
    public:
        Nexus<float> width, height;
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