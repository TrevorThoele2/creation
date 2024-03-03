#pragma once

#include "wxTreeItemIdHash.h"

#include <set>
#include <unordered_map>
#include <typeindex>

#include "NexusNode.h"
#include "SequenceNexusBase.h"

#include "Event.h"

namespace Creation::Editing
{
    class NexusSelection
    {
    public:
        using Nodes = std::set<NexusNode*>;
        using Types = std::unordered_map<std::type_index, int>;
        using SequenceNodes = std::set<SequenceNexusBase*>;

        using iterator = Nodes::iterator;
        using const_iterator = Nodes::const_iterator;

        using TreeIDs = std::set<wxTreeItemId>;
    public:
        struct Delta
        {
            Nodes select;
            Nodes deselect;
        };
    public:
        Event<const Delta&> onChanged;
    public:
        void Set(const Nodes& set);
        void Modify(const Delta& delta);

        [[nodiscard]] bool IsSelected(NexusNode& node) const;

        [[nodiscard]] size_t size() const;
        [[nodiscard]] bool empty() const;

        [[nodiscard]] iterator begin();
        [[nodiscard]] const_iterator begin() const;
        [[nodiscard]] iterator end();
        [[nodiscard]] const_iterator end() const;

        [[nodiscard]] const Types& AllTypes() const;
        [[nodiscard]] const SequenceNodes& AllSequenceNodes() const;
    private:
        Nodes selected;
        Types types;
        SequenceNodes sequenceNodes;
    private:
        static void IncreaseType(Types& types, std::type_index type);
        static void DecreaseType(Types& types, std::type_index type);
    };
}