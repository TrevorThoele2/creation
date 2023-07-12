#pragma once

#include "BuildPackage.h"

#include <Atmos/RandomAccessSequence.h>

namespace Creation
{
    namespace Build
    {
        template<class T>
        class Package<::Atmos::RandomAccessSequence<T>> : public PackageBase
        {
        public:
            typedef ::Atmos::RandomAccessSequence<T> BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            BuildT value;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<class T>
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::RandomAccessSequence<T>>)
        {
            scribe(value);
        }

        template<class T>
        Package<::Atmos::RandomAccessSequence<T>>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        template<class T>
        Package<::Atmos::RandomAccessSequence<T>>& Package<::Atmos::RandomAccessSequence<T>>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        template<class T>
        bool Package<::Atmos::RandomAccessSequence<T>>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        template<class T>
        bool Package<::Atmos::RandomAccessSequence<T>>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        template<class T>
        typename Package<::Atmos::RandomAccessSequence<T>>::BuildT Package<::Atmos::RandomAccessSequence<T>>::Build() const
        {
            return value;
        }
    }
}