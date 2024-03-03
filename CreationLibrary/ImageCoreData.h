#pragma once

#include "DataIncludes.h"
#include <Atmos/ImageCore.h>

#include "AssetData.h"
#include "StringData.h"
#include "IntegerData.h"
#include "ColorData.h"

namespace Creation::Editing
{
    namespace Data
    {
        class ImageCore
        {
        public:
            String asset{};
            int32_t assetIndex{};
        public:
            ImageCore() = default;
            ImageCore(const ImageCore& arg) = default;
            ImageCore& operator=(const ImageCore& arg) = default;

            Atmos::Render::ImageCore Build(Build::Context& context) const;
        private:
            INSCRIPTION_ACCESS;
        };
    }

    template<>
    class Property<Data::ImageCore> final : public CategoryProperty<Data::ImageCore>
    {
    public:
        AssetSelectorProperty asset;
        Property<std::int32_t> assetIndex;
    public:
        Property(
            const String& name,
            const String& label,
            wxPGProperty* parentProperty,
            wxPropertyGrid& grid,
            const NexusHistory& nexusHistory,
            UI& ui);
        Property(Property&& arg) noexcept;
    private:
        void SetupProperties();
    };

    template<>
    class Nexus<Data::ImageCore> final : public NexusCommon<Data::ImageCore>
    {
    public:
        Nexus<String> asset;
        Nexus<std::int32_t> assetIndex;
    public:
        Nexus(
            DataT& data,
            NexusNode* parent,
            const NexusHistory& nexusHistory,
            UI& ui,
            Arca::Reliquary& reliquary,
            const String& label);
        Nexus(Nexus&& arg, NexusNode* parent) noexcept;
        Nexus(Nexus&& arg) noexcept = default;
    private:
        void SetupChildren();
    };
}

namespace Inscription
{
    template<>
    class Scribe<Creation::Editing::Data::ImageCore> final
    {
    public:
        using ObjectT = Creation::Editing::Data::ImageCore;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            format("asset", object.asset);
            format("assetIndex", object.assetIndex);
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Editing::Data::ImageCore, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Editing::Data::ImageCore>;
    };
}