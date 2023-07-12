
#include "WorldGlobals.h"

#include "MainFrame.h"
#include "DataViewStateAssets.h"
#include "DataViewStateGameData.h"
#include "DataViewStateRegistries.h"

namespace Creation
{
    INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(WorldGlobals)
    {
        scribe(audioPackage);
        scribe(imagePackage);
        scribe(materialPackage);
        scribe(scriptPackage);
        scribe(shaderPackage);

        scribe(abilityPackage);
        scribe(characterClassPackage);
        scribe(itemPackage);
        scribe(questPackage);
        scribe(spellPackage);
        scribe(statusEffectPackage);

        scribe(globalContextResourcePackage);
        scribe(dataStandardStatPackage);
        scribe(globalContextElementPackage);

        scribe(worldStart);
    }

    void WorldGlobals::SetAsGlobals(bool move)
    {
        if (move)
        {
            // Assets
            {
                auto dataViewAssets = GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateAssets>();
                dataViewAssets->SetAudios(std::move(audioPackage));
                dataViewAssets->SetImages(std::move(imagePackage));
                dataViewAssets->SetMaterials(std::move(materialPackage));
                dataViewAssets->SetScripts(std::move(scriptPackage));
                dataViewAssets->SetShaders(std::move(shaderPackage));
            }

            // Registries
            {
                auto dataViewRegistries = GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateRegistries>();
                dataViewRegistries->SetAbilities(std::move(abilityPackage));
                dataViewRegistries->SetCharacterClasses(std::move(characterClassPackage));
                dataViewRegistries->SetItems(std::move(itemPackage));
                dataViewRegistries->SetQuests(std::move(questPackage));
                dataViewRegistries->SetSpells(std::move(spellPackage));
                dataViewRegistries->SetStatusEffects(std::move(statusEffectPackage));
            }

            // Game data
            {
                auto dataViewGameData = GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateGameData>();
                dataViewGameData->SetElementsGlobalContext(std::move(globalContextElementPackage));
                dataViewGameData->SetResourcesGlobalContext(std::move(globalContextResourcePackage));
                dataViewGameData->SetStatsDataStandard(std::move(dataStandardStatPackage));
            }
        }
        else
        {
            // Assets
            {
                auto dataViewAssets = GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateAssets>();
                dataViewAssets->SetAudios(audioPackage);
                dataViewAssets->SetImages(imagePackage);
                dataViewAssets->SetMaterials(materialPackage);
                dataViewAssets->SetScripts(scriptPackage);
                dataViewAssets->SetShaders(shaderPackage);
            }

            // Registries
            {
                auto dataViewRegistries = GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateRegistries>();
                dataViewRegistries->SetAbilities(abilityPackage);
                dataViewRegistries->SetCharacterClasses(characterClassPackage);
                dataViewRegistries->SetItems(itemPackage);
                dataViewRegistries->SetQuests(questPackage);
                dataViewRegistries->SetSpells(spellPackage);
                dataViewRegistries->SetStatusEffects(statusEffectPackage);
            }

            // Game data
            {
                auto dataViewGameData = GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateGameData>();
                dataViewGameData->SetElementsGlobalContext(globalContextElementPackage);
                dataViewGameData->SetResourcesGlobalContext(globalContextResourcePackage);
                dataViewGameData->SetStatsDataStandard(dataStandardStatPackage);
            }
        }
    }
}