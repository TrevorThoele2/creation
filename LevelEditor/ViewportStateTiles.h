#pragma once

#include <wx/checkbox.h>
#include <wx/scrolwin.h>

#include "ViewportStateBase.h"

#include "Selection.h"

#include "SpriteListView.h"
#include "Sprite.h"

#include "Tile.h"

#include "CCPOperation.h"
#include "MoveOperation.h"

namespace Creation
{
    namespace Viewport
    {
        class Viewport;
        class StateTiles : public StateBase
        {
        private:
            typedef ::Atmos::Tile ObjectT;
            typedef Build::Package<ObjectT> PackageT;

            typedef CCPOperation<PackageT> CCPOperationT;
            typedef MoveOperation<PackageT> MoveOperationT;
        private:
            Selection<PackageT> selection;
            bool ignoreTreeItem;

            CCPOperationT* CreateCCP();
            MoveOperationT* CreateMove();
            std::vector<PackageT*> CreateTileVector();
            std::vector<const PackageT*> CreateConstTileVector() const;

            void ClearSelection();
        public:
            StateTiles(Viewport &viewport);
            Mode GetMode() const override final { return Mode::TILES; }

            void Select() override final {}
            void Deselect() override final;

            void SelectItem(wxTreeItemId id) override final;
            void DeselectItem(wxTreeItemId id) override final;

            void OnMouseMove(wxMouseEvent &e) override final {}
            void OnMouseLeftDown(wxMouseEvent &e) override final {}
            void OnMouseLeftUp(wxMouseEvent &e) override final {}
            void OnMouseRightDown(wxMouseEvent &e) override final {}
            void OnMouseRightUp(wxMouseEvent &e) override final {}
            void OnDelete() override final;
            void OnMove() override final;

            void ConsumeLeftBoxSelector(BoxOperation &box) override final;
            void ConsumeRightBoxSelector(BoxOperation &box) override final;
            // If this is true, then a box operation will happen for this state, otherwise it will only pick singles
            bool UsesRightBoxOperation() const override final;

            PreviewOperation* CreateMoveOperation() override final;
            PreviewOperation* Cut() override final;
            PreviewOperation* Copy() override final;

            bool IsSelectionEmpty() const override final;
            bool IsMouseOverSelection(const Point &pt) const override final;
        };
    }
}