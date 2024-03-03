#include "GridLines.h"

#include "GridLinesInformation.h"

#include <Atmos/Point2D.h>
#include <Atmos/GridCellSize.h>
#include <Atmos/Line.h>
#include <Atmos/Camera.h>

#include <Atmos/BoundsMoved.h>
#include <Atmos/BoundsScaled.h>

#include <Arca/Create.h>
#include <Arca/Destroy.h>

namespace Creation
{
    GridLines::GridLines(Init init) : Curator(init)
    {
        CreateLines();

        Owner().On<Atmos::Spatial::BoundsMoved>([this](const Atmos::Spatial::BoundsMoved& signal)
            {
                if (signal.id == Owner().Find<Atmos::Render::Camera>().ID())
                    CreateLines();
            });

        Owner().On<Atmos::Spatial::BoundsScaled>([this](const Atmos::Spatial::BoundsScaled& signal)
            {
                if (signal.id == Owner().Find<Atmos::Render::Camera>().ID())
                    CreateLines();
            });
    }

    void GridLines::Handle(const ChangeGridLineMaterial& command)
    {
        MutablePointer().Of<GridLinesInformation>()->material = command.material;
        CreateLines();
    }

    void GridLines::CreateLines()
    {
        for (auto line = lines.begin(); line != lines.end();)
        {
            Owner().Do(Arca::Destroy<Atmos::Render::Line>{ *line });
            line = lines.erase(line); 
        }

        const auto cameraSides = Owner().Find<Atmos::Render::Camera>()->Sides();
        const auto left = static_cast<int>(cameraSides.Left());
        const auto top = static_cast<int>(cameraSides.Top());
        const auto right = static_cast<int>(cameraSides.Right());
        const auto bottom = static_cast<int>(cameraSides.Bottom());

        auto& information = *Owner().Find<GridLinesInformation>();
        const auto material = information.material;
        const auto boldFrequency = information.boldFrequency;

        CreateAlongDimension(top, bottom, left, right, 1, &PointXY, boldFrequency, material);
        CreateAlongDimension(left, right, top, bottom, 0, &PointYX, boldFrequency, material);
    }

    void GridLines::CreateAlongDimension(
        int fixedDimensionStart,
        int fixedDimensionEnd,
        int changeDimensionStart,
        int changeDimensionEnd,
        int addChangeDimension,
        Atmos::Spatial::Point2D(*point)(int, int),
        int boldFrequency,
        Arca::Index<Atmos::Asset::Material> material)
    {
        const auto cellSize = Atmos::Spatial::Grid::CellSize<int>;

        const auto boldDistance = boldFrequency * cellSize;

        const auto middleColor = Atmos::Render::Color{ 255, 180, 0, 0 };
        const auto boldColor = Atmos::Render::Color{ 255, 127, 127, 0 };
        const auto normalColor = Atmos::Render::Color{ 255, 127, 127, 127 };

        constexpr auto z = std::numeric_limits<Atmos::Spatial::Point2D::Value>::lowest() / 2 - 1;
        const auto width = 1.0f;

        const auto changeDimensionStartOffset = changeDimensionStart % cellSize;
        auto lineDistance = changeDimensionStart - changeDimensionStartOffset;

        while(lineDistance < changeDimensionEnd)
        {
            const auto from = point(lineDistance + addChangeDimension, fixedDimensionStart);
            const auto to = point(lineDistance + addChangeDimension, fixedDimensionEnd);

            Atmos::Render::Color color;

            if (lineDistance == 0)
                color = middleColor;
            else if (lineDistance % boldDistance == 0)
                color = boldColor;
            else
                color = normalColor;

            CreateLine(from, to, z, width, color, material);

            lineDistance += cellSize;
        }
    }

    void GridLines::CreateLine(
        Atmos::Spatial::Point2D from,
        Atmos::Spatial::Point2D to,
        Atmos::Spatial::Point2D::Value z,
        Atmos::Render::LineWidth width,
        Atmos::Render::Color color,
        Arca::Index<Atmos::Asset::Material> material)
    {
        const auto created = Owner().Do(Arca::Create<Atmos::Render::Line> {
            std::vector<Atmos::Spatial::Point2D>{ from, to }, z, material, width, color });
        lines.push_back(created);
    }
}