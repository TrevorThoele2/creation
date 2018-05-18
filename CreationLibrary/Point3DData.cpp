#include "Point3DData.h"

namespace Creation::Editing
{
    Property<Atmos::Spatial::Point3D>::Property(
        const String& name,
        const String& label,
        wxPGProperty* parentProperty,
        wxPropertyGrid& grid,
        const NexusHistory& nexusHistory,
        UI& ui)
        :
        CategoryProperty(name, label, parentProperty, grid, ui),
        x("X", "X", WxProperty(), grid, nexusHistory, ui),
        y("Y", "Y", WxProperty(), grid, nexusHistory, ui),
        z("Z", "Z", WxProperty(), grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    Property<Atmos::Spatial::Point3D>::Property(Property&& arg) noexcept :
        CategoryProperty(std::move(arg)),
        x(std::move(arg.x)),
        y(std::move(arg.y)),
        z(std::move(arg.z))
    {
        SetupProperties();
    }

    void Property<Atmos::Spatial::Point3D>::SetupProperties()
    {
        Auto(x, &Nexus::x);
        Auto(y, &Nexus::y);
        Auto(z, &Nexus::z);
    }

    Nexus<Atmos::Spatial::Point3D>::Nexus(
        DataT& data,
        NexusNode* parent,
        const NexusHistory& nexusHistory,
        UI& ui,
        Arca::Reliquary& reliquary,
        const String& label)
        :
        NexusCommon(data, parent, nexusHistory, ui, reliquary, label),
        x(data.x, this, nexusHistory, ui, reliquary, "X"),
        y(data.y, this, nexusHistory, ui, reliquary, "Y"),
        z(data.z, this, nexusHistory, ui, reliquary, "Z")
    {
        SetupChildren();
    }

    Nexus<Atmos::Spatial::Point3D>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        NexusCommon(std::move(arg), parent),
        x(std::move(arg.x), this),
        y(std::move(arg.y), this),
        z(std::move(arg.z), this)
    {
        SetupChildren();
    }

    void Nexus<Atmos::Spatial::Point3D>::SetupChildren()
    {
        autoHandler.Auto(*this, x, &DataT::x);
        autoHandler.Auto(*this, y, &DataT::y);
        autoHandler.Auto(*this, z, &DataT::z);
    }
}