
#include "DataViewStateGameData.h"
#include "CurrentWorld.h"
#include "MainFrame.h"
#include <wx/treectrl.h>

namespace Creation
{
    void DataViewStateGameData::SetupBreakdowns()
    {
        typedef decltype(decltype(stats)::entries) StatsEntryList;
        typedef decltype(decltype(elements)::entries) ElementEntryList;

        resources.Setup(CurrentWorld::globals.globalContextResourcePackage);
        stats.Setup(CurrentWorld::globals.dataStandardStatPackage);
        stats.entries.SetNiceNameFunctions(StatsEntryList::NiceNameExtractorFunction(static_cast<String(*)(StatsEntryList::BreakdownT&)>([](StatsEntryList::BreakdownT &breakdown) { return breakdown.name.Get()->Build(); })),
            StatsEntryList::NiceNameGetEventFunction(static_cast<Event<const DataBreakdownEditArgs&>*(*)(StatsEntryList::BreakdownT&)>([](StatsEntryList::BreakdownT &breakdown) -> Event<const DataBreakdownEditArgs&>* { return &breakdown.name.edited; })),
            StatsEntryList::NameSetFunction(static_cast<void(*)(StatsEntryList::BreakdownT&, const String&)>([](StatsEntryList::BreakdownT &breakdown, const String &str) { Build::Package<::Atmos::Name> package; package.value = str; breakdown.name.Edit(std::move(package)); })));
        elements.Setup(CurrentWorld::globals.globalContextElementPackage);
        elements.entries.SetNiceNameFunctions(ElementEntryList::NiceNameExtractorFunction(static_cast<String(*)(ElementEntryList::BreakdownT&)>([](ElementEntryList::BreakdownT &breakdown) { return breakdown.name.Get()->Build(); })),
            ElementEntryList::NiceNameGetEventFunction(static_cast<Event<const DataBreakdownEditArgs&>*(*)(ElementEntryList::BreakdownT&)>([](ElementEntryList::BreakdownT &breakdown) -> Event<const DataBreakdownEditArgs&>* { return &breakdown.name.edited; })),
            ElementEntryList::NameSetFunction(static_cast<void(*)(ElementEntryList::BreakdownT&, const String&)>([](ElementEntryList::BreakdownT &breakdown, const String &str) { Build::Package<::Atmos::Name> package; package.value = str; breakdown.name.Edit(std::move(package)); })));
    }

    void DataViewStateGameData::StartImpl()
    {

    }

    void DataViewStateGameData::StopImpl()
    {

    }

    void DataViewStateGameData::SelectImpl(wxTreeItemId id)
    {
        auto data = static_cast<DataBreakdownWXItemData*>(Tree()->GetItemData(id))->data;
        data->CreateEditorProperties(nullptr);
        GetMainFrame()->GetDataView()->PropertyGrid()->FitColumns();
    }

    void DataViewStateGameData::DeselectImpl(wxTreeItemId id)
    {

    }

    void DataViewStateGameData::DeselectAllImpl()
    {
        GetMainFrame()->GetDataView()->Deselect(resources.GetTreeItemID());
        GetMainFrame()->GetDataView()->Deselect(stats.GetTreeItemID());
        GetMainFrame()->GetDataView()->Deselect(elements.GetTreeItemID());
    }

    void DataViewStateGameData::AddImpl()
    {

    }

    void DataViewStateGameData::RemoveImpl()
    {

    }

    void DataViewStateGameData::CreateBreakdownsFromScratchImpl()
    {
        resources.CreateBreakdowns();
        stats.CreateBreakdowns();
        elements.CreateBreakdowns();
    }

    void DataViewStateGameData::DestroyBreakdownsImpl()
    {
        resources.DestroyBreakdowns();
        stats.DestroyBreakdowns();
        elements.DestroyBreakdowns();
    }

    void DataViewStateGameData::CreateTreePiecesImpl()
    {
        resources.CreateTreePiece(TreeRootID());
        stats.CreateTreePiece(TreeRootID());
        elements.CreateTreePiece(TreeRootID());
    }

    void DataViewStateGameData::CreateEditorPropertiesImpl()
    {
        resources.CreateEditorProperties(nullptr);
        stats.CreateEditorProperties(nullptr);
        elements.CreateEditorProperties(nullptr);

        GetMainFrame()->GetDataView()->PropertyGrid()->FitColumns();
    }

    void DataViewStateGameData::DestroyEditorPropertiesImpl(bool destroyTreeItems)
    {
        resources.DestroyEditorProperties(destroyTreeItems);
        stats.DestroyEditorProperties(destroyTreeItems);
        elements.DestroyEditorProperties(destroyTreeItems);
    }

    DataViewStateGameData::Type DataViewStateGameData::GetTypeImpl() const
    {
        return type;
    }

    DataViewStateGameData::DataViewStateGameData(DataView *dataView) : DataViewState(dataView),
        resources("Resources Global Context", nullptr),
        stats("Stats Data Standard", nullptr),
        elements("Elements Global Context", nullptr)
    {
        SetupBreakdowns();
    }

    void DataViewStateGameData::SetResourcesGlobalContext(const ResourceBreakdown::PackageT &set)
    {
        resources.Edit(set);
    }

    void DataViewStateGameData::SetResourcesGlobalContext(ResourceBreakdown::PackageT &&set)
    {
        resources.Edit(std::move(set));
    }

    void DataViewStateGameData::SetStatsDataStandard(const StatBreakdown::PackageT &set)
    {
        stats.Edit(set);
    }

    void DataViewStateGameData::SetStatsDataStandard(StatBreakdown::PackageT &&set)
    {
        stats.Edit(std::move(set));
    }

    void DataViewStateGameData::SetElementsGlobalContext(const ElementBreakdown::PackageT &set)
    {
        elements.Edit(set);
    }

    void DataViewStateGameData::SetElementsGlobalContext(ElementBreakdown::PackageT &&set)
    {
        elements.Edit(std::move(set));
    }

    String DataViewStateGameData::GetTreeString()
    {
        return "Game Data";
    }
}