#include "ActionAssetData.h"

#include <Arca/Create.h>

namespace Creation::Editing
{
    namespace Data
    {
        void ActionAsset::Build(Build::Context& context) const
        {
            Atmos::Asset::Action::Modifiers defaultModifierKeys;
            for (auto& [key] : this->defaultModifierKeys)
                defaultModifierKeys.emplace(key);

            context.reliquary.Do(Arca::Create<Atmos::Asset::Action> {
                name,
                defaultKey,
                defaultModifierKeys });
        }
    }

    NexusBatch<Data::ActionAsset>::NexusBatch(wxPropertyGrid& grid, NexusHistory nexusHistory, UI& ui) :
        NexusBatchCommon(grid),
        name("Name", "Name", nullptr, grid, nexusHistory, ui),
        defaultKey("DefaultKey", "Default Key", nullptr, grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    NexusBatch<Data::ActionAsset>::NexusBatch(NexusBatch&& arg) noexcept :
        NexusBatchCommon(std::move(arg)),
        name(std::move(arg.name)),
        defaultKey(std::move(arg.defaultKey))
    {
        SetupProperties();
    }

    void NexusBatch<Data::ActionAsset>::SetupProperties()
    {
        Auto(name, &Nexus::name);
        Auto(defaultKey, &Nexus::defaultKey);
    }

    Nexus<Data::ActionAsset>::Nexus(
        DataT& data, NexusNode* parent, NexusHistory nexusHistory, UI& ui, Arca::Reliquary& reliquary)
        :
        EditableAssetNexusCommon(
            data,
            parent,
            nexusHistory,
            ui,
            reliquary,
            CalculateLabel(data)),
        name(data.name, this, nexusHistory, ui, reliquary, "Name"),
        defaultKey(data.defaultKey, this, nexusHistory, ui, reliquary, "Default Key"),
        defaultModifierKeys(data.defaultModifierKeys, this, nexusHistory, ui, reliquary, "Default Modifier Keys")
    {
        SetupChildren();
    }

    Nexus<Data::ActionAsset>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        EditableAssetNexusCommon(std::move(arg), parent),
        name(std::move(arg.name), this),
        defaultKey(std::move(arg.defaultKey), this),
        defaultModifierKeys(std::move(arg.defaultModifierKeys), this)
    {
        SetupChildren();
    }

    String Nexus<Data::ActionAsset>::CalculateLabel(const DataT& data) const
    {
        const auto label = File::Path(data.name).filename().replace_extension().string();
        return !label.empty() ? label : "Action Asset";
    }

    void Nexus<Data::ActionAsset>::SetupChildren()
    {
        autoHandler.Auto(*this, name, &DataT::name);
        autoHandler.Auto(*this, defaultKey, &DataT::defaultKey);
        autoHandler.Auto(*this, defaultModifierKeys, &DataT::defaultModifierKeys);

        eventConnections =
        {
            name.onDataChanged.Subscribe([this](const File::Path&) { OnLabelChanged(); })
        };
    }
}