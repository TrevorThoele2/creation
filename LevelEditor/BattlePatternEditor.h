#pragma once

#include <wx\panel.h>
#include <wx\textctrl.h>
#include <wx\choice.h>
#include <wx\dcclient.h>
#include <wx\statbox.h>
#include <wx\sizer.h>
#include <wx\valnum.h>
#include <wx\event.h>

#include "Point.h"
#include "GridLines.h"

#include <Atmos/BattlePatternHolder.h>
#include <Atmos/RenderSurface.h>

namespace Creation
{
    class BattlePatternEditor;

    class BattlePatternEvent : public wxCommandEvent
    {
    public:
        typedef Atmos::RelativeGridPosition RelativeGridPosition;
    private:
        RelativeGridPosition relGridPosition;
    public:
        BattlePatternEvent(const RelativeGridPosition &relGridPosition, wxEventType commandEventType = wxEVT_NULL, int id = 0);
        BattlePatternEvent* Clone() const override;
        const RelativeGridPosition& GetRelGridPosition() const;
    };
}

wxDECLARE_EVENT(LE_BATTLE_PATTERN_ADDED, Creation::BattlePatternEvent);
wxDECLARE_EVENT(LE_BATTLE_PATTERN_REMOVED, Creation::BattlePatternEvent);
wxDECLARE_EVENT(LE_BATTLE_PATTERN_GRID_CLICKED, wxMouseEvent);

namespace Creation
{
    class BattlePatternEditor : public wxPanel
    {
    public:
        typedef ::Atmos::BattlePatternHolder PatternT;
        typedef PatternT::Piece PieceT;
        typedef PatternT::PatternT::KeyT RelTilePosition;
    private:
        PatternT pattern;

        wxTextCtrl *leftDimText;
        wxTextCtrl *rightDimText;
        wxTextCtrl *topDimText;
        wxTextCtrl *bottomDimText;
        wxTextCtrl *originXText;
        wxTextCtrl *originYText;
        wxTextCtrl *zText;
        wxChoice *direction;
        wxPanel *grid;

        typedef short PositionDim;
        PositionDim originX;
        PositionDim originY;
        PositionDim curZ;

        typedef unsigned short Dimension;
        Dimension leftDim;
        Dimension rightDim;
        Dimension topDim;
        Dimension bottomDim;

        typedef unsigned int SizeDimension;
        SizeDimension gridWidth;
        SizeDimension gridHeight;

        Atmos::RenderSurface *renderSurface;

        void OnOriginXTextChanged(wxCommandEvent &e);
        void OnOriginYTextChanged(wxCommandEvent &e);
        void OnZTextChanged(wxCommandEvent &e);
        void OnLeftColsChanged(wxCommandEvent &e);
        void OnRightColsChanged(wxCommandEvent &e);
        void OnTopRowsChanged(wxCommandEvent &e);
        void OnBottomRowsChanged(wxCommandEvent &e);
        void OnDirectionChanged(wxCommandEvent &e);
        void OnPaintGrid(wxPaintEvent &e);
        void OnResizeGrid(wxSizeEvent &e);
        void OnLeftDownGrid(wxMouseEvent &e);

        void SetXOrigin(PositionDim set);
        void SetYOrigin(PositionDim set);
        void SetZText(PositionDim set);
        void SetDimension(wxTextCtrl &text, Dimension &dim, Dimension set);
        void SetDimensionFromText(wxTextCtrl &text, Dimension &dim);
        void CalculateGridSize();

        RelTilePosition GetTilePositionFromScreenPosition(const Point &screenPos) const;
        bool CheckPositionInsideGrid(const RelTilePosition &pos) const;
    public:
        BattlePatternEditor(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxString &name = "BattlePatternEditor");
        ~BattlePatternEditor();

        void AddPiece(const RelTilePosition &pos, PieceT &add);
        void AddPieceAtScreenPosition(const Point &pos, PieceT &add);
        void RemovePiece(const RelTilePosition &remove);
        void RemovePieceAtScreenPosition(const Point &pos);
        PieceT* FindPiece(const RelTilePosition &find);
        const PieceT* FindPiece(const RelTilePosition &find) const;

        void Reset();
        void Reset(const PatternT &use);

        const PatternT& GetObject() const;
    };
}