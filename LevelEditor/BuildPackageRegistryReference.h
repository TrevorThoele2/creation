#pragma once

#include "BuildPackage.h"
#include "BuildPackageGeneral.h"

namespace Creation
{
    namespace Build
    {
        template<class T>
        class Package<::Atmos::RegistryObjectReference<T>> : public PackageBase
        {
        public:
            typedef ::Atmos::RegistryObjectReference<T> BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Name> name;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<class T>
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::RegistryObjectReference<T>>)
        {
            scribe(name);
        }

        template<class T>
        Package<::Atmos::RegistryObjectReference<T>>::Package(Package &&arg) : name(std::move(arg.name))
        {}

        template<class T>
        Package<::Atmos::RegistryObjectReference<T>>& Package<::Atmos::RegistryObjectReference<T>>::operator=(Package &&arg)
        {
            name = std::move(arg.name);
            return *this;
        }

        template<class T>
        bool Package<::Atmos::RegistryObjectReference<T>>::operator==(const Package &arg) const
        {
            return name == arg.name;
        }

        template<class T>
        bool Package<::Atmos::RegistryObjectReference<T>>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        template<class T>
        typename Package<::Atmos::RegistryObjectReference<T>>::BuildT Package<::Atmos::RegistryObjectReference<T>>::Build() const
        {
            return ::Atmos::Registry<T>::Find(name.Build());
        }
    }
}