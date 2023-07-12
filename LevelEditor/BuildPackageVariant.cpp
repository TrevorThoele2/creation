
#include "BuildPackageVariant.h"

namespace Creation
{
    namespace Build
    {
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Variant>)
        {
            scribe(value);
        }

        Package<::Atmos::Variant>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<::Atmos::Variant>& Package<::Atmos::Variant>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<::Atmos::Variant>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<::Atmos::Variant>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Variant>::BuildT Package<::Atmos::Variant>::Build() const
        {
            return value;
        }
    }
}