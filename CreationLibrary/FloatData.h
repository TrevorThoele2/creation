#pragma once

#include "DataIncludes.h"
#include <wx/propgrid/props.h>

namespace Creation::Editing
{
    template<class T>
    class FloatProperty : public TerminalProperty<T>
    {
    private:
        using BaseT = TerminalProperty<T>;
    public:
        using DataT = typename BaseT::DataT;
        using DataSet = typename BaseT::NexusSet;

        using BaseT::WxProperty;
    public:
        FloatProperty(
            const String& name,
            const String& label,
            wxPGProperty* parentProperty,
            wxPropertyGrid& grid,
            const NexusHistory& nexusHistory,
            UI& ui);
        FloatProperty(FloatProperty&& arg) noexcept = default;
    protected:
        [[nodiscard]] DataT ValueFromProperty() const override;
        [[nodiscard]] wxVariant VariantFromData(const DataT& data) override;
    private:
        wxFloatProperty* property = nullptr;
    };

    template<class T>
    FloatProperty<T>::FloatProperty(
        const String& name,
        const String& label,
        wxPGProperty* parentProperty,
        wxPropertyGrid& grid,
        const NexusHistory& nexusHistory,
        UI& ui)
        :
        TerminalProperty<T>(
            label,
            new wxFloatProperty(label, PropertyName(name, parentProperty)),
            parentProperty,
            grid,
            nexusHistory,
            ui)
    {
        using NumericLimitsT = std::numeric_limits<T>;
        property = static_cast<wxFloatProperty*>(WxProperty());
    }

    template<class T>
    auto FloatProperty<T>::ValueFromProperty() const -> DataT
    {
        return property->GetValue().GetAny().As<DataT>();
    }

    template<class T>
    wxVariant FloatProperty<T>::VariantFromData(const DataT& data)
    {
        return data;
    }

    template<>
    class Property<float> final : public FloatProperty<float>
    {
    public:
        using FloatProperty<float>::FloatProperty;
    };

    template<>
    class Property<double> final : public FloatProperty<double>
    {
    public:
        using FloatProperty<double>::FloatProperty;
    };

    template<>
    class Nexus<float> final : public NexusCommon<float>
    {
    public:
        using NexusCommon<float>::NexusCommon;
    };

    template<>
    class Nexus<double> final : public NexusCommon<double>
    {
    public:
        using NexusCommon<double>::NexusCommon;
    };
}