#include "DataRoot.h"

#include "WorldElementBase.h"

namespace Creation::Editing::Data
{
    Root::Root(bool visible, const NexusHistory& nexusHistory) :
        visible(visible), nexusHistory(nexusHistory)
    {}

    Root::~Root() = default;

    void Root::CreateTreeElements(PropertiesTree& tree)
    {
        for (auto& nexus : TopNexi())
            OverNexusThenChildren(*nexus, &NexusNode::CreateTreeElement, tree);
    }

    void Root::DestroyTreeElements()
    {
        for (auto& nexus : TopNexi())
            OverChildrenThenNexus(*nexus, &NexusNode::DestroyTreeElement);
    }

    void Root::Show()
    {
        visible = true;
        for (auto& nexus : TopNexi())
        {
            for (auto& child : nexus->Children())
            {
                auto worldElement = child->WorldElement();
                if (worldElement)
                    worldElement->Show();
            }
        }
    }

    void Root::Hide()
    {
        visible = false;
        for (auto& nexus : TopNexi())
        {
            for(auto& child : nexus->Children())
            {
                auto worldElement = child->WorldElement();
                if (worldElement)
                    worldElement->Hide();
            }
        }
    }

    bool Root::IsVisible() const
    {
        return visible;
    }

    const NexusHistory& Root::RetrieveNexusHistory() const
    {
        return nexusHistory;
    }
}