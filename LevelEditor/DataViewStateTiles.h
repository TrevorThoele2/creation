#pragma once

#include <unordered_map>

#include "DataViewState.h"
#include "DataBreakdownTiles.h"
#include "String.h"

#include <Atmos/Tile.h>

namespace Creation
{
    class DataViewStateTiles : public DataViewState
    {
    public:
        static constexpr const Type type = Type::TILES;
        typedef Build::Package<::Atmos::Tile> PackageT;
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

        DataViewStateTiles(DataView *dataView);

        BreakdownT* Find(const PositionPackageT &find);
        BreakdownT* Find(const PackageT &find);

        void Select(const PositionPackageT &pos);
        void Select(const std::vector<PositionPackageT> &positions);
        void Deselect(const PositionPackageT &pos);
        void Deselect(const std::vector<PositionPackageT> &positions);

        static String GetTreeString();
    };
}