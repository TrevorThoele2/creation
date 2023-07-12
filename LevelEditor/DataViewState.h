#pragma once

#include <Atmos/GridPosition.h>
#include <wx/panel.h>
#include <wx/treebase.h>

class wxTreeCtrl;

namespace Creation
{
    class DataView;

    class DataViewState
    {
    public:
        enum Type : unsigned char
        {
            ASSETS,
            REGISTRIES,
            GAME_DATA,

            TILES,
            ENTITIES,

            NONE
        };
    private:
        DataView *dataView;

        virtual void StartImpl() = 0;
        virtual void StopImpl() = 0;

        virtual void SelectImpl(wxTreeItemId id) = 0;
        virtual void DeselectImpl(wxTreeItemId id) = 0;
        virtual void DeselectAllImpl() = 0;
        virtual void AddImpl() = 0;
        virtual void RemoveImpl() = 0;

        virtual void CreateBreakdownsFromScratchImpl() = 0;
        virtual void DestroyBreakdownsImpl() = 0;
        virtual void CreateTreePiecesImpl() = 0;
        virtual void CreateEditorPropertiesImpl() = 0;
        virtual void DestroyEditorPropertiesImpl(bool destroyTreeItems) = 0;

        virtual Type GetTypeImpl() const = 0;
    protected:
        DataView* GetDataView();
        const DataView* GetDataView() const;

        wxTreeCtrl* Tree();
        const wxTreeCtrl* Tree() const;

        wxTreeItemId TreeRootID() const;

        wxWindow* EditorPanel();
        const wxWindow* EditorPanel() const;
    public:
        DataViewState(DataView *dataView);
        
        void Start();
        void Stop();

        void Select(wxTreeItemId id);
        void Deselect(wxTreeItemId id);
        void DeselectAll();

        void Add();
        void Remove();

        void CreateBreakdownsFromScratch();
        void DestroyBreakdowns();
        void CreateTreePieces();
        void CreateEditorProperties();
        void DestroyEditorProperties(bool destroyTreeItems = false);

        Type GetType() const;
    };
}