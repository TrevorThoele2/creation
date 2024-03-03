#pragma once

#include "DataIncludes.h"
#include <wx/propgrid/props.h>

#include "EnumDescriptors.h"

namespace Creation::Editing
{
    template<class T>
    struct EnumTraits;

    template<class T>
    class EnumProperty : public TerminalProperty<T>
    {
    private:
        using BaseT = TerminalProperty<T>;
    public:
        using DataT = typename BaseT::DataT;
        using DataSet = typename BaseT::NexusSet;

        using BaseT::WxProperty;
    public:
        EnumProperty(
            const String& name,
            const String& label,
            wxPGProperty* parentProperty,
            wxPropertyGrid& grid,
            const NexusHistory& nexusHistory,
            UI& ui);
    protected:
        [[nodiscard]] DataT ValueFromProperty() const override;
        [[nodiscard]] wxVariant VariantFromData(const DataT& data) override;
    private:
        wxEnumProperty* property = nullptr;
    };

    template<class T>
    EnumProperty<T>::EnumProperty(
        const String& name,
        const String& label,
        wxPGProperty* parentProperty,
        wxPropertyGrid& grid,
        const NexusHistory& nexusHistory,
        UI& ui)
        :
        TerminalProperty<T>(
            label,
            new wxEnumProperty(
                label,
                PropertyName(name, parentProperty),
                EnumTraits<T>::descriptors.Names(),
                EnumTraits<T>::descriptors.Values()),
            parentProperty,
            grid,
            nexusHistory,
            ui)
    {
        property = static_cast<wxEnumProperty*>(WxProperty());
    }

    template<class T>
    auto EnumProperty<T>::ValueFromProperty() const -> DataT
    {
        return static_cast<T>(property->GetValue().GetLong());
    }

    template<class T>
    wxVariant EnumProperty<T>::VariantFromData(const DataT& data)
    {
        return static_cast<long>(data);
    }
}