#include "Size3DData.h"

namespace Creation::Editing
{
    Property<Atmos::Spatial::Size3D>::Property(
        const String& name,
        const String& label,
        wxPGProperty* parentProperty,
        wxPropertyGrid& grid,
        const NexusHistory& nexusHistory,
        UI& ui)
        :
        CategoryProperty(name, label, parentProperty, grid, ui),
        width("Width", "Width", WxProperty(), grid, nexusHistory, ui),
        height("Height", "Height", WxProperty(), grid, nexusHistory, ui),
        depth("Depth", "Depth", WxProperty(), grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    Property<Atmos::Spatial::Size3D>::Property(Property&& arg) noexcept :
        CategoryProperty(std::move(arg)),
        width(std::move(arg.width)),
        height(std::move(arg.height)),
        depth(std::move(arg.depth))
    {
        SetupProperties();
    }

    void Property<Atmos::Spatial::Size3D>::SetupProperties()
    {
        Auto(width, &Nexus::width);
        Auto(height, &Nexus::height);
        Auto(depth, &Nexus::depth);
    }

    Nexus<Atmos::Spatial::Size3D>::Nexus(
        DataT& data,
        NexusNode* parent,
        const NexusHistory& nexusHistory,
        UI& ui,
        Arca::Reliquary& reliquary,
        const String& label)
        :
        NexusCommon(data, parent, nexusHistory, ui, reliquary, label),
        width(data.width, this, nexusHistory, ui, reliquary, "Width"),
        height(data.height, this, nexusHistory, ui, reliquary, "Height"),
        depth(data.depth, this, nexusHistory, ui, reliquary, "Depth")
    {
        SetupChildren();
    }

    Nexus<Atmos::Spatial::Size3D>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        NexusCommon(std::move(arg), parent),
        width(std::move(arg.width), this),
        height(std::move(arg.height), this),
        depth(std::move(arg.depth), this)
    {
        SetupChildren();
    }

    void Nexus<Atmos::Spatial::Size3D>::SetupChildren()
    {
        autoHandler.Auto(*this, width, &DataT::width);
        autoHandler.Auto(*this, height, &DataT::height);
        autoHandler.Auto(*this, depth, &DataT::depth);
    }
}