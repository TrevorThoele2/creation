
#include <wx/dcclient.h>
#include "BoxOperation.h"
#include "Viewport.h"
#include <Atmos/GraphicsHandlerBase.h>

namespace Creation
{
    BoxOperation::BoxOperation() : BoxOperation(Atmos::Color())
    {}

    BoxOperation::BoxOperation(const Atmos::Color &color) : mouseDown(false), image("", color)
    {}

    bool BoxOperation::IsWorking() const
    {
        return mouseDown;
    }

    const Rectangle& BoxOperation::GetBounds()
    {
        return rectangle;
    }

    void BoxOperation::SetColor(const Atmos::Color &color)
    {
        image.color = color;
    }

    void BoxOperation::MouseDown(const Point &pt)
    {
        anchor = pt;
        rectangle.left = rectangle.right = anchor.x;
        rectangle.top = rectangle.bottom = anchor.y;
        mouseDown = true;
    }

    void BoxOperation::MouseUp(const Point &pt)
    {
        if (IsWorking())
        {
            mouseDown = false;
            consume(*this);
        }
    }

    void BoxOperation::MouseMove(const Point &pt)
    {
        if (IsWorking())
        {
            if (pt.x < anchor.x)
            {
                rectangle.left = pt.x;
                rectangle.right = anchor.x;
            }
            else
            {
                rectangle.left = anchor.x;
                rectangle.right = pt.x;
            }

            if (pt.y < anchor.y)
            {
                rectangle.top = pt.y;
                rectangle.bottom = anchor.y;
            }
            else
            {
                rectangle.top = anchor.y;
                rectangle.bottom = pt.y;
            }
        }
    }

    void BoxOperation::Draw(wxGraphicsContext &graphics)
    {
        if (!IsWorking())
            return;

        auto brush = graphics.CreateBrush(wxBrush(wxColour(0, 0, 255, 127)));
        graphics.DrawRectangle(rectangle.left, rectangle.top, rectangle.right - rectangle.left, rectangle.top - rectangle.bottom);
    }

    void BoxOperation::Draw(Atmos::GraphicsHandlerBase &handler, Atmos::Position3D::ValueT z)
    {
        if (!IsWorking())
            return;

        image.SetAsset(pixelImageName);

        auto width = rectangle.right - rectangle.left;
        auto height = rectangle.bottom - rectangle.top;
        image.SetXScaler(width);
        image.SetYScaler(height);
        image.SetPosition(Atmos::Position3D(rectangle.left + (width / 2), rectangle.top + (height / 2), z));

        handler.RenderUnknownFragment(image);
    }

    void BoxOperation::Clear()
    {
        mouseDown = false;
    }
}