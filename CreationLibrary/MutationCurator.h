#pragma once

#include <Arca/Curator.h>

namespace Creation
{
    class MutationCurator : public Arca::Curator
    {
    public:
        using Arca::Curator::Curator;

        [[nodiscard]] Arca::MutablePointer RetrieveMutablePointer();
    };
}

namespace Arca
{
    template<>
    struct Traits<Creation::MutationCurator>
    {
        static constexpr ObjectType objectType = ObjectType::Curator;
        static const inline TypeName typeName = "Creation::MutationCurator";
    };
}

namespace Inscription
{
    template<class Format>
    struct ScribeTraits<Creation::MutationCurator, Format> final
    {
        using Category = ArcaNullScribeCategory<Creation::MutationCurator>;
    };
}