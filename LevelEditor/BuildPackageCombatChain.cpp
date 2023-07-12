
#include "BuildPackageCombatChain.h"

namespace Creation
{
    namespace Build
    {
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::CombatChain::Node>)
        {
            scribe(transaction);
            scribe(statusEffect);
        }

        Package<::Atmos::CombatChain::Node>::Package(Package &&arg) : transaction(std::move(arg.transaction)), statusEffect(std::move(arg.statusEffect))
        {}

        Package<::Atmos::CombatChain::Node>& Package<::Atmos::CombatChain::Node>::operator=(Package &&arg)
        {
            transaction = std::move(arg.transaction);
            statusEffect = std::move(arg.statusEffect);
            return *this;
        }

        bool Package<::Atmos::CombatChain::Node>::operator==(const Package &arg) const
        {
            return transaction == arg.transaction && statusEffect == arg.statusEffect;
        }

        bool Package<::Atmos::CombatChain::Node>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::CombatChain::Node>::BuildT Package<::Atmos::CombatChain::Node>::Build() const
        {
            return BuildT(transaction.Build(), statusEffect.Build());
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::CombatChain>)
        {
            scribe(nodes);
        }

        Package<::Atmos::CombatChain>::Package(Package &&arg) : nodes(std::move(arg.nodes))
        {}

        Package<::Atmos::CombatChain>& Package<::Atmos::CombatChain>::operator=(Package &&arg)
        {
            nodes = std::move(arg.nodes);
            return *this;
        }

        bool Package<::Atmos::CombatChain>::operator==(const Package &arg) const
        {
            return nodes == arg.nodes;
        }

        bool Package<::Atmos::CombatChain>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::CombatChain>::BuildT Package<::Atmos::CombatChain>::Build() const
        {
            BuildT ret;
            for (auto &loop : nodes.value)
                ret.AddNode(std::move(loop.Build()));
            return ret;
        }
    }
}