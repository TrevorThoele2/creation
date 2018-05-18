#pragma once

#include "DataIncludes.h"
#include <Atmos/Script.h>

#include "VariantData.h"
#include "StringData.h"
#include "ListData.h"
#include "AssetData.h"

#include "DynamicWorldImage.h"

namespace Creation::Editing
{
    namespace Data
    {
        class Script
        {
        public:
            String assetName;
            Atmos::Name executeName;
            std::list<Variant> parameters = {};
        public:
            Script() = default;
            Script(const Script& arg) = default;
            Script& operator=(const Script& arg) = default;

            Arca::Index<Atmos::Scripting::Script> Build(Build::Context& context) const;
        private:
            INSCRIPTION_ACCESS;
        };
    }

    template<>
    class Property<Data::Script> final : public CategoryProperty<Data::Script>
    {
    public:
        AssetSelectorProperty assetName;
        Property<Atmos::Name> executeName;
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
    class NexusBatch<Data::Script> final : public NexusBatchCommon<Data::Script>
    {
    public:
        AssetSelectorProperty assetName;
        Property<Atmos::Name> executeName;
    public:
        NexusBatch(wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui);
        NexusBatch(NexusBatch&& arg) noexcept;
    private:
        void SetupProperties();
    };

    template<>
    class Nexus<Data::Script> final : public EditableNexusCommon<Data::Script>
    {
    public:
        Nexus<String> assetName;
        Nexus<Atmos::Name> executeName;
        Nexus<std::list<Data::Variant>> parameters;
    public:
        Nexus(
            DataT& data,
            NexusNode* parent,
            NexusHistory nexusHistory,
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
    class Scribe<Creation::Editing::Data::Script> final
    {
    public:
        using ObjectT = Creation::Editing::Data::Script;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            format("assetName", object.assetName);
            format("executeName", object.executeName);
            format("parameters", object.parameters);
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Editing::Data::Script, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Editing::Data::Script>;
    };
}