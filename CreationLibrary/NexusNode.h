#pragma once

#include <vector>
#include <functional>
#include "String.h"

namespace Creation::Editing
{
    class PropertiesTree;
    class TreeElementBase;
    class WorldElementBase;

    class NexusNode
    {
    public:
        NexusNode(const NexusNode& arg) = delete;

        virtual ~NexusNode() = 0;

        [[nodiscard]] virtual NexusNode* Parent() = 0;
        [[nodiscard]] virtual const NexusNode* Parent() const = 0;

        virtual void CreateTreeElement(PropertiesTree& tree) = 0;
        virtual void DestroyTreeElement() = 0;
        [[nodiscard]] virtual TreeElementBase* TreeElement() = 0;

        virtual void CreateWorldElement() = 0;
        virtual void DestroyWorldElement() = 0;
        virtual WorldElementBase* WorldElement() = 0;

        virtual void Select() = 0;
        virtual void Deselect() = 0;
        [[nodiscard]] virtual bool IsSelected() const = 0;

        [[nodiscard]] virtual std::vector<NexusNode*> Children() = 0;

        [[nodiscard]] virtual String Label() const = 0;
    protected:
        NexusNode() = default;
    };

    template<class RetT, class... FuncArgs, class... PassArgs>
    void OverNexusThenChildren(NexusNode& node, RetT(NexusNode::* method)(FuncArgs...), PassArgs&& ... passArgs)
    {
        (node.*method)(std::forward<PassArgs>(passArgs)...);
        auto children = node.Children();
        for (auto& child : children)
            OverNexusThenChildren(*child, method, std::forward<PassArgs>(passArgs)...);
    }

    template<class Method>
    void OverNexusThenChildren(NexusNode& node, Method method)
    {
        method(node);
        auto children = node.Children();
        for (auto& child : children)
            OverNexusThenChildren(*child, method);
    }

    template<class RetT, class... FuncArgs, class... PassArgs>
    void OverChildrenThenNexus(NexusNode& node, RetT(NexusNode::* method)(FuncArgs...), PassArgs&& ... passArgs)
    {
        auto children = node.Children();
        for (auto& child : children)
            OverChildrenThenNexus(*child, method, std::forward<PassArgs>(passArgs)...);
        (node.*method)(std::forward<PassArgs>(passArgs)...);
    }

    template<class Method>
    void OverChildrenThenNexus(NexusNode& node, Method method)
    {
        auto children = node.Children();
        for (auto& child : children)
            OverChildrenThenNexus(*child, method);
        method(node);
    }
}
