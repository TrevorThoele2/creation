#pragma once

#include "DataBreakdownGeneral.h"
#include "DataBreakdownVariant.h"

#include "BuildPackageNameValuePair.h"

namespace Creation
{
    template<>
    class DataBreakdown<Build::Package<::Atmos::NameValuePair>> : public DataBreakdownBase<Build::Package<::Atmos::NameValuePair>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Variant>> variant;
        DataBreakdown<Build::Package<::Atmos::Name>> name;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };
}