#pragma once

#include <Arca/Command.h>

#include <Atmos/MaterialAsset.h>

namespace Creation
{
    struct ChangeDefaultImageMaterials
    {
        Arca::Index<Atmos::Asset::Material> material;
        Arca::Index<Atmos::Asset::Material> selected;
        Arca::Index<Atmos::Asset::Material> ghost;
    };
}

namespace Arca
{
    template<>
    struct Traits<Creation::ChangeDefaultImageMaterials>
    {
        static constexpr ObjectType objectType = ObjectType::Command;
        static const inline TypeName typeName = "Creation::ChangeDefaultImageMaterials";
    };
}