#pragma once

#include <Arca/Curator.h>

#include "EntityRenderInformation.h"
#include "InitializeEntityRenderInformation.h"

namespace Creation
{
    class EntityRenderInformationCurator : public Arca::Curator
    {
    public:
        explicit EntityRenderInformationCurator(Init init);
    public:
        void Handle(const InitializeEntityRenderInformation& command);
    private:
        Arca::Index<EntityRenderInformation> rendering;
    };
}

namespace Arca
{
    template<>
    struct Traits<Creation::EntityRenderInformationCurator>
    {
        static constexpr ObjectType objectType = ObjectType::Curator;
        static const inline TypeName typeName = "Creation::EntityRenderInformationCurator";
        using HandledCommands = HandledCommands<Creation::InitializeEntityRenderInformation>;
    };
}

namespace Inscription
{
    template<class Format>
    struct ScribeTraits<Creation::EntityRenderInformationCurator, Format> final
    {
        using Category = ArcaNullScribeCategory<Creation::EntityRenderInformationCurator>;
    };
}