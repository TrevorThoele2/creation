
#include "DataBreakdownTiles.h"

#include "TileViewManager.h"

#include <Atmos/StringUtility.h>
#include "GridPositionDialog.h"
#include "ViewportStateTiles.h"

#include <wx/artprov.h>

namespace Creation
{
    void DataBreakdown<Build::Package<::Atmos::Tile>>::AddAllChildren()
    {
        AddChild(position);
        AddChild(solid);
        AddChild(sprites);
    }

    void DataBreakdown<Build::Package<::Atmos::Tile>>::SubscribeEvents()
    {
        sprites.added.Subscribe(&DataBreakdown::OnSpriteAdded, *this);
        sprites.postRemove.Subscribe(&DataBreakdown::OnSpriteRemoved, *this);
    }

    void DataBreakdown<Build::Package<::Atmos::Tile>>::OnSpriteAdded(const DataBreakdownAddArgs &args)
    {
        auto spriteBreakdown = static_cast<DataBreakdown<SpritePackageT>*>(args.Added());
        spriteBreakdown->edited.Subscribe(&DataBreakdown::OnSpriteEdited, *this);
        TileViewManager::Evaluate(Get()->position);
    }

    void DataBreakdown<Build::Package<::Atmos::Tile>>::OnSpriteRemoved(const DataBreakdownPostRemoveArgs &args)
    {
        TileViewManager::Evaluate(Get()->position);
    }

    void DataBreakdown<Build::Package<::Atmos::Tile>>::OnSpriteEdited(const DataBreakdownEditArgs &args)
    {
        TileViewManager::Evaluate(Get()->position);
    }

    void DataBreakdown<Build::Package<::Atmos::Tile>>::SetupImpl()
    {
        position.Setup(Get()->position);
        solid.Setup(Get()->solid);
        sprites.Setup(Get()->sprites);
    }

    DataBreakdown<Build::Package<::Atmos::Tile>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        position("Position", this),
        solid("Solid", this),
        sprites("Sprites", this)
    {
        AddAllChildren();
        SubscribeEvents();
        sprites.SetPrependEntryName("Sprite");
    }

    DataBreakdown<Build::Package<::Atmos::Tile>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        position(std::move(arg.position), this),
        solid(std::move(arg.solid), this),
        sprites(std::move(arg.sprites), this)
    {
        AddAllChildren();
        SubscribeEvents();
    }

    DataBreakdown<Build::Package<::Atmos::Tile>>& DataBreakdown<Build::Package<::Atmos::Tile>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        position = std::move(arg.position);
        solid = std::move(arg.solid);
        sprites = std::move(arg.sprites);
        return *this;
    }

    ::Atmos::String DataBreakdown<Build::Package<::Atmos::Tile>>::GetString(const Build::Package<::Atmos::GridPosition> &position)
    {
        return ::Atmos::String("(" + ::Atmos::ToString(position.x.Build()) + ", " + ::Atmos::ToString(position.y.Build()) + ", " + ::Atmos::ToString(position.z.Build()) + ")");
    }
}