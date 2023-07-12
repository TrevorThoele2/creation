
#include "BuildPackageAction.h"

namespace Creation
{
    namespace Build
    {
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Act::Action::Parameter>)
        {
            scribe(variant);
        }

        Package<::Atmos::Act::Action::Parameter>::Package(Package &&arg) : variant(std::move(arg.variant))
        {}

        Package<::Atmos::Act::Action::Parameter>& Package<::Atmos::Act::Action::Parameter>::operator=(Package &&arg)
        {
            variant = std::move(arg.variant);
            return *this;
        }

        bool Package<::Atmos::Act::Action::Parameter>::operator==(const Package &arg) const
        {
            return variant == arg.variant;
        }

        bool Package<::Atmos::Act::Action::Parameter>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Act::Action::Parameter>::BuildT Package<::Atmos::Act::Action::Parameter>::Build() const
        {
            return BuildT(variant.Build());
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Act::Action>)
        {
            scribe(id);
            scribe(parameters);
        }

        Package<::Atmos::Act::Action>::Package(Package &&arg) : id(std::move(arg.id)), parameters(std::move(arg.parameters))
        {}

        Package<::Atmos::Act::Action>& Package<::Atmos::Act::Action>::operator=(Package &&arg)
        {
            id = std::move(arg.id);
            parameters = std::move(arg.parameters);
            return *this;
        }

        bool Package<::Atmos::Act::Action>::operator==(const Package &arg) const
        {
            return id == arg.id && parameters == arg.parameters;
        }

        bool Package<::Atmos::Act::Action>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Act::Action>::BuildT Package<::Atmos::Act::Action>::Build() const
        {
            BuildT ret(id.Build());
            std::uint32_t count = 0;
            for (auto &loop : parameters.value)
                ret.SetParameter(count, loop.Build());
            return ret;
        }
    }
}