#pragma once

#include "AssetData.h"
#include <Atmos/FontAsset.h>
#include "Settings.h"

namespace Creation::Editing
{
    namespace Data
    {
        class FontAsset
        {
        public:
            File::Path filePath;
        public:
            FontAsset() = default;
            FontAsset(const FontAsset& arg) = default;
            FontAsset& operator=(const FontAsset& arg) = default;

            void Build(Build::Context& context) const;
        private:
            INSCRIPTION_ACCESS;
        };
    }

    template<>
    class NexusBatch<Data::FontAsset> final : public NexusBatchCommon<Data::FontAsset>
    {
    public:
        Property<File::Path> filePath;
    public:
        NexusBatch(wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui);
        NexusBatch(NexusBatch&& arg) noexcept;
    private:
        void SetupProperties();
    };

    template<>
    class WorldElement<Data::FontAsset> final : public WorldElementCommon<Data::FontAsset>
    {
    public:
        WorldElement(Nexus& nexus, Arca::Reliquary& reliquary);
        WorldElement(WorldElement&& arg) noexcept = default;
        ~WorldElement();
    protected:
        void OnDataChanged(DataT data) override;
    private:
        using Object = Atmos::Asset::Font;
        using Index = Arca::Index<Object>;

        Index object;

        Index CreateObject(DataT data);
        void DestroyObject(Index index);
    private:
        using ObjectConstructorArgs = std::tuple<
            String,
            std::unique_ptr<Atmos::Asset::Resource::Font>>;
        [[nodiscard]] static ObjectConstructorArgs ObjectConstructorArgsFor(
            Data::FontAsset data, Arca::Reliquary& reliquary);
        [[nodiscard]] static Arca::Index<Atmos::Asset::Font> CreateAtmos(
            Data::FontAsset data, Arca::Reliquary& reliquary);
    };

    template<>
    class Nexus<Data::FontAsset> final : public EditableAssetNexusCommon<Data::FontAsset>
    {
    public:
        Nexus<File::Path> filePath;
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
    class Scribe<Creation::Editing::Data::FontAsset> final
    {
    public:
        using ObjectT = Creation::Editing::Data::FontAsset;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            if (format.IsOutput())
            {
                auto relative = std::filesystem::relative(object.filePath, Creation::settings.fontAssetPath);
                format("filePath", relative);
            }
            else
            {
                Atmos::File::Path relative;
                format("filePath", relative);

                object.filePath = Creation::settings.fontAssetPath / relative;
            }
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Editing::Data::FontAsset, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Editing::Data::FontAsset>;
    };
}