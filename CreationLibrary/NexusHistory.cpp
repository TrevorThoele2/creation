#include "NexusHistory.h"

#include "NexusSelection.h"

namespace Creation::Editing
{
    NexusHistory::NexusHistory(History& history, NexusSelection& selection) :
        history(&history), selection(&selection)
    {}

    void NexusHistory::Add(const std::vector<NexusNode*>& children)
    {
        const auto name = NameFrom(children);

        history->Push(
            "Added to " + name,
            [selection = this->selection, children = children, storedNexi = std::vector<StoredNexus>()](bool forward) mutable
            {
                if (forward)
                {
                    for (auto nexus = storedNexi.begin(); nexus != storedNexi.end();)
                    {
                        children.push_back(nexus->parent->Reinstate(std::move(nexus->child)));
                        nexus = storedNexi.erase(nexus);
                    }
                }
                else
                {
                    {
                        const NexusSelection::Nodes deselectNodes(children.begin(), children.end());
                        selection->Modify({ {}, deselectNodes });
                    }

                    for (auto& child : children)
                    {
                        auto parent = dynamic_cast<SequenceNexusBase*>(child->Parent());
                        storedNexi.emplace_back(parent, parent->Release(*child));
                    }

                    children.clear();
                }
            });
    }

    void NexusHistory::Remove(const std::vector<NexusNode*>& children)
    {
        const auto name = NameFrom(children);

        history->Push(
            "Removed from " + name,
            [selection = this->selection, children = children, storedNexi = std::vector<StoredNexus>()] (bool forward) mutable
            {
                if (forward)
                {
                    {
                        const NexusSelection::Nodes deselectNodes(children.begin(), children.end());
                        selection->Modify({ {}, deselectNodes });
                    }

                    for (auto& child : children)
                    {
                        auto parent = dynamic_cast<SequenceNexusBase*>(child->Parent());
                        storedNexi.emplace_back(parent, parent->Release(*child));
                    }

                    children.clear();
                }
                else
                {
                    for (auto nexus = storedNexi.begin(); nexus != storedNexi.end();)
                    {
                        children.push_back(nexus->parent->Reinstate(std::move(nexus->child)));
                        nexus = storedNexi.erase(nexus);
                    }
                }
            });
    }

    String NexusHistory::NameFrom(const std::vector<NexusNode*>& children)
    {
        return children.size() == 1
            ? children[0]->Parent()->Label()
            : "Group";
    }
}