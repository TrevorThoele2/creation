#include "BoolData.h"

namespace Creation::Editing
{
    Property<bool>::Property(
        const String& name,
        const String& label,
        wxPGProperty* parentProperty,
        wxPropertyGrid& grid,
        const NexusHistory& nexusHistory,
        UI& ui)
        :
        TerminalProperty(
            label,
            new wxBoolProperty(label, PropertyName(name, parentProperty)),
            parentProperty,
            grid,
            nexusHistory,
            ui)
    {
        property = static_cast<wxBoolProperty*>(WxProperty());
    }

    auto Property<bool>::ValueFromProperty() const -> DataT
    {
        return property->GetValue().GetAny().As<bool>();
    }

    wxVariant Property<bool>::VariantFromData(const DataT& data)
    {
        return data;
    }
}