#include "MaterialAssetData.h"

#include <Arca/Create.h>
#include <Arca/Destroy.h>
#include <Inscription/ListScribe.h>

namespace Creation::Editing
{
    namespace Data
    {
        MaterialAsset::MaterialAsset(const String& name, const std::list<MaterialAssetPass>& passes) :
            name(name), passes(passes)
        {}
    }

    Arca::Index<Atmos::Asset::Material> CreateAtmos(Data::MaterialAsset data, Arca::Reliquary& reliquary)
    {
        const auto findShader = [&reliquary](String name)
        {
            return reliquary.Do(Atmos::Asset::FindByName<Atmos::Asset::Shader> { name });
        };

        std::vector<Atmos::Asset::Material::Pass> createdPasses;
        for (auto& pass : data.passes)
        {
            const auto vertexShader = findShader(pass.vertexShader);
            const auto fragmentShader = findShader(pass.fragmentShader);
            
            if (vertexShader || fragmentShader)
                createdPasses.emplace_back(vertexShader, fragmentShader);
        }

        if (createdPasses.empty())
            return {};

        auto created = reliquary.Do(Arca::Create<Atmos::Asset::Material> { data.name, createdPasses });
        return created;
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
        name("Name", "Name", nullptr, grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    NexusBatch<Data::MaterialAsset>::NexusBatch(NexusBatch&& arg) noexcept :
        NexusBatchCommon(std::move(arg)),
        name(std::move(arg.name))
    {
        SetupProperties();
    }

    void NexusBatch<Data::MaterialAsset>::SetupProperties()
    {
        Auto(name, &Nexus::name);
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
        passes(data.passes, this, nexusHistory, ui, reliquary, "Passes", []() { return "Pass"; })
    {
        SetupChildren();
    }

    Nexus<Data::MaterialAsset>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        EditableAssetNexusCommon(std::move(arg), parent),
        name(std::move(arg.name), this),
        passes(std::move(arg.passes), this)
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
        autoHandler.Auto(*this, passes, &DataT::passes);

        eventConnections =
        {
            name.onDataChanged.Subscribe([this](const String&) { OnLabelChanged(); })
        };
    }
}