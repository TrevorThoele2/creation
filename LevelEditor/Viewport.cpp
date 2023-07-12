
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>

#include "Viewport.h"

#include "ViewportStateTiles.h"
#include "ViewportStateEntities.h"

#include "GridLines.h"

#include "CommandStack.h"
#include "MainFrame.h"
#include "CurrentWorld.h"
#include "InternalShaders.h"
#include "ImageRegistry.h"

#include "Point.h"

#include "GraphicsHandler.h"
#include <Atmos/Environment.h>
#include <Atmos/NullAudio.h>
#include <Atmos/FileSystemWindows.h>
#include <Atmos/WindowsInput.h>
#include <Atmos/Camera.h>
#include <Atmos/EntitySystem.h>
#include <Atmos/MasterSoundHandler.h>

#include <AGUI/System.h>
#include <AGUI/DXGraphics.h>

namespace Creation
{
    namespace Viewport
    {
        HWND hWnd = nullptr;
    }
}

namespace Atmos
{
    namespace Input
    {
        class EditorHandler : public WindowsHandler
        {
        private:
            void AddInputsImpl() override
            {}

            void WorkInputsImpl(InputVector &inputs) override
            {}

            bool ShouldAddActions() const override
            {
                return false;
            }

            MousePosition GetMousePositionImpl() const override
            {
                POINT pt;
                GetCursorPos(&pt);
                ScreenToClient(::Creation::Viewport::hWnd, &pt);
                return MousePosition(static_cast<MousePosition::ValueT>(pt.x), static_cast<MousePosition::ValueT>(pt.y));
            }
        };
    }
}

namespace Creation
{
    namespace Viewport
    {
        void Viewport::BoxSelectorConcat::ConsumeBoxSelector(BoxOperation &box)
        {
            switch (side)
            {
            case Side::LEFT:
                viewport->ConsumeLeftBoxSelector(box);
                break;
            case Side::RIGHT:
                viewport->ConsumeRightBoxSelector(box);
                break;
            }
        }

        Point Viewport::BoxSelectorConcat::TransformPoint(const Point &pt)
        {
            Atmos::Position2D position(Atmos::Position2D::FromScreen(Atmos::Position2D(pt.x, pt.y), Atmos::Position2D(viewport->GetTopLeft().x, viewport->GetTopLeft().y)));
            return Point(position.GetX(), position.GetY());
        }

        Viewport::BoxSelectorConcat::BoxSelectorConcat() : side(Side::NONE)
        {
            wrapped.consume.Subscribe(&BoxSelectorConcat::ConsumeBoxSelector, *this);
        }

        void Viewport::BoxSelectorConcat::LeftDown(const Point &pt)
        {
            if (side != Side::NONE)
                return;

            side = Side::LEFT;
            wrapped.SetColor(Atmos::Color(127, 0, 0, 255));
            wrapped.MouseDown(TransformPoint(pt));
        }

        void Viewport::BoxSelectorConcat::LeftUp(const Point &pt)
        {
            if (side != Side::LEFT || !wrapped.IsWorking())
                return;

            wrapped.MouseUp(TransformPoint(pt));
            side = Side::NONE;
        }

        void Viewport::BoxSelectorConcat::RightDown(const Point &pt)
        {
            if (side != Side::NONE)
                return;

            side = Side::RIGHT;
            wrapped.SetColor(Atmos::Color(127, 255, 255, 255));
            wrapped.MouseDown(TransformPoint(pt));
        }

        void Viewport::BoxSelectorConcat::RightUp(const Point &pt)
        {
            if (side != Side::RIGHT || !wrapped.IsWorking())
                return;

            wrapped.MouseUp(TransformPoint(pt));
            side = Side::NONE;
        }

        void Viewport::BoxSelectorConcat::MouseMove(const Point &pt)
        {
            wrapped.MouseMove(TransformPoint(pt));
        }

        void Viewport::BoxSelectorConcat::Draw()
        {
            if(wrapped.IsWorking())
                wrapped.Draw(*Atmos::Environment::GetGraphics(), 0.0f);
        }

        bool Viewport::BoxSelectorConcat::IsWorking() const
        {
            return wrapped.IsWorking();
        }

        void Viewport::BoxSelectorConcat::Clear()
        {
            side = Side::NONE;
            wrapped.Clear();
        }

        void Viewport::OnResize(wxSizeEvent &e)
        {
            Atmos::Join2<UINT> size(GetClientSize().GetWidth(), GetClientSize().GetHeight());
            if (Atmos::Environment::GetGraphics()->GetMainDimensions() == size)
                return;

            Atmos::Environment::GetGraphics()->SetMainDimensions(size);
            Atmos::Environment::GetGraphics()->Reinitialize();
            Atmos::Camera::Work();
            e.Skip();
        }

        void Viewport::OnPaint(wxPaintEvent &e)
        {
            wxPaintDC dc(this);

            if (!active)
            {
                dc.Clear();
                return;
            }

            GetCurrentRenderFragments()->Work();

            auto graphicsHandler = Atmos::Environment::GetGraphics();
            if (!graphicsHandler->Start())
            {
                dc.Clear();
                return;
            }
            
            {
                typedef Atmos::GraphicsHandlerBase::Target Target;
                graphicsHandler->ClearTarget(Atmos::Flags<Target>({ Target::MAIN }), Atmos::Color(255, 0, 0, 0));
            }

            Point viewportTopLeft(GetTopLeft());

            graphicsHandler->StartLines();
            RenderDimensionLinesFill(GetClientSize().GetWidth(), GetClientSize().GetHeight(), viewportTopLeft, 4);
            graphicsHandler->EndLines();

            graphicsHandler->StartSprites();
            CurrentWorld::Draw(static_cast<MainFrame*>(GetParent())->GetZView() + ::Atmos::GRID_SIZE<int>);
            graphicsHandler->Flush();
            boxSelector.Draw();

            graphicsHandler->EndSprites();

            graphicsHandler->End();
            graphicsHandler->Present();
        }

        void Viewport::OnMouseLeftDown(wxMouseEvent &e)
        {
            if (!IsCurrentStateValid())
            {
                e.Skip();
                return;
            }
            
            auto useState = currentState->second.get();
            Point pt(e.GetPosition());

            // This is when we should be moving the selection
            if (!useState->IsSelectionEmpty() && useState->IsMouseOverSelection(pt))
            {
                moveOperation.reset(useState->CreateMoveOperation());
                moveOperation->OnMouseDown(pt);
            }
            else if (ccpOperation)
                ccpOperation->OnMouseDown(pt);

            boxSelector.LeftDown(e.GetPosition());
            useState->OnMouseLeftDown(e);

            e.Skip();
        }

        void Viewport::OnMouseLeftUp(wxMouseEvent &e)
        {
            if (!IsCurrentStateValid())
            {
                e.Skip();
                return;
            }

            auto useState = currentState->second.get();
            Point pt(e.GetPosition());

            if (moveOperation)
            {
                moveOperation->OnMouseUp(pt);
                useState->OnMove();
                moveOperation.reset();
            }
            else if (ccpOperation)
                ccpOperation->OnMouseUp(pt);

            boxSelector.LeftUp(pt);
            useState->OnMouseLeftUp(e);

            e.Skip();
        }

        void Viewport::OnMouseRightDown(wxMouseEvent &e)
        {
            if (IsCurrentStateValid())
            {
                if(currentState->second->UsesRightBoxOperation())
                    boxSelector.RightDown(Point(e.GetPosition()));

                currentState->second->OnMouseRightDown(e);
            }

            e.Skip();
        }

        void Viewport::OnMouseRightUp(wxMouseEvent &e)
        {
            if (IsCurrentStateValid())
            {
                if (currentState->second->UsesRightBoxOperation())
                    boxSelector.RightUp(Point(e.GetPosition()));

                currentState->second->OnMouseRightUp(e);
            }

            e.Skip();
        }

        void Viewport::OnMouseMove(wxMouseEvent &e)
        {
            if (!IsCurrentStateValid())
            {
                e.Skip();
                return;
            }

            ::Atmos::Position3D screenPos(::Atmos::Position3D::FromScreen(::Atmos::Position3D(e.GetPosition().x, e.GetPosition().y), ::Atmos::Position3D(GetTopLeft().x, GetTopLeft().y), GetZView()));
            GetMainFrame()->SetStatusText("(" + ::Atmos::ToString(::Atmos::GridPosition::DimensionFromPosition(screenPos.GetX())) + ", " + ::Atmos::ToString(::Atmos::GridPosition::DimensionFromPosition(screenPos.GetY())) + ", " + ::Atmos::ToString(::Atmos::GridPosition::DimensionFromPosition(screenPos.GetZ())) + ")", 1);

            auto useState = currentState->second.get();
            Point pt(e.GetPosition());

            if (moveOperation && !useState->IsSelectionEmpty())
                moveOperation->OnMouseMove(pt);
            else if (ccpOperation && ccpOperation->IsWorking())
                ccpOperation->OnMouseMove(pt);
            else if(boxSelector.IsWorking())
                boxSelector.MouseMove(pt);

            useState->OnMouseMove(e);

            e.Skip();
        }

        void Viewport::OnKeyDown(wxKeyEvent &e)
        {
            auto arrowKeyFunc = [&](Key focus)
            {
                arrowKeys.find(focus)->second = true;
                if (!movementTimer.IsRunning())
                {
                    movementTimer.Start(1);
                    refreshTimer.Stop();
                }
            };

            std::string name;

            switch (e.GetKeyCode())
            {
            case WXK_UP:
                arrowKeyFunc(Key::UP);
                break;
            case WXK_DOWN:
                arrowKeyFunc(Key::DOWN);
                break;
            case WXK_LEFT:
                arrowKeyFunc(Key::LEFT);
                break;
            case WXK_RIGHT:
                arrowKeyFunc(Key::RIGHT);
                break;
            }

            e.Skip();
        }

        void Viewport::OnKeyUp(wxKeyEvent &e)
        {
            auto arrowKeyFunc = [&](Key focus)
            {
                arrowKeys.find(focus)->second = false;
                for (auto &loop : arrowKeys)
                {
                    if (loop.second)
                        return;
                }

                movementTimer.Stop();
                refreshTimer.Start(16);
            };

            switch (e.GetKeyCode())
            {
            case WXK_UP:
                arrowKeyFunc(Key::UP);
                break;
            case WXK_DOWN:
                arrowKeyFunc(Key::DOWN);
                break;
            case WXK_LEFT:
                arrowKeyFunc(Key::LEFT);
                break;
            case WXK_RIGHT:
                arrowKeyFunc(Key::RIGHT);
                break;
            case WXK_DELETE:
                if (IsCurrentStateValid())
                    currentState->second->OnDelete();
                break;
            }

            e.Skip();
        }

        void Viewport::OnRefreshTimer(wxTimerEvent &e)
        {
            if(IsShown())
                Refresh();

            e.Skip();
        }

        void Viewport::OnMovementTimer(wxTimerEvent &e)
        {
            const double SCROLL_FACTOR = 5.0;

            bool up = arrowKeys.find(Key::UP)->second;
            bool down = arrowKeys.find(Key::DOWN)->second;
            bool left = arrowKeys.find(Key::LEFT)->second;
            bool right = arrowKeys.find(Key::RIGHT)->second;

            Point &origin = GetOrigin();
            if (up && !down)
                SetOrigin(Point(origin.x, origin.y - SCROLL_FACTOR));
            else if (down && !up)
                SetOrigin(Point(origin.x, origin.y + SCROLL_FACTOR));

            if (left && !right)
                SetOrigin(Point(origin.x - SCROLL_FACTOR, origin.y));
            else if (right && !left)
                SetOrigin(Point(origin.x + SCROLL_FACTOR, origin.y));

            Refresh();
            e.Skip();
        }

        void Viewport::OnLostFocus(wxFocusEvent &e)
        {
            boxSelector.Clear();
            e.Skip();
        }
    }
}

wxBEGIN_EVENT_TABLE(Creation::Viewport::Viewport, wxWindow)
    EVT_SIZE(Creation::Viewport::Viewport::OnResize)
    EVT_PAINT(Creation::Viewport::Viewport::OnPaint)
    EVT_LEFT_DOWN(Creation::Viewport::Viewport::OnMouseLeftDown)
    EVT_LEFT_UP(Creation::Viewport::Viewport::OnMouseLeftUp)
    EVT_RIGHT_DOWN(Creation::Viewport::Viewport::OnMouseRightDown)
    EVT_RIGHT_UP(Creation::Viewport::Viewport::OnMouseRightUp)
    EVT_MOTION(Creation::Viewport::Viewport::OnMouseMove)
    EVT_KEY_DOWN(Creation::Viewport::Viewport::OnKeyDown)
    EVT_KEY_UP(Creation::Viewport::Viewport::OnKeyUp)
    EVT_TIMER(1, Creation::Viewport::Viewport::OnMovementTimer)
    EVT_TIMER(2, Creation::Viewport::Viewport::OnRefreshTimer)
    EVT_KILL_FOCUS(Creation::Viewport::Viewport::OnLostFocus)
wxEND_EVENT_TABLE()

namespace Creation
{
    namespace Viewport
    {
        void Viewport::OnCommandStack()
        {

        }

        void Viewport::ConsumeLeftBoxSelector(BoxOperation &box)
        {
            DoIfCurrentStateValid(&StateBase::ConsumeLeftBoxSelector, box);
        }

        void Viewport::ConsumeRightBoxSelector(BoxOperation &box)
        {
            DoIfCurrentStateValid(&StateBase::ConsumeRightBoxSelector, box);
        }

        void Viewport::SetOrigin(const Point &set)
        {
            if (Point(Atmos::Camera::GetViewOrigin().GetX(), Atmos::Camera::GetViewOrigin().GetY()) == set)
                return;

            Atmos::Camera::MoveToInstant(set.ToAtmos());
        }

        bool Viewport::IsCurrentStateValid() const
        {
            return currentState != modeStates.end();
        }

        Viewport::Viewport(wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size, long style, const wxString &name) : wxWindow(parent, winid, pos, size, style | wxFULL_REPAINT_ON_RESIZE, name), active(false), refreshTimer(this, 2), movementTimer(this, 1), mode(Mode::NONE), currentState(modeStates.end())
        {
            hWnd = GetHWND();

            Atmos::Environment::CreateFileSystem<::Atmos::FileSystem::WindowsHandler>();
            Atmos::Environment::CreateInputHandler<::Atmos::Input::EditorHandler>();
            Atmos::ErrorHandler::Init();
            Atmos::Environment::CreateGraphicsHandler<GraphicsHandler>(GetHWND(), Atmos::Join2<UINT>(GetClientSize().GetWidth(), GetClientSize().GetHeight()), false, false);
            Atmos::Environment::CreateAudioHandler<Atmos::NullAudioHandler>();
            agui::System::Initialize(agui::Resolution::Size(Atmos::Environment::GetDefaultSize().first, Atmos::Environment::GetDefaultSize().second), new agui::DX9GraphicsHandler(Atmos::Environment::GetGraphics<Atmos::DX9GraphicsHandler>()->GetDevice()));
            // Images
            ImageRegistry::Add(::Atmos::Environment::GetGraphics<GraphicsHandler>()->CreateCreationImageAsset("Images\\Pixel.png"));
            ImageRegistry::Add(::Atmos::Environment::GetGraphics<GraphicsHandler>()->CreateCreationImageAsset("Images\\VoidTile.png"));
            ImageRegistry::Add(::Atmos::Environment::GetGraphics<GraphicsHandler>()->CreateCreationImageAsset("Images\\VoidEntity.png"));
            ImageRegistry::Add(::Atmos::Environment::GetGraphics<GraphicsHandler>()->CreateCreationImageAsset("Images\\Target.png"));
            // Shaders
            InternalShaders::Add(Atmos::Environment::GetFileSystem()->GetExePath().Append("Shaders\\SpriteSelection.fx").GetValue());
            InternalShaders::ConstructAll();

            Atmos::Ent::SystemHandler::Init();
            ::Atmos::MasterSoundHandler::SetMasterVolume(0);
            ::Atmos::Ent::SystemHandler::IgnoreStateApproval(true);

            SetBackgroundStyle(wxBG_STYLE_PAINT);
            SetBackgroundColour(*wxLIGHT_GREY);

            arrowKeys.emplace(Key::UP, false);
            arrowKeys.emplace(Key::DOWN, false);
            arrowKeys.emplace(Key::LEFT, false);
            arrowKeys.emplace(Key::RIGHT, false);

            viewport = this;
            Command::Stack::Instance().onChanged.Subscribe(&Viewport::OnCommandStack, *this);

            StateBase *newState = new StateTiles(*this);
            modeStates.emplace(newState->GetMode(), ModeStatePtr(newState));
            newState = new StateEntities(*this);
            modeStates.emplace(newState->GetMode(), ModeStatePtr(newState));

            Atmos::Camera::MoveToInstant(Atmos::Position2D());

            refreshTimer.Start(16);
        }

        void Viewport::SetMode(Mode set)
        {
            if (mode == set)
                return;

            mode = set;

            DoIfCurrentStateValid(&StateBase::Deselect);
            currentState = modeStates.find(mode);
            DoIfCurrentStateValid(&StateBase::Select);
        }

        Mode Viewport::GetMode() const
        {
            return mode;
        }

        void Viewport::Activate()
        {
            active = true;
        }

        void Viewport::Deactivate()
        {
            active = false;
        }

        Point Viewport::GetTopLeft() const
        {
            return Point(Atmos::Camera::GetTopLeft().GetX(), Atmos::Camera::GetTopLeft().GetY());
        }

        Point Viewport::GetOrigin() const
        {
            return Point(Atmos::Camera::GetViewOrigin().GetX(), Atmos::Camera::GetViewOrigin().GetY());
        }

        Atmos::GridPosition::ValueT Viewport::GetZView() const
        {
            return static_cast<MainFrame*>(GetParent())->GetZView();
        }

        void Viewport::Cut()
        {
            if (IsCurrentStateValid())
                ccpOperation.reset(currentState->second->Cut());
        }

        void Viewport::Copy()
        {
            if (IsCurrentStateValid())
                ccpOperation.reset(currentState->second->Copy());
        }

        void Viewport::Paste()
        {
            if (IsCurrentStateValid() && ccpOperation && (!moveOperation || moveOperation->IsWorking()))
                static_cast<CCPOperationBase*>(ccpOperation.get())->Paste();
        }

        void Viewport::SelectItem(wxTreeItemId id)
        {
            DoIfCurrentStateValid(&StateBase::SelectItem, id);
        }

        void Viewport::DeselectItem(wxTreeItemId id)
        {
            DoIfCurrentStateValid(&StateBase::DeselectItem, id);
        }

        Viewport *viewport;
    }
}