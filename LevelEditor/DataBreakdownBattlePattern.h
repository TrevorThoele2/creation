#pragma once

#include "DataBreakdownGameData.h"
#include "DataBreakdownSenses.h"
#include "DataBreakdownCombatChain.h"

#include "BuildPackageBattlePattern.h"

#include "BattlePatternEditor.h"

namespace Creation
{
    template<>
    class DataBreakdown<Build::Package<::Atmos::BattlePatternHolder::Piece>> : public DataBreakdownBase<Build::Package<::Atmos::BattlePatternHolder::Piece>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Sprite>> selectionSprite;
        DataBreakdown<Build::Package<BuildT::Power>> power;
        DataBreakdown<Build::Package<::Atmos::CombatChain>> chain;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::BattlePatternHolder>::PatternPiece> : public DataBreakdownBase<Build::Package<::Atmos::BattlePatternHolder>::PatternPiece>
    {
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::RelativeGridPosition>> position;
        DataBreakdown<Build::Package<std::uint32_t>> registryPosition;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::BattlePatternHolder>> : public DataBreakdownBase<Build::Package<::Atmos::BattlePatternHolder>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        typedef DataBreakdownList<Build::Package<::Atmos::BattlePatternHolder::Piece>> RegistryBreakdownT;
        RegistryBreakdownT registry;
        DataBreakdownList<PackageT::PatternPiece> pattern;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };
}