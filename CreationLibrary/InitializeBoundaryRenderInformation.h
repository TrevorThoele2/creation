#pragma once

#include <Arca/Command.h>

#include <Atmos/MaterialAsset.h>

namespace Creation
{
    struct InitializeEntityBoundaryRenderInformation
    {
        Arca::Index<Atmos::Asset::Material> standardMaterial;
        Arca::Index<Atmos::Asset::Material> selectedMaterial;
        Arca::Index<Atmos::Asset::Material> ghostMaterial;
    };
}

namespace Arca
{
    template<>
    struct Traits<Creation::InitializeEntityBoundaryRenderInformation>
    {
        static constexpr ObjectType objectType = ObjectType::Command;
        static const inline TypeName typeName = "Creation::InitializeEntityBoundaryRenderInformation";
    };
}