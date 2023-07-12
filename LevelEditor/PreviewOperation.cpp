
#include "PreviewOperation.h"
#include "CurrentWorld.h"
#include "Viewport.h"

namespace Creation
{
    PreviewOperation::Entry::Entry(::Atmos::RenderFragment *fragment, const Atmos::GridPosition &originalTilePos, const Atmos::RelativeGridPosition &relTilePos, Data *data) : fragment(fragment), originalTilePos(originalTilePos), relTilePos(relTilePos), data(data)
    {
        this->fragment->SetDynamic();
    }

    PreviewOperation::Entry::~Entry()
    {
        if(fragment)
            CurrentWorld::GetCurrentField()->renderFragments.Remove(*fragment);
    }

    PreviewOperation::Entry::Entry(Entry &&arg) : fragment(std::move(arg.fragment)), originalTilePos(std::move(arg.originalTilePos)), relTilePos(std::move(arg.relTilePos)), data(std::move(arg.data))
    {}

    PreviewOperation::Entry& PreviewOperation::Entry::operator=(Entry &&arg)
    {
        fragment = std::move(arg.fragment);
        originalTilePos = std::move(arg.originalTilePos);
        relTilePos = std::move(arg.relTilePos);
        data = std::move(arg.data);
        return *this;
    }

    void PreviewOperation::SignalWorking(bool set)
    {
        working = set;
    }

    void PreviewOperation::AddEntry(::Atmos::RenderFragment *fragment, const Atmos::GridPosition &originalPos, const Atmos::RelativeGridPosition &offset, bool render)
    {
        AddEntry(fragment, originalPos, offset, nullptr, render);
    }

    void PreviewOperation::AddEntry(::Atmos::RenderFragment *fragment, const Atmos::GridPosition &originalPos, const Atmos::RelativeGridPosition &offset, Entry::Data *data, bool render)
    {
        entryList.push_back(Entry(fragment, originalPos, offset, data));
        entryList.back().fragment->SetPosition(Atmos::GridPosition(currentGridPos, offset));
        if (render)
            CurrentWorld::GetCurrentField()->renderFragments.Add(*entryList.back().fragment);
    }

    void PreviewOperation::ClearEntries()
    {
        entryList.clear();
    }

    void PreviewOperation::RenderEntries(bool render)
    {
        if (render)
            for (auto &loop : entryList)
                CurrentWorld::GetCurrentField()->renderFragments.Add(*loop.fragment);
        else
            for (auto &loop : entryList)
                CurrentWorld::GetCurrentField()->renderFragments.Remove(*loop.fragment);
    }

    bool PreviewOperation::AttemptMoveEntries(const Atmos::GridPosition &position, bool skipCheck)
    {
        if (!skipCheck && currentGridPos == position)
            return false;

        // Check if we can move this operation
        {
            TilePositionVector sendVector;

            for (auto &loop : entryList)
            {
                // Add in all of the entry's proposed tile positions, while skipping over positions that also exist in the original selection
                Atmos::GridPosition proposedPosition(position);
                proposedPosition.Edit(loop.relTilePos);

                bool checkContinue = false;
                for (auto &checkLoop : entryList)
                {
                    if (checkLoop.originalTilePos == proposedPosition)
                    {
                        checkContinue = true;
                        break;
                    }
                }

                if (checkContinue)
                    continue;

                Build::Package<::Atmos::GridPosition> nPackage;
                nPackage.x.value = proposedPosition.x;
                nPackage.y.value = proposedPosition.y;
                nPackage.z.value = proposedPosition.z;
                sendVector.push_back(std::move(nPackage));
            }

            if (isOverlappingOuter(sendVector))
                return false;
        }

        for (auto &loop : entryList)
            loop.fragment->SetPosition(Atmos::Position3D(Atmos::GridPosition(position, loop.relTilePos)));

        currentGridPos = position;

        return true;
    }

    void PreviewOperation::SetCurrentGridPosition(const Atmos::GridPosition &set)
    {
        currentGridPos = set;
    }

    void PreviewOperation::SetCurrentGridPosition(const Point &pt)
    {
        SetCurrentGridPosition(Atmos::GridPosition::FromScreen(pt.ToAtmos(), Viewport::viewport->GetZView(), Viewport::viewport->GetTopLeft().ToAtmos()));
    }

    const Atmos::GridPosition& PreviewOperation::GetCurrentGridPosition() const
    {
        return currentGridPos;
    }

    Point PreviewOperation::GetMousePosition()
    {
        return Point(Viewport::viewport->ScreenToClient(wxGetMousePosition()));
    }

    Atmos::GridPosition::ValueT PreviewOperation::GetZView()
    {
        return Viewport::viewport->GetZView();
    }

    Atmos::GridPosition PreviewOperation::GetGridPosition(const Point &pt)
    {
        return Atmos::GridPosition::FromScreen(pt.ToAtmos(), Viewport::viewport->GetZView(), Viewport::viewport->GetTopLeft().ToAtmos());
    }

    PreviewOperation::PreviewOperation(IsOverlappingOuterFunc &&isOverlappingOuter) : isOverlappingOuter(std::move(isOverlappingOuter)), working(false)
    {}

    bool PreviewOperation::IsWorking() const
    {
        return working;
    }

    void PreviewOperation::OnMouseDown(const Point &pt)
    {
        OnMouseDownImpl(pt);
    }

    void PreviewOperation::OnMouseUp(const Point &pt)
    {
        OnMouseUpImpl(pt);
        working = false;
    }

    void PreviewOperation::OnMouseMove(const Point &pt)
    {
        if (!IsWorking())
            return;

        Optional<Atmos::RelativeGridPosition> offset(AttemptMoveEntries(GetGridPosition(pt)));
        if(offset)
            OnMouseMoveImpl(pt, *offset);
    }

    void PreviewOperation::Clear()
    {
        ClearEntries();
        ClearImpl();
    }
}