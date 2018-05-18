#pragma once

#include <Arca/Relic.h>

#include <Atmos/MaterialAsset.h>

namespace Creation
{
    class DefaultImageMaterials
    {
    public:
        Arca::Index<Atmos::Asset::Material> material;
        Arca::Index<Atmos::Asset::Material> selected;
        Arca::Index<Atmos::Asset::Material> ghost;

        DefaultImageMaterials() = default;
        DefaultImageMaterials(const DefaultImageMaterials& arg) = default;
    };
}

namespace Arca
{
    template<>
    struct Traits<Creation::DefaultImageMaterials>
    {
        static constexpr ObjectType objectType = ObjectType::Relic;
        static const inline TypeName typeName = "Creation::DefaultImageMaterials";
        static constexpr Locality locality = Locality::Global;
    };
}

namespace Inscription
{
    template<class Format>
    struct ScribeTraits<Creation::DefaultImageMaterials, Format> final
    {
        using Category = ArcaNullScribeCategory<Creation::DefaultImageMaterials>;
    };
}