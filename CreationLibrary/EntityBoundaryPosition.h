#pragma once

#include <Arca/Relic.h>

#include <Atmos/GridPoint.h>

namespace Creation::Editing
{
    class EntityBoundaryPosition final
    {
    public:
        using Value = Atmos::Spatial::Grid::Point::Value;

        enum class Status
        {
            Selected,
            Ghost
        };
    public:
        Value x = 0;
        Value y = 0;

        std::optional<Status> status;

        EntityBoundaryPosition() = default;
        EntityBoundaryPosition(Value x, Value y, std::optional<Status> status);

        [[nodiscard]] operator Atmos::Spatial::Grid::Point() const;
    };
}

namespace Arca
{
    template<>
    struct Traits<Creation::Editing::EntityBoundaryPosition>
    {
        static constexpr ObjectType objectType = ObjectType::Relic;
        static const inline TypeName typeName = "Creation::Editing::EntityBoundaryPosition";
    };
}

namespace Inscription
{
    template<>
    class Scribe<Creation::Editing::EntityBoundaryPosition> final
    {
    public:
        using ObjectT = Creation::Editing::EntityBoundaryPosition;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            format("x", object.x);
            format("y", object.y);
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Editing::EntityBoundaryPosition, Format> final
    {
        using Category = ArcaCompositeScribeCategory<Creation::Editing::EntityBoundaryPosition>;
    };
}