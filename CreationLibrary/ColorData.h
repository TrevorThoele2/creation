#pragma once

#include "DataIncludes.h"
#include <Atmos/Color.h>

#include "IntegerData.h"

namespace Creation::Editing
{
    template<>
    class Property<Atmos::Render::Color> final : public CategoryProperty<Atmos::Render::Color>
    {
    public:
        Property<std::uint8_t> alpha, red, green, blue;
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
    class Nexus<Atmos::Render::Color> final : public NexusCommon<Atmos::Render::Color>
    {
    public:
        Nexus<std::uint8_t> alpha, red, green, blue;
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