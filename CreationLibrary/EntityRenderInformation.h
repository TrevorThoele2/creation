#pragma once

#include <Arca/Relic.h>

#include <Atmos/ImageAsset.h>

namespace Creation
{
    class EntityRenderInformation
    {
    public:
        Arca::Index<Atmos::Asset::Image> asset;

        EntityRenderInformation() = default;
    };
}

namespace Arca
{
    template<>
    struct Traits<Creation::EntityRenderInformation>
    {
        static constexpr ObjectType objectType = ObjectType::Relic;
        static const inline TypeName typeName = "Creation::EntityRenderInformation";
        static constexpr Locality locality = Locality::Global;
    };
}

namespace Inscription
{
    template<class Format>
    struct ScribeTraits<Creation::EntityRenderInformation, Format> final
    {
        using Category = ArcaNullScribeCategory<Creation::EntityRenderInformation>;
    };
}