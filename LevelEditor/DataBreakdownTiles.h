#pragma once

#include "DataBreakdownGeneral.h"
#include "DataBreakdownSenses.h"
#include "DataBreakdownOffset.h"

#include "BuildPackageTile.h"

namespace Creation
{
    template<>
    class DataBreakdown<Build::Package<::Atmos::Tile>> : public DataBreakdownBase<Build::Package<::Atmos::Tile>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
        typedef PackageT::SpritePackageT SpritePackageT;
    private:
        void AddAllChildren();
        void SubscribeEvents();

        void OnSpriteAdded(const DataBreakdownAddArgs &args);
        void OnSpriteRemoved(const DataBreakdownPostRemoveArgs &args);
        void OnSpriteEdited(const DataBreakdownEditArgs &args);

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::GridPosition>> position;
        DataBreakdown<Build::Package<bool>> solid;
        DataBreakdownList<SpritePackageT> sprites;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);

        static ::Atmos::String GetString(const Build::Package<::Atmos::GridPosition> &position);
    };
}