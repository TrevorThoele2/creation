
#include "DataViewStateEntities.h"

#include "DataViewStateAssets.h"
#include "Viewport.h"
#include "EntityViewManager.h"

#include "CurrentWorld.h"

#include <Atmos/EntityPositionSystem.h>

#include "MainFrame.h"
#include <wx/treectrl.h>

namespace Creation
{
    DataViewStateEntities::BreakdownT& DataViewStateEntities::CreateBreakdown(PackageT &add, bool onlyBreakdown)
    {
        decltype(breakdownList)::iterator breakdownAdded;
        if (onlyBreakdown)
            breakdownAdded = breakdownList.AddOnlyBreakdown(add);
        else
            breakdownAdded = breakdownList.Add(add);
        auto &emplaced = breakdownMap.emplace(add.generalComponent.position.Build(), EntryT(&*breakdownAdded, ::Atmos::EventScopedConnectionManager())).first->second;
        auto &breakdown = std::get<0>(emplaced);
        breakdown->Setup(add);
        return *breakdown;
    }

    void DataViewStateEntities::RemoveBreakdown(BreakdownListT::iterator remove)
    {
        for (auto loop = CurrentWorld::fieldPackage.entities.value.begin(); loop != CurrentWorld::fieldPackage.entities.value.end(); ++loop)
        {
            if (*loop == *remove->Get())
            {
                CurrentWorld::fieldPackage.entities.value.Remove(loop);
                break;
            }
        }

        breakdownMap.erase(remove->Get()->generalComponent.position.Build());
        Tree()->UnselectItem(remove->GetTreeItemID());
        Tree()->Delete(remove->GetTreeItemID());
        breakdownList.Remove(remove);
    }

    void DataViewStateEntities::OnBreakdownCreated(const DataBreakdownAddArgs &args)
    {
        auto casted = static_cast<BreakdownT*>(args.Added());
        auto &connections = std::get<1>(breakdownMap.emplace(casted->generalComponent.position.Get()->Build(), EntryT(casted, ::Atmos::EventScopedConnectionManager())).first->second);

        if (GetDataView()->GetCurrentState() == this)
            args.Added()->CreateTreePiece(TreeRootID());

        connections.Add(casted->generalComponent.position.preEdit.Subscribe(&DataViewStateEntities::OnPositionPreChanged, *this));
        connections.Add(casted->generalComponent.position.edited.Subscribe(&DataViewStateEntities::OnPositionChanged, *this));
        EntityViewManager::Evaluate(*casted->generalComponent.position.Get());
    }

    static Build::Package<::Atmos::GridPosition> focusedRemovePackage;

    void DataViewStateEntities::OnBreakdownPreRemoved(const DataBreakdownPreRemoveArgs &args)
    {
        auto casted = static_cast<BreakdownT*>(args.ToBeRemoved());
        breakdownMap.erase(casted->generalComponent.position.Get()->Build());
        focusedRemovePackage = *casted->generalComponent.position.Get();
        if (Viewport::viewport->GetMode() == Viewport::Mode::ENTITIES)
            Viewport::viewport->DeselectItem(casted->GetTreeItemID());
    }

    void DataViewStateEntities::OnBreakdownPostRemoved(const DataBreakdownPostRemoveArgs &args)
    {
        EntityViewManager::Evaluate(focusedRemovePackage);
    }

    void DataViewStateEntities::OnPositionPreChanged(DataBreakdownPreEditArgs &args)
    {
        // Find out if there's an object at this position
        auto found = breakdownMap.find(static_cast<Build::Package<::Atmos::GridPosition>*>(args.Proposed())->Build());
        if (found == breakdownMap.end())
            return;

        args.Reject(true);
    }

    void DataViewStateEntities::OnPositionChanged(const DataBreakdownEditArgs &args)
    {
        auto prevCasted = static_cast<Build::Package<::Atmos::GridPosition>*>(args.Prev());
        auto currentCasted = static_cast<Build::Package<::Atmos::GridPosition>*>(args.Current());
        auto found = breakdownMap.find(prevCasted->Build());
        breakdownMap.emplace(currentCasted->Build(), std::move(found->second));
        breakdownMap.erase(found);
        EntityViewManager::Evaluate(*prevCasted);
        EntityViewManager::Evaluate(*currentCasted);
    }

    void DataViewStateEntities::OnMaterialEdited(const DataBreakdownEditArgs &args)
    {
        for (auto &loop : breakdownList)
            EntityViewManager::Evaluate(*loop.Get());
    }

    void DataViewStateEntities::SetupBreakdowns()
    {
        breakdownList.Setup(CurrentWorld::fieldPackage.entities);
        breakdownList.SetNiceNameFunctions(BreakdownListT::NiceNameExtractorFunction(static_cast<String(*)(BreakdownListT::BreakdownT&)>([](BreakdownListT::BreakdownT &breakdown) { return breakdown.generalComponent.name.Get()->Build(); })),
            BreakdownListT::NiceNameGetEventFunction(static_cast<Event<const DataBreakdownEditArgs&>*(*)(BreakdownListT::BreakdownT&)>([](BreakdownListT::BreakdownT &breakdown) -> Event<const DataBreakdownEditArgs&>* { return &breakdown.generalComponent.name.edited; })),
            BreakdownListT::NameSetFunction(static_cast<void(*)(BreakdownListT::BreakdownT&, const String&)>([](BreakdownListT::BreakdownT &breakdown, const String &str)
        {
            Build::Package<::Atmos::Name> package;
            package.value = str;
            breakdown.generalComponent.name.Edit(package);
        })));
        breakdownList.added.Subscribe(&DataViewStateEntities::OnBreakdownCreated, *this);
        breakdownList.preRemove.Subscribe(&DataViewStateEntities::OnBreakdownPreRemoved, *this);
        breakdownList.postRemove.Subscribe(&DataViewStateEntities::OnBreakdownPostRemoved, *this);
        breakdownList.SetAddChildrenToProperties(false);
    }

    void DataViewStateEntities::StartImpl()
    {}

    void DataViewStateEntities::StopImpl()
    {}

    void DataViewStateEntities::SelectImpl(wxTreeItemId id)
    {}

    void DataViewStateEntities::DeselectImpl(wxTreeItemId id)
    {}

    void DataViewStateEntities::DeselectAllImpl()
    {
        for (auto &loop : breakdownList)
            GetMainFrame()->GetDataView()->Deselect(loop.GetTreeItemID());
    }

    void DataViewStateEntities::AddImpl()
    {}

    void DataViewStateEntities::RemoveImpl()
    {}

    void DataViewStateEntities::CreateBreakdownsFromScratchImpl()
    {
        for (auto &loop : CurrentWorld::fieldPackage.entities.value)
            CreateBreakdown(loop, true);
    }

    void DataViewStateEntities::DestroyBreakdownsImpl()
    {
        breakdownMap.clear();
        breakdownList.DestroyBreakdowns();
    }

    void DataViewStateEntities::CreateTreePiecesImpl()
    {
        for (auto &loop : breakdownList)
            loop.CreateTreePiece(TreeRootID());
    }

    void DataViewStateEntities::CreateEditorPropertiesImpl()
    {
        for (auto &loop : breakdownList)
            loop.CreateEditorProperties(nullptr);

        GetMainFrame()->GetDataView()->PropertyGrid()->FitColumns();
    }

    void DataViewStateEntities::DestroyEditorPropertiesImpl(bool destroyTreeItems)
    {
        for (auto &loop : breakdownList)
            loop.DestroyEditorProperties(destroyTreeItems);
    }

    DataViewStateEntities::Type DataViewStateEntities::GetTypeImpl() const
    {
        return type;
    }

    DataViewStateEntities::DataViewStateEntities(DataView *dataView) : DataViewState(dataView),
        breakdownList("List", nullptr)
    {
        SetupBreakdowns();
        breakdownList.SetPrependEntryName("Entity");
        GetDataView()->GetSpecificState<DataViewStateAssets>()->onMaterialEdited.Subscribe(&DataViewStateEntities::OnMaterialEdited, *this);
    }

    DataViewStateEntities::BreakdownT* DataViewStateEntities::Find(const PositionPackageT &find)
    {
        auto found = breakdownMap.find(find.Build());
        if (found == breakdownMap.end())
            return nullptr;

        return &*std::get<0>(found->second);
    }

    DataViewStateEntities::BreakdownT* DataViewStateEntities::Find(const PackageT &find)
    {
        for (auto &loop : breakdownList)
        {
            if (*loop.Get() == find)
                return &loop;
        }

        return nullptr;
    }

    void DataViewStateEntities::Select(PackageT &select)
    {
        auto found = breakdownMap.find(select.generalComponent.position.Build());
        if (found == breakdownMap.end())
            return;

        wxTreeItemId id(std::get<0>(found->second)->GetTreeItemID());
        if (!Tree()->IsSelected(id))
            GetMainFrame()->GetDataView()->Select(id);
    }

    String DataViewStateEntities::GetTreeString()
    {
        return "Entities";
    }
}