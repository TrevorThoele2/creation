#pragma once

#include "DataIncludes.h"
#include <Atmos/Bounds.h>

#include "Point3DData.h"
#include "Scalers2DData.h"

namespace Creation::Editing
{
    namespace Data
    {
        class Bounds
        {
        public:
            Atmos::Spatial::Point3D position;
            Atmos::Spatial::Scalers2D scalers = { 1, 1 };
            Atmos::Spatial::Angle2D rotation = 0.0f;
        public:
            Bounds() = default;
            Bounds(const Bounds& arg) = default;
            Bounds& operator=(const Bounds& arg) = default;

            Atmos::Spatial::Bounds Build(Build::Context& context) const;
        private:
            INSCRIPTION_ACCESS;
        };
    }

    template<>
    class Property<Data::Bounds> final : public CategoryProperty<Data::Bounds>
    {
    public:
        Property<Atmos::Spatial::Point3D> position;
        Property<Atmos::Spatial::Scalers2D> scalers;
        Property<Atmos::Spatial::Angle2D> rotation;
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
    class Nexus<Data::Bounds> final : public NexusCommon<Data::Bounds>
    {
    public:
        Nexus<Atmos::Spatial::Point3D> position;
        Nexus<Atmos::Spatial::Scalers2D> scalers;
        Nexus<Atmos::Spatial::Angle2D> rotation;
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

namespace Inscription
{
    template<>
    class Scribe<Creation::Editing::Data::Bounds> final
    {
    public:
        using ObjectT = Creation::Editing::Data::Bounds;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            format("position", object.position);
            format("scalers", object.scalers);
            format("rotation", object.rotation);
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Editing::Data::Bounds, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Editing::Data::Bounds>;
    };
}