#pragma once

#include "DataViewState.h"
#include "DataBreakdownGameData.h"

namespace Creation
{
    class DataViewStateGameData : public DataViewState
    {
    public:
        static constexpr const Type type = Type::GAME_DATA;
    private:
        typedef DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::ResourceAttributeTable>>> ResourceBreakdown;
        typedef DataBreakdown<Build::Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>> StatBreakdown;
        typedef DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::Element>>> ElementBreakdown;

        ResourceBreakdown resources;
        StatBreakdown stats;
        ElementBreakdown elements;

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
        DataViewStateGameData(DataView *dataView);

        void SetResourcesGlobalContext(const ResourceBreakdown::PackageT &set);
        void SetResourcesGlobalContext(ResourceBreakdown::PackageT &&set);
        void SetStatsDataStandard(const StatBreakdown::PackageT &set);
        void SetStatsDataStandard(StatBreakdown::PackageT &&set);
        void SetElementsGlobalContext(const ElementBreakdown::PackageT &set);
        void SetElementsGlobalContext(ElementBreakdown::PackageT &&set);

        static String GetTreeString();
    };
}