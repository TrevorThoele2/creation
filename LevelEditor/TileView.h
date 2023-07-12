#pragma once

#include "RenderWindow.h"
#include <Atmos\Tile.h>

namespace Creation
{
    class TileView : public RenderWindow
    {
    private:
        Atmos::Tile &tile;
    public:
        TileView(wxWindow *parent, wxWindowID winid, Atmos::Tile &tile, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, const wxString &name = "TileWindow");
        std::unordered_set<const Atmos::Sprite*> GetSprites() const override;
    };
}