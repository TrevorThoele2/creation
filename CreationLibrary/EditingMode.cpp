#include "EditingMode.h"

namespace Creation::Editing
{
    Mode::~Mode() = default;

    void Mode::ChangeRoot(UI& ui)
    {
        ChangeRootImpl(ui);
    }
    
    void Mode::OnPaint(Atmos::Spatial::AxisAlignedBox2D box)
    {
        OnPaintImpl(box);
    }

    void Mode::OnSelect(Atmos::Spatial::AxisAlignedBox2D box)
    {
        OnSelectImpl(box);
    }

    void Mode::OnMoved(const std::vector<GhostWorldElementBase*>& ghosts)
    {
        OnMovedImpl(ghosts);
    }

    auto Mode::OnCopy() -> PaintAction
    {
        return OnCopyImpl();
    }

    std::vector<std::unique_ptr<GhostWorldElementBase>> Mode::CreateGhosts() const
    {
        return CreateGhostsImpl();
    }

    bool Mode::IsPointInSelection(Atmos::Spatial::Point2D position, Arca::Reliquary& reliquary) const
    {
        return IsPointInSelectionImpl(position, reliquary);
    }

    Mode::Mode(NexusSelection& nexusSelection, NexusHistory nexusHistory) :
        nexusSelection(&nexusSelection), nexusHistory(nexusHistory)
    {}

    NexusSelection& Mode::CurrentNexusSelection()
    {
        return *nexusSelection;
    }

    const NexusSelection& Mode::CurrentNexusSelection() const
    {
        return *nexusSelection;
    }

    NexusHistory Mode::RetrieveNexusHistory() const
    {
        return nexusHistory;
    }
}