#pragma once

#include <wx/graphics.h>

#include "Point.h"
#include "Rectangle.h"
#include "Image.h"

#include <Function/Event.h>

namespace Atmos
{
    class GraphicsHandlerBase;
}

namespace Creation
{
    class BoxOperation
    {
    private:
        bool mouseDown;
        Point anchor;
        Rectangle rectangle;
        Image image;
    public:
        // Subscribe this to get when to consume the operation
        ::function::Event<BoxOperation&> consume;

        BoxOperation();
        BoxOperation(const Atmos::Color &color);
        bool IsWorking() const;
        const Rectangle& GetBounds();
        void SetColor(const Atmos::Color &color);

        void MouseDown(const Point &pt);
        void MouseUp(const Point &pt);
        void MouseMove(const Point &pt);
        void Draw(wxGraphicsContext &graphics);
        void Draw(Atmos::GraphicsHandlerBase &handler, Atmos::Position3D::ValueT z);

        void Clear();
    };
}