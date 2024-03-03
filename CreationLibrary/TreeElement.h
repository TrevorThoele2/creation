#pragma once

#include "TreeElementBase.h"
#include "PropertiesTree.h"

namespace Creation::Editing
{
    template<class T>
    class TreeElement final : public TreeElementBase
    {
    public:
        using DataT = T;
        using Nexus = Nexus<DataT>;
    public:
        TreeElement(Nexus& nexus, const String& label, PropertiesTree& tree);
    protected:
        [[nodiscard]] Nexus& UnderlyingNexus();
        [[nodiscard]] const Nexus& UnderlyingNexus() const;
    private:
        Nexus* nexus;
    };

    template<class T>
    TreeElement<T>::TreeElement(Nexus& nexus, const String& label, PropertiesTree& tree) :
        TreeElementBase(tree.Add(nexus, label), tree),
        nexus(&nexus)
    {}

    template <class T>
    auto TreeElement<T>::UnderlyingNexus() -> Nexus&
    {
        return *nexus;
    }

    template <class T>
    auto TreeElement<T>::UnderlyingNexus() const -> const Nexus&
    {
        return *nexus;
    }
}