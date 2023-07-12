#pragma once

#include "DataBreakdownGeneral.h"
#include "DataBreakdownElement.h"

namespace Creation
{
    template<>
    class DataBreakdown<Build::Package<::Atmos::CombatTransactionGenerator>> : public DataBreakdownBase<Build::Package<::Atmos::CombatTransactionGenerator>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> resourceName;
        DataBreakdown<Build::Package<::Atmos::Name>> statName;
        DataBreakdown<Build::Package<::Atmos::Element>> element;
        DataBreakdown<Build::Package<::Atmos::Name>> proficiencyName;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };
}