#pragma once

#include "BuildPackage.h"
#include "BuildPackageAsset.h"
#include "BuildPackageRegistries.h" 
#include "BuildPackageGameData.h"
#include "BuildPackageWorldStart.h"
#include <Atmos/Serialization.h>

namespace Creation
{
    class WorldGlobals
    {
    private:
        INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
        INSCRIPTION_ACCESS;
    public:
        typedef Build::Package<::Atmos::AudioAsset> AudioPackage;
        typedef Build::Package<::Atmos::ImageAsset> ImagePackage;
        typedef Build::Package<::Atmos::Material> MaterialPackage;
        typedef Build::Package<::Atmos::ScriptModuleBase> ScriptPackage;
        typedef Build::Package<::Atmos::ShaderAsset> ShaderPackage;

        typedef Build::Package<::Atmos::Ability> AbilityPackage;
        typedef Build::Package<::Atmos::CharacterClass> CharacterClassPackage;
        typedef Build::Package<::Atmos::Item> ItemPackage;
        typedef Build::Package<::Atmos::Quest> QuestPackage;
        typedef Build::Package<::Atmos::Spell> SpellPackage;
        typedef Build::Package<::Atmos::StatusEffect> StatusEffectPackage;

        typedef Build::Package<::Atmos::GlobalContext<::Atmos::ResourceAttributeTable>> GlobalContextResourcePackage;
        typedef Build::Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>> DataStandardStatPackage;
        typedef Build::Package<::Atmos::GlobalContext<::Atmos::Element>> GlobalContextElementPackage;

        typedef Build::Package<::Atmos::WorldStart> WorldStartPackage;

        Build::Package<::Atmos::RandomAccessSequence<AudioPackage>> audioPackage;
        Build::Package<::Atmos::RandomAccessSequence<ImagePackage>> imagePackage;
        Build::Package<::Atmos::RandomAccessSequence<MaterialPackage>> materialPackage;
        Build::Package<::Atmos::RandomAccessSequence<ScriptPackage>> scriptPackage;
        Build::Package<::Atmos::RandomAccessSequence<ShaderPackage>> shaderPackage;

        Build::Package<::Atmos::RandomAccessSequence<AbilityPackage>> abilityPackage;
        Build::Package<::Atmos::RandomAccessSequence<CharacterClassPackage>> characterClassPackage;
        Build::Package<::Atmos::RandomAccessSequence<ItemPackage>> itemPackage;
        Build::Package<::Atmos::RandomAccessSequence<QuestPackage>> questPackage;
        Build::Package<::Atmos::RandomAccessSequence<SpellPackage>> spellPackage;
        Build::Package<::Atmos::RandomAccessSequence<StatusEffectPackage>> statusEffectPackage;

        GlobalContextResourcePackage globalContextResourcePackage;
        DataStandardStatPackage dataStandardStatPackage;
        GlobalContextElementPackage globalContextElementPackage;

        WorldStartPackage worldStart;

        WorldGlobals() = default;

        // Will update all breakdowns inside of the data views
        // If move is true, then it'll move the packages instead of copying
        void SetAsGlobals(bool move = false);
    };
}