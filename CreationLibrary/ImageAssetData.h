#pragma once

#include "AssetData.h"
#include <Atmos/ImageAsset.h>
#include "IntegerData.h"
#include "Settings.h"

namespace Creation::Editing
{
    namespace Data
    {
        class ImageAsset
        {
        public:
            File::Path filePath;

            Atmos::Asset::Image::GridDimension columns = 1;
            Atmos::Asset::Image::GridDimension rows = 1;
        public:
            ImageAsset() = default;
            ImageAsset(const ImageAsset& arg) = default;
            ImageAsset& operator=(const ImageAsset & arg) = default;

            void Build(Build::Context& context) const;
        private:
            INSCRIPTION_ACCESS;
        };
    }

    template<>
    class NexusBatch<Data::ImageAsset> final : public NexusBatchCommon<Data::ImageAsset>
    {
    public:
        Property<File::Path> filePath;
        Property<Atmos::Asset::Image::GridDimension> columns;
        Property<Atmos::Asset::Image::GridDimension> rows;
    public:
        NexusBatch(wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui);
        NexusBatch(NexusBatch&& arg) noexcept;
    private:
        void SetupProperties();
    };

    template<>
    class WorldElement<Data::ImageAsset> final : public WorldElementCommon<Data::ImageAsset>
    {
    public:
        WorldElement(Nexus& nexus, Arca::Reliquary& reliquary);
        WorldElement(WorldElement&& arg) noexcept = default;
        ~WorldElement();
    protected:
        void OnDataChanged(DataT data) override;
    private:
        using Object = Atmos::Asset::Image;
        using Index = Arca::Index<Object>;

        Index object;

        Index CreateObject(DataT data);
        void DestroyObject(Index index);
    private:
        using ObjectConstructorArgs = std::tuple<
            String,
            std::unique_ptr<Atmos::Asset::Resource::Image>,
            Atmos::Asset::ImageGridSize>;
        [[nodiscard]] static ObjectConstructorArgs ObjectConstructorArgsFor(
            Data::ImageAsset data, Arca::Reliquary& reliquary);
        [[nodiscard]] static Arca::Index<Atmos::Asset::Image> CreateAtmos(
            Data::ImageAsset data, Arca::Reliquary& reliquary);
    };

    template<>
    class Nexus<Data::ImageAsset> final : public EditableAssetNexusCommon<Data::ImageAsset>
    {
    public:
        Nexus<File::Path> filePath;

        Nexus<Atmos::Asset::Image::GridDimension> columns;
        Nexus<Atmos::Asset::Image::GridDimension> rows;
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
    class Scribe<Creation::Editing::Data::ImageAsset> final
    {
    public:
        using ObjectT = Creation::Editing::Data::ImageAsset;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            if (format.IsOutput())
            {
                auto relative = std::filesystem::relative(object.filePath, Creation::settings.imageAssetPath);
                format("filePath", relative);
            }
            else
            {
                Atmos::File::Path relative;
                format("filePath", relative);

                object.filePath = Creation::settings.imageAssetPath / relative;
            }

            format("columns", object.columns);
            format("rows", object.rows);
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Editing::Data::ImageAsset, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Editing::Data::ImageAsset>;
    };
}