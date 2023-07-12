
#include "DataViewStateTiles.h"

#include "DataViewStateAssets.h"
#include "TileViewManager.h"

#include "CurrentWorld.h"
#include "Viewport.h"
#include "MainFrame.h"

#include <wx/treectrl.h>

namespace Creation
{
    DataViewStateTiles::BreakdownT& DataViewStateTiles::CreateBreakdown(PackageT &add, bool onlyBreakdown)
    {
        decltype(breakdownList)::iterator breakdownAdded;
        if (onlyBreakdown)
            breakdownAdded = breakdownList.AddOnlyBreakdown(add);
        else
            breakdownAdded = breakdownList.Add(add);
        auto &emplaced = breakdownMap.emplace(add.position.Build(), EntryT(&*breakdownAdded, ::Atmos::EventScopedConnectionManager())).first->second;
        auto &breakdown = std::get<0>(emplaced);
        breakdown->SetNiceName(BreakdownT::GetString(add.position));
        breakdown->Setup(add);
        breakdown->SortTreeItem(true);
        return *breakdown;
    }

    void DataViewStateTiles::RemoveBreakdown(BreakdownListT::iterator remove)
    {
        for (auto loop = CurrentWorld::fieldPackage.tiles.value.begin(); loop != CurrentWorld::fieldPackage.tiles.value.end(); ++loop)
        {
            if (*loop == *remove->Get())
            {
                CurrentWorld::fieldPackage.tiles.value.Remove(loop);
                break;
            }
        }
        
        breakdownMap.erase(remove->Get()->position.Build());
        Tree()->UnselectItem(remove->GetTreeItemID());
        Tree()->Delete(remove->GetTreeItemID());
        breakdownList.Remove(remove);
    }

    void DataViewStateTiles::OnBreakdownCreated(const DataBreakdownAddArgs &args)
    {
        auto casted = static_cast<BreakdownT*>(args.Added());
        auto &connections = std::get<1>(breakdownMap.emplace(casted->position.Get()->Build(), EntryT(casted, ::Atmos::EventScopedConnectionManager())).first->second);

        if (GetDataView()->GetCurrentState() == this)
            args.Added()->CreateTreePiece(TreeRootID());

        connections.Add(casted->position.preEdit.Subscribe(&DataViewStateTiles::OnPositionPreChanged, *this));
        connections.Add(casted->position.edited.Subscribe(&DataViewStateTiles::OnPositionChanged, *this));
        TileViewManager::Evaluate(*casted->position.Get());
    }

    static Build::Package<::Atmos::GridPosition> focusedRemovePackage;

    void DataViewStateTiles::OnBreakdownPreRemoved(const DataBreakdownPreRemoveArgs &args)
    {
        auto casted = static_cast<BreakdownT*>(args.ToBeRemoved());
        breakdownMap.erase(casted->position.Get()->Build());
        focusedRemovePackage = *casted->position.Get();
        if (Viewport::viewport->GetMode() == Viewport::Mode::TILES)
            Viewport::viewport->DeselectItem(casted->GetTreeItemID());
    }

    void DataViewStateTiles::OnBreakdownPostRemoved(const DataBreakdownPostRemoveArgs &args)
    {
        TileViewManager::Evaluate(focusedRemovePackage);
    }

    void DataViewStateTiles::OnPositionPreChanged(DataBreakdownPreEditArgs &args)
    {
        // Find out if there's an object at this position
        auto found = breakdownMap.find(static_cast<Build::Package<::Atmos::GridPosition>*>(args.Proposed())->Build());
        if (found == breakdownMap.end())
            return;

        args.Reject(true);
    }

    void DataViewStateTiles::OnPositionChanged(const DataBreakdownEditArgs &args)
    {
        auto prevCasted = static_cast<Build::Package<::Atmos::GridPosition>*>(args.Prev());
        auto currentCasted = static_cast<Build::Package<::Atmos::GridPosition>*>(args.Current());
        auto found = breakdownMap.find(prevCasted->Build());
        breakdownMap.emplace(currentCasted->Build(), std::move(found->second));
        breakdownMap.erase(found);
        TileViewManager::Evaluate(*prevCasted);
        TileViewManager::Evaluate(*currentCasted);
    }

    void DataViewStateTiles::OnMaterialEdited(const DataBreakdownEditArgs &args)
    {
        for (auto &loop : breakdownList)
            TileViewManager::Evaluate(*loop.Get());
    }

    void DataViewStateTiles::SetupBreakdowns()
    {
        breakdownList.Setup(CurrentWorld::fieldPackage.tiles);
        breakdownList.SetNiceNameFunctions(BreakdownListT::NiceNameExtractorFunction(static_cast<String(*)(BreakdownListT::BreakdownT&)>([](BreakdownListT::BreakdownT &breakdown) { return breakdown.position.Get()->ToString(); })),
            BreakdownListT::NiceNameGetEventFunction(static_cast<Event<const DataBreakdownEditArgs&>*(*)(BreakdownListT::BreakdownT&)>([](BreakdownListT::BreakdownT &breakdown) -> Event<const DataBreakdownEditArgs&>* { return &breakdown.position.edited; })),
            BreakdownListT::NameSetFunction(static_cast<void(*)(BreakdownListT::BreakdownT&, const String&)>([](BreakdownListT::BreakdownT &breakdown, const String &str) {})));
        breakdownList.added.Subscribe(&DataViewStateTiles::OnBreakdownCreated, *this);
        breakdownList.preRemove.Subscribe(&DataViewStateTiles::OnBreakdownPreRemoved, *this);
        breakdownList.postRemove.Subscribe(&DataViewStateTiles::OnBreakdownPostRemoved, *this);
        breakdownList.SetAddChildrenToProperties(false);
        GetDataView()->GetSpecificState<DataViewStateAssets>()->onMaterialEdited.Subscribe(&DataViewStateTiles::OnMaterialEdited, *this);
    }

    void DataViewStateTiles::StartImpl()
    {}

    void DataViewStateTiles::StopImpl()
    {}

    void DataViewStateTiles::SelectImpl(wxTreeItemId id)
    {}

    void DataViewStateTiles::DeselectImpl(wxTreeItemId id)
    {}

    void DataViewStateTiles::DeselectAllImpl()
    {
        for (auto &loop : breakdownList)
            GetMainFrame()->GetDataView()->Deselect(loop.GetTreeItemID());
    }

    void DataViewStateTiles::AddImpl()
    {}

    void DataViewStateTiles::RemoveImpl()
    {}

    void DataViewStateTiles::CreateBreakdownsFromScratchImpl()
    {
        for (auto &loop : CurrentWorld::fieldPackage.tiles.value)
            CreateBreakdown(loop, true);
    }

    void DataViewStateTiles::DestroyBreakdownsImpl()
    {
        breakdownMap.clear();
        breakdownList.DestroyBreakdowns();
    }

    void DataViewStateTiles::CreateTreePiecesImpl()
    {
        for (auto &loop : breakdownList)
            loop.CreateTreePiece(TreeRootID());
    }

    void DataViewStateTiles::CreateEditorPropertiesImpl()
    {
        for (auto &loop : breakdownList)
            loop.CreateEditorProperties(nullptr);

        GetMainFrame()->GetDataView()->PropertyGrid()->FitColumns();
    }

    void DataViewStateTiles::DestroyEditorPropertiesImpl(bool destroyTreeItems)
    {
        for (auto &loop : breakdownList)
            loop.DestroyEditorProperties(destroyTreeItems);
    }

    DataViewStateTiles::Type DataViewStateTiles::GetTypeImpl() const
    {
        return type;
    }

    DataViewStateTiles::DataViewStateTiles(DataView *dataView) : DataViewState(dataView),
        breakdownList("List", nullptr)
    {
        SetupBreakdowns();
        breakdownList.SetPrependEntryName("Tile");
    }

    DataViewStateTiles::BreakdownT* DataViewStateTiles::Find(const PositionPackageT &find)
    {
        auto found = breakdownMap.find(find.Build());
        if (found == breakdownMap.end())
            return nullptr;

        return std::get<0>(found->second);
    }

    DataViewStateTiles::BreakdownT* DataViewStateTiles::Find(const PackageT &find)
    {
        for (auto &loop : breakdownList)
        {
            if (*loop.Get() == find)
                return &loop;
        }

        return nullptr;
    }

    void DataViewStateTiles::Select(const PositionPackageT &pos)
    {
        auto found = breakdownMap.find(pos.Build());
        if (found == breakdownMap.end())
            return;

        wxTreeItemId id(std::get<0>(found->second)->GetTreeItemID());
        if (!Tree()->IsSelected(id))
            GetMainFrame()->GetDataView()->Select(id);
    }

    void DataViewStateTiles::Select(const std::vector<PositionPackageT> &positions)
    {
        std::vector<wxTreeItemId> pass;
        for (auto &loop : positions)
        {
            auto found = breakdownMap.find(loop.Build());
            if (found == breakdownMap.end())
                continue;

            wxTreeItemId id(std::get<0>(found->second)->GetTreeItemID());
            if (!Tree()->IsSelected(id))
                pass.push_back(id);
        }

        GetMainFrame()->GetDataView()->ChangeSelection(pass, std::vector<wxTreeItemId>());
    }

    void DataViewStateTiles::Deselect(const PositionPackageT &pos)
    {
        auto found = breakdownMap.find(pos.Build());
        if (found == breakdownMap.end())
            return;

        wxTreeItemId id(std::get<0>(found->second)->GetTreeItemID());
        if (Tree()->IsSelected(id))
            Tree()->UnselectItem(id);
    }

    void DataViewStateTiles::Deselect(const std::vector<PositionPackageT> &positions)
    {
        std::vector<wxTreeItemId> pass;
        for (auto &loop : positions)
        {
            auto found = breakdownMap.find(loop.Build());
            if (found == breakdownMap.end())
                continue;

            wxTreeItemId id(std::get<0>(found->second)->GetTreeItemID());
            if (!Tree()->IsSelected(id))
                pass.push_back(id);
        }

        GetMainFrame()->GetDataView()->ChangeSelection(std::vector<wxTreeItemId>(), pass);
    }

    String DataViewStateTiles::GetTreeString()
    {
        return String("Tiles");
    }
}