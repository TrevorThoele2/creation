#pragma once

namespace Creation
{
    class Point;
    // Bold frequency is how frequent (in lines) the bold lines are
    void RenderDimensionLinesFill(int width, int height, const Point &topLeft, int boldFrequency);
    void RenderDimensionLinesGrid(int width, int height, const Point &topLeft);
}