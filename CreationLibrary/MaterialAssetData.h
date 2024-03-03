#pragma once

#include "AssetData.h"
#include <Atmos/MaterialAsset.h>

#include "MaterialAssetPassData.h"
#include "IntegerData.h"
#include "StringData.h"
#include "EnumData.h"
#include "ListData.h"

#include <Atmos/FindAssetByName.h>

namespace Creation::Editing
{
    namespace Data
    {
        class MaterialAsset
        {
        public:
            String name;

            std::list<MaterialAssetPass> passes = {{}};
        public:
            MaterialAsset() = default;
            MaterialAsset(const String& name, const std::list<MaterialAssetPass>& passes);
            MaterialAsset(const MaterialAsset& arg) = default;
            MaterialAsset& operator=(const MaterialAsset & arg) = default;

            void Build(Build::Context& context) const;
        private:
            INSCRIPTION_ACCESS;
        };
    }
    
    template<>
    class NexusBatch<Data::MaterialAsset> final : public NexusBatchCommon<Data::MaterialAsset>
    {
    private:
        using BaseT = NexusBatchCommon<Data::MaterialAsset>;
    public:
        Property<String> name;
    public:
        NexusBatch(wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui);
        NexusBatch(NexusBatch&& arg) noexcept;
    private:
        using BaseT::Auto;
    private:
        void SetupProperties();
    };

    template<>
    class WorldElement<Data::MaterialAsset> final : public WorldElementCommon<Data::MaterialAsset>
    {
    private:
        using BaseT = WorldElementCommon<Data::MaterialAsset>;
    public:
        WorldElement(Nexus& nexus, Arca::Reliquary& reliquary);
        WorldElement(WorldElement&& arg) noexcept = default;
        ~WorldElement();
    protected:
        using BaseT::Reliquary;
    protected:
        void OnDataChanged(DataT data) override;
    private:
        using Object = Atmos::Asset::Material;
        using Index = Arca::Index<Object>;

        Index object;

        Index CreateObject(DataT data);
        void DestroyObject(Index index);
    };

    template<>
    class Nexus<Data::MaterialAsset> final : public EditableAssetNexusCommon<Data::MaterialAsset>
    {
    private:
        using BaseT = EditableAssetNexusCommon<Data::MaterialAsset>;
    public:
        Nexus<String> name;

        Nexus<std::list<Data::MaterialAssetPass>> passes;
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
        using BaseT::autoHandler;
        using BaseT::eventConnections;
        using BaseT::OnLabelChanged;
    protected:
        [[nodiscard]] String CalculateLabel(const DataT& data) const override;
    private:
        void SetupChildren();
    };
}

namespace Inscription
{
    template<>
    class Scribe<Creation::Editing::Data::MaterialAsset> final
    {
    public:
        using ObjectT = Creation::Editing::Data::MaterialAsset;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            format("name", object.name);
            format("passes", object.passes);
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Editing::Data::MaterialAsset, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Editing::Data::MaterialAsset>;
    };
}