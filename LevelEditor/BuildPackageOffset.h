#pragma once

#include "BuildPackage.h"

#include <Atmos/ObjectOffsetHandle.h>

namespace Creation
{
    namespace Build
    {
        template<class T, class Position>
        class Package<::Atmos::ObjectOffsetHandle<T, Position>> : public PackageBase
        {
        public:
            typedef ::Atmos::ObjectOffsetHandle<T, Position> BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<typename BuildT::ObjectT> wrapped;
            Package<typename ::Atmos::IDManagerBase::ID> id;
            Package<typename BuildT::OffsetValueT> xOffset;
            Package<typename BuildT::OffsetValueT> yOffset;
            Package<typename BuildT::OffsetValueT> zOffset;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<class T, class Position>
        void  Package<::Atmos::ObjectOffsetHandle<T, Position>>::Serialize(::inscription::Scribe &scribe)
        {
            scribe(wrapped);
            scribe(id);
            scribe(xOffset, yOffset, zOffset);
        }

        template<class T, class Position>
        Package<::Atmos::ObjectOffsetHandle<T, Position>>::Package(Package &&arg) : wrapped(std::move(arg.wrapped)), id(std::move(arg.id)), xOffset(std::move(arg.xOffset)), yOffset(std::move(arg.yOffset)), zOffset(std::move(arg.zOffset))
        {}

        template<class T, class Position>
        Package<::Atmos::ObjectOffsetHandle<T, Position>>& Package<::Atmos::ObjectOffsetHandle<T, Position>>::operator=(Package &&arg)
        {
            wrapped = std::move(arg.wrapped);
            id = std::move(arg.id);
            xOffset = std::move(arg.xOffset);
            yOffset = std::move(arg.yOffset);
            zOffset = std::move(arg.zOffset);
            return *this;
        }

        template<class T, class Position>
        bool Package<::Atmos::ObjectOffsetHandle<T, Position>>::operator==(const Package &arg) const
        {
            return wrapped == arg.wrapped && id == arg.id && xOffset == arg.xOffset && yOffset == arg.yOffset && zOffset == arg.zOffset;
        }

        template<class T, class Position>
        bool Package<::Atmos::ObjectOffsetHandle<T, Position>>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        template<class T, class Position>
        typename Package<::Atmos::ObjectOffsetHandle<T, Position>>::BuildT Package<::Atmos::ObjectOffsetHandle<T, Position>>::Build() const
        {
            return BuildT(wrapped.Build(), xOffset.Build(), yOffset.Build(), zOffset.Build());
        }
    }
}