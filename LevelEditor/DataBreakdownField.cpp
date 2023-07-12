
#include "DataBreakdownField.h"

namespace Creation
{
    void DataBreakdown<Build::Package<::Atmos::Field>>::AddAllChildren()
    {
        AddChild(tiles);
        AddChild(entities);
    }

    void DataBreakdown<Build::Package<::Atmos::Field>>::SetupImpl()
    {
        tiles.Setup(Get()->tiles);
        entities.Setup(Get()->entities);
    }

    DataBreakdown<Build::Package<::Atmos::Field>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        id("ID", this),
        tiles("Tiles", this),
        entities("Entities", this)
    {
        AddAllChildren();
        tiles.SetPrependEntryName("Tile");
        entities.SetPrependEntryName("Entity");
    }

    DataBreakdown<Build::Package<::Atmos::Field>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        id(std::move(arg.id), this),
        tiles(std::move(arg.tiles), this),
        entities(std::move(arg.entities), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Field>>& DataBreakdown<Build::Package<::Atmos::Field>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        id = std::move(arg.id);
        tiles = std::move(arg.tiles);
        entities = std::move(arg.entities);
        return *this;
    }
}