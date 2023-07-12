#pragma once

#include <wx/window.h>
#include <wx/timer.h>
#include <wx/treebase.h>

#include "ViewportStateBase.h"

#include "Point.h"

#include "BoxOperation.h"
#include "MoveOperation.h"

#include <Atmos/Entity.h>
#include <Atmos/GridPosition.h>

namespace Creation
{
    class Point;

    static const char* voidTileImageName = "VoidTile.png";
    static const char* voidEntityImageName = "VoidEntity.png";
    static const char* pixelImageName = "Pixel.png";
    static const char* targetImageName = "Target.png";
    static const char* spriteSelectionName = "SpriteSelection.fx";

    namespace Viewport
    {
        class Viewport : public wxWindow
        {
        private:
            enum class Key
            {
                UP,
                DOWN,
                LEFT,
                RIGHT
            };
        private:
            class BoxSelectorConcat
            {
            private:
                enum class Side
                {
                    NONE,
                    LEFT,
                    RIGHT
                };
            private:
                Side side;
                BoxOperation wrapped;
                void ConsumeBoxSelector(BoxOperation &box);
                Point TransformPoint(const Point &pt);
            public:
                BoxSelectorConcat();
                void LeftDown(const Point &pt);
                void LeftUp(const Point &pt);
                void RightDown(const Point &pt);
                void RightUp(const Point &pt);
                void MouseMove(const Point &pt);
                void Draw();

                bool IsWorking() const;

                void Clear();
            };
        private:
            void OnResize(wxSizeEvent &e);
            void OnPaint(wxPaintEvent &e);
            void OnMouseLeftDown(wxMouseEvent &e);
            void OnMouseLeftUp(wxMouseEvent &e);
            void OnMouseRightDown(wxMouseEvent &e);
            void OnMouseRightUp(wxMouseEvent &e);
            void OnMouseMove(wxMouseEvent &e);
            void OnKeyDown(wxKeyEvent &e);
            void OnKeyUp(wxKeyEvent &e);
            void OnRefreshTimer(wxTimerEvent &e);
            void OnMovementTimer(wxTimerEvent &e);
            void OnSetFocus(wxFocusEvent &e);
            void OnLostFocus(wxFocusEvent &e);
            wxDECLARE_EVENT_TABLE();

            void OnCommandStack();
            void ConsumeLeftBoxSelector(BoxOperation &box);
            void ConsumeRightBoxSelector(BoxOperation &box);
        private:
            bool active;

            wxTimer refreshTimer;
            wxTimer movementTimer;
            std::unordered_map<Key, bool> arrowKeys;

            Mode mode;
            typedef std::unique_ptr<StateBase> ModeStatePtr;
            typedef std::unordered_map<Mode, ModeStatePtr> ModeStates;
            ModeStates modeStates;
            ModeStates::iterator currentState;

            BoxSelectorConcat boxSelector;

            std::unique_ptr<PreviewOperation> moveOperation;
            std::unique_ptr<PreviewOperation> ccpOperation;

            void SetOrigin(const Point &set);
            template<class Ret, class... Args, class... PassArgs>
            void DoIfCurrentStateValid(Ret(StateBase::*func)(Args...), PassArgs && ... args);
            template<class Ret, class... Args, class... PassArgs>
            void DoIfCurrentStateValid(Ret(StateBase::*func)(Args...) const, PassArgs && ... args);
            bool IsCurrentStateValid() const;
        public:
            Viewport(wxWindow *parent, wxWindowID winid, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = 0, const wxString &name = "Viewport");
            void SetMode(Mode set);
            Mode GetMode() const;

            void Activate();
            void Deactivate();

            Point GetTopLeft() const;
            Point GetOrigin() const;
            Atmos::GridPosition::ValueT GetZView() const;

            void Cut();
            void Copy();
            void Paste();

            void SelectItem(wxTreeItemId id);
            void DeselectItem(wxTreeItemId id);
        };

        template<class Ret, class... Args, class... PassArgs>
        void Viewport::DoIfCurrentStateValid(Ret(StateBase::*func)(Args...), PassArgs && ... args)
        {
            if (IsCurrentStateValid())
                (currentState->second.get()->*func)(std::forward<PassArgs>(args)...);
        }

        template<class Ret, class... Args, class... PassArgs>
        void Viewport::DoIfCurrentStateValid(Ret(StateBase::*func)(Args...) const, PassArgs && ... args)
        {
            if (IsCurrentStateValid())
                (currentState->second.get()->*func)(std::forward<PassArgs>(args)...);
        }

        extern Viewport *viewport;
    }
}