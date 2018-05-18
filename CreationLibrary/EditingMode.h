#pragma once

#include "NexusSelection.h"
#include "NexusHistory.h"
#include "GhostWorldElementBase.h"

#include <Atmos/Point3D.h>
#include <Atmos/AxisAlignedBox2D.h>
#include <Atmos/SpatialAlgorithms.h>
#include <Arca/Reliquary.h>

namespace Creation::Editing
{
    class UI;

    class Mode
    {
    public:
        using PaintAction = std::function<void()>;
    public:
        virtual ~Mode() = 0;
    public:
        void ChangeRoot(UI& ui);
    public:
        void OnPaint(Atmos::Spatial::AxisAlignedBox2D box);
        void OnSelect(Atmos::Spatial::AxisAlignedBox2D box);

        void OnMoved(const std::vector<GhostWorldElementBase*>& ghosts);

        PaintAction OnCopy();

        [[nodiscard]] std::vector<std::unique_ptr<GhostWorldElementBase>> CreateGhosts() const;
        [[nodiscard]] bool IsPointInSelection(Atmos::Spatial::Point2D position, Arca::Reliquary& reliquary) const;
    protected:
        Mode(NexusSelection& nexusSelection, NexusHistory nexusHistory);

        [[nodiscard]] NexusSelection& CurrentNexusSelection();
        [[nodiscard]] const NexusSelection& CurrentNexusSelection() const;

        [[nodiscard]] NexusHistory RetrieveNexusHistory() const;

        template<class Function>
        void OverDifferentiatedBox(
            Function function,
            Atmos::Spatial::AxisAlignedBox2D box);
    protected:
        virtual void ChangeRootImpl(UI& ui) = 0;
        
        virtual void OnPaintImpl(Atmos::Spatial::AxisAlignedBox2D box) {}
        virtual void OnSelectImpl(Atmos::Spatial::AxisAlignedBox2D box) {}

        virtual void OnMovedImpl(const std::vector<GhostWorldElementBase*>& ghosts) {}

        virtual PaintAction OnCopyImpl() { return {}; }

        [[nodiscard]] virtual std::vector<std::unique_ptr<GhostWorldElementBase>> CreateGhostsImpl() const { return {}; }
        [[nodiscard]] virtual bool IsPointInSelectionImpl(
            Atmos::Spatial::Point2D position, Arca::Reliquary& reliquary) const { return false; }
    private:
        NexusSelection* nexusSelection;
        NexusHistory nexusHistory;
    };

    template<class Function>
    void Mode::OverDifferentiatedBox(
        Function function,
        Atmos::Spatial::AxisAlignedBox2D box)
    {
        const auto topLeft = Atmos::Spatial::Grid::ToPoint(Atmos::Spatial::Point2D{ box.Left(), box.Top() });
        const auto bottomRight = Atmos::Spatial::Grid::ToPoint(Atmos::Spatial::Point2D{ box.Right(), box.Bottom() });

        auto currentPosition = topLeft;
        const auto count = (bottomRight.x - topLeft.x + 1) * (bottomRight.y - topLeft.y + 1);

        for (auto i = 0; i < count; ++i)
        {
            function(currentPosition);

            currentPosition.x = currentPosition.x + 1;
            if (currentPosition.x > bottomRight.x)
            {
                currentPosition.x = topLeft.x;
                currentPosition.y = currentPosition.y + 1;
            }
        }
    }
}