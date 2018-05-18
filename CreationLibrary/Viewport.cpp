#include <wx/dcclient.h>
#include <wx/dcbuffer.h>

#include "Viewport.h"

#include <Atmos/Camera.h>
#include <Atmos/MoveBounds.h>
#include <Atmos/ScaleBounds.h>
#include <Atmos/Work.h>
#include <Atmos/SpatialAlgorithms.h>

namespace Creation::Editing
{
    Viewport::Viewport(
        ViewportStack& stack,
        wxWindow* parent,
        wxWindowID winID,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxString& name)
        :
        wxWindow(parent, winID, pos, size, style | wxFULL_REPAINT_ON_RESIZE, name),
        stack(&stack),
        frameTimer(this, 1)
    {
        wxWindowBase::SetBackgroundStyle(wxBG_STYLE_PAINT);
        wxWindowBase::SetBackgroundColour(*wxLIGHT_GREY);

        frameTimer.Start(16);

        Bind(wxEVT_SIZE, &Viewport::OnResize, this);
        Bind(wxEVT_PAINT, &Viewport::OnPaint, this);
        Bind(wxEVT_LEFT_DOWN, &Viewport::OnMouseLeftDown, this);
        Bind(wxEVT_LEFT_UP, &Viewport::OnMouseLeftUp, this);
        Bind(wxEVT_RIGHT_DOWN, &Viewport::OnMouseRightDown, this);
        Bind(wxEVT_RIGHT_UP, &Viewport::OnMouseRightUp, this);
        Bind(wxEVT_MOTION, &Viewport::OnMouseMove, this);
        Bind(wxEVT_TIMER, &Viewport::OnFrameTimer, this);
    }

    void Viewport::MoveOriginTo(const Point& set)
    {
        const auto& reliquary = stack->state.reliquary;
        const auto camera = reliquary->Find<Atmos::Render::Camera>();
        if (Point{ camera->Position().x, camera->Position().y } == set)
            return;

        const auto position = set.ToAtmos();
        reliquary->Do(Atmos::Spatial::MoveBounds(
            camera.ID(),
            Atmos::Spatial::Point3D{ position.x, position.y, 0.0f }));

        stack->commands.mouseMoved(ToAtmos(wxGetMousePosition()));
    }

    void Viewport::MoveOriginBy(Point::Value x, Point::Value y)
    {
        const auto origin = Origin();
        auto newOrigin = origin;
        newOrigin.x += x;
        newOrigin.y += y;

        if (origin != newOrigin)
            MoveOriginTo(newOrigin);
    }

    Point Viewport::TopLeft() const
    {
        const auto camera = stack->state.reliquary->Find<Atmos::Render::Camera>();
        return Point
        {
            camera->Sides().Left(),
            camera->Sides().Top()
        };
    }

    Point Viewport::Origin() const
    {
        const auto camera = stack->state.reliquary->Find<Atmos::Render::Camera>();
        return Point
        {
            camera->Position().x,
            camera->Position().y
        };
    }

    void Viewport::CheckForKeyboardMovement()
    {
        if (!HasFocus())
            return;

        const auto scrollFactor = 25.0;

        const auto up = wxGetKeyState(WXK_UP);
        const auto down = wxGetKeyState(WXK_DOWN);
        const auto left = wxGetKeyState(WXK_LEFT);
        const auto right = wxGetKeyState(WXK_RIGHT);

        if (up && !down)
            MoveOriginBy(0, -scrollFactor);
        else if (!up && down)
            MoveOriginBy(0, scrollFactor);

        if (left && !right)
            MoveOriginBy(-scrollFactor, 0);
        else if (!left && right)
            MoveOriginBy(scrollFactor, 0);
    }

    void Viewport::CheckForMouseMovement()
    {
        auto& currentMousePosition = stack->state.currentMousePosition;
        auto& previousMousePosition = stack->state.previousMousePosition;
        if (IsMiddleMouseButtonDown() && previousMousePosition && currentMousePosition)
        {
            const auto deltaX = previousMousePosition->x - currentMousePosition->x;
            const auto deltaY = previousMousePosition->y - currentMousePosition->y;
            MoveOriginBy(deltaX, deltaY);
        }
    }

    Atmos::Spatial::Point2D Viewport::ToAtmos(const wxPoint& point) const
    {
        const auto topLeft = Atmos::Spatial::Point2D
        {
            static_cast<float>(TopLeft().x),
            static_cast<float>(TopLeft().y)
        };

        const auto screenPoint = Atmos::Spatial::Point2D
        {
            static_cast<float>(point.x - this->GetScreenPosition().x),
            static_cast<float>(point.y - this->GetScreenPosition().y)
        };

        return topLeft + screenPoint;
    }

    bool Viewport::IsMiddleMouseButtonDown() const
    {
        const auto mouseState = wxGetMouseState();
        return mouseState.MiddleIsDown();
    }

    void Viewport::OnResize(wxSizeEvent& e)
    {
        const auto& reliquary = stack->state.reliquary;
        const auto camera = reliquary->Find<Atmos::Render::Camera>();
        const auto clientSize = GetClientSize();
        reliquary->Do(Atmos::Spatial::ScaleBounds{
            camera.ID(),
            Atmos::Spatial::Scalers2D
            {
                Atmos::Spatial::Scalers2D::Value(clientSize.GetWidth()),
                Atmos::Spatial::Scalers2D::Value(clientSize.GetHeight())
            } });

        e.Skip();
    }

    void Viewport::OnPaint(wxPaintEvent& e)
    {
        wxPaintDC drawingContext(this);

        if (!stack->state.isActive)
            drawingContext.Clear();
        else
            stack->state.reliquary->Do(Atmos::Work{});
    }

    void Viewport::OnMouseLeftDown(wxMouseEvent& e)
    {
        if (stack->state.isActive)
        {
            const auto mousePosition = ToAtmos(wxGetMousePosition());
            stack->commands.mouseLeftDown(mousePosition);
        }

        e.Skip();
    }

    void Viewport::OnMouseLeftUp(wxMouseEvent& e)
    {
        if (stack->state.isActive)
        {
            const auto mousePosition = ToAtmos(wxGetMousePosition());
            stack->commands.mouseLeftUp(mousePosition);
        }

        e.Skip();
    }

    void Viewport::OnMouseRightDown(wxMouseEvent& e)
    {
        if (stack->state.isActive)
        {
            const auto mousePosition = ToAtmos(wxGetMousePosition());
            stack->commands.mouseRightDown(mousePosition);
        }

        e.Skip();
    }

    void Viewport::OnMouseRightUp(wxMouseEvent& e)
    {
        if (stack->state.isActive)
        {
            const auto mousePosition = ToAtmos(wxGetMousePosition());
            stack->commands.mouseRightUp(mousePosition);
        }

        e.Skip();
    }

    void Viewport::OnMouseMove(wxMouseEvent& e)
    {
        if (stack->state.isActive)
        {
            const auto mousePosition = ToAtmos(wxGetMousePosition());
            stack->commands.mouseMoved(mousePosition);
        }

        e.Skip();
    }

    void Viewport::OnFrameTimer(wxTimerEvent& e)
    {
        const auto isActive = stack->state.isActive;
        auto& currentMousePosition = stack->state.currentMousePosition;
        auto& previousMousePosition = stack->state.previousMousePosition;

        if (IsShown() && isActive)
        {
            previousMousePosition = currentMousePosition;
            currentMousePosition = wxGetMousePosition();

            CheckForMouseMovement();
            CheckForKeyboardMovement();
            Refresh();
        }
        else
        {
            previousMousePosition.reset();
            currentMousePosition.reset();
        }

        e.Skip();
    }
}