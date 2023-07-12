#pragma once

#include "String.h"
#include <Atmos/Serialization.h>

namespace Creation
{
    namespace Build
    {
        class PackageBase
        {
        public:
            virtual ~PackageBase() = 0 {}
            virtual PackageBase* Clone() const = 0;
            virtual String ToString() const { return ""; };
        };

        template<class T>
        class Package;

#define BUILD_PACKAGE_DEFAULT_CONSTRUCTORS                  \
        Package() = default;                                \
        Package(const Package &arg) = default;              \
        Package& operator=(const Package &arg) = default;

#define BUILD_PACKAGE_DEFAULT_CONSTRUCTORS_SPECIFIC(type)   \
        type() = default;                                   \
        type(const type &arg) = default;                    \
        type& operator=(const type &arg) = default;

#define BUILD_PACKAGE_DEFAULT_CLONE  \
        Package* Clone() const override final { return new Package(); }

#define BUILD_PACKAGE_DEFAULT_CLONE_SPECIFIC(type)  \
        type* Clone() const override final { return new type(); }

// Combines default constructors and default clone
#define BUILD_PACKAGE_DEFAULT               \
        BUILD_PACKAGE_DEFAULT_CONSTRUCTORS; \
        BUILD_PACKAGE_DEFAULT_CLONE;

// Combines default constructors specific and default clone specific
#define BUILD_PACKAGE_DEFAULT_SPECIFIC(type)                \
        BUILD_PACKAGE_DEFAULT_CONSTRUCTORS_SPECIFIC(type);  \
        BUILD_PACKAGE_DEFAULT_CLONE_SPECIFIC(type);
    }
}