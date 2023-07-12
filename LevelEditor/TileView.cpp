
#include "TileView.h"

namespace Creation
{
    TileView::TileView(wxWindow *parent, wxWindowID winid, Atmos::Tile &tile, const wxPoint &pos, const wxSize &size, const wxString &name) : RenderWindow(parent, winid, pos, size, name), tile(tile)
    {}

    std::unordered_set<const Atmos::Sprite*> TileView::GetSprites() const
    {
        typedef std::unordered_set<const Atmos::Sprite*> Ret;
        Ret ret;
        for (auto &loop : tile.GetSpriteList())
            ret.emplace(&loop.second.Get());
        return ret;
    }
}