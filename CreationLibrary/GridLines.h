#pragma once

#include <Arca/Curator.h>

#include "ChangeGridLineMaterial.h"
#include <Atmos/Line.h>

namespace Creation
{
    class GridLines : public Arca::Curator
    {
    public:
        explicit GridLines(Init init);
    public:
        void Handle(const ChangeGridLineMaterial& command);
    private:
        std::vector<Arca::Index<Atmos::Render::Line>> lines;
        void CreateLines();

        void CreateAlongDimension(
            int fixedDimensionStart,
            int fixedDimensionEnd,
            int changeDimensionStart,
            int changeDimensionEnd,
            int addChangeDimension,
            Atmos::Spatial::Point2D(*point)(int, int),
            int boldFrequency,
            Arca::Index<Atmos::Asset::Material> material);

        void CreateLine(
            Atmos::Spatial::Point2D from,
            Atmos::Spatial::Point2D to,
            Atmos::Spatial::Point2D::Value z,
            Atmos::Render::LineWidth width,
            Atmos::Render::Color color,
            Arca::Index<Atmos::Asset::Material> material);

        static Atmos::Spatial::Point2D PointXY(int x, int y)
        {
            return Atmos::Spatial::Point2D{ static_cast<float>(x), static_cast<float>(y) };
        }

        static Atmos::Spatial::Point2D PointYX(int y, int x)
        {
            return Atmos::Spatial::Point2D{ static_cast<float>(x), static_cast<float>(y) };
        }
    };
}

namespace Arca
{
    template<>
    struct Traits<Creation::GridLines>
    {
        static constexpr ObjectType objectType = ObjectType::Curator;
        static const inline TypeName typeName = "Creation::GridLines";
        using HandledCommands = HandledCommands<Creation::ChangeGridLineMaterial>;
    };
}

namespace Inscription
{
    template<class Format>
    struct ScribeTraits<Creation::GridLines, Format> final
    {
        using Category = ArcaNullScribeCategory<Creation::GridLines>;
    };
}