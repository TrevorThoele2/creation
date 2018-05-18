#pragma once

#include "DataIncludes.h"
#include <Atmos/DynamicImage.h>

#include "RenderCoreData.h"
#include "ImageCoreData.h"
#include "BoundsData.h"

namespace Creation::Editing
{
    namespace Data
    {
        class DynamicImage
        {
        public:
            RenderCore renderCore;
            ImageCore imageCore;
            Bounds bounds;
        public:
            DynamicImage() = default;
            DynamicImage(const DynamicImage& arg) = default;
            DynamicImage& operator=(const DynamicImage& arg) = default;

            void Build(Build::Context& context) const;
        private:
            INSCRIPTION_ACCESS;
        };
    }

    template<>
    class Property<Data::DynamicImage> final : public CategoryProperty<Data::DynamicImage>
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
    class Nexus<Data::DynamicImage > final : public NexusCommon<Data::DynamicImage>
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
    class Scribe<Creation::Editing::Data::DynamicImage> final
    {
    public:
        using ObjectT = Creation::Editing::Data::DynamicImage;
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
    struct ScribeTraits<Creation::Editing::Data::DynamicImage, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Editing::Data::DynamicImage>;
    };
}