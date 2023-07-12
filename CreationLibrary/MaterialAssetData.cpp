#include "MaterialAssetData.h"

#include <Arca/Create.h>
#include <Arca/Destroy.h>
#include <Inscription/ListScribe.h>

namespace Creation::Editing
{
    namespace Data
    {
        MaterialAsset::MaterialAsset(const String& name, const String& asset, const String& executeName, const std::list<Variant>& parameters) :
            name(name), asset(asset), executeName(executeName), parameters(parameters)
        {}
    }

    Arca::Index<Atmos::Asset::Material> CreateAtmos(Data::MaterialAsset data, Arca::Reliquary& reliquary)
    {
        Atmos::Scripting::Parameters builtParameters;
        builtParameters.reserve(data.parameters.size());
        for (auto& parameter : data.parameters)
            builtParameters.push_back(parameter.Build());
        const auto asset = reliquary.Do(Atmos::Asset::FindByName<Atmos::Asset::Script>(data.asset));
        return reliquary.Do(Arca::Create<Atmos::Asset::Material>(data.name, asset, data.executeName, builtParameters));
    }

    namespace Data
    {
        void MaterialAsset::Build(Build::Context& context) const
        {
            CreateAtmos(*this, context.reliquary);
        }
    }

    NexusBatch<Data::MaterialAsset>::NexusBatch(
        wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui)
        :
        NexusBatchCommon<Data::MaterialAsset>(grid),
        name("Name", "Name", nullptr, grid, nexusHistory, ui),
        asset("Script Asset", "Script Asset", nullptr, grid, nexusHistory, ui, "Script", [&ui]() { return AllScriptAssetNames(ui); }),
        executeName("Execute Name", "Execute Name", nullptr, grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    NexusBatch<Data::MaterialAsset>::NexusBatch(NexusBatch&& arg) noexcept :
        NexusBatchCommon(std::move(arg)),
        name(std::move(arg.name)),
        asset(std::move(arg.asset)),
        executeName(std::move(arg.executeName))
    {
        SetupProperties();
    }

    void NexusBatch<Data::MaterialAsset>::SetupProperties()
    {
        Auto(name, &Nexus::name);
        Auto(executeName, &Nexus::executeName);
    }

    WorldElement<Data::MaterialAsset>::WorldElement(Nexus& nexus, Arca::Reliquary& reliquary) :
        WorldElementCommon<Data::MaterialAsset>(nexus, reliquary)
    {
        object = CreateObject(nexus.CurrentData());
    }

    WorldElement<Data::MaterialAsset>::~WorldElement()
    {
        DestroyObject(object);
    }

    void WorldElement<Data::MaterialAsset>::OnDataChanged(DataT data)
    {
        DestroyObject(object);
        object = CreateObject(data);
    }

    auto WorldElement<Data::MaterialAsset>::CreateObject(DataT data) -> Index
    {
        return CreateAtmos(data, Reliquary());
    }

    void WorldElement<Data::MaterialAsset>::DestroyObject(Index index)
    {
        Reliquary().Do(Arca::Destroy<Object>{ index.ID() });
    }

    Nexus<Data::MaterialAsset>::Nexus(
        DataT& data,
        NexusNode* parent,
        NexusHistory nexusHistory,
        UI& ui,
        Arca::Reliquary& reliquary)
        :
        EditableAssetNexusCommon<Data::MaterialAsset>(
            data,
            parent,
            nexusHistory,
            ui,
            reliquary,
            CalculateLabel(data)),
        name(data.name, this, nexusHistory, ui, reliquary, "Name"),
        executeName(data.executeName, this, nexusHistory, ui, reliquary, "Execute Name"),
        parameters(data.parameters, this, nexusHistory, ui, reliquary, "Parameters")
    {
        SetupChildren();
    }

    Nexus<Data::MaterialAsset>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        EditableAssetNexusCommon(std::move(arg), parent),
        name(std::move(arg.name), this),
        executeName(std::move(arg.executeName), this),
        parameters(std::move(arg.parameters), this)
    {
        SetupChildren();
    }

    String Nexus<Data::MaterialAsset>::CalculateLabel(const DataT& data) const
    {
        const auto label = data.name;
        return !label.empty() ? label : "Material Asset";
    }

    void Nexus<Data::MaterialAsset>::SetupChildren()
    {
        autoHandler.Auto(*this, name, &DataT::name);
        autoHandler.Auto(*this, executeName, &DataT::executeName);
        autoHandler.Auto(*this, parameters, &DataT::parameters);

        eventConnections =
        {
            name.onDataChanged.Subscribe([this](const String&) { OnLabelChanged(); })
        };
    }
}