#pragma once

#include "DataBreakdownSenses.h"
#include "DataBreakdownParticleFountain.h"

#include "BuildPackageAVEffect.h"

namespace Creation
{
    template<>
    class DataBreakdown<Build::Package<::Atmos::AVEffect>::NodePackage> : public DataBreakdownBase<Build::Package<::Atmos::AVEffect>::NodePackage>
    {
    public:
        typedef typename PackageT::BuildT BuildT;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::AVEffect>> : public DataBreakdownBase<Build::Package<::Atmos::AVEffect>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdownList<PackageT::NodePackage> nodes;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };
}