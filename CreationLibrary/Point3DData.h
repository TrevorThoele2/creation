#pragma once

#include "DataIncludes.h"
#include <Atmos/Point3D.h>

#include "FloatData.h"

namespace Creation::Editing
{
    template<>
    class Property<Atmos::Spatial::Point3D> final : public CategoryProperty<Atmos::Spatial::Point3D>
    {
    public:
        Property<float> x, y, z;
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
    class Nexus<Atmos::Spatial::Point3D> final : public NexusCommon<Atmos::Spatial::Point3D>
    {
    public:
        Nexus<float> x, y, z;
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