
#include "GridLines.h"

#include "Point.h"

#include <Atmos/Position2D.h>
#include <Atmos/GridSize.h>
#include <Atmos/Environment.h>
#include <Atmos/LineRender.h>

namespace Creation
{
    Atmos::Position2D PointXY(int x, int y)
    {
        return Atmos::Position2D(static_cast<float>(x), static_cast<float>(y));
    }

    Atmos::Position2D PointYX(int y, int x)
    {
        return Atmos::Position2D(static_cast<float>(x), static_cast<float>(y));
    }

    void RenderDimensionLinesFill(int width, int height, const Point &topLeft, int boldFrequency)
    {
        auto renderDimensionLines = [](int fixedDimensionEnd, int changeDimensionStart, int changeDimensionEnd, int centerDimension, Atmos::Position2D(*getPoint)(int, int), int boldFrequency)
        {
            const int gridSize(::Atmos::GRID_SIZE<int>);
            const int modBoldFrequency(boldFrequency * gridSize);

            int current = gridSize - (changeDimensionStart % gridSize);
            if (current > gridSize)
                current -= gridSize;

            while (current <= changeDimensionEnd)
            {
                if (current == centerDimension)
                    Atmos::Environment::GetGraphics()->RenderLine(Atmos::LineRender(getPoint(current, 0), getPoint(current, fixedDimensionEnd), Atmos::Color(255, 180, 0, 0)));
                else if((centerDimension - current) % modBoldFrequency == 0)
                    Atmos::Environment::GetGraphics()->RenderLine(Atmos::LineRender(getPoint(current, 0), getPoint(current, fixedDimensionEnd), Atmos::Color(255, 127, 127, 0)));
                else
                    Atmos::Environment::GetGraphics()->RenderLine(Atmos::LineRender(getPoint(current, 0), getPoint(current, fixedDimensionEnd), Atmos::Color(255, 127, 127, 127)));

                current += Atmos::GRID_SIZE<int>;
            }
        };

        const ::Atmos::Position2D topLeftInEngine(::Atmos::Position2D::FromScreen(topLeft.ToAtmos(), ::Atmos::Position2D(0, 0)));
        renderDimensionLines(height, topLeft.x, width, -topLeftInEngine.GetX(), &PointXY, boldFrequency);
        renderDimensionLines(width, topLeft.y, height, -topLeftInEngine.GetY(), &PointYX, boldFrequency);
    }

    void RenderDimensionLinesGrid(int width, int height, const Point &topLeft)
    {
        auto renderDimensionLines = [](int fixedDimensionStart, int fixedDimensionEnd, int changeDimensionStart, int changeDimensionEnd, Atmos::Position2D(*getPoint)(int, int))
        {
            while (changeDimensionStart <= changeDimensionEnd)
            {
                Atmos::Environment::GetGraphics()->RenderLine(Atmos::LineRender(getPoint(changeDimensionStart, fixedDimensionStart), getPoint(changeDimensionStart, fixedDimensionEnd), Atmos::Color(127, 255, 255, 255)));
                changeDimensionStart += Atmos::GRID_SIZE<int>;
            }
        };

        auto bottom = topLeft.y + height;
        auto right = topLeft.x + width;

        renderDimensionLines(topLeft.y, bottom, topLeft.x, right, &PointXY);
        renderDimensionLines(topLeft.x, right, topLeft.y, bottom, &PointYX);
    }
}