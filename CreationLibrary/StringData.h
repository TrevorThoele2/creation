#pragma once

#include "DataIncludes.h"
#include "String.h"

#include <wx/propgrid/props.h>

namespace Creation::Editing
{
    template<>
    class Property<String> final : public TerminalProperty<String>
    {
    public:
        Property(
            const String& name,
            const String& label,
            wxPGProperty* parentProperty,
            wxPropertyGrid& grid,
            const NexusHistory& nexusHistory,
            UI& ui);
        Property(Property&& arg) noexcept = default;
    protected:
        [[nodiscard]] DataT ValueFromProperty() const override;
        [[nodiscard]] wxVariant VariantFromData(const DataT& data) override;
    private:
        wxStringProperty* property = nullptr;
    };

    template<>
    class Nexus<String> final : public NexusCommon<String>
    {
    public:
        using NexusCommon<String>::NexusCommon;
    };
}