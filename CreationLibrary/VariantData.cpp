#include "VariantData.h"

namespace Creation::Editing
{
    namespace Data
    {
        Variant::Variant(VariantType type, const String& value) :
            type(type), value(value)
        {}

        Atmos::Variant Variant::Build() const
        {
            switch (type)
            {
            case VariantType::Bool:
                return Chroma::FromString<bool>(value);
            case VariantType::Int8:
                return Chroma::FromString<std::int8_t>(value);
            case VariantType::Int16:
                return Chroma::FromString<std::int16_t>(value);
            case VariantType::Int32:
                return Chroma::FromString<std::int32_t>(value);
            case VariantType::Int64:
                return Chroma::FromString<std::int64_t>(value);
            case VariantType::Uint8:
                return Chroma::FromString<std::uint8_t>(value);
            case VariantType::Uint16:
                return Chroma::FromString<std::uint16_t>(value);
            case VariantType::Uint32:
                return Chroma::FromString<std::uint32_t>(value);
            case VariantType::Uint64:
                return Chroma::FromString<std::uint64_t>(value);
            case VariantType::Float:
                return Chroma::FromString<float>(value);
            case VariantType::Double:
                return Chroma::FromString<double>(value);
            case VariantType::String:
                return value;
            default:
                throw std::runtime_error("Variant could not be built: type unknown.");
            }
        }
    }

    EnumDescriptors<Data::VariantType> EnumTraits<Data::VariantType>::descriptors({
        { EnumT::Bool, "Bool" },
        { EnumT::Int8, "Int8" },
        { EnumT::Int16, "Int16" },
        { EnumT::Int32, "Int32" },
        { EnumT::Int64, "Int64" },
        { EnumT::Uint8, "Uint8" },
        { EnumT::Uint16, "Uint16" },
        { EnumT::Uint32, "Uint32" },
        { EnumT::Uint64, "Uint64" },
        { EnumT::Float, "Float" },
        { EnumT::Double, "Double" },
        { EnumT::String, "String" } });

    NexusBatch<Data::Variant>::NexusBatch(wxPropertyGrid& grid, NexusHistory nexusHistory, UI& ui) :
        NexusBatchCommon(grid),
        type("Type", "Type", nullptr, grid, nexusHistory, ui),
        value("Value", "Value", nullptr, grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    NexusBatch<Data::Variant>::NexusBatch(NexusBatch&& arg) noexcept :
        NexusBatchCommon(std::move(arg)),
        type(std::move(arg.type)),
        value(std::move(arg.value))
    {
        SetupProperties();
    }

    void NexusBatch<Data::Variant>::SetupProperties()
    {
        Auto(type, &Nexus::type);
        Auto(value, &Nexus::value);
    }

    Nexus<Data::Variant>::Nexus(
        DataT& data,
        NexusNode* parent,
        NexusHistory nexusHistory,
        UI& ui,
        Arca::Reliquary& reliquary,
        const String& label)
        :
        EditableNexusCommon(
            data,
            parent,
            nexusHistory,
            ui,
            reliquary,
            label),
        type(data.type, parent, nexusHistory, ui, reliquary, "Type"),
        value(data.value, parent, nexusHistory, ui, reliquary, "Value")
    {
        SetupChildren();
    }

    Nexus<Data::Variant>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        EditableNexusCommon(std::move(arg), parent),
        type(std::move(arg.type), this),
        value(std::move(arg.value), this)
    {
        SetupChildren();
    }

    void Nexus<Data::Variant>::SetupChildren()
    {
        autoHandler.Auto(*this, type, &DataT::type);
        autoHandler.Auto(*this, value, &DataT::value);
    }
}