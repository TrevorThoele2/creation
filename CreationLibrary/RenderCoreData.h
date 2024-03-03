#pragma once

#include "DataIncludes.h"
#include <Atmos/RenderCore.h>

#include "StringData.h"
#include "IntegerData.h"
#include "ColorData.h"
#include "AssetData.h"

namespace Creation::Editing
{
    namespace Data
    {
        class RenderCore
        {
        public:
            Atmos::Render::Color color{};
            String material;
        public:
            RenderCore();
            RenderCore(const RenderCore& arg) = default;
            RenderCore& operator=(const RenderCore& arg) = default;

            Atmos::Render::RenderCore Build(Build::Context& context) const;
        private:
            INSCRIPTION_ACCESS;
        };
    }

    template<>
    class Property<Data::RenderCore> final : public CategoryProperty<Data::RenderCore>
    {
    public:
        Property<Atmos::Render::Color> color;
        AssetSelectorProperty material;
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
    class Nexus<Data::RenderCore> final : public NexusCommon<Data::RenderCore>
    {
    public:
        Nexus<Atmos::Render::Color> color;
        Nexus<String> material;
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
    class Scribe<Creation::Editing::Data::RenderCore> final
    {
    public:
        using ObjectT = Creation::Editing::Data::RenderCore;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            format("color", object.color);
            format("material", object.material);
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Editing::Data::RenderCore, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Editing::Data::RenderCore>;
    };
}