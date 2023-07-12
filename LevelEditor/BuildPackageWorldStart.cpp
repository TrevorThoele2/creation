
#include "BuildPackageWorldStart.h"

namespace Creation
{
    namespace Build
    {
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::WorldStart>)
        {
            scribe(id);
        }

        Package<::Atmos::WorldStart>::Package(Package &&arg) : id(std::move(arg.id))
        {}

        Package<::Atmos::WorldStart>& Package<::Atmos::WorldStart>::operator=(Package &&arg)
        {
            id = std::move(arg.id);
            return *this;
        }

        bool Package<::Atmos::WorldStart>::operator==(const Package &arg) const
        {
            return id == arg.id;
        }

        bool Package<::Atmos::WorldStart>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::WorldStart>::BuildT Package<::Atmos::WorldStart>::Build() const
        {
            return BuildT(id.Build());
        }
    }
}