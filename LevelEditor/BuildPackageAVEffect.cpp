
#include "BuildPackageAVEffect.h"

namespace Creation
{
    namespace Build
    {
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::AVEffect>::NodePackage)
        {
            scribe(type);
        }

        Package<::Atmos::AVEffect>::NodePackage::NodePackage(NodePackage &&arg) : type(std::move(arg.type))
        {}

        Package<::Atmos::AVEffect>::NodePackage& Package<::Atmos::AVEffect>::NodePackage::operator=(NodePackage &&arg)
        {
            type = std::move(arg.type);
            return *this;
        }

        bool Package<::Atmos::AVEffect>::NodePackage::operator==(const NodePackage &arg) const
        {
            return type == arg.type;
        }

        bool Package<::Atmos::AVEffect>::NodePackage::operator!=(const NodePackage &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::AVEffect>::NodePackage::BuildT Package<::Atmos::AVEffect>::NodePackage::Build() const
        {
            BuildT ret;
            return ret;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::AVEffect>)
        {
            scribe(nodes);
        }

        Package<::Atmos::AVEffect>::Package(Package &&arg) : nodes(std::move(arg.nodes))
        {}

        Package<::Atmos::AVEffect>& Package<::Atmos::AVEffect>::operator=(Package &&arg)
        {
            nodes = std::move(arg.nodes);
            return *this;
        }

        bool Package<::Atmos::AVEffect>::operator==(const Package &arg) const
        {
            return nodes == arg.nodes;
        }

        bool Package<::Atmos::AVEffect>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::AVEffect>::BuildT Package<::Atmos::AVEffect>::Build() const
        {
            BuildT ret;
            for (auto &loop : nodes.value)
                ret.AddNode(loop.Build());
            return ret;
        }
    }
}