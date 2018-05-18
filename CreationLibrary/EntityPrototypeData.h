#pragma once

#include "DataIncludes.h"
#include <Atmos/Entity.h>

#include "ScriptData.h"
#include "StringData.h"
#include "GridPointData.h"
#include "FloatData.h"
#include "BoolData.h"

#include "DynamicWorldImage.h"

namespace Creation::Editing
{
    namespace Data
    {
        class EntityPrototype
        {
        public:
            Atmos::Name name;
            Atmos::Spatial::Grid::Point position;
            bool solid;
            Script constructor;
        public:
            EntityPrototype() = default;
            EntityPrototype(const EntityPrototype& arg) = default;
            EntityPrototype& operator=(const EntityPrototype& arg) = default;

            void Build(Build::Context& context) const;
        private:
            INSCRIPTION_ACCESS;
        };
    }

    template<>
    class NexusBatch<Data::EntityPrototype> final : public NexusBatchCommon<Data::EntityPrototype>
    {
    public:
        Property<Atmos::Name> name;
        Property<Atmos::Spatial::Grid::Point> position;
        Property<bool> solid;
        Property<Data::Script> constructor;
    public:
        NexusBatch(wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui);
        NexusBatch(NexusBatch&& arg) noexcept;
    private:
        void SetupProperties();
    };

    template<>
    class GhostWorldElement<Data::EntityPrototype> final : public GhostWorldElementCommon<Data::EntityPrototype>
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
    private:
        Atmos::Spatial::Point3D ephemeralPosition;

        [[nodiscard]] static DynamicWorldImage::Data ImageData(DataT data, Arca::Reliquary& reliquary);
    };

    template<>
    class WorldElement<Data::EntityPrototype> final : public WorldElementCommon<Data::EntityPrototype>
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
        Arca::Index<Atmos::Asset::Image> asset;

        [[nodiscard]] DynamicWorldImage::Data ImageData(DataT data) const;
        [[nodiscard]] Atmos::Spatial::Point3D PositionFor(DataT data) const;
        [[nodiscard]] Atmos::Render::Color ColorFor(DataT data) const;
        [[nodiscard]] Arca::Index<Atmos::Asset::Material> MaterialFor(DataT data) const;
    };

    template<>
    class Nexus<Data::EntityPrototype> final : public EditableNexusCommon<Data::EntityPrototype>
    {
    public:
        Nexus<Atmos::Name> name;
        Nexus<Atmos::Spatial::Grid::Point> position;
        Nexus<bool> solid;
        Nexus<Data::Script> constructor;
    public:
        Nexus(
            DataT& data,
            NexusNode* parent,
            NexusHistory nexusHistory,
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
    class Scribe<Creation::Editing::Data::EntityPrototype> final
    {
    public:
        using ObjectT = Creation::Editing::Data::EntityPrototype;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            format("constructor", object.constructor);
            format("name", object.name);
            format("position", object.position);
            format("solid", object.solid);
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Editing::Data::EntityPrototype, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Editing::Data::EntityPrototype>;
    };
}