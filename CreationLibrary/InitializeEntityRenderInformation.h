#pragma once

#include <Arca/Command.h>

#include <Atmos/ImageAsset.h>

namespace Creation
{
    struct InitializeEntityRenderInformation
    {
        Arca::Index<Atmos::Asset::Image> asset;
    };
}

namespace Arca
{
    template<>
    struct Traits<Creation::InitializeEntityRenderInformation>
    {
        static constexpr ObjectType objectType = ObjectType::Command;
        static const inline TypeName typeName = "Creation::InitializeEntityRenderInformation";
    };
}