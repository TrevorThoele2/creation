#pragma once

#include <vector>
#include <list>
#include <memory>

#include "Image.h"
#include "Point.h"
#include "Optional.h"

#include "BuildPackage.h"

#include <Atmos/GridPosition.h>
#include <Function/Function.h>

namespace Creation
{
    // Defines an operation which has a preview (ghosted sprites)
    class PreviewOperation
    {
    public:
        typedef std::vector<Build::Package<Atmos::GridPosition>> TilePositionVector;
        typedef function::Function<bool, const TilePositionVector&> IsOverlappingOuterFunc;
    protected:
        struct Entry
        {
            class Data
            {
            public:
                virtual ~Data() = 0 {}
            };

            std::unique_ptr<::Atmos::RenderFragment> fragment;
            Atmos::GridPosition originalTilePos;
            Atmos::RelativeGridPosition relTilePos;
            std::unique_ptr<Data> data;

            Entry(::Atmos::RenderFragment *fragment, const Atmos::GridPosition &originalTilePos, const Atmos::RelativeGridPosition &relTilePos, Data *data);
            ~Entry();

            Entry(const Entry &arg) = delete;
            Entry& operator=(const Entry &arg) = delete;

            Entry(Entry &&arg);
            Entry& operator=(Entry &&arg);
        };

        typedef std::list<Entry> EntryList;
        EntryList entryList;
    private:
        bool working;

        Atmos::GridPosition currentGridPos;

        IsOverlappingOuterFunc isOverlappingOuter;

        virtual void OnMouseDownImpl(const Point &pt) = 0;
        virtual void OnMouseUpImpl(const Point &pt) = 0;
        virtual void OnMouseMoveImpl(const Point &pt, const Atmos::RelativeGridPosition &offset) = 0;
        virtual void ClearImpl() = 0;
    protected:
        void SignalWorking(bool set = true);
        // Fragment needs to be heap
        void AddEntry(::Atmos::RenderFragment *fragment, const Atmos::GridPosition &originalPos, const Atmos::RelativeGridPosition &offset, bool render = true);
        // Fragment & data needs to be heap
        void AddEntry(::Atmos::RenderFragment *fragment, const Atmos::GridPosition &originalPos, const Atmos::RelativeGridPosition &offset, Entry::Data *data, bool render = true);
        void ClearEntries();
        void RenderEntries(bool render = true);

        // Moves the entries (and the current position) to their positions relative to the point given
        // If skipCheck is true, then will skip checking if currentPosition == position
        // Returns if the movement happened
        bool AttemptMoveEntries(const Atmos::GridPosition &position, bool skipCheck = false);

        void SetCurrentGridPosition(const Atmos::GridPosition &set);
        void SetCurrentGridPosition(const Point &pt);
        const Atmos::GridPosition& GetCurrentGridPosition() const;

        static Point GetMousePosition();
        static Atmos::GridPosition::ValueT GetZView();
        static Atmos::GridPosition GetGridPosition(const Point &pt);
    public:
        PreviewOperation(IsOverlappingOuterFunc &&isOverlappingOuter);
        virtual ~PreviewOperation() = 0 {}
        bool IsWorking() const;

        void OnMouseDown(const Point &pt);
        void OnMouseUp(const Point &pt);
        void OnMouseMove(const Point &pt);

        void Clear();
    };
}