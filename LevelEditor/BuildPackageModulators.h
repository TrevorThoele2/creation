#pragma once

#include "BuildPackage.h"
#include "BuildPackageGeneral.h"
#include "BuildPackageList.h"
#include "BuildPackageVariant.h"

#include <Atmos/ModulatorGeneratorRoute.h>
#include <Function/Variant.h>

namespace Creation
{
    namespace Build
    {
        template<>
        class Package<::Atmos::Modulator::Value> : public PackageBase
        {
        public:
            typedef ::Atmos::Modulator::Value BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            typedef Package<::Atmos::Modulator::ValueTraits<BuildT::Type::INT>::T> IntPackage;
            typedef Package<::Atmos::Modulator::ValueTraits<BuildT::Type::FLOAT>::T> FloatPackage;

            typedef std::underlying_type<BuildT::Type>::type Underlying;
            Package<Underlying> type;
            typedef ::function::Variant<IntPackage, FloatPackage> VariantT;
            VariantT variant;

            Package();
            Package(const Package &arg);
            Package(Package &&arg);
            Package& operator=(const Package &arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
            BUILD_PACKAGE_DEFAULT_CLONE;

            void SetType(BuildT::Type type);
        };

        template<>
        class Package<::Atmos::Modulator::GeneratorRoute> : public PackageBase
        {
        public:
            typedef ::Atmos::Modulator::GeneratorRoute BuildT;

            class NodeEntryPackage : public PackageBase
            {
            private:
                INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
                INSCRIPTION_ACCESS;
            public:
                typedef Package<::Atmos::Modulator::TrackNodeInterpolation::Acceleration> InterpolationAccelerationT;
                typedef Package<::Atmos::Modulator::TrackNodeInterpolation::Rate> InterpolationRateT;
            public:
                class EndStateNormal : public PackageBase
                {
                private:
                    INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
                    INSCRIPTION_ACCESS;
                public:
                    Package<::Atmos::Modulator::Value> value;

                    EndStateNormal();
                    EndStateNormal(const EndStateNormal &arg) = default;
                    EndStateNormal& operator=(const EndStateNormal &arg) = default;
                    BUILD_PACKAGE_DEFAULT_CLONE_SPECIFIC(EndStateNormal);
                    EndStateNormal(EndStateNormal &&arg);
                    EndStateNormal& operator=(EndStateNormal &&arg);
                    bool operator==(const EndStateNormal &arg) const;
                    bool operator!=(const EndStateNormal &arg) const;

                    void SetType(::Atmos::Modulator::Value::Type type);
                };

                class EndStateRandom : public PackageBase
                {
                private:
                    INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
                    INSCRIPTION_ACCESS;
                public:
                    Package<::Atmos::Range<::Atmos::Modulator::Value>> value;

                    BUILD_PACKAGE_DEFAULT_SPECIFIC(EndStateRandom);
                    EndStateRandom(EndStateRandom &&arg);
                    EndStateRandom& operator=(EndStateRandom &&arg);
                    bool operator==(const EndStateRandom &arg) const;
                    bool operator!=(const EndStateRandom &arg) const;

                    void SetType(::Atmos::Modulator::Value::Type type);
                };

                class InterpolationLinear : public PackageBase
                {
                private:
                    INSCRIPTION_SERIALIZE_FUNCTION{}
                    INSCRIPTION_ACCESS;
                public:
                    BUILD_PACKAGE_DEFAULT_SPECIFIC(InterpolationLinear);
                    InterpolationLinear(InterpolationLinear &&arg);
                    InterpolationLinear& operator=(InterpolationLinear &&arg);
                    bool operator==(const InterpolationLinear &arg) const;
                    bool operator!=(const InterpolationLinear &arg) const;
                };

                class InterpolationOscillation : public PackageBase
                {
                private:
                    INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
                    INSCRIPTION_ACCESS;
                public:
                    InterpolationAccelerationT acceleration;
                    InterpolationRateT rate;
                    BUILD_PACKAGE_DEFAULT_SPECIFIC(InterpolationOscillation);
                    InterpolationOscillation(InterpolationOscillation &&arg);
                    InterpolationOscillation& operator=(InterpolationOscillation &&arg);
                    bool operator==(const InterpolationOscillation &arg) const;
                    bool operator!=(const InterpolationOscillation &arg) const;
                };
            public:
                typedef std::underlying_type<::Atmos::Modulator::TrackNodeEndState::Type>::type EndStateTypeUnderlying;
                Package<EndStateTypeUnderlying> endStateType;
                typedef ::function::Variant<EndStateNormal, EndStateRandom> EndStateVariantT;
                EndStateVariantT endStateVariant;

                typedef std::underlying_type<::Atmos::Modulator::TrackNodeInterpolation::Type>::type InterpolationTypeUnderlying;
                Package<InterpolationTypeUnderlying> interpolationType;
                typedef ::function::Variant<InterpolationLinear, InterpolationOscillation> InterpolationVariantT;
                InterpolationVariantT interpolationVariant;

                NodeEntryPackage();
                NodeEntryPackage(const NodeEntryPackage &arg) = default;
                NodeEntryPackage(NodeEntryPackage &&arg);
                NodeEntryPackage& operator=(const NodeEntryPackage &arg) = default;
                NodeEntryPackage& operator=(NodeEntryPackage &&arg);
                bool operator==(const NodeEntryPackage &arg) const;
                bool operator!=(const NodeEntryPackage &arg) const;
                BUILD_PACKAGE_DEFAULT_CLONE_SPECIFIC(NodeEntryPackage);
            };

            class TrackNodePackage : public PackageBase
            {
            private:
                INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
                INSCRIPTION_ACCESS;
            public:
                Package<::Atmos::Name> prototype;
                Package<::Atmos::RandomAccessSequence<NodeEntryPackage>> nodes;

                BUILD_PACKAGE_DEFAULT_SPECIFIC(TrackNodePackage);
                TrackNodePackage(TrackNodePackage &&arg);
                TrackNodePackage& operator=(TrackNodePackage &&arg);
                bool operator==(const TrackNodePackage &arg) const;
                bool operator!=(const TrackNodePackage &arg) const;
            };
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Name> prototype;
            Package<::Atmos::RandomAccessSequence<TrackNodePackage>> tracks;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };
    }
}