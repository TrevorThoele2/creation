#include "NexusSelection.h"

#include "NexusSelectionExceptions.h"

namespace Creation::Editing
{
    void NexusSelection::Set(const Nodes& set)
    {
        const auto& newSelectedNexi = set;
        const auto& oldSelectedNexi = selected;
        Nodes select;
        std::set_difference(
            newSelectedNexi.begin(), newSelectedNexi.end(),
            oldSelectedNexi.begin(), oldSelectedNexi.end(),
            std::inserter(select, select.begin()));
        Nodes deselect;
        std::set_difference(
            oldSelectedNexi.begin(), oldSelectedNexi.end(),
            newSelectedNexi.begin(), newSelectedNexi.end(),
            std::inserter(deselect, deselect.begin()));

        Modify({ select, deselect });
    }

    void NexusSelection::Modify(const Delta& delta)
    {
        const auto& select = delta.select;
        const auto& deselect = delta.deselect;
        if (select.empty() && deselect.empty())
            return;

        {
            Nodes intersection;
            std::set_intersection(
                select.begin(), select.end(),
                deselect.begin(), deselect.end(),
                std::inserter(intersection, intersection.begin()));
            if (!intersection.empty())
                throw ModifyHasNodeInSelectAndDeselect();
        }
        
        for (auto& node : select)
        {
            selected.emplace(node);
            IncreaseType(types, typeid(*node));

            const auto dynamic = dynamic_cast<SequenceNexusBase*>(node);
            if (dynamic)
                sequenceNodes.emplace(dynamic);

            node->Select();
        }
        
        for (auto& node : deselect)
        {
            selected.erase(node);
            DecreaseType(types, typeid(*node));

            const auto dynamic = dynamic_cast<SequenceNexusBase*>(node);
            if (dynamic)
                sequenceNodes.erase(dynamic);

            node->Deselect();
        }

        onChanged(delta);
    }

    bool NexusSelection::IsSelected(NexusNode& node) const
    {
        return selected.find(&node) != selected.end();
    }

    size_t NexusSelection::size() const
    {
        return selected.size();
    }

    bool NexusSelection::empty() const
    {
        return selected.empty();
    }

    auto NexusSelection::begin() -> iterator
    {
        return selected.begin();
    }

    auto NexusSelection::begin() const -> const_iterator
    {
        return selected.begin();
    }

    auto NexusSelection::end() -> iterator
    {
        return selected.end();
    }

    auto NexusSelection::end() const -> const_iterator
    {
        return selected.end();
    }

    auto NexusSelection::AllTypes() const -> const Types&
    {
        return types;
    }

    auto NexusSelection::AllSequenceNodes() const -> const SequenceNodes&
    {
        return sequenceNodes;
    }

    void NexusSelection::IncreaseType(Types& types, std::type_index type)
    {
        auto found = types.find(type);
        if (found == types.end())
            types.emplace(type, 1);
        else
            ++found->second;
    }

    void NexusSelection::DecreaseType(Types& types, std::type_index type)
    {
        auto found = types.find(type);
        if (found != types.end())
        {
            --found->second;
            if (found->second == 0)
                types.erase(found);
        }
    }
}