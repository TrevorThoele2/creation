#pragma once

#include <vector>

#include "DataViewState.h"
#include "DataBreakdownEntities.h"

#include <Atmos/Entity.h>

namespace Creation
{
    class DataViewStateEntities : public DataViewState
    {
    public:
        static constexpr const Type type = Type::ENTITIES;
        typedef Build::Package<::Atmos::Entity> PackageT;
        typedef DataBreakdown<PackageT> BreakdownT;
        typedef Build::Package<::Atmos::GridPosition> PositionPackageT;

        typedef DataBreakdownList<PackageT> BreakdownListT;
    private:
        typedef std::tuple<BreakdownT*, ::Atmos::EventScopedConnectionManager> EntryT;
        typedef std::unordered_map<::Atmos::GridPosition, EntryT> BreakdownMap;
        BreakdownMap breakdownMap;

        BreakdownT& CreateBreakdown(PackageT &add, bool onlyBreakdown);
        void RemoveBreakdown(BreakdownListT::iterator remove);
        void OnBreakdownCreated(const DataBreakdownAddArgs &args);
        void OnBreakdownPreRemoved(const DataBreakdownPreRemoveArgs &args);
        void OnBreakdownPostRemoved(const DataBreakdownPostRemoveArgs &args);
        void OnPositionPreChanged(DataBreakdownPreEditArgs &args);
        void OnPositionChanged(const DataBreakdownEditArgs &args);
        void OnMaterialEdited(const DataBreakdownEditArgs &args);

        void SetupBreakdowns();

        void StartImpl() override final;
        void StopImpl() override final;

        void SelectImpl(wxTreeItemId id) override final;
        void DeselectImpl(wxTreeItemId id) override final;
        void DeselectAllImpl() override final;
        void AddImpl() override final;
        void RemoveImpl() override final;

        void CreateBreakdownsFromScratchImpl() override final;
        void DestroyBreakdownsImpl() override final;
        void CreateTreePiecesImpl() override final;
        void CreateEditorPropertiesImpl() override final;
        void DestroyEditorPropertiesImpl(bool destroyTreeItems) override final;

        Type GetTypeImpl() const override final;
    public:
        BreakdownListT breakdownList;

        DataViewStateEntities(DataView *dataView);

        BreakdownT* Find(const PositionPackageT &find);
        BreakdownT* Find(const PackageT &find);

        void Select(PackageT &select);

        static String GetTreeString();
    };
}