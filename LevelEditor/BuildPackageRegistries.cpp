
#include "BuildPackageRegistries.h"

namespace Creation
{
    namespace Build
    {
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Ability>)
        {
            scribe(name);
            scribe(niceName);
            scribe(description);
            scribe(id);

            scribe(pattern);
            scribe(range);
            scribe(cost);
        }

        Package<::Atmos::Ability>::Package(Package &&arg) : name(std::move(arg.name)), niceName(std::move(arg.niceName)), description(std::move(arg.description)),
            id(std::move(arg.id)), pattern(std::move(arg.pattern)), range(std::move(arg.range)), cost(std::move(arg.cost))
        {}

        Package<::Atmos::Ability>& Package<::Atmos::Ability>::operator=(Package &&arg)
        {
            name = std::move(arg.name);
            niceName = std::move(arg.niceName);
            description = std::move(arg.description);
            id = std::move(arg.id);
            pattern = std::move(arg.pattern);
            range = std::move(arg.range);
            cost = std::move(arg.cost);
            return *this;
        }

        bool Package<::Atmos::Ability>::operator==(const Package &arg) const
        {
            return name == arg.name && niceName == arg.niceName && description == arg.description && id == arg.id && pattern == arg.pattern && range == arg.range && cost == arg.cost;
        }

        bool Package<::Atmos::Ability>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        ::Atmos::RegistryObjectReference<Package<::Atmos::Ability>::BuildT> Package<::Atmos::Ability>::Build() const
        {
            ::Atmos::RegistryObjectReference<BuildT> made;
            if (id.Build() == BuildT::nullID)
                made = ::Atmos::Registry<BuildT>::Register(name.Build());
            else
                made = ::Atmos::Registry<BuildT>::Register(id.Build(), name.Build());
            auto use = const_cast<BuildT*>(made.Get());
            use->niceName = niceName.Build();
            use->description = description.Build();
            use->pattern = pattern.Build();
            use->range = range.Build();
            use->cost = cost.Build();
            return made;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::CharacterClass>::AttributePackage)
        {
            scribe(name);
            scribe(base);
            scribe(growth);
        }

        Package<::Atmos::CharacterClass>::AttributePackage::AttributePackage(AttributePackage &&arg) : name(std::move(arg.name)), base(std::move(arg.base)), growth(std::move(arg.growth))
        {}

        Package<::Atmos::CharacterClass>::AttributePackage& Package<::Atmos::CharacterClass>::AttributePackage::operator=(AttributePackage &&arg)
        {
            name = std::move(arg.name);
            base = std::move(arg.base);
            growth = std::move(arg.growth);
            return *this;
        }

        bool Package<::Atmos::CharacterClass>::AttributePackage::operator==(const AttributePackage &arg) const
        {
            return name == arg.name && base == arg.base && growth == arg.growth;
        }

        bool Package<::Atmos::CharacterClass>::AttributePackage::operator!=(const AttributePackage &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::CharacterClass>::AttributePackage::BuildT Package<::Atmos::CharacterClass>::AttributePackage::Build() const
        {
            BuildT ret;
            ret.base = base.Build();
            ret.growth = base.Build();
            return ret;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::CharacterClass>::ProficiencyPackage)
        {
            scribe(name);
            scribe(rating);
        }

        Package<::Atmos::CharacterClass>::ProficiencyPackage::ProficiencyPackage(ProficiencyPackage &&arg) : name(std::move(arg.name)), rating(std::move(arg.rating))
        {}

        Package<::Atmos::CharacterClass>::ProficiencyPackage& Package<::Atmos::CharacterClass>::ProficiencyPackage::operator=(ProficiencyPackage &&arg)
        {
            name = std::move(arg.name);
            rating = std::move(arg.rating);
            return *this;
        }

        bool Package<::Atmos::CharacterClass>::ProficiencyPackage::operator==(const ProficiencyPackage &arg) const
        {
            return name == arg.name && rating == arg.rating;
        }

        bool Package<::Atmos::CharacterClass>::ProficiencyPackage::operator!=(const ProficiencyPackage &arg) const
        {
            return !(*this == arg);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::CharacterClass>)
        {
            scribe(name);
            scribe(niceName);
            scribe(description);
            scribe(id);

            scribe(resources);
            scribe(stats);
            scribe(proficiencies);
            scribe(permanentStashSize);
            scribe(temporaryStashSize);
        }

        Package<::Atmos::CharacterClass>::Package()
        {
            permanentStashSize.value = 1;
            temporaryStashSize.value = 1;
        }

        Package<::Atmos::CharacterClass>::Package(Package &&arg) : name(std::move(arg.name)), niceName(std::move(arg.niceName)), description(std::move(arg.description)),
            id(std::move(arg.id)), resources(std::move(arg.resources)), stats(std::move(arg.stats)), proficiencies(std::move(arg.proficiencies)),
            permanentStashSize(std::move(arg.permanentStashSize)), temporaryStashSize(std::move(arg.temporaryStashSize))
        {}

        Package<::Atmos::CharacterClass>& Package<::Atmos::CharacterClass>::operator=(Package &&arg)
        {
            name = std::move(arg.name);
            niceName = std::move(arg.niceName);
            description = std::move(arg.description);
            id = std::move(arg.id);
            resources = std::move(arg.resources);
            stats = std::move(arg.stats);
            proficiencies = std::move(arg.proficiencies);
            permanentStashSize = std::move(arg.permanentStashSize);
            temporaryStashSize = std::move(arg.temporaryStashSize);
            return *this;
        }

        bool Package<::Atmos::CharacterClass>::operator==(const Package &arg) const
        {
            return name == arg.name && niceName == arg.niceName && description == arg.description && id == arg.id && resources == arg.resources && stats == arg.stats && proficiencies == arg.proficiencies
                && permanentStashSize == arg.permanentStashSize && temporaryStashSize == arg.temporaryStashSize;
        }

        ::Atmos::RegistryObjectReference<Package<::Atmos::CharacterClass>::BuildT> Package<::Atmos::CharacterClass>::Build() const
        {
            ::Atmos::RegistryObjectReference<BuildT> made;
            if (id.Build() == BuildT::nullID)
                made = ::Atmos::Registry<BuildT>::Register(name.Build());
            else
                made = ::Atmos::Registry<BuildT>::Register(id.Build(), name.Build());
            auto use = const_cast<BuildT*>(made.Get());
            use->niceName = niceName.Build();
            use->description = description.Build();
            //use->resources = resources.Build();
            //use->stats = stats.Build();
            //use->proficiencies = proficiencies.Build();
            use->permanentMaxItemCount = permanentStashSize.Build();
            use->temporaryMaxItemCount = temporaryStashSize.Build();
            return made;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::ConsumableAspect>)
        {
            scribe(script);
        }

        Package<::Atmos::ConsumableAspect>::Package(Package &&arg) : script(std::move(arg.script))
        {}

        Package<::Atmos::ConsumableAspect>& Package<::Atmos::ConsumableAspect>::operator=(Package &&arg)
        {
            script = std::move(arg.script);
            return *this;
        }

        bool Package<::Atmos::ConsumableAspect>::operator==(const Package &arg) const
        {
            return script == arg.script;
        }

        bool Package<::Atmos::ConsumableAspect>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::ConsumableAspect>::BuildT Package<::Atmos::ConsumableAspect>::Build() const
        {
            BuildT ret;
            ret.script = script.Build();
            return ret;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::EquippableAspect>::AmmoAdditionalPackage)
        {
            scribe(ammoType);
        }

        Package<::Atmos::EquippableAspect>::AmmoAdditionalPackage::AmmoAdditionalPackage(AmmoAdditionalPackage &&arg) : ammoType(std::move(arg.ammoType))
        {}

        Package<::Atmos::EquippableAspect>::AmmoAdditionalPackage& Package<::Atmos::EquippableAspect>::AmmoAdditionalPackage::operator=(AmmoAdditionalPackage &&arg)
        {
            ammoType = std::move(arg.ammoType);
            return *this;
        }

        bool Package<::Atmos::EquippableAspect>::AmmoAdditionalPackage::operator==(const AmmoAdditionalPackage &arg) const
        {
            return ammoType == arg.ammoType;
        }

        bool Package<::Atmos::EquippableAspect>::AmmoAdditionalPackage::operator!=(const AmmoAdditionalPackage &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::EquippableAspect>::AmmoAdditionalPackage::BuildT Package<::Atmos::EquippableAspect>::AmmoAdditionalPackage::Build() const
        {
            BuildT ret;
            ret.ammoType = ammoType.Build();
            return ret;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::UsesAmmoPackage)
        {

        }

        Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::UsesAmmoPackage::UsesAmmoPackage(UsesAmmoPackage &&arg)
        {}

        Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::UsesAmmoPackage& Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::UsesAmmoPackage::operator=(UsesAmmoPackage &&arg)
        {
            return *this;
        }

        bool Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::UsesAmmoPackage::operator==(const UsesAmmoPackage &arg) const
        {
            return true;
        }

        bool Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::UsesAmmoPackage::operator!=(const UsesAmmoPackage &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::UsesAmmoPackage::BuildT Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::UsesAmmoPackage::Build() const
        {
            return BuildT();
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::EquippableAspect>::AttackAdditionalPackage)
        {
            scribe(power);
            scribe(pattern);
            scribe(range);
            scribe(allowedClasses);
            scribe(proficiencyName);
            scribe(usesAmmo);
        }

        Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::AttackAdditionalPackage(AttackAdditionalPackage &&arg) : power(std::move(arg.power)),
            pattern(std::move(arg.pattern)), range(std::move(arg.range)), allowedClasses(std::move(arg.allowedClasses)), proficiencyName(std::move(arg.proficiencyName)),
            usesAmmo(std::move(arg.usesAmmo))
        {}

        Package<::Atmos::EquippableAspect>::AttackAdditionalPackage& Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::operator=(AttackAdditionalPackage &&arg)
        {
            power = std::move(arg.power);
            pattern = std::move(arg.pattern);
            range = std::move(arg.range);
            allowedClasses = std::move(arg.allowedClasses);
            proficiencyName = std::move(arg.proficiencyName);
            usesAmmo = std::move(arg.usesAmmo);
            return *this;
        }

        bool Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::operator==(const AttackAdditionalPackage &arg) const
        {
            return power == arg.power && pattern == arg.pattern && range == arg.range && allowedClasses == arg.allowedClasses && proficiencyName == arg.proficiencyName
                && usesAmmo == arg.usesAmmo;
        }

        bool Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::operator!=(const AttackAdditionalPackage &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::BuildT Package<::Atmos::EquippableAspect>::AttackAdditionalPackage::Build() const
        {
            BuildT ret;
            ret.power = power.Build();
            ret.pattern = pattern.Build();
            ret.range = range.Build();
            ret.allowedClasses = allowedClasses.Build();
            ret.proficiencyName = proficiencyName.Build();
            ret.usesAmmo = usesAmmo.Build();
            return ret;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::EquippableAspect>)
        {
            scribe(equipRegion);
            scribe(defense);
            scribe(ammoAdditional);
            scribe(attackAdditional);
        }

        Package<::Atmos::EquippableAspect>::Package(Package &&arg) : equipRegion(std::move(arg.equipRegion)), defense(std::move(arg.defense)),
            ammoAdditional(std::move(arg.ammoAdditional)), attackAdditional(std::move(arg.attackAdditional))
        {}

        Package<::Atmos::EquippableAspect>& Package<::Atmos::EquippableAspect>::operator=(Package &&arg)
        {
            equipRegion = std::move(arg.equipRegion);
            defense = std::move(arg.defense);
            ammoAdditional = std::move(arg.ammoAdditional);
            attackAdditional = std::move(arg.attackAdditional);
            return *this;
        }

        bool Package<::Atmos::EquippableAspect>::operator==(const Package &arg) const
        {
            return equipRegion == arg.equipRegion && defense == arg.defense && ammoAdditional == arg.ammoAdditional && attackAdditional == arg.attackAdditional;
        }

        bool Package<::Atmos::EquippableAspect>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::EquippableAspect>::BuildT Package<::Atmos::EquippableAspect>::Build() const
        {
            BuildT ret;
            ret.equipRegion = equipRegion.Build();
            ret.defense = defense.Build();
            auto &useAmmoAdditional = ammoAdditional.Build();
            auto &useAttackAdditional = attackAdditional.Build();
            if (useAmmoAdditional)
            {
                ret.SignalAmmo();
                *ret.AsAmmo() = useAmmoAdditional->Build();
                goto additionalsDone;
            }

            if (useAttackAdditional)
            {
                ret.SignalAttack();
                *ret.AsAttack() = useAttackAdditional->Build();
                goto additionalsDone;
            }

        additionalsDone:

            return ret;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Item>)
        {
            scribe(name);
            scribe(niceName);
            scribe(description);
            scribe(id);

            scribe(flags);
            scribe(consumableAspect);
            scribe(equippableAspect);
            scribe(buyingPrice);
            scribe(sellingPrice);
            scribe(portrait);
        }

        Package<::Atmos::Item>::Package(Package &&arg) : name(std::move(arg.name)), niceName(std::move(arg.niceName)), description(std::move(arg.description)),
            id(std::move(arg.id)), flags(std::move(arg.flags)), consumableAspect(std::move(arg.consumableAspect)), equippableAspect(std::move(arg.equippableAspect)),
            buyingPrice(std::move(arg.buyingPrice)), sellingPrice(std::move(arg.sellingPrice)), portrait(std::move(arg.portrait))
        {}

        Package<::Atmos::Item>& Package<::Atmos::Item>::operator=(Package &&arg)
        {
            name = std::move(arg.name);
            niceName = std::move(arg.niceName);
            description = std::move(arg.description);
            id = std::move(arg.id);
            flags = std::move(arg.flags);
            consumableAspect = std::move(arg.consumableAspect);
            equippableAspect = std::move(arg.equippableAspect);
            buyingPrice = std::move(arg.buyingPrice);
            sellingPrice = std::move(arg.sellingPrice);
            portrait = std::move(arg.portrait);
            return *this;
        }

        bool Package<::Atmos::Item>::operator==(const Package &arg) const
        {
            return name == arg.name && niceName == arg.niceName && description == arg.description && id == arg.id && flags == arg.flags && consumableAspect == arg.consumableAspect &&
                equippableAspect == arg.equippableAspect && buyingPrice == arg.buyingPrice && sellingPrice == arg.sellingPrice && portrait == arg.portrait;
        }

        bool Package<::Atmos::Item>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        ::Atmos::RegistryObjectReference<Package<::Atmos::Item>::BuildT> Package<::Atmos::Item>::Build() const
        {
            ::Atmos::RegistryObjectReference<BuildT> made;
            if (id.Build() == BuildT::nullID)
                made = ::Atmos::Registry<BuildT>::Register(name.Build());
            else
                made = ::Atmos::Registry<BuildT>::Register(id.Build(), name.Build());
            auto use = const_cast<BuildT*>(made.Get());
            use->niceName = niceName.Build();
            use->description = description.Build();
            use->flags = flags.Build();
            //use->consumableAspect = consumableAspect.Build();
            //use->equippableAspect = equippableAspect.Build();
            use->buyingPrice = buyingPrice.Build();
            use->sellingPrice = sellingPrice.Build();
            use->portrait = portrait.Build();
            return made;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Quest::Part>)
        {
            scribe(name);
            scribe(description);
            scribe(type);
        }

        Package<::Atmos::Quest::Part>::Package(Package &&arg) : name(std::move(arg.name)), description(std::move(arg.description)), type(std::move(arg.type))
        {}

        Package<::Atmos::Quest::Part>& Package<::Atmos::Quest::Part>::operator=(Package &&arg)
        {
            name = std::move(arg.name);
            description = std::move(arg.description);
            type = std::move(arg.type);
            return *this;
        }

        bool Package<::Atmos::Quest::Part>::operator==(const Package &arg) const
        {
            return name == arg.name && description == arg.description && type == arg.type;
        }

        bool Package<::Atmos::Quest::Part>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Quest::Part>::BuildT Package<::Atmos::Quest::Part>::Build() const
        {
            return BuildT(name.Build(), description.Build(), static_cast<BuildT::Type>(type.Build()));
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Quest>)
        {
            scribe(name);
            scribe(niceName);
            scribe(description);
            scribe(id);

            scribe(parts);
            scribe(script);
        }

        Package<::Atmos::Quest>::Package(Package &&arg) : name(std::move(arg.name)), niceName(std::move(arg.niceName)), description(std::move(arg.description)),
            id(std::move(arg.id)), parts(std::move(arg.parts)), script(std::move(arg.script))
        {}

        Package<::Atmos::Quest>& Package<::Atmos::Quest>::operator=(Package &&arg)
        {
            name = std::move(arg.name);
            niceName = std::move(arg.niceName);
            description = std::move(arg.description);
            id = std::move(arg.id);
            parts = std::move(arg.parts);
            script = std::move(arg.script);
            return *this;
        }

        bool Package<::Atmos::Quest>::operator==(const Package &arg) const
        {
            return name == arg.name && niceName == arg.niceName && description == arg.description && id == arg.id && parts == arg.parts && script == arg.script;
        }

        bool Package<::Atmos::Quest>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        ::Atmos::RegistryObjectReference<Package<::Atmos::Quest>::BuildT> Package<::Atmos::Quest>::Build() const
        {
            ::Atmos::RegistryObjectReference<BuildT> made;
            if (id.Build() == BuildT::nullID)
                made = ::Atmos::Registry<BuildT>::Register(name.Build());
            else
                made = ::Atmos::Registry<BuildT>::Register(id.Build(), name.Build());
            auto use = const_cast<BuildT*>(made.Get());
            use->niceName = niceName.Build();
            use->description = description.Build();
            for (auto &loop : parts.value)
                *use->AddPart() = loop.Build();
            use->script = script.Build();
            return made;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Spell>)
        {
            scribe(name);
            scribe(niceName);
            scribe(description);
            scribe(id);

            scribe(attackPattern);
            scribe(pieceOverworld);
            scribe(range);
            scribe(resourceCost);
            scribe(allowedClasses);
        }

        Package<::Atmos::Spell>::Package(Package &&arg) : name(std::move(arg.name)), niceName(std::move(arg.niceName)), description(std::move(arg.description)),
            id(std::move(arg.id)), attackPattern(std::move(arg.attackPattern)), pieceOverworld(std::move(arg.pieceOverworld)), range(std::move(arg.range)),
            resourceCost(std::move(arg.resourceCost)), allowedClasses(std::move(arg.allowedClasses))
        {}

        Package<::Atmos::Spell>& Package<::Atmos::Spell>::operator=(Package &&arg)
        {
            name = std::move(arg.name);
            niceName = std::move(arg.niceName);
            description = std::move(arg.description);
            id = std::move(arg.id);
            attackPattern = std::move(arg.attackPattern);
            pieceOverworld = std::move(arg.pieceOverworld);
            range = std::move(arg.range);
            resourceCost = std::move(arg.resourceCost);
            allowedClasses = std::move(arg.allowedClasses);
            return *this;
        }

        bool Package<::Atmos::Spell>::operator==(const Package &arg) const
        {
            return name == arg.name && niceName == arg.niceName && description == arg.description && id == arg.id && attackPattern == arg.attackPattern && pieceOverworld == arg.pieceOverworld &&
                range == arg.range && resourceCost == arg.resourceCost && allowedClasses == arg.allowedClasses;
        }

        bool Package<::Atmos::Spell>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        ::Atmos::RegistryObjectReference<Package<::Atmos::Spell>::BuildT> Package<::Atmos::Spell>::Build() const
        {
            ::Atmos::RegistryObjectReference<BuildT> made;
            if (id.Build() == BuildT::nullID)
                made = ::Atmos::Registry<BuildT>::Register(name.Build());
            else
                made = ::Atmos::Registry<BuildT>::Register(id.Build(), name.Build());
            auto use = const_cast<BuildT*>(made.Get());
            use->niceName = niceName.Build();
            use->description = description.Build();
            use->attackPattern = attackPattern.Build();
            //use->pieceOverworld = pieceOverworld.Build();
            use->range = range.Build();
            use->resourceCost = resourceCost.Build();
            use->allowedClasses = allowedClasses.Build();
            return made;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::StatusEffect>)
        {
            scribe(name);
            scribe(niceName);
            scribe(description);
            scribe(id);

            scribe(script);
            scribe(applicationCount);
            scribe(proficiencyName);
            scribe(accuracy);
            scribe(positive);
        }

        Package<::Atmos::StatusEffect>::Package(Package &&arg) : name(std::move(arg.name)), niceName(std::move(arg.niceName)), description(std::move(arg.description)),
            id(std::move(arg.id)), script(std::move(arg.script)), applicationCount(std::move(arg.applicationCount)), proficiencyName(std::move(arg.proficiencyName)),
            accuracy(std::move(arg.accuracy)), positive(std::move(arg.positive))
        {}

        Package<::Atmos::StatusEffect>& Package<::Atmos::StatusEffect>::operator=(Package &&arg)
        {
            name = std::move(arg.name);
            niceName = std::move(arg.niceName);
            description = std::move(arg.description);
            id = std::move(arg.id);
            script = std::move(arg.script);
            applicationCount = std::move(arg.applicationCount);
            proficiencyName = std::move(arg.proficiencyName);
            accuracy = std::move(arg.accuracy);
            positive = std::move(arg.positive);
            return *this;
        }

        bool Package<::Atmos::StatusEffect>::operator==(const Package &arg) const
        {
            return name == arg.name && niceName == arg.niceName && description == arg.description && id == arg.id && script == arg.script && applicationCount == arg.applicationCount &&
                proficiencyName == arg.proficiencyName && accuracy == arg.accuracy && positive == arg.positive;
        }

        bool Package<::Atmos::StatusEffect>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        ::Atmos::RegistryObjectReference<Package<::Atmos::StatusEffect>::BuildT> Package<::Atmos::StatusEffect>::Build() const
        {
            ::Atmos::RegistryObjectReference<BuildT> made;
            if (id.Build() == BuildT::nullID)
                made = ::Atmos::Registry<BuildT>::Register(name.Build());
            else
                made = ::Atmos::Registry<BuildT>::Register(id.Build(), name.Build());
            auto use = const_cast<BuildT*>(made.Get());
            use->niceName = niceName.Build();
            use->description = description.Build();
            use->script = script.Build();
            use->applicationCount = applicationCount.Build();
            use->proficiencyName = proficiencyName.Build();
            use->accuracy = accuracy.Build();
            use->positive = positive.Build();
            return made;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::ItemStack>)
        {
            scribe(wrapped);
            scribe(count);
        }

        Package<::Atmos::ItemStack>::Package(Package &&arg) : wrapped(std::move(arg.wrapped)), count(std::move(arg.count))
        {}

        Package<::Atmos::ItemStack>& Package<::Atmos::ItemStack>::operator=(Package &&arg)
        {
            wrapped = std::move(arg.wrapped);
            count = std::move(arg.count);
            return *this;
        }

        bool Package<::Atmos::ItemStack>::operator==(const Package &arg) const
        {
            return wrapped == arg.wrapped && count == arg.count;
        }

        bool Package<::Atmos::ItemStack>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::ItemStack>::BuildT Package<::Atmos::ItemStack>::Build() const
        {
            return BuildT(wrapped.Build(), count.Build());
        }
    }
}