#pragma once

#include <Arca/Relic.h>

#include <Atmos/MaterialAsset.h>

namespace Creation
{
    class EntityBoundaryRenderInformation
    {
    public:
        Arca::Index<Atmos::Asset::Material> standardMaterial;
        Arca::Index<Atmos::Asset::Material> selectedMaterial;
        Arca::Index<Atmos::Asset::Material> ghostMaterial;

        EntityBoundaryRenderInformation() = default;
    };
}

namespace Arca
{
    template<>
    struct Traits<Creation::EntityBoundaryRenderInformation>
    {
        static constexpr ObjectType objectType = ObjectType::Relic;
        static const inline TypeName typeName = "Creation::EntityBoundaryRenderInformation";
        static constexpr Locality locality = Locality::Global;
    };
}

namespace Inscription
{
    template<class Format>
    struct ScribeTraits<Creation::EntityBoundaryRenderInformation, Format> final
    {
        using Category = ArcaNullScribeCategory<Creation::EntityBoundaryRenderInformation>;
    };
}