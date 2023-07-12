#pragma once

#include "DataBreakdownCombatTransaction.h"
#include "DataBreakdownRegistryReference.h"

#include "BuildPackageCombatChain.h"
#include "BuildPackageRegistries.h"

namespace Creation
{
    template<>
    class DataBreakdown<Build::Package<::Atmos::CombatChain::Node>> : public DataBreakdownBase<Build::Package<::Atmos::CombatChain::Node>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::CombatTransactionGenerator>> transaction;
        DataBreakdown<Build::Package<::Atmos::RegistryObjectReference<::Atmos::StatusEffect>>> statusEffect;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::CombatChain>> : public DataBreakdownBase<Build::Package<::Atmos::CombatChain>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdownList<Build::Package<::Atmos::CombatChain::Node>> nodes;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };
}