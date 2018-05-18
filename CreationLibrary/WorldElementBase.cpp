#include "WorldElementBase.h"

namespace Creation::Editing
{
    WorldElementBase::~WorldElementBase() = default;

    void WorldElementBase::Select()
    {
        DoSelect();
    }

    void WorldElementBase::Deselect()
    {
        DoDeselect();
    }
    
    void WorldElementBase::Show()
    {
        if (isShown)
            return;

        isShown = true;
        DoShow();
    }

    void WorldElementBase::Hide()
    {
        if (!isShown)
            return;

        isShown = false;
        DoHide();
    }

    bool WorldElementBase::IsShown() const
    {
        return isShown;
    }

    std::unique_ptr<GhostWorldElementBase> WorldElementBase::CreateGhost() const
    {
        return CreateGhostImpl();
    }

    void WorldElementBase::DoSelect()
    {}

    void WorldElementBase::DoDeselect()
    {}

    void WorldElementBase::DoShow()
    {}

    void WorldElementBase::DoHide()
    {}
}