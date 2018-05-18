#include "ColorData.h"

#include <Atmos/StringUtility.h>

namespace Creation::Editing
{
    Property<Atmos::Render::Color>::Property(
        const String& name,
        const String& label,
        wxPGProperty* parentProperty,
        wxPropertyGrid& grid,
        const NexusHistory& nexusHistory,
        UI& ui)
        :
        CategoryProperty(name, label, parentProperty, grid, ui),
        alpha("Alpha", "Alpha", WxProperty(), grid, nexusHistory, ui),
        red("Red", "Red", WxProperty(), grid, nexusHistory, ui),
        green("Green", "Green", WxProperty(), grid, nexusHistory, ui),
        blue("Blue", "Blue", WxProperty(), grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    Property<Atmos::Render::Color>::Property(Property&& arg) noexcept :
        CategoryProperty(std::move(arg)),
        alpha(std::move(arg.alpha)),
        red(std::move(arg.red)),
        green(std::move(arg.green)),
        blue(std::move(arg.blue))
    {
        SetupProperties();
    }

    void Property<Atmos::Render::Color>::SetupProperties()
    {
        Auto(alpha, &Nexus::alpha);
        Auto(red, &Nexus::red);
        Auto(green, &Nexus::green);
        Auto(blue, &Nexus::blue);
    }

    Nexus<Atmos::Render::Color>::Nexus(
        DataT& data,
        NexusNode* parent,
        const NexusHistory& nexusHistory,
        UI& ui,
        Arca::Reliquary& reliquary,
        const String& label)
        :
        NexusCommon(data, parent, nexusHistory, ui, reliquary, label),
        alpha(data.alpha, this, nexusHistory, ui, reliquary, "Alpha"),
        red(data.red, this, nexusHistory, ui, reliquary, "Red"),
        green(data.green, this, nexusHistory, ui, reliquary, "Green"),
        blue(data.blue, this, nexusHistory, ui, reliquary, "Blue")
    {
        SetupChildren();
    }

    Nexus<Atmos::Render::Color>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        NexusCommon(std::move(arg), parent),
        alpha(std::move(arg.alpha), this),
        red(std::move(arg.red), this),
        green(std::move(arg.green), this),
        blue(std::move(arg.blue), this)
    {
        SetupChildren();
    }

    void Nexus<Atmos::Render::Color>::SetupChildren()
    {
        autoHandler.Auto(*this, alpha, &DataT::alpha);
        autoHandler.Auto(*this, red, &DataT::red);
        autoHandler.Auto(*this, green, &DataT::green);
        autoHandler.Auto(*this, blue, &DataT::blue);
    }
}