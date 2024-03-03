#include "BoundsData.h"

namespace Creation::Editing
{
    namespace Data
    {
        Atmos::Spatial::Bounds Bounds::Build(Build::Context& context) const
        {
            Atmos::Spatial::Bounds built;
            built.Position(position);
            built.Scalers(scalers);
            built.Rotation(rotation);
            return built;
        }
    }

    Property<Data::Bounds>::Property(
        const String& name,
        const String& label,
        wxPGProperty* parentProperty,
        wxPropertyGrid& grid,
        const NexusHistory& nexusHistory,
        UI& ui)
        :
        CategoryProperty(name, label, parentProperty, grid, ui),
        position("Position", "Position", WxProperty(), grid, nexusHistory, ui),
        scalers("Scalers", "Scalers", WxProperty(), grid, nexusHistory, ui),
        rotation("Rotation", "Rotation", WxProperty(), grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    Property<Data::Bounds>::Property(Property&& arg) noexcept :
        CategoryProperty(std::move(arg)),
        position(std::move(arg.position)),
        scalers(std::move(arg.scalers)),
        rotation(std::move(arg.rotation))
    {
        SetupProperties();
    }

    void Property<Data::Bounds>::SetupProperties()
    {
        Auto(position, &Nexus::position);
        Auto(scalers, &Nexus::scalers);
        Auto(rotation, &Nexus::rotation);
    }

    Nexus<Data::Bounds>::Nexus(
        DataT& data,
        NexusNode* parent,
        const NexusHistory& nexusHistory,
        UI& ui,
        Arca::Reliquary& reliquary,
        const String& label)
        :
        NexusCommon(data, parent, nexusHistory, ui, reliquary, label),
        position(data.position, this, nexusHistory, ui, reliquary, "Position"),
        scalers(data.scalers, this, nexusHistory, ui, reliquary, "Scalers"),
        rotation(data.rotation, this, nexusHistory, ui, reliquary, "Rotation")
    {
        SetupChildren();
    }

    Nexus<Data::Bounds>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        NexusCommon(std::move(arg), parent),
        position(std::move(arg.position), this),
        scalers(std::move(arg.scalers), this),
        rotation(std::move(arg.rotation), this)
    {
        SetupChildren();
    }

    void Nexus<Data::Bounds>::SetupChildren()
    {
        autoHandler.Auto(*this, position, &DataT::position);
        autoHandler.Auto(*this, scalers, &DataT::scalers);
        autoHandler.Auto(*this, rotation, &DataT::rotation);
    }
}