#pragma once

#include "BuildPackage.h"

#include <Atmos/AssetReference.h>
#include <Atmos/BoundedNumber.h>
#include <Atmos/FilePath.h>
#include <Atmos/Percentage.h>
#include <Atmos/Flags.h>
#include <Atmos/Angle.h>
#include <Atmos/GridPosition.h>
#include <Atmos/Position3D.h>
#include <Atmos/Name.h>
#include <Atmos/RegistryObjectReference.h>
#include <Atmos/CharacterClassGroup.h>
#include <Atmos/Script.h>
#include <Atmos/Sound.h>
#include <Atmos/Color.h>
#include <Atmos/Sprite.h>
#include <Atmos/Element.h>
#include <Atmos/CombatTransaction.h>
#include <Atmos/Acumen.h>
#include <Atmos/Action.h>

namespace Creation
{
    namespace Build
    {
        template<>
        class Package<bool> : public PackageBase
        {
        public:
            typedef bool BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            BuildT value;

            Package();
            Package(const Package &arg) = default;
            Package(Package &&arg);
            Package& operator=(const Package &arg) = default;
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            Package* Clone() const override final;
            String ToString() const override final;
        };

        template<>
        class Package<std::uint8_t> : public PackageBase
        {
        public:
            typedef std::uint8_t BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            BuildT value;

            Package();
            Package(const Package &arg) = default;
            Package(Package &&arg);
            Package& operator=(const Package &arg) = default;
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            Package* Clone() const override final;
            String ToString() const override final;
        };

        template<>
        class Package<std::uint16_t> : public PackageBase
        {
        public:
            typedef std::uint16_t BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            BuildT value;

            Package();
            Package(const Package &arg) = default;
            Package(Package &&arg);
            Package& operator=(const Package &arg) = default;
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            Package* Clone() const override final;
            String ToString() const override final;
        };

        template<>
        class Package<std::uint32_t> : public PackageBase
        {
        public:
            typedef std::uint32_t BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            BuildT value;

            Package();
            Package(const Package &arg) = default;
            Package(Package &&arg);
            Package& operator=(const Package &arg) = default;
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            Package* Clone() const override final;
            String ToString() const override final;
        };

        template<>
        class Package<std::uint64_t> : public PackageBase
        {
        public:
            typedef std::uint64_t BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            BuildT value;

            Package();
            Package(const Package &arg) = default;
            Package(Package &&arg);
            Package& operator=(const Package &arg) = default;
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            Package* Clone() const override final;
            String ToString() const override final;
        };

        template<>
        class Package<std::int8_t> : public PackageBase
        {
        public:
            typedef std::int8_t BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            BuildT value;

            Package();
            Package(const Package &arg) = default;
            Package(Package &&arg);
            Package& operator=(const Package &arg) = default;
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            Package* Clone() const override final;
            String ToString() const override final;
        };

        template<>
        class Package<std::int16_t> : public PackageBase
        {
        public:
            typedef std::int16_t BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            BuildT value;

            Package();
            Package(const Package &arg) = default;
            Package(Package &&arg);
            Package& operator=(const Package &arg) = default;
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            Package* Clone() const override final;
            String ToString() const override final;
        };

        template<>
        class Package<std::int32_t> : public PackageBase
        {
        public:
            typedef std::int32_t BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            BuildT value;

            Package();
            Package(const Package &arg) = default;
            Package(Package &&arg);
            Package& operator=(const Package &arg) = default;
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            Package* Clone() const override final;
            String ToString() const override final;
        };

        template<>
        class Package<std::int64_t> : public PackageBase
        {
        public:
            typedef std::int64_t BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            BuildT value;

            Package();
            Package(const Package &arg) = default;
            Package(Package &&arg);
            Package& operator=(const Package &arg) = default;
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            Package* Clone() const override final;
            String ToString() const override final;
        };

        template<>
        class Package<float> : public PackageBase
        {
        public:
            typedef float BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            BuildT value;

            Package();
            Package(const Package &arg) = default;
            Package(Package &&arg);
            Package& operator=(const Package &arg) = default;
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            Package* Clone() const override final;
            String ToString() const override final;
        };

        template<>
        class Package<double> : public PackageBase
        {
        public:
            typedef double BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            BuildT value;

            Package();
            Package(const Package &arg) = default;
            Package(Package &&arg);
            Package& operator=(const Package &arg) = default;
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            Package* Clone() const override final;
            String ToString() const override final;
        };

        template<class T, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type lowerBound, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type upperBound>
        class Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>> : public PackageBase
        {
        public:
            typedef ::Atmos::StaticBoundedNumber<T, lowerBound, upperBound> BuildT;
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
            String ToString() const override final;
        };

        template<class T, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type lowerBound, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type upperBound>
        void Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>::Serialize(::inscription::Scribe &scribe)
        {
            scribe(value);
        }

        template<class T, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type lowerBound, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type upperBound>
        Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        template<class T, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type lowerBound, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type upperBound>
        Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>& Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        template<class T, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type lowerBound, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type upperBound>
        bool Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        template<class T, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type lowerBound, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type upperBound>
        bool Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        template<class T, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type lowerBound, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type upperBound>
        typename Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>::BuildT Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>::Build() const
        {
            return value;
        }

        template<class T, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type lowerBound, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type upperBound>
        String Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>::ToString() const
        {
            return ::Atmos::ToString(value.Get());
        }

        template<class T>
        class Package<::Atmos::FixedPoint<T>> : public PackageBase
        {
        public:
            typedef ::Atmos::FixedPoint<T> BuildT;
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
            String ToString() const override final;
        };

        template<class T>
        void Package<::Atmos::FixedPoint<T>>::Serialize(::inscription::Scribe &scribe)
        {
            scribe(value);
        }

        template<class T>
        Package<::Atmos::FixedPoint<T>>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        template<class T>
        Package<::Atmos::FixedPoint<T>>& Package<::Atmos::FixedPoint<T>>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        template<class T>
        bool Package<::Atmos::FixedPoint<T>>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        template<class T>
        bool Package<::Atmos::FixedPoint<T>>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        template<class T>
        typename Package<::Atmos::FixedPoint<T>>::BuildT Package<::Atmos::FixedPoint<T>>::Build() const
        {
            return value;
        }

        template<class T>
        String Package<::Atmos::FixedPoint<T>>::ToString() const
        {
            return ::Atmos::ToString(value);
        }

        template<>
        class Package<::Atmos::String> : public PackageBase
        {
        public:
            typedef ::Atmos::String BuildT;
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
            String ToString() const override final;
        };

        template<>
        class Package<::Atmos::FilePath> : public PackageBase
        {
        public:
            typedef ::Atmos::FilePath BuildT;
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
            String ToString() const override final;
        };

        template<>
        class Package<::Atmos::FileName> : public PackageBase
        {
        public:
            typedef ::Atmos::FileName BuildT;
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
            String ToString() const override final;
        };

        template<>
        class Package<::Atmos::Percentage> : public PackageBase
        {
        public:
            typedef ::Atmos::Percentage BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<BuildT::WrappedT> value;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            String ToString() const override final;
        };

        template<class Flag>
        class Package<::Atmos::Flags<Flag>> : public PackageBase
        {
        public:
            typedef ::Atmos::Flags<Flag> BuildT;
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

        template<class Flag>
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Flags<Flag>>)
        {
            scribe(value);
        }

        template<class Flag>
        Package<::Atmos::Flags<Flag>>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        template<class Flag>
        Package<::Atmos::Flags<Flag>>& Package<::Atmos::Flags<Flag>>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        template<class Flag>
        bool Package<::Atmos::Flags<Flag>>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        template<class Flag>
        bool Package<::Atmos::Flags<Flag>>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        template<class Flag>
        typename Package<::Atmos::Flags<Flag>>::BuildT Package<::Atmos::Flags<Flag>>::Build() const
        {
            return value;
        }

        template<class PackageT>
        class Package<::Atmos::Optional<PackageT>> : public PackageBase
        {
        public:
            typedef ::Atmos::Optional<PackageT> BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<bool> valid;
            PackageT value;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<class PackageT>
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Optional<PackageT>>)
        {
            scribe(valid);
            if(valid.Build())
                scribe(value);
        }

        template<class PackageT>
        Package<::Atmos::Optional<PackageT>>::Package(Package &&arg) : valid(std::move(arg.valid)), value(std::move(arg.value))
        {}

        template<class PackageT>
        Package<::Atmos::Optional<PackageT>>& Package<::Atmos::Optional<PackageT>>::operator=(Package &&arg)
        {
            valid = std::move(arg.valid);
            value = std::move(arg.value);
            return *this;
        }

        template<class PackageT>
        bool Package<::Atmos::Optional<PackageT>>::operator==(const Package &arg) const
        {
            if (valid.Build())
                return valid == arg.valid && value == arg.value;
            else
                return valid == arg.valid;
        }

        template<class PackageT>
        bool Package<::Atmos::Optional<PackageT>>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        template<class PackageT>
        typename Package<::Atmos::Optional<PackageT>>::BuildT Package<::Atmos::Optional<PackageT>>::Build() const
        {
            if (valid.Build())
                return BuildT(value);
            else
                return BuildT();
        }

        template<>
        class Package<::Atmos::Angle> : public PackageBase
        {
        public:
            typedef ::Atmos::Angle BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<BuildT::ValueT> value;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            String ToString() const override final;
        };

        template<>
        class Package<::Atmos::Position3D> : public PackageBase
        {
        public:
            typedef ::Atmos::Position3D BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<BuildT::ValueT> x;
            Package<BuildT::ValueT> y;
            Package<BuildT::ValueT> z;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            String ToString() const override final;
        };

        template<>
        class Package<::Atmos::GridPosition> : public PackageBase
        {
        public:
            typedef ::Atmos::GridPosition BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<BuildT::ValueT> x;
            Package<BuildT::ValueT> y;
            Package<BuildT::ValueT> z;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            String ToString() const override final;
        };

        template<>
        class Package<::Atmos::RelativeGridPosition> : public PackageBase
        {
        public:
            typedef ::Atmos::RelativeGridPosition BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<BuildT::ValueT> x;
            Package<BuildT::ValueT> y;
            Package<BuildT::ValueT> z;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            String ToString() const override final;
        };

        template<>
        class Package<::Atmos::Direction> : public PackageBase
        {
        public:
            typedef ::Atmos::Direction BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<std::underlying_type<BuildT::ValueT>::type> value;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<class T>
        class Package<::Atmos::AssetReference<T>> : public PackageBase
        {
        public:
            typedef ::Atmos::AssetReference<T> BuildT;
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
        Package<::Atmos::AssetReference<T>>::Package(Package &&arg) : name(std::move(arg.name))
        {}

        template<class T>
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::AssetReference<T>>)
        {
            scribe(name);
        }

        template<class T>
        Package<::Atmos::AssetReference<T>>& Package<::Atmos::AssetReference<T>>::operator=(Package &&arg)
        {
            name = std::move(arg.name);
            return *this;
        }

        template<class T>
        bool Package<::Atmos::AssetReference<T>>::operator==(const Package &arg) const
        {
            return name == arg.name;
        }

        template<class T>
        bool Package<::Atmos::AssetReference<T>>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        template<class T>
        typename Package<::Atmos::AssetReference<T>>::BuildT Package<::Atmos::AssetReference<T>>::Build() const
        {
            return ::Atmos::AssetRegistry<T>::Find(name.Build());
        }

        template<>
        class Package<::Atmos::Color> : public PackageBase
        {
        public:
            typedef ::Atmos::Color BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<BuildT::ValueT> a;
            Package<BuildT::ValueT> r;
            Package<BuildT::ValueT> g;
            Package<BuildT::ValueT> b;

            Package();
            Package(const Package &arg) = default;
            Package(Package &&arg);
            Package& operator=(const Package &arg) = default;
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            Package* Clone() const override final;
        };

        template<>
        class Package<::Atmos::Sprite> : public PackageBase
        {
        public:
            typedef ::Atmos::Sprite BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::AssetReference<::Atmos::Material>> material;
            Package<::Atmos::AssetReference<::Atmos::ShaderAsset>> shaderPatch;
            Package<BuildT::Index> index;
            Package<::Atmos::Color> color;
            Package<::Atmos::Size3D::ValueT> xScaler;
            Package<::Atmos::Size3D::ValueT> yScaler;
            Package<::Atmos::Size3D::ValueT> zScaler;
            Package<::Atmos::Angle> xRotation;
            Package<::Atmos::Angle> yRotation;
            Package<::Atmos::Angle> zRotation;

            Package();
            Package(const Package &arg) = default;
            Package(Package &&arg);
            Package& operator=(const Package &arg) = default;
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            Package* Clone() const override final;
        };

        template<>
        class Package<::Atmos::Sound> : public PackageBase
        {
        public:
            typedef ::Atmos::Sound BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::AssetReference<::Atmos::AudioAsset>> audio;
            Package<::Atmos::Position3D> position;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::Element> : public PackageBase
        {
        public:
            typedef ::Atmos::Element BuildT;
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

        template<>
        class Package<::Atmos::CombatTransactionGenerator> : public PackageBase
        {
        public:
            typedef ::Atmos::CombatTransactionGenerator BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Name> resourceName;
            Package<::Atmos::Name> statName;
            Package<::Atmos::Element> element;
            Package<::Atmos::Name> proficiencyName;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::Acumen> : public PackageBase
        {
        public:
            typedef ::Atmos::Acumen BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<BuildT::ValueT> value;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<class T>
        class Package<::Atmos::Range<T>> : public PackageBase
        {
        public:
            typedef ::Atmos::Range<T> BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<T> first;
            Package<T> second;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<class T>
        void Package<::Atmos::Range<T>>::Serialize(::inscription::Scribe &scribe)
        {
            scribe(first, second);
        }

        template<class T>
        Package<::Atmos::Range<T>>::Package(Package &&arg) : first(std::move(arg.first)), second(std::move(arg.second))
        {}

        template<class T>
        Package<::Atmos::Range<T>>& Package<::Atmos::Range<T>>::operator=(Package &&arg)
        {
            first = std::move(arg.first);
            second = std::move(arg.second);
            return *this;
        }

        template<class T>
        bool Package<::Atmos::Range<T>>::operator==(const Package &arg) const
        {
            return first == arg.first && second == arg.second;
        }

        template<class T>
        bool Package<::Atmos::Range<T>>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        template<class T>
        typename Package<::Atmos::Range<T>>::BuildT Package<::Atmos::Range<T>>::Build() const
        {
            return BuildT(first.Build(), second.Build());
        }
    }
}