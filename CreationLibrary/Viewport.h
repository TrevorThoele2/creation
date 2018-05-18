#pragma once

#include <wx/window.h>
#include <wx/timer.h>

#include "ViewportStack.h"

namespace Creation::Editing
{
    class Viewport final : public wxWindow
    {
    public:
        Viewport(
            ViewportStack& stack,
            wxWindow* parent,
            wxWindowID winID,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = 0,
            const wxString& name = "Viewport");
    private:
        ViewportStack* stack;
    private:
        void MoveOriginTo(const Point& set);
        void MoveOriginBy(Point::Value x, Point::Value y);

        [[nodiscard]] Point TopLeft() const;
        [[nodiscard]] Point Origin() const;
    private:
        wxTimer frameTimer;

        void CheckForKeyboardMovement();
        void CheckForMouseMovement();

        [[nodiscard]] Atmos::Spatial::Point2D ToAtmos(const wxPoint& point) const;
        [[nodiscard]] bool IsMiddleMouseButtonDown() const;
    private:
        void OnResize(wxSizeEvent& e);
        void OnPaint(wxPaintEvent& e);
        void OnMouseLeftDown(wxMouseEvent& e);
        void OnMouseLeftUp(wxMouseEvent& e);
        void OnMouseRightDown(wxMouseEvent& e);
        void OnMouseRightUp(wxMouseEvent& e);
        void OnMouseMove(wxMouseEvent& e);
        void OnFrameTimer(wxTimerEvent& e);
    };
}