#pragma once

#include "DataIncludes.h"
#include <Atmos/ScriptVariant.h>

#include "EnumData.h"
#include "StringData.h"

namespace Creation::Editing
{
    namespace Data
    {
        enum class VariantType
        {
            Bool,
            Int8,
            Int16,
            Int32,
            Int64,
            Uint8,
            Uint16,
            Uint32,
            Uint64,
            Float,
            Double,
            String
        };

        class Variant
        {
        public:
            VariantType type = VariantType::Int32;
            String value;
        public:
            Variant() = default;
            Variant(const Variant& arg) = default;
            Variant& operator=(const Variant& arg) = default;

            Atmos::Variant Build(Build::Context& context) const;
        private:
            INSCRIPTION_ACCESS;
        };
    }

    template<>
    struct EnumTraits<Data::VariantType>
    {
        using EnumT = Data::VariantType;
        static EnumDescriptors<EnumT> descriptors;
    };

    template<>
    class Property<Data::VariantType> final : public EnumProperty<Data::VariantType>
    {
    public:
        using EnumProperty::EnumProperty;
    };

    template<>
    class Nexus<Data::VariantType> final :
        public NexusCommon<Data::VariantType>
    {
    public:
        using NexusCommon<Data::VariantType>::NexusCommon;
    };

    template<>
    class NexusBatch<Data::Variant> final : public NexusBatchCommon<Data::Variant>
    {
    public:
        Property<Data::VariantType> type;

        Property<String> value;
    public:
        NexusBatch(wxPropertyGrid& grid, NexusHistory nexusHistory, UI& ui);
        NexusBatch(NexusBatch&& arg) noexcept;
    private:
        void SetupProperties();
    };

    template<>
    class Nexus<Data::Variant> final : public EditableNexusCommon<Data::Variant>
    {
    public:
        Nexus<Data::VariantType> type;

        Nexus<String> value;
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
    template<class Format>
    struct ScribeTraits<Creation::Editing::Data::VariantType, Format> final
    {
        using Category = EnumScribeCategory<Creation::Editing::Data::VariantType>;
    };

    template<>
    class Scribe<Creation::Editing::Data::Variant> final
    {
    public:
        using ObjectT = Creation::Editing::Data::Variant;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            format("type", object.type);
            format("value", object.value);
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Editing::Data::Variant, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Editing::Data::Variant>;
    };
}