#include "RenderCoreData.h"

#include "AtmosRender.h"
#include <Atmos/FindAssetByName.h>

namespace Creation::Editing
{
    namespace Data
    {
        RenderCore::RenderCore() : material(atmosDefaultImageMaterialName)
        {}

        Atmos::Render::RenderCore RenderCore::Build(Build::Context& context) const
        {
            Atmos::Render::RenderCore built;
            built.color = color;
            built.material = context.reliquary.Do(Atmos::Asset::FindByName<Atmos::Asset::Material>(material));
            return built;
        }
    }

    Property<Data::RenderCore>::Property(
        const String& name,
        const String& label,
        wxPGProperty* parentProperty,
        wxPropertyGrid& grid,
        const NexusHistory& nexusHistory,
        UI& ui)
        :
        CategoryProperty(name, label, parentProperty, grid, ui),
        color("Color", "Color", WxProperty(), grid, nexusHistory, ui),
        material("Material", "Material", WxProperty(), grid, nexusHistory, ui, "Material", [this]() { return AllMaterialAssetNames(OwningUI()); })
    {
        SetupProperties();
    }

    Property<Data::RenderCore>::Property(Property&& arg) noexcept :
        CategoryProperty(std::move(arg)),
        color(std::move(arg.color)),
        material(std::move(arg.material))
    {
        SetupProperties();
    }

    void Property<Data::RenderCore>::SetupProperties()
    {
        Auto(color, &Nexus::color);
        Auto(material, &Nexus::material);
    }

    Nexus<Data::RenderCore>::Nexus(
        DataT& data,
        NexusNode* parent,
        const NexusHistory& nexusHistory,
        UI& ui,
        Arca::Reliquary& reliquary,
        const String& label)
        :
        NexusCommon(data, parent, nexusHistory, ui, reliquary, label),
        color(data.color, this, nexusHistory, ui, reliquary, "Color"),
        material(data.material, this, nexusHistory, ui, reliquary, "Material")
    {
        SetupChildren();
    }

    Nexus<Data::RenderCore>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        NexusCommon(std::move(arg), parent),
        color(std::move(arg.color), this),
        material(std::move(arg.material), this)
    {
        SetupChildren();
    }

    void Nexus<Data::RenderCore>::SetupChildren()
    {
        autoHandler.Auto(*this, color, &DataT::color);
        autoHandler.Auto(*this, material, &DataT::material);
    }
}