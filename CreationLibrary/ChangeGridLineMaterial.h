#pragma once

#include <Arca/Command.h>

#include <Atmos/MaterialAsset.h>

namespace Creation
{
    struct ChangeGridLineMaterial
    {
        Arca::Index<Atmos::Asset::Material> material;
    };
}

namespace Arca
{
    template<>
    struct Traits<Creation::ChangeGridLineMaterial>
    {
        static constexpr ObjectType objectType = ObjectType::Command;
        static const inline TypeName typeName = "Creation::ChangeGridLineMaterial";
    };
}