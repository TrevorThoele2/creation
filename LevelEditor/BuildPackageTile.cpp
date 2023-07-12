
#include "BuildPackageTile.h"

namespace Creation
{
    namespace Build
    {
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Tile>)
        {
            scribe(position);
            scribe(solid);
            scribe(sprites);
        }

        Package<::Atmos::Tile>::Package(Package &&arg) : position(std::move(arg.position)), solid(std::move(arg.solid)), sprites(std::move(arg.sprites))
        {}

        Package<::Atmos::Tile>& Package<::Atmos::Tile>::operator=(Package &&arg)
        {
            position = std::move(arg.position);
            solid = std::move(arg.solid);
            sprites = std::move(arg.sprites);
            return *this;
        }

        bool Package<::Atmos::Tile>::operator==(const Package &arg) const
        {
            return position == arg.position && solid == arg.solid && sprites == arg.sprites;
        }

        bool Package<::Atmos::Tile>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Tile>::BuildT Package<::Atmos::Tile>::Build() const
        {
            BuildT ret(position.Build());
            ret.SetSolid(solid.Build());
            for (auto &loop : sprites.value)
                ret.CreateSprite(loop.id.Build(), loop.Build());
            return ret;
        }
    }
}