
#include "DataBreakdownRegistryReference.h"

#include "CurrentWorld.h"

namespace Creation
{
    const Build::Package<::Atmos::RandomAccessSequence<RegistryObjectReferenceTraits<::Atmos::Ability>::PackageT>>& RegistryObjectReferenceTraits<::Atmos::Ability>::Sequence()
    {
        return CurrentWorld::globals.abilityPackage;
    }

    const Build::Package<::Atmos::RandomAccessSequence<RegistryObjectReferenceTraits<::Atmos::CharacterClass>::PackageT>>& RegistryObjectReferenceTraits<::Atmos::CharacterClass>::Sequence()
    {
        return CurrentWorld::globals.characterClassPackage;
    }

    const Build::Package<::Atmos::RandomAccessSequence<RegistryObjectReferenceTraits<::Atmos::Item>::PackageT>>& RegistryObjectReferenceTraits<::Atmos::Item>::Sequence()
    {
        return CurrentWorld::globals.itemPackage;
    }

    const Build::Package<::Atmos::RandomAccessSequence<RegistryObjectReferenceTraits<::Atmos::Quest>::PackageT>>& RegistryObjectReferenceTraits<::Atmos::Quest>::Sequence()
    {
        return CurrentWorld::globals.questPackage;
    }

    const Build::Package<::Atmos::RandomAccessSequence<RegistryObjectReferenceTraits<::Atmos::Spell>::PackageT>>& RegistryObjectReferenceTraits<::Atmos::Spell>::Sequence()
    {
        return CurrentWorld::globals.spellPackage;
    }

    const Build::Package<::Atmos::RandomAccessSequence<RegistryObjectReferenceTraits<::Atmos::StatusEffect>::PackageT>>& RegistryObjectReferenceTraits<::Atmos::StatusEffect>::Sequence()
    {
        return CurrentWorld::globals.statusEffectPackage;
    }
}