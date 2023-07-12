
#include "BuildPackageNameValuePair.h"

namespace Creation
{
    namespace Build
    {
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::NameValuePair>)
        {
            scribe(name);
            scribe(variant);
        }

        Package<::Atmos::NameValuePair>::Package(Package &&arg) : name(std::move(arg.name)), variant(std::move(arg.variant))
        {}

        Package<::Atmos::NameValuePair>& Package<::Atmos::NameValuePair>::operator=(Package &&arg)
        {
            name = std::move(arg.name);
            variant = std::move(arg.variant);
            return *this;
        }

        bool Package<::Atmos::NameValuePair>::operator==(const Package &arg) const
        {
            return name == arg.name && variant == arg.variant;
        }

        bool Package<::Atmos::NameValuePair>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::NameValuePair>::BuildT Package<::Atmos::NameValuePair>::Build() const
        {
            return BuildT(name.Build(), variant.Build());
        }
    }
}