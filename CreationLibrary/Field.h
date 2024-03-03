#pragma once

#include <Atmos/Field.h>

#include "IntegerData.h"
#include "EntityPrototypeData.h"
#include "EntityBoundaryPositionData.h"
#include "StaticImageData.h"

namespace Creation
{
    struct Field
    {
        std::uint32_t id;
        std::list<Editing::Data::EntityPrototype> entities;
        std::list<Editing::Data::EntityBoundaryPosition> entityBoundary;
        std::list<Editing::Data::StaticImage> terrain;
    };
}

namespace Inscription
{
    template<>
    class Scribe<Creation::Field> final
    {
    public:
        using ObjectT = Creation::Field;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            format("id", object.id);
            format("entities", object.entities);
            format("entityBoundary", object.entityBoundary);
            format("terrain", object.terrain);
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Field, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Field>;
    };
}