#include "Scalers2DData.h"

namespace Creation::Editing
{
    Property<Atmos::Spatial::Scalers2D>::Property(
        const String& name,
        const String& label,
        wxPGProperty* parentProperty,
        wxPropertyGrid& grid,
        const NexusHistory& nexusHistory,
        UI& ui)
        :
        CategoryProperty(name, label, parentProperty, grid, ui),
        x("X", "X", WxProperty(), grid, nexusHistory, ui),
        y("Y", "Y", WxProperty(), grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    Property<Atmos::Spatial::Scalers2D>::Property(Property&& arg) noexcept :
        CategoryProperty(std::move(arg)),
        x(std::move(arg.x)),
        y(std::move(arg.y))
    {
        SetupProperties();
    }

    void Property<Atmos::Spatial::Scalers2D>::SetupProperties()
    {
        Auto(x, &Nexus::x);
        Auto(y, &Nexus::y);
    }

    Nexus<Atmos::Spatial::Scalers2D>::Nexus(
        DataT& data,
        NexusNode* parent,
        const NexusHistory& nexusHistory,
        UI& ui,
        Arca::Reliquary& reliquary,
        const String& label)
        :
        NexusCommon(data, parent, nexusHistory, ui, reliquary, label),
        x(data.x, this, nexusHistory, ui, reliquary, "X"),
        y(data.y, this, nexusHistory, ui, reliquary, "Y")
    {
        SetupChildren();
    }

    Nexus<Atmos::Spatial::Scalers2D>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        NexusCommon(std::move(arg), parent),
        x(std::move(arg.x), this),
        y(std::move(arg.y), this)
    {
        SetupChildren();
    }

    void Nexus<Atmos::Spatial::Scalers2D>::SetupChildren()
    {
        autoHandler.Auto(*this, x, &DataT::x);
        autoHandler.Auto(*this, y, &DataT::y);
    }
}