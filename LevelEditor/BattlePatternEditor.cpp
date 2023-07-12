
#include "BattlePatternEditor.h"

#include "DirectionData.h"

#include <Atmos/Environment.h>
#include <Atmos/GraphicsHandlerBase.h>
#include <Atmos/RenderSurface.h>
#include <Atmos/Camera.h>
#include <Atmos/Color.h>
#include <Atmos/String.h>
#include <Atmos/GridSize.h>
#include <Atmos/StringUtility.h>

namespace Creation
{
    BattlePatternEvent::BattlePatternEvent(const RelativeGridPosition &relGridPosition, wxEventType commandEventType, int id) : wxCommandEvent(commandEventType, id), relGridPosition(relGridPosition)
    {}

    BattlePatternEvent* BattlePatternEvent::Clone() const
    {
        return new BattlePatternEvent(*this);
    }

    const BattlePatternEvent::RelativeGridPosition& BattlePatternEvent::GetRelGridPosition() const
    {
        return relGridPosition;
    }
}

wxDEFINE_EVENT(LE_BATTLE_PATTERN_ADDED, Creation::BattlePatternEvent);
wxDEFINE_EVENT(LE_BATTLE_PATTERN_REMOVED, Creation::BattlePatternEvent);
wxDEFINE_EVENT(LE_BATTLE_PATTERN_GRID_CLICKED, wxMouseEvent);

namespace Creation
{
    void BattlePatternEditor::OnOriginXTextChanged(wxCommandEvent &e)
    {
        SetXOrigin(Atmos::FromString<PositionDim>(originXText->GetValue().ToStdString()));
    }

    void BattlePatternEditor::OnOriginYTextChanged(wxCommandEvent &e)
    {
        SetYOrigin(Atmos::FromString<PositionDim>(originYText->GetValue().ToStdString()));
    }

    void BattlePatternEditor::OnZTextChanged(wxCommandEvent &e)
    {
        curZ = Atmos::FromString<decltype(curZ)>(zText->GetValue().ToStdString());
    }

    void BattlePatternEditor::OnLeftColsChanged(wxCommandEvent &e)
    {
        SetDimensionFromText(*leftDimText, leftDim);
    }

    void BattlePatternEditor::OnRightColsChanged(wxCommandEvent &e)
    {
        SetDimensionFromText(*rightDimText, rightDim);
    }

    void BattlePatternEditor::OnTopRowsChanged(wxCommandEvent &e)
    {
        SetDimensionFromText(*topDimText, topDim);
    }

    void BattlePatternEditor::OnBottomRowsChanged(wxCommandEvent &e)
    {
        SetDimensionFromText(*bottomDimText, bottomDim);
    }

    void BattlePatternEditor::OnDirectionChanged(wxCommandEvent &e)
    {
        auto relativeDirection = pattern.pieces.GetDirection().GetRelativeDirection(DataManager<::Atmos::Direction::ValueT>::FindFromString(direction->GetStringSelection().ToStdString())->GetValue());
        pattern.pieces.Rotate(relativeDirection);

        switch (relativeDirection)
        {
        case Atmos::Direction::RelativeValueT::SAME:
            break;
        case Atmos::Direction::RelativeValueT::LEFT:
        {
            auto prevTop = topDim;
            SetDimension(*topDimText, topDim, rightDim);
            SetDimension(*rightDimText, rightDim, bottomDim);
            SetDimension(*bottomDimText, bottomDim, leftDim);
            SetDimension(*leftDimText, leftDim, prevTop);
            Refresh();
        }
        break;
        case Atmos::Direction::RelativeValueT::RIGHT:
        {
            auto prevTop = topDim;
            SetDimension(*topDimText, topDim, leftDim);
            SetDimension(*leftDimText, leftDim, bottomDim);
            SetDimension(*bottomDimText, bottomDim, rightDim);
            SetDimension(*rightDimText, rightDim, prevTop);
            Refresh();
        }
        break;
        case Atmos::Direction::RelativeValueT::OPPOSED:
        {
            auto prevTop = topDim;
            auto prevLeft = leftDim;
            SetDimension(*topDimText, topDim, bottomDim);
            SetDimension(*bottomDimText, bottomDim, prevTop);
            SetDimension(*leftDimText, leftDim, rightDim);
            SetDimension(*rightDimText, rightDim, prevLeft);
            Refresh();
        }
        break;
        }
    }

    void BattlePatternEditor::OnPaintGrid(wxPaintEvent &e)
    {
        wxPaintDC dc(grid);

        auto graphicsHandler = Atmos::Environment::GetGraphics();
        if (!graphicsHandler->Start())
        {
            e.Skip();
            return;
        }

        renderSurface->SetAsRenderTarget();

        {
            typedef Atmos::GraphicsHandlerBase::Target Target;
            graphicsHandler->ClearTarget(Atmos::Flags<Target>({ Target::MAIN }), Atmos::Color(255, 0, 0, 0));
        }

        // Width, height, top left and previous view origin
        Atmos::Position2D prevCameraViewOrigin(Atmos::Camera::GetViewOrigin());
        // Move camera
        Atmos::Camera::MoveToInstant(Atmos::Position2D((originX * Atmos::GRID_SIZE<Atmos::Position2D::ValueT>) + (Atmos::GRID_SIZE<Atmos::Position2D::ValueT> / 2.0), (originY * Atmos::GRID_SIZE<Atmos::Position2D::ValueT>) + (Atmos::GRID_SIZE<Atmos::Position2D::ValueT> / 2.0)));
        Atmos::Position2D cameraViewOrigin(Atmos::Camera::GetViewOrigin());
        // Find top left of the center tile position, and then move by leftDim/topDim, and then move by camera view origin
        Point::ValueT left = (((grid->GetClientSize().GetX() / 2.0)) - (leftDim * Atmos::GRID_SIZE<Atmos::Position2D::ValueT>)) - cameraViewOrigin.GetX();
        Point::ValueT top = (((grid->GetClientSize().GetY() / 2.0)) - (topDim * Atmos::GRID_SIZE<Atmos::Position2D::ValueT>)) - cameraViewOrigin.GetY();

        graphicsHandler->StartLines();
        RenderDimensionLinesGrid(gridWidth, gridHeight, Point(left, top));
        graphicsHandler->EndLines();

        // Draw middle sprite
        Atmos::Sprite middleSprite("target", 1, Atmos::Color());
        middleSprite.SetPosition(Atmos::GridPosition(0, 0, 0));

        graphicsHandler->StartSprites(pattern.pieces.size());
        Atmos::GridPosition centerPos(0, 0, 0);
        for (auto &loop : pattern.pieces)
        {
            Atmos::Position2D pos(centerPos.FindOffset(loop.first));
            pos.DecrementX(16.0f);
            pos.DecrementY(16.0f);
            loop.second->selectionSprite.Draw();
        }

        graphicsHandler->Flush();
        graphicsHandler->RenderSprite(middleSprite);
        graphicsHandler->EndSprites();

        graphicsHandler->End();
        graphicsHandler->Present();
        graphicsHandler->SetRenderTargetToMain();

        // Move camera back
        Atmos::Camera::MoveToInstant(prevCameraViewOrigin);

        e.Skip();
    }

    void BattlePatternEditor::OnResizeGrid(wxSizeEvent &e)
    {
        if (!renderSurface)
        {
            renderSurface = &Atmos::Environment::GetGraphics()->CreateRenderSurface(grid->GetHWND());
            renderSurface->FitToWindow();
            e.Skip();
            return;
        }

        {
            std::remove_const<std::remove_reference<decltype(renderSurface->GetDimensions())>::type>::type size;
            size.first = e.GetSize().GetX();
            size.second = e.GetSize().GetY();
            if (size == renderSurface->GetDimensions())
            {
                e.Skip();
                return;
            }
        }

        // Check size
        {
            auto &size = e.GetSize();
            if (size.GetX() == 0 || size.GetY() == 0)
            {
                renderSurface->DestroyThis();
                renderSurface = nullptr;
                e.Skip();
                return;
            }
        }

        renderSurface->FitToWindow();
        e.Skip();
    }

    void BattlePatternEditor::OnLeftDownGrid(wxMouseEvent &e)
    {
        wxMouseEvent postE(e);
        postE.SetEventType(LE_BATTLE_PATTERN_GRID_CLICKED);
        wxPostEvent(this, postE);

        e.Skip();
    }

    void BattlePatternEditor::SetXOrigin(PositionDim set)
    {
        originX = set;
        Refresh();
    }

    void BattlePatternEditor::SetYOrigin(PositionDim set)
    {
        originY = set;
        Refresh();
    }

    void BattlePatternEditor::SetZText(PositionDim set)
    {
        curZ = set;
        zText->SetValue(std::to_string(set));
    }

    void BattlePatternEditor::SetDimension(wxTextCtrl &text, Dimension &dim, Dimension set)
    {
        if (set == 0)
            set = 1;

        text.ChangeValue(std::to_string(set));
        dim = set;

        CalculateGridSize();
        Refresh();
    }

    void BattlePatternEditor::SetDimensionFromText(wxTextCtrl &text, Dimension &dim)
    {
        SetDimension(text, dim, Atmos::FromString<Dimension>(text.GetValue().ToStdString()));
    }

    void BattlePatternEditor::CalculateGridSize()
    {
        gridWidth = (leftDim + rightDim + 1) * Atmos::GRID_SIZE<Dimension>;
        gridHeight = (topDim + bottomDim + 1) * Atmos::GRID_SIZE<Dimension>;

        for (auto loop = pattern.pieces.begin(); loop != pattern.pieces.end();)
        {
            if (!CheckPositionInsideGrid(loop->first))
            {
                BattlePatternEvent postE(loop->first, LE_BATTLE_PATTERN_REMOVED);
                wxPostEvent(this, postE);

                loop = pattern.pieces.Remove(loop);
            }
            else
                ++loop;
        }
    }

    typename BattlePatternEditor::RelTilePosition BattlePatternEditor::GetTilePositionFromScreenPosition(const Point &screenPos) const
    {
        auto newX = (screenPos.x - (originX * Atmos::GRID_SIZE<PositionDim>)) - (grid->GetClientSize().GetWidth() / 2.0) + (Atmos::GRID_SIZE<double> / 2.0);
        auto newY = (screenPos.y - (originY * Atmos::GRID_SIZE<PositionDim>)) - (grid->GetClientSize().GetHeight() / 2.0) + (Atmos::GRID_SIZE<double> / 2.0);
        Atmos::GridPosition tilePos(Atmos::Position2D(newX, newY), curZ);
        return RelTilePosition(tilePos.x, tilePos.y, tilePos.z);
    }

    bool BattlePatternEditor::CheckPositionInsideGrid(const RelTilePosition &pos) const
    {
        return !(pos.x < -leftDim || pos.x > rightDim || pos.y < -topDim || pos.y > bottomDim);
    }

    BattlePatternEditor::BattlePatternEditor(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxString &name) : wxPanel(parent, id, pos, wxDefaultSize, 0, name), curZ(0), leftDim(1), rightDim(1), topDim(1), bottomDim(1)
    {
        auto sizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, "Hit Pattern"), wxVERTICAL);
        SetSizer(sizer);

        // Cols/rows textctrls and direction
        {
            auto totalTextCtrlSizer = new wxBoxSizer(wxVERTICAL);
            sizer->Add(totalTextCtrlSizer, 0, wxEXPAND);

            auto topTextCtrlSizer = new wxBoxSizer(wxHORIZONTAL);
            totalTextCtrlSizer->Add(topTextCtrlSizer, 0, wxEXPAND);

            // Origin X
            {
                auto thisSizer = new wxStaticBoxSizer(new wxStaticBox(sizer->GetStaticBox(), wxID_ANY, "X"), wxVERTICAL);
                topTextCtrlSizer->Add(thisSizer);

                originXText = new wxTextCtrl(thisSizer->GetStaticBox(), wxID_ANY, '0', wxDefaultPosition, wxDefaultSize, 0, wxIntegerValidator<PositionDim>());
                originXText->Bind(wxEVT_TEXT, &BattlePatternEditor::OnOriginXTextChanged, this);
                thisSizer->Add(originXText);
            }

            // Origin Y
            {
                auto thisSizer = new wxStaticBoxSizer(new wxStaticBox(sizer->GetStaticBox(), wxID_ANY, "Y"), wxVERTICAL);
                topTextCtrlSizer->Add(thisSizer);

                originYText = new wxTextCtrl(thisSizer->GetStaticBox(), wxID_ANY, '0', wxDefaultPosition, wxDefaultSize, 0, wxIntegerValidator<PositionDim>());
                originYText->Bind(wxEVT_TEXT, &BattlePatternEditor::OnOriginYTextChanged, this);
                thisSizer->Add(originYText);
            }

            // Work Z
            {
                auto thisSizer = new wxStaticBoxSizer(new wxStaticBox(sizer->GetStaticBox(), wxID_ANY, "Z"), wxVERTICAL);
                topTextCtrlSizer->Add(thisSizer);

                zText = new wxTextCtrl(thisSizer->GetStaticBox(), wxID_ANY, '0', wxDefaultPosition, wxDefaultSize, 0, wxIntegerValidator<PositionDim>());
                zText->Bind(wxEVT_TEXT, &BattlePatternEditor::OnZTextChanged, this);
                thisSizer->Add(zText);
            }

            auto midTextCtrlSizer = new wxBoxSizer(wxHORIZONTAL);
            totalTextCtrlSizer->Add(midTextCtrlSizer);

            // Left
            {
                auto thisSizer = new wxStaticBoxSizer(new wxStaticBox(sizer->GetStaticBox(), wxID_ANY, "Left"), wxVERTICAL);
                midTextCtrlSizer->Add(thisSizer);

                leftDimText = new wxTextCtrl(thisSizer->GetStaticBox(), wxID_ANY, '1', wxDefaultPosition, wxDefaultSize, 0, wxIntegerValidator<Dimension>());
                leftDimText->Bind(wxEVT_TEXT, &BattlePatternEditor::OnLeftColsChanged, this);
                thisSizer->Add(leftDimText);
            }

            // Right
            {
                auto thisSizer = new wxStaticBoxSizer(new wxStaticBox(sizer->GetStaticBox(), wxID_ANY, "Right"), wxVERTICAL);
                midTextCtrlSizer->Add(thisSizer);

                rightDimText = new wxTextCtrl(thisSizer->GetStaticBox(), wxID_ANY, '1', wxDefaultPosition, wxDefaultSize, 0, wxIntegerValidator<Dimension>());
                rightDimText->Bind(wxEVT_TEXT, &BattlePatternEditor::OnRightColsChanged, this);
                thisSizer->Add(rightDimText);
            }

            // Direction
            {
                auto thisSizer = new wxStaticBoxSizer(new wxStaticBox(sizer->GetStaticBox(), wxID_ANY, "Direction"), wxVERTICAL);
                midTextCtrlSizer->Add(thisSizer);

                direction = new wxChoice(thisSizer->GetStaticBox(), wxID_ANY);
                for (auto &loop : DataManager<::Atmos::Direction::ValueT>::Get())
                    direction->Append(loop.GetString());
                direction->Select(0);
                direction->Bind(wxEVT_CHOICE, &BattlePatternEditor::OnDirectionChanged, this);
                thisSizer->Add(direction);
            }

            auto bottomTextCtrlSizer = new wxBoxSizer(wxHORIZONTAL);
            totalTextCtrlSizer->Add(bottomTextCtrlSizer, 0, wxEXPAND);

            // Top
            {
                auto thisSizer = new wxStaticBoxSizer(new wxStaticBox(sizer->GetStaticBox(), wxID_ANY, "Top"), wxVERTICAL);
                bottomTextCtrlSizer->Add(thisSizer);

                topDimText = new wxTextCtrl(sizer->GetStaticBox(), wxID_ANY, '1', wxDefaultPosition, wxDefaultSize, 0, wxIntegerValidator<Dimension>());
                topDimText->Bind(wxEVT_TEXT, &BattlePatternEditor::OnTopRowsChanged, this);
                thisSizer->Add(topDimText);
            }

            // Bottom
            {
                auto thisSizer = new wxStaticBoxSizer(new wxStaticBox(sizer->GetStaticBox(), wxID_ANY, "Bottom"), wxVERTICAL);
                bottomTextCtrlSizer->Add(thisSizer);

                bottomDimText = new wxTextCtrl(sizer->GetStaticBox(), wxID_ANY, '1', wxDefaultPosition, wxDefaultSize, 0, wxIntegerValidator<Dimension>());
                bottomDimText->Bind(wxEVT_TEXT, &BattlePatternEditor::OnBottomRowsChanged, this);
                thisSizer->Add(bottomDimText);
            }
        }

        // Grid
        {
            grid = new wxPanel(sizer->GetStaticBox());
            grid->SetMinClientSize(wxSize(Atmos::GRID_SIZE<int> * 11, Atmos::GRID_SIZE<int> * 11));
            grid->Bind(wxEVT_PAINT, &BattlePatternEditor::OnPaintGrid, this);
            grid->Bind(wxEVT_SIZE, &BattlePatternEditor::OnResizeGrid, this);
            grid->Bind(wxEVT_LEFT_DOWN, &BattlePatternEditor::OnLeftDownGrid, this);
            sizer->Add(grid);

            renderSurface = &Atmos::Environment::GetGraphics()->CreateRenderSurface(grid->GetHWND());
            Layout();

            CalculateGridSize();
        }
    }

    BattlePatternEditor::~BattlePatternEditor()
    {
        renderSurface->DestroyThis();
    }

    void BattlePatternEditor::AddPiece(const RelTilePosition &pos, PieceT &add)
    {
        if (!CheckPositionInsideGrid(pos))
            return;

        pattern.pieces.Add(pos, &add);

        grid->Refresh();
        BattlePatternEvent postE(pos, LE_BATTLE_PATTERN_ADDED);
        wxPostEvent(this, postE);
    }

    void BattlePatternEditor::AddPieceAtScreenPosition(const Point &pos, PieceT &add)
    {
        AddPiece(GetTilePositionFromScreenPosition(pos), add);
    }

    void BattlePatternEditor::RemovePiece(const RelTilePosition &remove)
    {
        if (!pattern.pieces.Remove(remove))
            return;

        grid->Refresh();
        BattlePatternEvent postE(remove, LE_BATTLE_PATTERN_REMOVED);
        wxPostEvent(this, postE);
    }

    void BattlePatternEditor::RemovePieceAtScreenPosition(const Point &pos)
    {
        RemovePiece(GetTilePositionFromScreenPosition(pos));
    }

    typename BattlePatternEditor::PieceT* BattlePatternEditor::FindPiece(const RelTilePosition &find)
    {
        return *pattern.pieces.Find(find);
    }

    typename const BattlePatternEditor::PieceT* BattlePatternEditor::FindPiece(const RelTilePosition &find) const
    {
        return *pattern.pieces.Find(find);
    }

    void BattlePatternEditor::Reset()
    {
        const Dimension resetTo = 1;

        pattern.pieces.Clear();
        SetDimension(*leftDimText, leftDim, resetTo);
        SetDimension(*rightDimText, rightDim, resetTo);
        SetDimension(*topDimText, topDim, resetTo);
        SetDimension(*bottomDimText, bottomDim, resetTo);
        SetZText(0);
        SetXOrigin(0);
        SetYOrigin(0);
    }

    void BattlePatternEditor::Reset(const PatternT &use)
    {
        pattern.pieces.Clear();

        Dimension leftDimTemp = 1;
        Dimension rightDimTemp = 1;
        Dimension topDimTemp = 1;
        Dimension bottomDimTemp = 1;

        for (auto &loop : use.pieces)
        {
            if (loop.first.x < -leftDimTemp)
                leftDimTemp = -loop.first.x;
            else if (loop.first.x > rightDimTemp)
                rightDimTemp = loop.first.x;

            if (loop.first.y < -topDimTemp)
                topDimTemp = -loop.first.y;
            else if (loop.first.y > bottomDimTemp)
                bottomDimTemp = loop.first.y;
        }

        SetDimension(*leftDimText, leftDim, leftDimTemp);
        SetDimension(*rightDimText, rightDim, rightDimTemp);
        SetDimension(*topDimText, topDim, topDimTemp);
        SetDimension(*bottomDimText, bottomDim, bottomDimTemp);

        pattern = use;

        SetZText(0);
        SetXOrigin(0);
        SetYOrigin(0);
    }

    const BattlePatternEditor::PatternT& BattlePatternEditor::GetObject() const
    {
        return pattern;
    }
}