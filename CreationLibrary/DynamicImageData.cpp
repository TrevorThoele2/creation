#include "DynamicImageData.h"

#include <Arca/Create.h>

namespace Creation::Editing
{
    namespace Data
    {
        void DynamicImage::Build(Build::Context& context) const
        {
            auto builtRenderCore = renderCore.Build(context);
            auto builtCore = imageCore.Build(context);
            auto builtBounds = bounds.Build(context);

            const auto asset = builtCore.asset;
            if (asset)
                builtBounds.BaseSize(asset->SliceSize());

            context.reliquary.Do(Arca::Create<Atmos::Render::DynamicImage> {
                builtCore.asset,
                builtCore.assetIndex,
                builtRenderCore.material,
                builtRenderCore.color,
                builtBounds.Position(),
                builtBounds.Scalers(),
                builtBounds.Rotation() });
        }
    }

    Property<Data::DynamicImage>::Property(
        const String& name,
        const String& label,
        wxPGProperty* parentProperty,
        wxPropertyGrid& grid,
        const NexusHistory& nexusHistory,
        UI& ui)
        :
        CategoryProperty(name, label, parentProperty, grid, ui),
        renderCore("Render Core", "Render Core", WxProperty(), grid, nexusHistory, ui),
        imageCore("Core", "Core", WxProperty(), grid, nexusHistory, ui),
        bounds("Bounds", "Bounds", WxProperty(), grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    Property<Data::DynamicImage>::Property(Property && arg) noexcept :
        CategoryProperty(std::move(arg)),
        renderCore(std::move(arg.renderCore)),
        imageCore(std::move(arg.imageCore)),
        bounds(std::move(arg.bounds))
    {
        SetupProperties();
    }

    void Property<Data::DynamicImage>::SetupProperties()
    {
        Auto(renderCore, &Nexus::renderCore);
        Auto(imageCore, &Nexus::imageCore);
        Auto(bounds, &Nexus::bounds);
    }

    Nexus<Data::DynamicImage>::Nexus(
        DataT& data,
        NexusNode* parent,
        const NexusHistory& nexusHistory,
        UI& ui,
        Arca::Reliquary& reliquary,
        const String& label)
        :
        NexusCommon(data, parent, nexusHistory, ui, reliquary, label),
        renderCore(data.renderCore, this, nexusHistory, ui, reliquary, "Render Core"),
        imageCore(data.imageCore, this, nexusHistory, ui, reliquary, "Core"),
        bounds(data.bounds, this, nexusHistory, ui, reliquary, "Bounds")
    {
        SetupChildren();
    }

    Nexus<Data::DynamicImage>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        NexusCommon(std::move(arg), parent),
        renderCore(std::move(arg.renderCore), this),
        imageCore(std::move(arg.imageCore), this),
        bounds(std::move(arg.bounds), this)
    {
        SetupChildren();
    }

    void Nexus<Data::DynamicImage>::SetupChildren()
    {
        autoHandler.Auto(*this, renderCore, &DataT::renderCore);
        autoHandler.Auto(*this, imageCore, &DataT::imageCore);
        autoHandler.Auto(*this, bounds, &DataT::bounds);
    }
}