
#include "DataViewState.h"

#include "DataView.h"
#include "DataBreakdownWXItemData.h"
#include <wx/treectrl.h>
#include <wx/button.h>
#include <wx/sizer.h>

namespace Creation
{
    DataView* DataViewState::GetDataView()
    {
        return dataView;
    }

    const DataView* DataViewState::GetDataView() const
    {
        return dataView;
    }

    wxTreeCtrl* DataViewState::Tree()
    {
        return dataView->Tree();
    }

    const wxTreeCtrl* DataViewState::Tree() const
    {
        return dataView->Tree();
    }

    wxTreeItemId DataViewState::TreeRootID() const
    {
        return dataView->TreeRootID();
    }

    wxWindow* DataViewState::EditorPanel()
    {
        return dataView->EditorPanel();
    }

    const wxWindow* DataViewState::EditorPanel() const
    {
        return dataView->EditorPanel();
    }

    DataViewState::DataViewState(DataView *dataView) : dataView(dataView)
    {}

    void DataViewState::Start()
    {
        CreateTreePieces();
        StartImpl();
    }

    void DataViewState::Stop()
    {
        DeselectAll();
        DestroyEditorProperties(true);
        StopImpl();
    }

    void DataViewState::Select(wxTreeItemId id)
    {
        SelectImpl(id);
    }

    void DataViewState::Deselect(wxTreeItemId id)
    {
        DeselectImpl(id);
    }

    void DataViewState::DeselectAll()
    {
        DeselectAllImpl();
    }

    void DataViewState::Add()
    {
        AddImpl();
    }

    void DataViewState::Remove()
    {
        RemoveImpl();
    }

    void DataViewState::CreateBreakdownsFromScratch()
    {
        CreateBreakdownsFromScratchImpl();
    }

    void DataViewState::DestroyBreakdowns()
    {
        DestroyBreakdownsImpl();
    }

    void DataViewState::CreateTreePieces()
    {
        CreateTreePiecesImpl();
    }

    void DataViewState::CreateEditorProperties()
    {
        CreateEditorPropertiesImpl();
    }

    void DataViewState::DestroyEditorProperties(bool destroyTreeItems)
    {
        DestroyEditorPropertiesImpl(destroyTreeItems);
    }

    DataViewState::Type DataViewState::GetType() const
    {
        return GetTypeImpl();
    }
}