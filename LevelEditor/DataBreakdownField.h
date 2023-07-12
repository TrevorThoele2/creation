#pragma once

#include "DataBreakdownTiles.h"
#include "DataBreakdownEntities.h"

#include "BuildPackageField.h"

namespace Creation
{
    template<>
    class DataBreakdown<Build::Package<::Atmos::Field>> : public DataBreakdownBase<Build::Package<::Atmos::Field>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<BuildT::ID>> id;

        DataBreakdownList<Build::Package<::Atmos::Tile>> tiles;
        DataBreakdownList<Build::Package<::Atmos::Entity>> entities;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };
}