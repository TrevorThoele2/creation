#pragma once

#include "AssetData.h"
#include <Atmos/ActionAsset.h>

#include "StringData.h"
#include "KeyData.h"
#include "ListData.h"

#include <Inscription/FilePathScribe.h>

namespace Creation::Editing
{
    namespace Data
    {
        class ActionAsset
        {
        public:
            String name;
            Atmos::Input::Key defaultKey;
            std::list<Data::ModifierKey> defaultModifierKeys;
        public:
            ActionAsset() = default;
            ActionAsset(const ActionAsset& arg) = default;
            ActionAsset& operator=(const ActionAsset& arg) = default;

            void Build(Build::Context& context) const;
        private:
            INSCRIPTION_ACCESS;
        };
    }

    template<>
    class NexusBatch<Data::ActionAsset> final : public NexusBatchCommon<Data::ActionAsset>
    {
    public:
        Property<String> name;
        Property<Atmos::Input::Key> defaultKey;
    public:
        NexusBatch(wxPropertyGrid& grid, NexusHistory nexusHistory, UI& ui);
        NexusBatch(NexusBatch&& arg) noexcept;
    private:
        void SetupProperties();
    };

    template<>
    class Nexus<Data::ActionAsset> final : public EditableAssetNexusCommon<Data::ActionAsset>
    {
    public:
        Nexus<String> name;
        Nexus<Atmos::Input::Key> defaultKey;
        Nexus<std::list<Data::ModifierKey>> defaultModifierKeys;
    public:
        Nexus(
            DataT& data,
            NexusNode* parent,
            NexusHistory nexusHistory,
            UI& ui,
            Arca::Reliquary& reliquary);
        Nexus(Nexus&& arg, NexusNode* parent) noexcept;
        Nexus(Nexus&& arg) noexcept = default;
    protected:
        [[nodiscard]] String CalculateLabel(const DataT& data) const override;
    private:
        void SetupChildren();
    };
}

namespace Inscription
{
    template<>
    class Scribe<Creation::Editing::Data::ActionAsset> final
    {
    public:
        using ObjectT = Creation::Editing::Data::ActionAsset;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            format("name", object.name);
            format("defaultKey", object.defaultKey);
            format("defaultModifierKeys", object.defaultModifierKeys);
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Editing::Data::ActionAsset, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Editing::Data::ActionAsset>;
    };
}