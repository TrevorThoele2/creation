#include "StringData.h"

namespace Creation::Editing
{
    Property<String>::Property(
        const String& name,
        const String& label,
        wxPGProperty* parentProperty,
        wxPropertyGrid& grid,
        const NexusHistory& nexusHistory,
        UI& ui)
        :
        TerminalProperty(
            label,
            new wxStringProperty(label, PropertyName(name, parentProperty)),
            parentProperty,
            grid,
            nexusHistory,
            ui)
    {
        property = static_cast<wxStringProperty*>(WxProperty());
    }

    auto Property<String>::ValueFromProperty() const -> DataT
    {
        return String(property->GetValueAsString());
    }

    wxVariant Property<String>::VariantFromData(const DataT& data)
    {
        return data;
    }
}