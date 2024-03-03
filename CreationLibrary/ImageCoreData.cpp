#include "ImageCoreData.h"

#include "AtmosRender.h"
#include <Atmos/FindAssetByName.h>

namespace Creation::Editing
{
    namespace Data
    {
        Atmos::Render::ImageCore ImageCore::Build(Build::Context& context) const
        {
            Atmos::Render::ImageCore built;
            built.asset = context.reliquary.Do(Atmos::Asset::FindByName<Atmos::Asset::Image>(asset));
            built.assetIndex = assetIndex;
            return built;
        }
    }

    Property<Data::ImageCore>::Property(
        const String& name,
        const String& label,
        wxPGProperty* parentProperty,
        wxPropertyGrid& grid,
        const NexusHistory& nexusHistory,
        UI& ui)
        :
        CategoryProperty(name, label, parentProperty, grid, ui),
        asset("Asset", "Asset", WxProperty(), grid, nexusHistory, ui, "Image", [this]() { return AllImageAssetNames(OwningUI()); }),
        assetIndex("AssetIndex", "Asset Index", WxProperty(), grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    Property<Data::ImageCore>::Property(Property&& arg) noexcept :
        CategoryProperty(std::move(arg)),
        asset(std::move(arg.asset)),
        assetIndex(std::move(arg.assetIndex))
    {
        SetupProperties();
    }

    void Property<Data::ImageCore>::SetupProperties()
    {
        Auto(asset, &Nexus::asset);
        Auto(assetIndex, &Nexus::assetIndex);
    }

    Nexus<Data::ImageCore>::Nexus(
        DataT& data,
        NexusNode* parent,
        const NexusHistory& nexusHistory,
        UI& ui,
        Arca::Reliquary& reliquary,
        const String& label)
        :
        NexusCommon(data, parent, nexusHistory, ui, reliquary, label),
        asset(data.asset, this, nexusHistory, ui, reliquary, "Asset"),
        assetIndex(data.assetIndex, this, nexusHistory, ui, reliquary, "Asset Index")
    {
        SetupChildren();
    }

    Nexus<Data::ImageCore>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        NexusCommon(std::move(arg), parent),
        asset(std::move(arg.asset), this),
        assetIndex(std::move(arg.assetIndex), this)
    {
        SetupChildren();
    }

    void Nexus<Data::ImageCore>::SetupChildren()
    {
        autoHandler.Auto(*this, asset, &DataT::asset);
        autoHandler.Auto(*this, assetIndex, &DataT::assetIndex);
    }
}