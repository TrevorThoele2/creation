#pragma once

#include <Arca/Relic.h>

#include <Atmos/MaterialAsset.h>

namespace Creation
{
    class GridLinesInformation
    {
    public:
        int boldFrequency = 4;

        Arca::Index<Atmos::Asset::Material> material;

        GridLinesInformation() = default;

        GridLinesInformation(const GridLinesInformation& arg) = default;
    };
}

namespace Arca
{
    template<>
    struct Traits<Creation::GridLinesInformation>
    {
        static constexpr ObjectType objectType = ObjectType::Relic;
        static const inline TypeName typeName = "Creation::GridLinesInformation";
        static constexpr Locality locality = Locality::Global;
    };
}

namespace Inscription
{
    template<class Format>
    struct ScribeTraits<Creation::GridLinesInformation, Format> final
    {
        using Category = ArcaNullScribeCategory<Creation::GridLinesInformation>;
    };
}