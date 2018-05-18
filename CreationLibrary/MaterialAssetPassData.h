#pragma once

#include "AssetData.h"
#include <Atmos/MaterialAsset.h>

#include "IntegerData.h"
#include "StringData.h"
#include "ListData.h"

namespace Creation::Editing
{
    namespace Data
    {
        class MaterialAssetPass
        {
        public:
            String vertexShader;
            String fragmentShader;
        public:
            MaterialAssetPass() = default;
            MaterialAssetPass(const String& vertexShader, const String& fragmentShader);
            MaterialAssetPass(const MaterialAssetPass& arg) = default;
            MaterialAssetPass& operator=(const MaterialAssetPass& arg) = default;
        private:
            INSCRIPTION_ACCESS;
        };
    }

    template<>
    class NexusBatch<Data::MaterialAssetPass> final : public NexusBatchCommon<Data::MaterialAssetPass>
    {
    public:
        AssetSelectorProperty vertexShader;
        AssetSelectorProperty fragmentShader;
    public:
        NexusBatch(wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui);
        NexusBatch(NexusBatch&& arg) noexcept;
    private:
        void SetupProperties();
    };

    template<>
    class Nexus<Data::MaterialAssetPass> final : public EditableNexusCommon<Data::MaterialAssetPass>
    {
    public:
        Nexus<String> vertexShader;
        Nexus<String> fragmentShader;
    public:
        Nexus(
            DataT& data,
            NexusNode* parent,
            NexusHistory nexusHistory,
            UI& ui,
            Arca::Reliquary& reliquary,
            const String& label);
        Nexus(Nexus&& arg, NexusNode* parent) noexcept;
        Nexus(Nexus&& arg) noexcept = default;
    private:
        void SetupChildren();
    };
}

namespace Inscription
{
    template<>
    class Scribe<Creation::Editing::Data::MaterialAssetPass> final
    {
    public:
        using ObjectT = Creation::Editing::Data::MaterialAssetPass;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            format("vertexShader", object.vertexShader);
            format("fragmentShader", object.fragmentShader);
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Editing::Data::MaterialAssetPass, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Editing::Data::MaterialAssetPass>;
    };
}