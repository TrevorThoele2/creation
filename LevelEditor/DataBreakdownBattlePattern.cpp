
#include "DataBreakdownBattlePattern.h"

namespace Creation
{
    void DataBreakdown<Build::Package<::Atmos::BattlePatternHolder::Piece>>::AddAllChildren()
    {
        AddChild(power);
        AddChild(selectionSprite);
        AddChild(chain);
    }

    void DataBreakdown<Build::Package<::Atmos::BattlePatternHolder::Piece>>::SetupImpl()
    {
        selectionSprite.Setup(Get()->selectionSprite);
        power.Setup(Get()->power);
        chain.Setup(Get()->chain);
    }

    DataBreakdown<Build::Package<::Atmos::BattlePatternHolder::Piece>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        selectionSprite("Selection Sprite", this),
        power("Power", this),
        chain("Chain", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::BattlePatternHolder::Piece>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        selectionSprite(std::move(arg.selectionSprite), this),
        power(std::move(arg.power), this),
        chain(std::move(arg.chain), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::BattlePatternHolder::Piece>>& DataBreakdown<Build::Package<::Atmos::BattlePatternHolder::Piece>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        selectionSprite = std::move(arg.selectionSprite);
        power = std::move(arg.power);
        chain = std::move(arg.chain);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::BattlePatternHolder>::PatternPiece>::AddAllChildren()
    {
        AddChild(registryPosition);
        AddChild(position);
    }

    void DataBreakdown<Build::Package<::Atmos::BattlePatternHolder>::PatternPiece>::SetupImpl()
    {
        position.Setup(Get()->position);
        registryPosition.Setup(Get()->registryPosition);
    }

    DataBreakdown<Build::Package<::Atmos::BattlePatternHolder>::PatternPiece>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        position("Position", this),
        registryPosition("Registry ID", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::BattlePatternHolder>::PatternPiece>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        position(std::move(arg.position), this),
        registryPosition(std::move(arg.registryPosition), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::BattlePatternHolder>::PatternPiece>& DataBreakdown<Build::Package<::Atmos::BattlePatternHolder>::PatternPiece>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        position = std::move(arg.position);
        registryPosition = std::move(arg.registryPosition);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::BattlePatternHolder>>::AddAllChildren()
    {
        AddChild(registry);
        AddChild(pattern);
    }

    void DataBreakdown<Build::Package<::Atmos::BattlePatternHolder>>::SetupImpl()
    {
        registry.Setup(Get()->registry);
        pattern.Setup(Get()->pattern);
    }

    DataBreakdown<Build::Package<::Atmos::BattlePatternHolder>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        registry("Registry", this),
        pattern("Pattern", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::BattlePatternHolder>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        registry(std::move(arg.registry), this),
        pattern(std::move(arg.pattern), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::BattlePatternHolder>>& DataBreakdown<Build::Package<::Atmos::BattlePatternHolder>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        registry = std::move(arg.registry);
        pattern = std::move(arg.pattern);
        return *this;
    }
}