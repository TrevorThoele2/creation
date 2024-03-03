#pragma once

#include <Arca/Curator.h>

#include "EntityBoundaryRenderInformation.h"
#include "InitializeBoundaryRenderInformation.h"

namespace Creation
{
    class EntityBoundaryRenderInformationCurator : public Arca::Curator
    {
    public:
        explicit EntityBoundaryRenderInformationCurator(Init init);
    public:
        void Handle(const InitializeEntityBoundaryRenderInformation& command);
    private:
        Arca::Index<EntityBoundaryRenderInformation> information;
    };
}

namespace Arca
{
    template<>
    struct Traits<Creation::EntityBoundaryRenderInformationCurator>
    {
        static constexpr ObjectType objectType = ObjectType::Curator;
        static const inline TypeName typeName = "Creation::EntityBoundaryRenderInformationCurator";
        using HandledCommands = HandledCommands<Creation::InitializeEntityBoundaryRenderInformation>;
    };
}

namespace Inscription
{
    template<class Format>
    struct ScribeTraits<Creation::EntityBoundaryRenderInformationCurator, Format> final
    {
        using Category = ArcaNullScribeCategory<Creation::EntityBoundaryRenderInformationCurator>;
    };
}