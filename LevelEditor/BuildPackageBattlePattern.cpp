
#include "BuildPackageBattlePattern.h"

namespace Creation
{
    namespace Build
    {
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::BattlePatternHolder::Piece>)
        {
            scribe(selectionSprite);
            scribe(power);
            scribe(chain);
        }

        Package<::Atmos::BattlePatternHolder::Piece>::Package(Package &&arg) : selectionSprite(std::move(arg.selectionSprite)), power(std::move(arg.power)), chain(std::move(arg.chain))
        {}

        Package<::Atmos::BattlePatternHolder::Piece>& Package<::Atmos::BattlePatternHolder::Piece>::operator=(Package &&arg)
        {
            selectionSprite = std::move(arg.selectionSprite);
            power = std::move(arg.power);
            chain = std::move(arg.chain);
            return *this;
        }

        bool Package<::Atmos::BattlePatternHolder::Piece>::operator==(const Package &arg) const
        {
            return selectionSprite == arg.selectionSprite && power == arg.power && chain == arg.chain;
        }

        bool Package<::Atmos::BattlePatternHolder::Piece>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::BattlePatternHolder::Piece>::BuildT Package<::Atmos::BattlePatternHolder::Piece>::Build() const
        {
            return BuildT(selectionSprite.Build(), power.Build(), chain.Build());
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::BattlePatternHolder>::PatternPiece)
        {
            scribe(position);
            scribe(registryPosition);
        }

        Package<::Atmos::BattlePatternHolder>::PatternPiece::PatternPiece(PatternPiece &&arg) : position(std::move(arg.position)), registryPosition(std::move(arg.registryPosition))
        {}

        Package<::Atmos::BattlePatternHolder>::PatternPiece& Package<::Atmos::BattlePatternHolder>::PatternPiece::operator=(PatternPiece &&arg)
        {
            position = std::move(arg.position);
            registryPosition = std::move(arg.registryPosition);
            return *this;
        }

        bool Package<::Atmos::BattlePatternHolder>::PatternPiece::operator==(const PatternPiece &arg) const
        {
            return position == arg.position && registryPosition == arg.registryPosition;
        }

        bool Package<::Atmos::BattlePatternHolder>::PatternPiece::operator!=(const PatternPiece &arg) const
        {
            return !(*this == arg);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::BattlePatternHolder>)
        {
            scribe(registry);
            scribe(pattern);
        }

        Package<::Atmos::BattlePatternHolder>::Package(Package &&arg) : registry(std::move(arg.registry)), pattern(std::move(arg.pattern))
        {}

        Package<::Atmos::BattlePatternHolder>& Package<::Atmos::BattlePatternHolder>::operator=(Package &&arg)
        {
            registry = std::move(arg.registry);
            pattern = std::move(arg.pattern);
            return *this;
        }

        bool Package<::Atmos::BattlePatternHolder>::operator==(const Package &arg) const
        {
            return registry == arg.registry && pattern == arg.pattern;
        }

        bool Package<::Atmos::BattlePatternHolder>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::BattlePatternHolder>::BuildT Package<::Atmos::BattlePatternHolder>::Build() const
        {
            std::vector<decltype(BuildT::registry)::iterator> registryIterators;
            registryIterators.reserve(registry.value.size());

            BuildT ret;
            for (auto &loop : registry.value)
            {
                ret.registry.push_back(std::move(loop.Build()));
                registryIterators.push_back(--ret.registry.end());
            }

            for (auto &loop : pattern.value)
                ret.pieces.Add(loop.position.Build(), &*registryIterators[loop.registryPosition.Build()]);

            return ret;
        }
    }
}