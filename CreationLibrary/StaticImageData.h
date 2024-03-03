#pragma once

#include "DataIncludes.h"
#include <Atmos/StaticImage.h>

#include "RenderCoreData.h"
#include "ImageCoreData.h"
#include "BoundsData.h"

#include "DynamicWorldImage.h"

namespace Creation::Editing
{
    namespace Data
    {
        class StaticImage
        {
        public:
            RenderCore renderCore;
            ImageCore imageCore;
            Bounds bounds;
        public:
            StaticImage() = default;
            StaticImage(const StaticImage& arg) = default;
            StaticImage& operator=(const StaticImage& arg) = default;

            void Build(Build::Context& context) const;
        private:
            INSCRIPTION_ACCESS;
        };
    }

    template<>
    class Property<Data::StaticImage> final : public CategoryProperty<Data::StaticImage>
    {
    public:
        Property<Data::RenderCore> renderCore;
        Property<Data::ImageCore> imageCore;
        Property<Data::Bounds> bounds;
    public:
        Property(
            const String& name,
            const String& label,
            wxPGProperty* parentProperty,
            wxPropertyGrid& grid,
            const NexusHistory& nexusHistory,
            UI& ui);
        Property(Property&& arg) noexcept;
    private:
        void SetupProperties();
    };

    template<>
    class NexusBatch<Data::StaticImage> final : public NexusBatchCommon<Data::StaticImage>
    {
    public:
        Property<Data::RenderCore> renderCore;
        Property<Data::ImageCore> imageCore;
        Property<Data::Bounds> bounds;
    public:
        NexusBatch(wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui);
        NexusBatch(NexusBatch&& arg) noexcept;
    private:
        void SetupProperties();
    };

    template<>
    class GhostWorldElement<Data::StaticImage> final : public GhostWorldElementCommon<Data::StaticImage>
    {
    public:
        GhostWorldElement(Nexus& nexus, Arca::Reliquary& reliquary);
    public:
        [[nodiscard]] DataT CurrentData() const override;
    protected:
        void MoveByImpl(const Atmos::Spatial::Point2D& by) override;
    private:
        DataT data;

        DynamicWorldImage image;
        DynamicWorldImage::Data imageData;
    };

    template<>
    class WorldElement<Data::StaticImage> final : public WorldElementCommon<Data::StaticImage>
    {
    public:
        WorldElement(Nexus& nexus, Arca::Reliquary& reliquary);
        WorldElement(WorldElement&& arg) noexcept;
    protected:
        void OnDataChanged(DataT data) override;

        void DoSelect() override;
        void DoDeselect() override;

        void DoShow() override;
        void DoHide() override;
    private:
        DataT data;

        DynamicWorldImage image;

        bool isSelected = false;
    private:
        [[nodiscard]] DynamicWorldImage::Data ImageData(DataT data) const;
        [[nodiscard]] Atmos::Render::Color ColorFor(DataT data) const;
        [[nodiscard]] Arca::Index<Atmos::Asset::Material> MaterialFor(DataT data) const;
    };

    template<>
    class Nexus<Data::StaticImage> final : public EditableNexusCommon<Data::StaticImage>
    {
    public:
        Nexus<Data::RenderCore> renderCore;
        Nexus<Data::ImageCore> imageCore;
        Nexus<Data::Bounds> bounds;
    public:
        Nexus(
            DataT& data,
            NexusNode* parent,
            const NexusHistory& nexusHistory,
            UI& ui,
            Arca::Reliquary& reliquary);
        Nexus(Nexus&& arg, NexusNode* parent) noexcept;
        Nexus(Nexus&& arg) noexcept = default;
    private:
        void SetupChildren();

        [[nodiscard]] static String CalculateLabel(const DataT& data);
    };
}

namespace Inscription
{
    template<>
    class Scribe<Creation::Editing::Data::StaticImage> final
    {
    public:
        using ObjectT = Creation::Editing::Data::StaticImage;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            format("renderCore", object.renderCore);
            format("imageCore", object.imageCore);
            format("bounds", object.bounds);
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Editing::Data::StaticImage, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Editing::Data::StaticImage>;
    };
}