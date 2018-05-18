#pragma once

#include <Arca/Curator.h>

#include "ChangeDefaultImageMaterials.h"

namespace Creation
{
    class DefaultImageMaterialsCurator : public Arca::Curator
    {
    public:
        explicit DefaultImageMaterialsCurator(Init init);
    public:
        void Handle(const ChangeDefaultImageMaterials& command);
    };
}

namespace Arca
{
    template<>
    struct Traits<Creation::DefaultImageMaterialsCurator>
    {
        static constexpr ObjectType objectType = ObjectType::Curator;
        static const inline TypeName typeName = "Creation::DefaultImageMaterialsCurator";
        using HandledCommands = HandledCommands<Creation::ChangeDefaultImageMaterials>;
    };
}

namespace Inscription
{
    template<class Format>
    struct ScribeTraits<Creation::DefaultImageMaterialsCurator, Format> final
    {
        using Category = ArcaNullScribeCategory<Creation::DefaultImageMaterialsCurator>;
    };
}