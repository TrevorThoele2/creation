#pragma once

#include <wx\window.h>

#include <Atmos\Sprite.h>
#include "Optional.h"

namespace Creation
{
    class RenderWindow : public wxWindow
    {
    private:
        Atmos::Color refreshColor;

        void OnPaint(wxPaintEvent &e);
    public:
        RenderWindow(wxWindow *parent, wxWindowID winid, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, const wxString &name = "RenderWindow");
        virtual ~RenderWindow() = 0 {}

        void SetRefreshColor(const Atmos::Color &set);
        const Atmos::Color& GetRefreshColor() const;

        virtual std::unordered_set<const Atmos::Sprite*> GetSprites() const = 0;
    };
}