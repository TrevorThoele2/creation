#pragma once

#include "PreviewOperation.h"

#include "DataBreakdownBase.h"
#include "Point.h"

#include "Command.h"

namespace Creation
{
    class CCPOperationBase : public PreviewOperation
    {
    public:
        CCPOperationBase(IsOverlappingOuterFunc &&isOverlappingOuter);
        virtual ~CCPOperationBase() = 0 {}
        virtual void Paste() = 0;
    };

    // Cut-copy-paste operation
    template<class Package>
    class CCPOperation : public CCPOperationBase
    {
    public:
        typedef Package PackageT;
        typedef std::vector<const PackageT*> PassVector;
        typedef DataBreakdownList<PackageT> BreakdownListT;

        typedef function::Function<::Atmos::RenderFragment*, const PackageT&> MakeFragmentFunc;
        typedef function::Function<void, PackageT&, const Build::Package<Atmos::GridPosition>&> SetGridPositionFunc;
        typedef function::Function<Build::Package<Atmos::GridPosition>, const PackageT&> GetGridPositionFunc;
    private:
        class EntryData : public PreviewOperation::Entry::Data
        {
        public:
            PackageT package;
            EntryData(const PackageT &package);
        };
    private:
        BreakdownListT *list;

        Image defaultImage;

        MakeFragmentFunc makeFragment;
        SetGridPositionFunc setGridPos;
        GetGridPositionFunc getGridPos;

        void OnMouseDownImpl(const Point &pt) override;
        void OnMouseUpImpl(const Point &pt) override;
        void OnMouseMoveImpl(const Point &pt, const Atmos::RelativeGridPosition &offset) override;
        void ClearImpl() override;

        void AddEntry(const PackageT &add, const Atmos::GridPosition &entryPosition, const Atmos::GridPosition &standardPosition);
        void PlaceCopies();
    public:
        CCPOperation(BreakdownListT *list, Image &&defaultImage, IsOverlappingOuterFunc &&isOverlappingOuter, MakeFragmentFunc &&makeFragment, SetGridPositionFunc &&setGridPos, GetGridPositionFunc &&getGridPos);

        // You must pass in pointers, but they can be deleted immediately after this call
        // Copies will (obviously) probably not be valid anymore after the call to this
        void Cut(const PassVector &copies);
        void Cut(const PackageT &cut);
        // You must pass in pointers, but they can be deleted immediately after this call
        void Copy(const PassVector &copies);
        void Copy(const PackageT &copy);
        void Paste() override;
    };

    template<class PackageT>
    CCPOperation<PackageT>::EntryData::EntryData(const PackageT &package) : package(package)
    {}

    template<class PackageT>
    void CCPOperation<PackageT>::OnMouseDownImpl(const Point &pt)
    {
        if(IsWorking())
            PlaceCopies();
    }

    template<class PackageT>
    void CCPOperation<PackageT>::OnMouseUpImpl(const Point &pt)
    {}

    template<class PackageT>
    void CCPOperation<PackageT>::OnMouseMoveImpl(const Point &pt, const Atmos::RelativeGridPosition &offset)
    {}

    template<class PackageT>
    void CCPOperation<PackageT>::ClearImpl()
    {}

    template<class PackageT>
    void CCPOperation<PackageT>::AddEntry(const PackageT &add, const Atmos::GridPosition &entryPosition, const Atmos::GridPosition &standardPosition)
    {
        auto fragment = makeFragment(add);
        if (fragment)
            PreviewOperation::AddEntry(fragment, entryPosition, Atmos::RelativeGridPosition(standardPosition, entryPosition), new EntryData(add), false);
        else
            PreviewOperation::AddEntry(new Image(defaultImage), entryPosition, Atmos::RelativeGridPosition(standardPosition, entryPosition), new EntryData(add), false);
    }

    template<class PackageT>
    void CCPOperation<PackageT>::PlaceCopies()
    {
        typedef Command::Add<BreakdownListT> AddCommandT;

        // Add a group command to add all of the entries
        typename Command::Group<AddCommandT>::ActionVector vector;
        for (auto &loop : entryList)
        {
            PackageT nPackage(static_cast<EntryData*>(loop.data.get())->package);
            Build::Package<::Atmos::GridPosition> positionPackage;
            ::Atmos::GridPosition position(GetCurrentGridPosition(), loop.relTilePos);
            positionPackage.x.value = position.x;
            positionPackage.y.value = position.y;
            positionPackage.z.value = position.z;
            setGridPos(nPackage, positionPackage);
            vector.push_back(AddCommandT::Create(list, nPackage));
        }

        auto groupCommand = Command::Group<AddCommandT>::Create(std::move(vector));
        groupCommand->Commit();

        RenderEntries(false);
        SignalWorking(false);
    }

    template<class PackageT>
    CCPOperation<PackageT>::CCPOperation(BreakdownListT *list, Image &&defaultImage, IsOverlappingOuterFunc &&isOverlappingOuter, MakeFragmentFunc &&makeFragment, SetGridPositionFunc &&setGridPos, GetGridPositionFunc &&getGridPos) : CCPOperationBase(std::move(isOverlappingOuter)), list(list), defaultImage(std::move(defaultImage)), makeFragment(std::move(makeFragment)), setGridPos(std::move(setGridPos)), getGridPos(std::move(getGridPos))
    {}

    template<class PackageT>
    void CCPOperation<PackageT>::Cut(const PassVector &copies)
    {
        typedef Command::Remove<BreakdownListT> RemoveCommandT;
        if (copies.empty())
            return;

        Copy(copies);

        // Erase the objects through a group command
        typename Command::Group<RemoveCommandT>::ActionVector vector;
        for (auto &copyLoop : copies)
        {
            for (auto loop = list->begin(); loop != list->end(); ++loop)
            {
                if(loop->Get() == copyLoop)
                    vector.push_back(RemoveCommandT::Create(list, loop));
            }
        }

        auto groupCommand = Command::Group<RemoveCommandT>::Create(std::move(vector));
        groupCommand->Commit();
    }

    template<class PackageT>
    void CCPOperation<PackageT>::Cut(const PackageT &cut)
    {
        Copy(cut);
        createRemove(cut)->Commit();
    }

    template<class PackageT>
    void CCPOperation<PackageT>::Copy(const PassVector &copies)
    {
        if (copies.empty())
            return;

        Atmos::GridPosition topLeft(getGridPos(**copies.begin()).Build());
        Atmos::GridPosition bottomRight(topLeft);

        // First, get all the ghost sprites and also figure out the center of this
        for (auto &loop : copies)
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

        for (auto &loop : copies)
            AddEntry(*loop, getGridPos(*loop).Build(), center);

        SetCurrentGridPosition(center);
    }

    template<class PackageT>
    void CCPOperation<PackageT>::Copy(const PackageT &copy)
    {
        Atmos::TilePosition position(getTilePos(*loop));
        AddEntry(copy, position, position);
        SetCurrentTilePosition(position);
    }

    template<class PackageT>
    void CCPOperation<PackageT>::Paste()
    {
        if (IsWorking())
        {
            PlaceCopies();
            return;
        }

        AttemptMoveEntries(GetGridPosition(GetMousePosition()), true);
        RenderEntries();
        SignalWorking();
    }
}