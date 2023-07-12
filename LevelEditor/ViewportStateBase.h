#pragma once

#include <wx/event.h>
#include "ViewportMode.h"
#include "PreviewOperation.h"

namespace Creation
{
    class BoxOperation;
    class Point;

    namespace Viewport
    {
        class StateBase
        {
        public:
            virtual ~StateBase() = 0 {}
            virtual Mode GetMode() const = 0;

            virtual void Select() = 0;
            virtual void Deselect() = 0;

            virtual void SelectItem(wxTreeItemId id) = 0;
            virtual void DeselectItem(wxTreeItemId id) = 0;

            virtual void OnMouseMove(wxMouseEvent &e) = 0;
            virtual void OnMouseLeftDown(wxMouseEvent &e) = 0;
            virtual void OnMouseLeftUp(wxMouseEvent &e) = 0;
            virtual void OnMouseRightDown(wxMouseEvent &e) = 0;
            virtual void OnMouseRightUp(wxMouseEvent &e) = 0;
            virtual void OnDelete() = 0;
            virtual void OnMove() = 0;

            virtual void ConsumeLeftBoxSelector(BoxOperation &box) = 0;
            virtual void ConsumeRightBoxSelector(BoxOperation &box) = 0;
            // If this is true, then a box operation will happen for this state, otherwise it will only pick singles
            virtual bool UsesRightBoxOperation() const = 0;

            virtual PreviewOperation* CreateMoveOperation() = 0;
            virtual PreviewOperation* Cut() = 0;
            virtual PreviewOperation* Copy() = 0;

            virtual bool IsSelectionEmpty() const = 0;
            virtual bool IsMouseOverSelection(const Point &pt) const = 0;
        };
    }
}