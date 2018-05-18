#pragma once

#include "DataIncludes.h"
#include <wx/propgrid/props.h>

namespace Creation::Editing
{
    template<>
    class Property<bool> final : public TerminalProperty<bool>
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
        wxBoolProperty* property = nullptr;
    };

    template<>
    class Nexus<bool> final : public NexusCommon<bool>
    {
    public:
        using NexusCommon<bool>::NexusCommon;
    };
}