#include "ScriptData.h"

#include <Atmos/Script.h>
#include <Atmos/ScriptAsset.h>
#include <Atmos/FindAssetByName.h>
#include <Arca/Create.h>

namespace Creation::Editing
{
    namespace Data
    {
        Arca::Index<Atmos::Scripting::Script> Script::Build(Build::Context& context) const
        {
            Atmos::Scripting::Parameters builtParameters;
            builtParameters.reserve(parameters.size());
            for (auto& parameter : parameters)
                builtParameters.push_back(parameter.Build(context));
            const auto asset = context.reliquary.Do(Atmos::Asset::FindByName<Atmos::Asset::Script>(assetName));
            return context.reliquary.Do(Arca::Create<Atmos::Scripting::Script>(asset, executeName, builtParameters));
        }
    }

    Property<Data::Script>::Property(
        const String& name,
        const String& label,
        wxPGProperty* parentProperty,
        wxPropertyGrid& grid,
        const NexusHistory& nexusHistory,
        UI& ui)
        :
        CategoryProperty(name, label, parentProperty, grid, ui),
        assetName("Asset Name", "Asset Name", WxProperty(), grid, nexusHistory, ui, "Script", [&ui]() { return AllScriptAssetNames(ui); }),
        executeName("Execute Name", "Execute Name", WxProperty(), grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    Property<Data::Script>::Property(Property&& arg) noexcept :
        CategoryProperty(std::move(arg)),
        assetName(std::move(arg.assetName)),
        executeName(std::move(arg.executeName))
    {
        SetupProperties();
    }

    void Property<Data::Script>::SetupProperties()
    {
        Auto(assetName, &Nexus::assetName);
        Auto(executeName, &Nexus::executeName);
    }

    NexusBatch<Data::Script>::NexusBatch(
        wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui)
        :
        NexusBatchCommon(grid),
        assetName("AssetName", "Asset Name", nullptr, grid, nexusHistory, ui, "Script", [&ui]() { return AllScriptAssetNames(ui); }),
        executeName("ExecuteName", "Execute Name", nullptr, grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    NexusBatch<Data::Script>::NexusBatch(NexusBatch&& arg) noexcept :
        NexusBatchCommon(std::move(arg)),
        assetName(std::move(arg.assetName)),
        executeName(std::move(arg.executeName))
    {
        SetupProperties();
    }

    void NexusBatch<Data::Script>::SetupProperties()
    {
        Auto(assetName, &Nexus::assetName);
        Auto(executeName, &Nexus::executeName);
    }

    Nexus<Data::Script>::Nexus(
        DataT& data,
        NexusNode* parent,
        NexusHistory nexusHistory,
        UI& ui,
        Arca::Reliquary& reliquary,
        const String& label)
        :
        EditableNexusCommon(
            data,
            parent,
            nexusHistory,
            ui,
            reliquary,
            label),
        assetName(data.assetName, this, nexusHistory, ui, reliquary, "Asset Name"),
        executeName(data.executeName, this, nexusHistory, ui, reliquary, "Execute Name"),
        parameters(data.parameters, this, nexusHistory, ui, reliquary, "Parameters")
    {
        SetupChildren();
    }

    Nexus<Data::Script>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        EditableNexusCommon(std::move(arg), parent),
        assetName(std::move(arg.assetName), this),
        executeName(std::move(arg.executeName), this),
        parameters(std::move(arg.parameters), this)
    {
        SetupChildren();
    }

    void Nexus<Data::Script>::SetupChildren()
    {
        autoHandler.Auto(*this, assetName, &DataT::assetName);
        autoHandler.Auto(*this, executeName, &DataT::executeName);
        autoHandler.Auto(*this, parameters, &DataT::parameters);
    }
}