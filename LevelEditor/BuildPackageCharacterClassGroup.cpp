
#include "BuildPackageCharacterClassGroup.h"

#include "BuildPackageRegistries.h"

namespace Creation
{
    namespace Build
    {
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::CharacterClassGroup>)
        {
            scribe(classes);
        }

        Package<::Atmos::CharacterClassGroup>::Package(Package &&arg) : classes(std::move(arg.classes))
        {}

        Package<::Atmos::CharacterClassGroup> & Package<::Atmos::CharacterClassGroup>::operator=(Package &&arg)
        {
            classes = std::move(arg.classes);
            return *this;
        }

        bool Package<::Atmos::CharacterClassGroup>::operator==(const Package &arg) const
        {
            return classes == arg.classes;
        }

        bool Package<::Atmos::CharacterClassGroup>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::CharacterClassGroup>::BuildT Package<::Atmos::CharacterClassGroup>::Build() const
        {
            BuildT ret;
            for (auto &loop : classes.value)
                ret.Add(loop.Build());
            return ret;
        }
    }
}