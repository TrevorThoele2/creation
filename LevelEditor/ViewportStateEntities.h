#pragma once

#include <wx/spinbutt.h>
#include <wx/choice.h>
#include <wx/listbox.h>
#include <wx/textctrl.h>

#include "ViewportStateBase.h"
#include "BuildPackageEntities.h"

#include "Entity.h"
#include "Selection.h"

#include "CCPOperation.h"

namespace Creation
{
    namespace Viewport
    {
        class Viewport;
        class StateEntities : public StateBase
        {
        private:
            typedef ::Atmos::Entity ObjectT;
            typedef Build::Package<ObjectT> PackageT;

            typedef CCPOperation<PackageT> CCPOperationT;
            typedef MoveOperation<PackageT> MoveOperationT;
        private:
            Selection<PackageT> selection;
            bool ignoreTreeItem;

            CCPOperationT* CreateCCP();
            MoveOperationT* CreateMove();
            std::vector<PackageT*> CreateEntityVector();
            std::vector<const PackageT*> CreateConstEntityVector();

            void ClearSelection();
        public:
            StateEntities(Viewport &viewport);
            Mode GetMode() const override final { return Mode::ENTITIES; }

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