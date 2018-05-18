#pragma once

#include "DataIncludes.h"
#include <cstdint>

#include <wx/propgrid/props.h>

namespace Creation::Editing
{
    template<class T>
    class IntegerProperty : public TerminalProperty<T>
    {
    private:
        using BaseT = TerminalProperty<T>;
    public:
        using DataT = typename BaseT::DataT;
        using DataSet = typename BaseT::NexusSet;

        using BaseT::WxProperty;
    public:
        IntegerProperty(
            const String& name,
            const String& label,
            wxPGProperty* parentProperty,
            wxPropertyGrid& grid,
            const NexusHistory& nexusHistory,
            UI& ui);
        IntegerProperty(IntegerProperty&& arg) noexcept = default;

        void SetMax(T set);
        void SetMin(T set);
    protected:
        [[nodiscard]] DataT ValueFromProperty() const override;
        [[nodiscard]] wxVariant VariantFromData(const DataT& data) override;
    private:
        wxIntProperty* property = nullptr;
        wxPropertyGrid* grid;
    private:
        using WxWidgetsValue = std::conditional_t<std::is_signed_v<T>, wxLongLong, wxULongLong>;
    };

    template<class T>
    IntegerProperty<T>::IntegerProperty(
        const String& name,
        const String& label,
        wxPGProperty* parentProperty,
        wxPropertyGrid& grid,
        const NexusHistory& nexusHistory,
        UI& ui)
        :
        TerminalProperty<T>(
            label,
            new wxIntProperty(label, PropertyName(name, parentProperty)),
            parentProperty,
            grid,
            nexusHistory,
            ui),
        grid(&grid)
    {
        using NumericLimitsT = std::numeric_limits<T>;
        property = static_cast<wxIntProperty*>(WxProperty());
        SetMin(NumericLimitsT::min());
        SetMax(NumericLimitsT::max());
    }

    template<class T>
    void IntegerProperty<T>::SetMax(T set)
    {
        property->SetAttribute("Max", wxAny(set));
    }

    template<class T>
    void IntegerProperty<T>::SetMin(T set)
    {
        property->SetAttribute("Min", wxAny(set));
    }

    template<class T>
    auto IntegerProperty<T>::ValueFromProperty() const -> DataT
    {
        return static_cast<DataT>(property->GetValue().GetLongLong().GetValue());
    }

    template<class T>
    wxVariant IntegerProperty<T>::VariantFromData(const DataT& data)
    {
        return wxVariant(wxLongLong(static_cast<long long>(data)));
    }

    template<>
    class Property<std::int8_t> final : public IntegerProperty<std::int8_t>
    {
    public:
        using IntegerProperty<std::int8_t>::IntegerProperty;
    };

    template<>
    class Property<std::int16_t> final : public IntegerProperty<std::int16_t>
    {
    public:
        using IntegerProperty<std::int16_t>::IntegerProperty;
    };

    template<>
    class Property<std::int32_t> final : public IntegerProperty<std::int32_t>
    {
    public:
        using IntegerProperty<std::int32_t>::IntegerProperty;
    };

    template<>
    class Property<std::int64_t> final : public IntegerProperty<std::int64_t>
    {
    public:
        using IntegerProperty<std::int64_t>::IntegerProperty;
    };

    template<>
    class Property<std::uint8_t> final : public IntegerProperty<std::uint8_t>
    {
    public:
        using IntegerProperty<std::uint8_t>::IntegerProperty;
    };

    template<>
    class Property<std::uint16_t> final : public IntegerProperty<std::uint16_t>
    {
    public:
        using IntegerProperty<std::uint16_t>::IntegerProperty;
    };

    template<>
    class Property<std::uint32_t> final : public IntegerProperty<std::uint32_t>
    {
    public:
        using IntegerProperty<std::uint32_t>::IntegerProperty;
    };

    template<>
    class Property<std::uint64_t> final : public IntegerProperty<std::uint64_t>
    {
    public:
        using IntegerProperty<std::uint64_t>::IntegerProperty;
    };

    template<>
    class Nexus<std::int8_t> final : public NexusCommon<std::int8_t>
    {
    public:
        using NexusCommon<std::int8_t>::NexusCommon;
    };

    template<>
    class Nexus<std::int16_t> final : public NexusCommon<std::int16_t>
    {
    public:
        using NexusCommon<std::int16_t>::NexusCommon;
    };

    template<>
    class Nexus<std::int32_t> final : public NexusCommon<std::int32_t>
    {
    public:
        using NexusCommon<std::int32_t>::NexusCommon;
    };

    template<>
    class Nexus<std::int64_t> final : public NexusCommon<std::int64_t>
    {
    public:
        using NexusCommon<std::int64_t>::NexusCommon;
    };

    template<>
    class Nexus<std::uint8_t> final : public NexusCommon<std::uint8_t>
    {
    public:
        using NexusCommon<std::uint8_t>::NexusCommon;
    };

    template<>
    class Nexus<std::uint16_t> final : public NexusCommon<std::uint16_t>
    {
    public:
        using NexusCommon<std::uint16_t>::NexusCommon;
    };

    template<>
    class Nexus<std::uint32_t> final : public NexusCommon<std::uint32_t>
    {
    public:
        using NexusCommon<std::uint32_t>::NexusCommon;
    };

    template<>
    class Nexus<std::uint64_t> final : public NexusCommon<std::uint64_t>
    {
    public:
        using NexusCommon<std::uint64_t>::NexusCommon;
    };
}