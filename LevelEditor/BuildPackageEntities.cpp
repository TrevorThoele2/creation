
#include "BuildPackageEntities.h"

namespace Creation
{
    namespace Build
    {
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Ent::ActionComponent>)
        {
            scribe(activator);
            scribe(action);
        }

        Package<::Atmos::Ent::ActionComponent>::Package(Package &&arg) : activator(std::move(arg.activator)), action(std::move(arg.action))
        {}

        Package<::Atmos::Ent::ActionComponent>& Package<::Atmos::Ent::ActionComponent>::operator=(Package &&arg)
        {
            activator = std::move(arg.activator);
            action = std::move(arg.action);
            return *this;
        }

        bool Package<::Atmos::Ent::ActionComponent>::operator==(const Package &arg) const
        {
            return activator == arg.activator && action == arg.action;
        }

        bool Package<::Atmos::Ent::ActionComponent>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Ent::ActionComponent>::BuildT Package<::Atmos::Ent::ActionComponent>::Build() const
        {
            BuildT ret;
            ret.activator = static_cast<BuildT::Activator>(activator.Build());
            ret.act = action.Build();
            return ret;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Ent::AIComponent>)
        {
            scribe(ai);
            scribe(battleAI);
        }

        Package<::Atmos::Ent::AIComponent>::Package(Package &&arg) : ai(std::move(arg.ai)), battleAI(std::move(arg.battleAI))
        {}

        Package<::Atmos::Ent::AIComponent>& Package<::Atmos::Ent::AIComponent>::operator=(Package &&arg)
        {
            ai = std::move(arg.ai);
            battleAI = std::move(arg.battleAI);
            return *this;
        }

        bool Package<::Atmos::Ent::AIComponent>::operator==(const Package &arg) const
        {
            return ai == arg.ai && battleAI == arg.battleAI;
        }

        bool Package<::Atmos::Ent::AIComponent>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Ent::AIComponent>::BuildT Package<::Atmos::Ent::AIComponent>::Build() const
        {
            BuildT ret;
            ret.ai = ai.Build();
            ret.battleAI = battleAI.Build();
            return ret;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Ent::AvatarComponent>)
        {
            scribe(gold);
        }

        Package<::Atmos::Ent::AvatarComponent>::Package(Package &&arg) : gold(std::move(arg.gold))
        {}

        Package<::Atmos::Ent::AvatarComponent>& Package<::Atmos::Ent::AvatarComponent>::operator=(Package &&arg)
        {
            gold = std::move(arg.gold);
            return *this;
        }

        bool Package<::Atmos::Ent::AvatarComponent>::operator==(const Package &arg) const
        {
            return gold == arg.gold;
        }

        bool Package<::Atmos::Ent::AvatarComponent>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Ent::AvatarComponent>::BuildT Package<::Atmos::Ent::AvatarComponent>::Build() const
        {
            BuildT ret;
            ret.gold = gold.Build();
            return ret;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Ent::CharacterComponent::ImplMonster>)
        {

        }

        Package<::Atmos::Ent::CharacterComponent::ImplMonster>::Package(Package &&arg)
        {}

        Package<::Atmos::Ent::CharacterComponent::ImplMonster>& Package<::Atmos::Ent::CharacterComponent::ImplMonster>::operator=(Package &&arg)
        {
            return *this;
        }

        bool Package<::Atmos::Ent::CharacterComponent::ImplMonster>::operator==(const Package &arg) const
        {
            return true;
        }

        bool Package<::Atmos::Ent::CharacterComponent::ImplMonster>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Ent::CharacterComponent::ImplMonster>::BuildT Package<::Atmos::Ent::CharacterComponent::ImplMonster>::Build() const
        {
            return BuildT();
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Ent::CharacterComponent>)
        {
            scribe(type);
            scribe(monsterImpl);
        }

        Package<::Atmos::Ent::CharacterComponent>::Package(Package &&arg) : type(std::move(arg.type)), monsterImpl(std::move(arg.monsterImpl))
        {}

        Package<::Atmos::Ent::CharacterComponent>& Package<::Atmos::Ent::CharacterComponent>::operator=(Package &&arg)
        {
            type = std::move(arg.type);
            monsterImpl = std::move(arg.monsterImpl);
            return *this;
        }

        bool Package<::Atmos::Ent::CharacterComponent>::operator==(const Package &arg) const
        {
            return type == arg.type && monsterImpl == arg.monsterImpl;
        }

        bool Package<::Atmos::Ent::CharacterComponent>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Ent::CharacterComponent>::BuildT Package<::Atmos::Ent::CharacterComponent>::Build() const
        {
            BuildT ret;
            ret.type = static_cast<BuildT::Type>(type.Build());
            auto &useMonsterImpl = monsterImpl.Build();
            if (useMonsterImpl)
            {
                ret.SetMonster();
                *ret.GetImpl<BuildT::MONSTER>() = useMonsterImpl->Build();
            }

            return ret;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Ent::CombatComponent>::EntryPackage)
        {
            scribe(slot);
            scribe(item);
        }

        Package<::Atmos::Ent::CombatComponent>::EntryPackage::EntryPackage(EntryPackage &&arg) : slot(std::move(arg.slot)), item(std::move(arg.item))
        {}

        Package<::Atmos::Ent::CombatComponent>::EntryPackage& Package<::Atmos::Ent::CombatComponent>::EntryPackage::operator=(EntryPackage &&arg)
        {
            slot = std::move(arg.slot);
            item = std::move(arg.item);
            return *this;
        }

        bool Package<::Atmos::Ent::CombatComponent>::EntryPackage::operator==(const EntryPackage &arg) const
        {
            return slot == arg.slot && item == arg.item;
        }

        bool Package<::Atmos::Ent::CombatComponent>::EntryPackage::operator!=(const EntryPackage &arg) const
        {
            return !(*this == arg);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Ent::CombatComponent>)
        {
            scribe(charClass);
            scribe(acumen);
            scribe(permanentStash);
            scribe(equipment);
            scribe(level);
            scribe(movementRange);
            scribe(spells);
        }

        Package<::Atmos::Ent::CombatComponent>::Package(Package &&arg) : charClass(std::move(arg.charClass)), acumen(std::move(arg.acumen)), permanentStash(std::move(arg.permanentStash)),
            equipment(std::move(arg.equipment)), level(std::move(arg.level)), movementRange(std::move(arg.movementRange)), spells(std::move(arg.spells))
        {}

        Package<::Atmos::Ent::CombatComponent>& Package<::Atmos::Ent::CombatComponent>::operator=(Package &&arg)
        {
            charClass = std::move(arg.charClass);
            acumen = std::move(arg.acumen);
            permanentStash = std::move(arg.permanentStash);
            equipment = std::move(arg.equipment);
            level = std::move(arg.level);
            movementRange = std::move(arg.movementRange);
            spells = std::move(arg.spells);
            return *this;
        }

        bool Package<::Atmos::Ent::CombatComponent>::operator==(const Package &arg) const
        {
            return charClass == arg.charClass && acumen == arg.acumen && permanentStash == arg.permanentStash && equipment == arg.equipment && level == arg.level &&
                movementRange == arg.movementRange && spells == arg.spells;
        }

        bool Package<::Atmos::Ent::CombatComponent>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Ent::CombatComponent>::BuildT Package<::Atmos::Ent::CombatComponent>::Build() const
        {
            BuildT ret;
            ret.charClass = charClass.Build();
            ret.acumen = acumen.Build();
            for (auto &loop : permanentStash.value)
                ret.permanentStash.AddBack(loop.Build());
            for (auto &loop : equipment.value)
                ret.Equip(static_cast<::Atmos::EquipSlot>(loop.slot.Build()), loop.item.Build());
            return ret;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Ent::DialogueComponent>)
        {
            scribe(script);
        }

        Package<::Atmos::Ent::DialogueComponent>::Package(Package &&arg) : script(std::move(arg.script))
        {}

        Package<::Atmos::Ent::DialogueComponent>& Package<::Atmos::Ent::DialogueComponent>::operator=(Package &&arg)
        {
            script = std::move(arg.script);
            return *this;
        }

        bool Package<::Atmos::Ent::DialogueComponent>::operator==(const Package &arg) const
        {
            return script == arg.script;
        }

        bool Package<::Atmos::Ent::DialogueComponent>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Ent::DialogueComponent>::BuildT Package<::Atmos::Ent::DialogueComponent>::Build() const
        {
            BuildT ret;
            ret.script = script.Build();
            return ret;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Ent::GeneralComponent>::StoragePackage)
        {
            scribe(name);
        }

        Package<::Atmos::Ent::GeneralComponent>::StoragePackage::StoragePackage(StoragePackage &&arg) : name(std::move(arg.name))
        {}

        Package<::Atmos::Ent::GeneralComponent>::StoragePackage& Package<::Atmos::Ent::GeneralComponent>::StoragePackage::operator=(StoragePackage &&arg)
        {
            name = std::move(arg.name);
            return *this;
        }

        bool Package<::Atmos::Ent::GeneralComponent>::StoragePackage::operator==(const StoragePackage &arg) const
        {
            return name == arg.name;
        }

        bool Package<::Atmos::Ent::GeneralComponent>::StoragePackage::operator!=(const StoragePackage &arg) const
        {
            return !(*this == arg);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Ent::GeneralComponent>)
        {
            scribe(name);
            scribe(niceName);
            scribe(position);
            scribe(direction);
            scribe(solid);
            scribe(storage);
            scribe(tags);
        }

        Package<::Atmos::Ent::GeneralComponent>::Package(Package &&arg) : name(std::move(arg.name)), niceName(std::move(arg.niceName)), position(std::move(arg.position)),
            direction(std::move(arg.direction)), solid(std::move(arg.solid)), storage(std::move(arg.storage)), tags(std::move(arg.tags))
        {}

        Package<::Atmos::Ent::GeneralComponent>& Package<::Atmos::Ent::GeneralComponent>::operator=(Package &&arg)
        {
            name = std::move(arg.name);
            niceName = std::move(arg.niceName);
            position = std::move(arg.position);
            direction = std::move(arg.direction);
            solid = std::move(arg.solid);
            storage = std::move(arg.storage);
            tags = std::move(arg.tags);
            return *this;
        }

        bool Package<::Atmos::Ent::GeneralComponent>::operator==(const Package &arg) const
        {
            return name == arg.name && niceName == arg.niceName && position == arg.position && direction == arg.direction && solid == arg.solid && storage == arg.storage &&
                tags == arg.tags;
        }

        bool Package<::Atmos::Ent::GeneralComponent>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Ent::GeneralComponent>::BuildT Package<::Atmos::Ent::GeneralComponent>::Build() const
        {
            BuildT ret;
            ret.name = name.Build();
            ret.niceName = niceName.Build();
            ret.position = position.Build();
            ret.direction = direction.Build();
            ret.solid = solid.Build();
            for (auto &loop : storage.value)
                ret.storage.emplace(loop.name.Build(), BuildT::Storage(loop.name.Build(), loop.variant.Build()));
            for (auto &loop : tags.value)
                ret.tags.emplace(loop.Build());
            return ret;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Ent::InventoryComponent>)
        {
            scribe(items);
        }

        Package<::Atmos::Ent::InventoryComponent>::Package(Package &&arg) : items(std::move(arg.items))
        {}

        Package<::Atmos::Ent::InventoryComponent>& Package<::Atmos::Ent::InventoryComponent>::operator=(Package &&arg)
        {
            items = std::move(arg.items);
            return *this;
        }

        bool Package<::Atmos::Ent::InventoryComponent>::operator==(const Package &arg) const
        {
            return items == arg.items;
        }

        bool Package<::Atmos::Ent::InventoryComponent>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Ent::InventoryComponent>::BuildT Package<::Atmos::Ent::InventoryComponent>::Build() const
        {
            BuildT ret;
            for (auto &loop : items.value)
                ret.container.AddBack(loop.Build());
            return ret;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Ent::MovementComponent>)
        {
            scribe(upMod);
            scribe(downMod);
            scribe(leftMod);
            scribe(rightMod);
        }

        Package<::Atmos::Ent::MovementComponent>::Package(Package &&arg) : upMod(std::move(arg.upMod)), downMod(std::move(arg.downMod)), leftMod(std::move(arg.leftMod)),
            rightMod(std::move(arg.rightMod))
        {}

        Package<::Atmos::Ent::MovementComponent>& Package<::Atmos::Ent::MovementComponent>::operator=(Package &&arg)
        {
            upMod = std::move(arg.upMod);
            downMod = std::move(arg.downMod);
            leftMod = std::move(arg.leftMod);
            rightMod = std::move(arg.rightMod);
            return *this;
        }

        bool Package<::Atmos::Ent::MovementComponent>::operator==(const Package &arg) const
        {
            return upMod == arg.upMod && downMod == arg.downMod && leftMod == arg.leftMod && rightMod == arg.rightMod;
        }

        bool Package<::Atmos::Ent::MovementComponent>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Ent::MovementComponent>::BuildT Package<::Atmos::Ent::MovementComponent>::Build() const
        {
            BuildT ret;
            ret.upMod = upMod.Build();
            ret.downMod = downMod.Build();
            ret.leftMod = leftMod.Build();
            ret.rightMod = rightMod.Build();
            return ret;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Ent::SenseComponent>::ModulatorPackPackage)
        {
            scribe(name);
            scribe(entries);
        }

        Package<::Atmos::Ent::SenseComponent>::ModulatorPackPackage::ModulatorPackPackage(ModulatorPackPackage &&arg) : PackageBase(std::move(arg)), name(std::move(arg.name)), entries(std::move(arg.entries))
        {}

        Package<::Atmos::Ent::SenseComponent>::ModulatorPackPackage& Package<::Atmos::Ent::SenseComponent>::ModulatorPackPackage::operator=(ModulatorPackPackage &&arg)
        {
            PackageBase::operator=(std::move(arg));
            name = std::move(arg.name);
            entries = std::move(arg.entries);
            return *this;
        }

        bool Package<::Atmos::Ent::SenseComponent>::ModulatorPackPackage::operator==(const ModulatorPackPackage &arg) const
        {
            return name == arg.name && entries == arg.entries;
        }

        bool Package<::Atmos::Ent::SenseComponent>::ModulatorPackPackage::operator!=(const ModulatorPackPackage &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Ent::SenseComponent>::ModulatorPackPackage::BuildT Package<::Atmos::Ent::SenseComponent>::ModulatorPackPackage::Build() const
        {
            BuildT ret;
            for (auto &loop : entries.Build())
                ret.Add(loop.Build());
            return ret;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage)
        {
            scribe(objectID);
            scribe(type);
            scribe(generatorRoute);
        }

        Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage::ModulatorEntryPackage(ModulatorEntryPackage &&arg) : objectID(std::move(arg.objectID)), type(std::move(arg.type)), generatorRoute(std::move(arg.generatorRoute))
        {}

        Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage& Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage::operator=(ModulatorEntryPackage &&arg)
        {
            objectID = std::move(arg.objectID);
            type = std::move(arg.type);
            generatorRoute = std::move(arg.generatorRoute);
            return *this;
        }

        bool Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage::operator==(const ModulatorEntryPackage &arg) const
        {
            return objectID == arg.objectID && type == arg.type && generatorRoute == arg.generatorRoute;
        }

        bool Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage::operator!=(const ModulatorEntryPackage &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage::BuildT Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage::Build() const
        {
            return BuildT(objectID.Build(), BuildT::Type(type.Build()), generatorRoute.Build());
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Ent::SenseComponent>)
        {
            scribe(sprites);
            scribe(sounds);
            scribe(avEffects);

            scribe(modulatorPacks);
        }

        Package<::Atmos::Ent::SenseComponent>::Package(Package &&arg) : sprites(std::move(arg.sprites)), sounds(std::move(arg.sounds)), avEffects(std::move(arg.avEffects)),
            modulatorPacks(std::move(arg.modulatorPacks))
        {}

        Package<::Atmos::Ent::SenseComponent>& Package<::Atmos::Ent::SenseComponent>::operator=(Package &&arg)
        {
            sprites = std::move(arg.sprites);
            sounds = std::move(arg.sounds);
            avEffects = std::move(arg.avEffects);
            modulatorPacks = std::move(arg.modulatorPacks);
            return *this;
        }

        bool Package<::Atmos::Ent::SenseComponent>::operator==(const Package &arg) const
        {
            return sprites == arg.sprites && sounds == arg.sounds && avEffects == arg.avEffects && modulatorPacks == arg.modulatorPacks;
        }

        bool Package<::Atmos::Ent::SenseComponent>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Ent::SenseComponent>::BuildT Package<::Atmos::Ent::SenseComponent>::Build() const
        {
            BuildT ret;
            for (auto &loop : sprites.value)
                ret.sprites.Add(loop.id.Build(), loop.Build());
            for (auto &loop : sounds.value)
                ret.sounds.Add(loop.id.Build(), loop.Build());
            for (auto &loop : avEffects.value)
                ret.avEffects.Add(loop.id.Build(), loop.Build());
            for (auto &loop : modulatorPacks.value)
            {
                auto added = ret.AddModulatorPack(loop.name.Build());
                *added = std::move(loop.Build());
            }
            return ret;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Ent::Entity>)
        {
            scribe(actionComponent);
            scribe(aiComponent);
            scribe(avatarComponent);
            scribe(characterComponent);
            scribe(combatComponent);
            scribe(dialogueComponent);
            scribe(generalComponent);
            scribe(inventoryComponent);
            scribe(movementComponent);
            scribe(senseComponent);

            scribe(id);
        }

        Package<::Atmos::Ent::Entity>::Package(Package &&arg) : actionComponent(std::move(arg.actionComponent)), aiComponent(std::move(arg.aiComponent)),
            avatarComponent(std::move(arg.avatarComponent)), characterComponent(std::move(arg.characterComponent)), combatComponent(std::move(arg.combatComponent)),
            dialogueComponent(std::move(arg.dialogueComponent)), generalComponent(std::move(arg.generalComponent)), inventoryComponent(std::move(arg.inventoryComponent)),
            movementComponent(std::move(arg.movementComponent)), senseComponent(std::move(arg.senseComponent)), id(std::move(arg.id))
        {}

        Package<::Atmos::Ent::Entity>& Package<::Atmos::Ent::Entity>::operator=(Package &&arg)
        {
            actionComponent = std::move(arg.actionComponent);
            aiComponent = std::move(arg.aiComponent);
            avatarComponent = std::move(arg.avatarComponent);
            characterComponent = std::move(arg.characterComponent);
            combatComponent = std::move(arg.combatComponent);
            dialogueComponent = std::move(arg.dialogueComponent);
            generalComponent = std::move(arg.generalComponent);
            inventoryComponent = std::move(arg.inventoryComponent);
            movementComponent = std::move(arg.movementComponent);
            senseComponent = std::move(arg.senseComponent);
            id = std::move(arg.id);
            return *this;
        }

        bool Package<::Atmos::Ent::Entity>::operator==(const Package &arg) const
        {
            return actionComponent == arg.actionComponent && aiComponent == arg.aiComponent && avatarComponent == arg.avatarComponent &&
                characterComponent == arg.characterComponent && combatComponent == arg.combatComponent && dialogueComponent == arg.dialogueComponent &&
                generalComponent == arg.generalComponent && inventoryComponent == arg.inventoryComponent && movementComponent == arg.movementComponent &&
                senseComponent == arg.senseComponent && id == arg.id;
        }

        bool Package<::Atmos::Ent::Entity>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }
    }
}