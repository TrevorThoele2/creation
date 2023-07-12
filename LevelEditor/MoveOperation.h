#pragma once

#include "PreviewOperation.h"

#include "DataBreakdownBase.h"
#include "BuildPackage.h"
#include "Command.h"
#include "Event.h"

namespace Creation
{
    template<class Package>
    class MoveOperation : public PreviewOperation
    {
    public:
        typedef Package PackageT;
        typedef Command::Edit<DataBreakdown<Build::Package<::Atmos::GridPosition>>> MoveCommandT;
        typedef std::vector<PackageT*> PassVector;

        typedef function::Function<::Atmos::RenderFragment*, const PackageT&> MakeFragmentFunc;
        typedef function::Function<Build::Package<Atmos::GridPosition>, const PackageT&> GetGridPositionFunc;
        typedef function::Function<MoveCommandT*, PackageT&, const Build::Package<Atmos::GridPosition>&> CreateMoveCommandFunc;
    private:
        class EntryData : public Entry::Data
        {
        public:
            PackageT package;
            EntryData(const PackageT &package);
        };
    private:
        ::Atmos::GridPosition startingGridPos;
        Image defaultImage;

        MakeFragmentFunc makeFragment;
        GetGridPositionFunc getGridPos;
        CreateMoveCommandFunc createMove;

        void OnMouseDownImpl(const Point &pt) override;
        void OnMouseUpImpl(const Point &pt) override;
        void OnMouseMoveImpl(const Point &pt, const Atmos::RelativeGridPosition &offset) override;
        void ClearImpl() override;

        void AddEntry(PackageT &add, const Atmos::GridPosition &entryPosition, const Atmos::GridPosition &standardPosition);
    public:
        MoveOperation(Image &&defaultImage, IsOverlappingOuterFunc &&isOverlappingOuter, MakeFragmentFunc &&makeFragment, GetGridPositionFunc &&getGridPos, CreateMoveCommandFunc &&createMove);
        // You must pass in pointers, but they can be deleted immediately after this call
        void Setup(const PassVector &add);
        void Setup(PackageT &add);
    };

    template<class Package>
    MoveOperation<Package>::EntryData::EntryData(const PackageT &package) : package(package)
    {}

    template<class Package>
    void MoveOperation<Package>::OnMouseDownImpl(const Point &pt)
    {
        ::Atmos::GridPosition pos(GetGridPosition(pt));
        startingGridPos = pos;

        AttemptMoveEntries(pos);
        SetCurrentGridPosition(pt);
        RenderEntries();
        SignalWorking();
    }

    template<class Package>
    void MoveOperation<Package>::OnMouseUpImpl(const Point &pt)
    {
        if (!IsWorking())
            return;

        // Check for moving into the same position
        if (GetCurrentGridPosition() == startingGridPos)
            return;

        typename Command::Group<MoveCommandT>::ActionVector vector;
        for (auto &entry : entryList)
        {
            Atmos::GridPosition gridPos(GetCurrentGridPosition());
            gridPos.Edit(entry.relTilePos);
            Build::Package<::Atmos::GridPosition> positionPackage;
            positionPackage.x.value = gridPos.x;
            positionPackage.y.value = gridPos.y;
            positionPackage.z.value = gridPos.z;
            vector.push_back(createMove(static_cast<EntryData*>(entry.data.get())->package, positionPackage));
        }

        auto groupCommand = Command::Group<MoveCommandT>::Create(std::move(vector));
        groupCommand->Commit();

        Clear();
    }

    template<class Package>
    void MoveOperation<Package>::OnMouseMoveImpl(const Point &pt, const Atmos::RelativeGridPosition &offset)
    {}

    template<class Package>
    void MoveOperation<Package>::ClearImpl()
    {}

    template<class Package>
    void MoveOperation<Package>::AddEntry(PackageT &add, const Atmos::GridPosition &entryPosition, const Atmos::GridPosition &standardPosition)
    {
        auto fragment = makeFragment(add);
        if (fragment)
            PreviewOperation::AddEntry(fragment, getGridPos(add).Build(), Atmos::RelativeGridPosition(standardPosition, entryPosition), new EntryData(add), false);
        else
            PreviewOperation::AddEntry(new Image(defaultImage), getGridPos(add).Build(), Atmos::RelativeGridPosition(standardPosition, entryPosition), new EntryData(add), false);
    }

    template<class Package>
    MoveOperation<Package>::MoveOperation(Image &&defaultImage, IsOverlappingOuterFunc &&isOverlappingOuter, MakeFragmentFunc &&makeFragment, GetGridPositionFunc &&getGridPos, CreateMoveCommandFunc &&createMove) : PreviewOperation(std::move(isOverlappingOuter)), defaultImage(std::move(defaultImage)), makeFragment(std::move(makeFragment)), getGridPos(std::move(getGridPos)), createMove(std::move(createMove))
    {}

    template<class Package>
    void MoveOperation<Package>::Setup(const PassVector &add)
    {
        if (add.empty())
            return;

        Atmos::GridPosition topLeft(getGridPos(**add.begin()).Build());
        Atmos::GridPosition bottomRight(topLeft);

        // First, get all the ghost sprites and also figure out the center of this
        for (auto &loop : add)
        {
            Atmos::GridPosition tilePos(getGridPos(*loop).Build());

            if (tilePos.x < topLeft.x)
                topLeft.x = tilePos.x;
            else if (tilePos.x > bottomRight.x)
                bottomRight.x = tilePos.x;

            if (tilePos.y < topLeft.y)
                topLeft.y = tilePos.y;
            else if (tilePos.y > bottomRight.y)
                bottomRight.y = tilePos.y;
        }

        // Now, use the center to figure out the relative tile positions and add in the resulting entry
        Atmos::GridPosition center(Atmos::GetMidpoint(topLeft.x, bottomRight.x), Atmos::GetMidpoint(topLeft.y, bottomRight.y), GetZView());

        for (auto &loop : add)
            AddEntry(*loop, getGridPos(*loop).Build(), center);
    }

    template<class Package>
    void MoveOperation<Package>::Setup(PackageT &add)
    {
        Atmos::GridPosition tilePos(getGridPos(add));
        AddEntry(add, tilePos, tilePos);
    }
}