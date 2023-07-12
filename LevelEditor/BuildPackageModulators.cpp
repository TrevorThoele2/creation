
#include "BuildPackageModulators.h"

namespace Creation
{
    namespace Build
    {
        struct PackageValueStrategies
        {
            enum class StrategyType
            {
                SERIALIZE,
                SET_TYPE
            };

            template<StrategyType strategy>
            using Selector = ::function::StrategySelector<StrategyType, strategy>;

            template<class T>
            static void Do(T &package, ::inscription::Scribe &scribe, Selector<StrategyType::SERIALIZE>)
            {
                scribe(package);
            }

            static void Do(Package<::Atmos::Modulator::Value>::IntPackage &package, ::Atmos::Modulator::Value::Type type, Selector<StrategyType::SET_TYPE>)
            {
                package.value = 0;
            }

            static void Do(Package<::Atmos::Modulator::Value>::FloatPackage &package, ::Atmos::Modulator::Value::Type type, Selector<StrategyType::SET_TYPE>)
            {
                package.value = 0;
            }
        };

        template<PackageValueStrategies::StrategyType strategy>
        using ValueStrategy = PackageValueStrategies::Selector<strategy>;

        struct PackageNodeEntryStrategies
        {
            enum class StrategyType
            {
                SERIALIZE
            };

            template<StrategyType strategy>
            using Selector = ::function::StrategySelector<StrategyType, strategy>;

            template<class T>
            static void Do(T &package, ::inscription::Scribe &scribe, Selector<StrategyType::SERIALIZE>)
            {
                scribe(package);
            }
        };

        template<PackageNodeEntryStrategies::StrategyType strategy>
        using NodeEntryStrategy = PackageNodeEntryStrategies::Selector<strategy>;

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Modulator::Value>)
        {
            scribe(type);
            ::function::Visit<PackageValueStrategies>(variant, scribe, ValueStrategy<PackageValueStrategies::StrategyType::SERIALIZE>{});
        }

        Package<::Atmos::Modulator::Value>::Package() : variant(IntPackage())
        {
            type.value = static_cast<Underlying>(BuildT::Type::INT);
            variant.Set(IntPackage());
        }

        Package<::Atmos::Modulator::Value>::Package(const Package &arg) : PackageBase(arg), type(arg.type), variant(arg.variant)
        {}

        Package<::Atmos::Modulator::Value>::Package(Package &&arg) : PackageBase(std::move(arg)), type(std::move(arg.type)), variant(std::move(arg.variant))
        {}

        Package<::Atmos::Modulator::Value>& Package<::Atmos::Modulator::Value>::operator=(const Package &arg)
        {
            PackageBase::operator=(arg);
            type = arg.type;
            variant = arg.variant;
            return *this;
        }

        Package<::Atmos::Modulator::Value>& Package<::Atmos::Modulator::Value>::operator=(Package &&arg)
        {
            PackageBase::operator=(std::move(arg));
            type = std::move(arg.type);
            variant = std::move(arg.variant);
            return *this;
        }

        bool Package<::Atmos::Modulator::Value>::operator==(const Package &arg) const
        {
            return type == arg.type && variant == arg.variant;
        }

        bool Package<::Atmos::Modulator::Value>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Modulator::Value>::BuildT Package<::Atmos::Modulator::Value>::Build() const
        {
            BuildT ret;
            return ret;
        }

        void Package<::Atmos::Modulator::Value>::SetType(BuildT::Type type)
        {
            this->type.value = static_cast<Underlying>(type);
            ::function::Visit<PackageValueStrategies>(variant, type, ValueStrategy<PackageValueStrategies::StrategyType::SET_TYPE>{});
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateNormal)
        {
            scribe(value);
        }

        Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateNormal::EndStateNormal()
        {}

        Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateNormal::EndStateNormal(EndStateNormal &&arg) : value(std::move(arg.value))
        {}

        Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateNormal& Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateNormal::operator=(EndStateNormal &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateNormal::operator==(const EndStateNormal &arg) const
        {
            return value == arg.value;
        }

        bool Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateNormal::operator!=(const EndStateNormal &arg) const
        {
            return !(*this == arg);
        }

        void Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateNormal::SetType(::Atmos::Modulator::Value::Type type)
        {
            value.SetType(type);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateRandom)
        {
            scribe(value);
        }

        Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateRandom::EndStateRandom(EndStateRandom &&arg) : value(std::move(arg.value))
        {}

        Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateRandom& Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateRandom::operator=(EndStateRandom &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateRandom::operator==(const EndStateRandom &arg) const
        {
            return value == arg.value;
        }

        bool Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateRandom::operator!=(const EndStateRandom &arg) const
        {
            return !(*this == arg);
        }

        void Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateRandom::SetType(::Atmos::Modulator::Value::Type type)
        {
            value.first.SetType(type);
            value.second.SetType(type);
        }

        Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::InterpolationLinear::InterpolationLinear(InterpolationLinear &&arg)
        {}

        Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::InterpolationLinear& Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::InterpolationLinear::operator=(InterpolationLinear &&arg)
        {
            return *this;
        }

        bool Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::InterpolationLinear::operator==(const InterpolationLinear &arg) const
        {
            return true;
        }

        bool Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::InterpolationLinear::operator!=(const InterpolationLinear &arg) const
        {
            return !(*this == arg);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::InterpolationOscillation)
        {
            scribe(acceleration);
            scribe(rate);
        }

        Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::InterpolationOscillation::InterpolationOscillation(InterpolationOscillation &&arg) : acceleration(std::move(arg.acceleration)), rate(std::move(arg.rate))
        {}

        Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::InterpolationOscillation& Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::InterpolationOscillation::operator=(InterpolationOscillation &&arg)
        {
            acceleration = std::move(arg.acceleration);
            rate = std::move(arg.rate);
            return *this;
        }

        bool Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::InterpolationOscillation::operator==(const InterpolationOscillation &arg) const
        {
            return acceleration == arg.acceleration && rate == arg.rate;
        }

        bool Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::InterpolationOscillation::operator!=(const InterpolationOscillation &arg) const
        {
            return !(*this == arg);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage)
        {
            if (scribe.IsOutput())
            {
                scribe.Save(endStateType);
                ::function::Visit<PackageNodeEntryStrategies>(endStateVariant, scribe, NodeEntryStrategy<PackageNodeEntryStrategies::StrategyType::SERIALIZE>{});
                scribe.Save(interpolationType);
                ::function::Visit<PackageNodeEntryStrategies>(interpolationVariant, scribe, NodeEntryStrategy<PackageNodeEntryStrategies::StrategyType::SERIALIZE>{});
            }
            else // INPUT
            {
                scribe.Load(endStateType);
                switch (endStateType.Build())
                {
                case ::Atmos::Modulator::TrackNodeEndState::Type::NORMAL:
                    endStateVariant.Set(EndStateNormal());
                    break;
                case ::Atmos::Modulator::TrackNodeEndState::Type::RANDOM:
                    endStateVariant.Set(EndStateRandom());
                    break;
                }
                ::function::Visit<PackageNodeEntryStrategies>(endStateVariant, scribe, NodeEntryStrategy<PackageNodeEntryStrategies::StrategyType::SERIALIZE>{});
                
                scribe.Load(interpolationType);
                switch (interpolationType.Build())
                {
                case ::Atmos::Modulator::TrackNodeInterpolation::Type::LINEAR:
                    interpolationVariant.Set(InterpolationLinear());
                    break;
                case ::Atmos::Modulator::TrackNodeInterpolation::Type::OSCILLATION:
                    interpolationVariant.Set(InterpolationOscillation());
                    break;
                }
                ::function::Visit<PackageNodeEntryStrategies>(interpolationVariant, scribe, NodeEntryStrategy<PackageNodeEntryStrategies::StrategyType::SERIALIZE>{});
            }
        }

        Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::NodeEntryPackage() : endStateVariant(EndStateNormal()), interpolationVariant(InterpolationLinear())
        {
            endStateType.value = static_cast<EndStateTypeUnderlying>(::Atmos::Modulator::TrackNodeEndState::Type::NORMAL);
            endStateVariant.Set(EndStateNormal());
            interpolationType.value = static_cast<InterpolationTypeUnderlying>(::Atmos::Modulator::TrackNodeInterpolation::Type::LINEAR);
            interpolationVariant.Set(InterpolationLinear());
        }

        Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::NodeEntryPackage(NodeEntryPackage &&arg) : endStateType(std::move(arg.endStateType)),
            endStateVariant(std::move(arg.endStateVariant)), interpolationType(std::move(arg.interpolationType)), interpolationVariant(std::move(arg.interpolationVariant))
        {}

        Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage& Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::operator=(NodeEntryPackage &&arg)
        {
            endStateType = std::move(arg.endStateType);
            endStateVariant = std::move(arg.endStateVariant);
            interpolationType = std::move(arg.interpolationType);
            interpolationVariant = std::move(arg.interpolationVariant);
            return *this;
        }

        bool Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::operator==(const NodeEntryPackage &arg) const
        {
            return endStateType == arg.endStateType && endStateVariant == arg.endStateVariant && interpolationType == arg.interpolationType && interpolationVariant == arg.interpolationVariant;
        }

        bool Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::operator!=(const NodeEntryPackage &arg) const
        {
            return !(*this == arg);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Modulator::GeneratorRoute>::TrackNodePackage)
        {
            scribe(prototype);
            scribe(nodes);
        }

        Package<::Atmos::Modulator::GeneratorRoute>::TrackNodePackage::TrackNodePackage(TrackNodePackage &&arg) : prototype(std::move(arg.prototype)), nodes(std::move(arg.nodes))
        {}

        Package<::Atmos::Modulator::GeneratorRoute>::TrackNodePackage& Package<::Atmos::Modulator::GeneratorRoute>::TrackNodePackage::operator=(TrackNodePackage &&arg)
        {
            prototype = std::move(arg.prototype);
            nodes = std::move(arg.nodes);
            return *this;
        }

        bool Package<::Atmos::Modulator::GeneratorRoute>::TrackNodePackage::operator==(const TrackNodePackage &arg) const
        {
            return prototype == arg.prototype && nodes == arg.nodes;
        }

        bool Package<::Atmos::Modulator::GeneratorRoute>::TrackNodePackage::operator!=(const TrackNodePackage &arg) const
        {
            return !(*this == arg);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Modulator::GeneratorRoute>)
        {
            scribe(prototype);
            scribe(tracks);
        }

        Package<::Atmos::Modulator::GeneratorRoute>::Package(Package &&arg) : prototype(std::move(arg.prototype)), tracks(std::move(arg.tracks))
        {}

        Package<::Atmos::Modulator::GeneratorRoute>& Package<::Atmos::Modulator::GeneratorRoute>::operator=(Package &&arg)
        {
            prototype = std::move(arg.prototype);
            tracks = std::move(arg.tracks);
            return *this;
        }

        bool Package<::Atmos::Modulator::GeneratorRoute>::Package::operator==(const Package &arg) const
        {
            return prototype == arg.prototype && tracks == arg.tracks;
        }

        bool Package<::Atmos::Modulator::GeneratorRoute>::Package::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Modulator::GeneratorRoute>::BuildT Package<::Atmos::Modulator::GeneratorRoute>::Build() const
        {
            BuildT ret(prototype.Build());
            for (auto &loop : tracks.Build())
            {
                auto &track = ret.AddTrackEntry(loop.prototype.Build());
                for (auto &nodeLoop : loop.nodes.Build())
                {
                    typedef ::Atmos::Modulator::TrackNodeEndState::Type EndStateType;
                    typedef ::Atmos::Modulator::TrackNodeInterpolation::Type InterpolationType;
                    typedef Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage NodeEntryPackage;
                    
                    std::unique_ptr<::Atmos::Modulator::TrackNodeEndState> endState;
                    switch (nodeLoop.endStateType.Build())
                    {
                    case EndStateType::NORMAL:
                    {
                        auto &value = nodeLoop.endStateVariant.Get<NodeEntryPackage::EndStateNormal>().value;
                        auto made = new ::Atmos::Modulator::TrackNodeEndState(static_cast<::Atmos::Modulator::Value::Type>(value.type.Build()));
                        made->SetNormal(value.Build());
                        endState.reset(made);
                        break;
                    }
                    case EndStateType::RANDOM:
                    {
                        auto &value = nodeLoop.endStateVariant.Get<NodeEntryPackage::EndStateRandom>().value;
                        auto made = new ::Atmos::Modulator::TrackNodeEndState(static_cast<::Atmos::Modulator::Value::Type>(value.first.type.Build()));
                        made->SetRandom(value.Build());
                        endState.reset(made);
                        break;
                    }
                    }

                    ::Atmos::Modulator::TrackNodeInterpolation interpolation;

                    switch (static_cast<EndStateType>(nodeLoop.endStateType.Build()))
                    {
                    case EndStateType::NORMAL:
                        endState->SetNormal(nodeLoop.endStateVariant.Get<NodeEntryPackage::EndStateNormal>().value.Build());
                        break;
                    case EndStateType::RANDOM:
                        endState->SetRandom(nodeLoop.endStateVariant.Get<NodeEntryPackage::EndStateRandom>().value.Build());
                        break;
                    }

                    switch (static_cast<InterpolationType>(nodeLoop.interpolationType.Build()))
                    {
                    case InterpolationType::LINEAR:
                        interpolation.SetLinear();
                        break;
                    case InterpolationType::OSCILLATION:
                    {
                        auto &oscillationPackage = nodeLoop.interpolationVariant.Get<NodeEntryPackage::InterpolationOscillation>();
                        interpolation.SetOscillation(oscillationPackage.acceleration.Build(), oscillationPackage.rate.Build());
                        break;
                    }
                    }

                    track.AddNode(*endState, interpolation);
                }
            }

            return ret;
        }
    }
}