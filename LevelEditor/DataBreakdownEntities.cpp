
#include "DataBreakdownEntities.h"

#include "EntityViewManager.h"
#include "MainFrame.h"
#include "CurrentWorld.h"

#include <Atmos/ModulatorGenerator.h>
#include <Atmos/ModulatorDescribers.h>

#include <wx/statline.h>
#include <wx/artprov.h>
#include <wx/textdlg.h>

namespace Creation
{
    void DataBreakdown<Build::Package<::Atmos::Ent::ActionComponent>>::AddAllChildren()
    {
        AddChild(activator);
        AddChild(action);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::ActionComponent>>::SetupImpl()
    {
        activator.Setup(Get()->activator);
        action.Setup(Get()->action);
    }

    DataBreakdown<Build::Package<::Atmos::Ent::ActionComponent>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        activator("Activator", this),
        action("Action", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::ActionComponent>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        activator(std::move(arg.activator), this),
        action(std::move(arg.action), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::ActionComponent>>& DataBreakdown<Build::Package<::Atmos::Ent::ActionComponent>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        activator = std::move(arg.activator);
        action = std::move(arg.action);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::AIComponent>>::AddAllChildren()
    {
        AddChild(ai);
        AddChild(battleAI);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::AIComponent>>::SetupImpl()
    {
        ai.Setup(Get()->ai);
        battleAI.Setup(Get()->battleAI);
    }

    DataBreakdown<Build::Package<::Atmos::Ent::AIComponent>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        ai("AI", this),
        battleAI("Battle AI", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::AIComponent>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        ai(std::move(arg.ai), this),
        battleAI(std::move(arg.battleAI), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::AIComponent>>& DataBreakdown<Build::Package<::Atmos::Ent::AIComponent>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        ai = std::move(arg.ai);
        battleAI = std::move(arg.battleAI);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::AvatarComponent>>::AddAllChildren()
    {
        AddChild(gold);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::AvatarComponent>>::SetupImpl()
    {
        gold.Setup(Get()->gold);
    }

    DataBreakdown<Build::Package<::Atmos::Ent::AvatarComponent>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        gold("Gold", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::AvatarComponent>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        gold(std::move(arg.gold), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::AvatarComponent>>& DataBreakdown<Build::Package<::Atmos::Ent::AvatarComponent>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        gold = std::move(arg.gold);
        return *this;
    }

    DataBreakdown<Build::Package<::Atmos::Ent::CharacterComponent::ImplMonster>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent)
    {}

    DataBreakdown<Build::Package<::Atmos::Ent::CharacterComponent::ImplMonster>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent)
    {}

    DataBreakdown<Build::Package<::Atmos::Ent::CharacterComponent::ImplMonster>>& DataBreakdown<Build::Package<::Atmos::Ent::CharacterComponent::ImplMonster>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::CharacterComponent>>::AddAllChildren()
    {
        AddChild(type);
        AddChild(monsterImpl);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::CharacterComponent>>::SetupImpl()
    {
        type.Setup(Get()->type);
        monsterImpl.Setup(Get()->monsterImpl);
    }

    DataBreakdown<Build::Package<::Atmos::Ent::CharacterComponent>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        type("Type", this),
        monsterImpl("Monster Impl", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::CharacterComponent>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        type(std::move(arg.type), this),
        monsterImpl(std::move(arg.monsterImpl), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::CharacterComponent>>& DataBreakdown<Build::Package<::Atmos::Ent::CharacterComponent>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        type = std::move(arg.type);
        monsterImpl = std::move(arg.monsterImpl);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::CombatComponent>::EntryPackage>::AddAllChildren()
    {
        AddChild(slot);
        AddChild(item);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::CombatComponent>::EntryPackage>::SetupImpl()
    {
        slot.Setup(Get()->slot);
        item.Setup(Get()->item);
    }

    DataBreakdown<Build::Package<::Atmos::Ent::CombatComponent>::EntryPackage>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        slot("Slot", this),
        item("Item", this)
    {}

    DataBreakdown<Build::Package<::Atmos::Ent::CombatComponent>::EntryPackage>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        slot(std::move(arg.slot), this),
        item(std::move(arg.item), this)
    {}

    DataBreakdown<Build::Package<::Atmos::Ent::CombatComponent>::EntryPackage>& DataBreakdown<Build::Package<::Atmos::Ent::CombatComponent>::EntryPackage>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        slot = std::move(arg.slot);
        item = std::move(arg.item);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::CombatComponent>>::AddAllChildren()
    {
        AddChild(charClass);
        AddChild(acumen);
        AddChild(permanentStash);
        AddChild(equipment);
        AddChild(level);
        AddChild(movementRange);
        AddChild(spells);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::CombatComponent>>::SetupImpl()
    {
        charClass.Setup(Get()->charClass);
        acumen.Setup(Get()->acumen);
        permanentStash.Setup(Get()->permanentStash);
        equipment.Setup(Get()->equipment);
        level.Setup(Get()->level);
        movementRange.Setup(Get()->movementRange);
        spells.Setup(Get()->spells);
    }

    DataBreakdown<Build::Package<::Atmos::Ent::CombatComponent>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        charClass("Character Class", this),
        acumen("Acumen", this),
        permanentStash("Permanent Stash", this),
        equipment("Equipment", this),
        level("Level", this),
        movementRange("Movement Range", this),
        spells("Spells", this)
    {
        AddAllChildren();
        permanentStash.SetPrependEntryName("Item");
        equipment.SetPrependEntryName("Item");
        spells.SetPrependEntryName("Spell");
    }

    DataBreakdown<Build::Package<::Atmos::Ent::CombatComponent>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        charClass(std::move(arg.charClass), this),
        acumen(std::move(arg.acumen), this),
        permanentStash(std::move(arg.permanentStash), this),
        equipment(std::move(arg.equipment), this),
        level(std::move(arg.level), this),
        movementRange(std::move(arg.movementRange), this),
        spells(std::move(arg.spells), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::CombatComponent>>& DataBreakdown<Build::Package<::Atmos::Ent::CombatComponent>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        charClass = std::move(arg.charClass);
        acumen = std::move(arg.acumen);
        permanentStash = std::move(arg.permanentStash);
        equipment = std::move(arg.equipment);
        level = std::move(arg.level);
        movementRange = std::move(arg.movementRange);
        spells = std::move(arg.spells);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::DialogueComponent>>::AddAllChildren()
    {
        AddChild(script);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::DialogueComponent>>::SetupImpl()
    {
        script.Setup(Get()->script);
    }

    DataBreakdown<Build::Package<::Atmos::Ent::DialogueComponent>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        script("Script", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::DialogueComponent>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        script(std::move(arg.script), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::DialogueComponent>>& DataBreakdown<Build::Package<::Atmos::Ent::DialogueComponent>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        script = std::move(arg.script);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::GeneralComponent>::StoragePackage>::AddAllChildren()
    {
        AddChild(name);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::GeneralComponent>::StoragePackage>::SetupImpl()
    {
        name.Setup(Get()->name);
    }

    DataBreakdown<Build::Package<::Atmos::Ent::GeneralComponent>::StoragePackage>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        name("Name", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::GeneralComponent>::StoragePackage>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        name(std::move(arg.name), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::GeneralComponent>::StoragePackage>& DataBreakdown<Build::Package<::Atmos::Ent::GeneralComponent>::StoragePackage>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        name = std::move(arg.name);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::GeneralComponent>>::AddAllChildren()
    {
        AddChild(name);
        AddChild(niceName);
        AddChild(position);
        AddChild(direction);
        AddChild(solid);
        AddChild(storage);
        AddChild(tags);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::GeneralComponent>>::SetupImpl()
    {
        name.Setup(Get()->name);
        niceName.Setup(Get()->niceName);
        position.Setup(Get()->position);
        direction.Setup(Get()->direction);
        solid.Setup(Get()->solid);
        storage.Setup(Get()->storage);
        tags.Setup(Get()->tags);
    }

    DataBreakdown<Build::Package<::Atmos::Ent::GeneralComponent>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        name("Name", this),
        niceName("Nice Name", this),
        position("Position", this),
        direction("Direction", this),
        solid("Solid", this),
        storage("Storage", this),
        tags("Tags", this)
    {
        AddAllChildren();
        tags.SetPrependEntryName("Tag");
    }

    DataBreakdown<Build::Package<::Atmos::Ent::GeneralComponent>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        name(std::move(arg.name), this),
        niceName(std::move(arg.niceName), this),
        position(std::move(arg.position), this),
        direction(std::move(arg.direction), this),
        solid(std::move(arg.solid), this),
        storage(std::move(arg.storage), this),
        tags(std::move(arg.tags), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::GeneralComponent>>& DataBreakdown<Build::Package<::Atmos::Ent::GeneralComponent>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        name = std::move(arg.name);
        niceName = std::move(arg.niceName);
        position = std::move(arg.position);
        direction = std::move(arg.direction);
        solid = std::move(arg.solid);
        storage = std::move(arg.storage);
        tags = std::move(arg.tags);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::InventoryComponent>>::AddAllChildren()
    {
        AddChild(items);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::InventoryComponent>>::SetupImpl()
    {
        items.Setup(Get()->items);
    }

    DataBreakdown<Build::Package<::Atmos::Ent::InventoryComponent>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        items("Items", this)
    {
        AddAllChildren();
        items.SetPrependEntryName("Item");
    }

    DataBreakdown<Build::Package<::Atmos::Ent::InventoryComponent>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        items(std::move(arg.items), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::InventoryComponent>>& DataBreakdown<Build::Package<::Atmos::Ent::InventoryComponent>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        items = std::move(arg.items);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::MovementComponent>>::AddAllChildren()
    {
        AddChild(upMod);
        AddChild(downMod);
        AddChild(leftMod);
        AddChild(rightMod);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::MovementComponent>>::SetupImpl()
    {
        upMod.Setup(Get()->upMod);
        downMod.Setup(Get()->downMod);
        leftMod.Setup(Get()->leftMod);
        rightMod.Setup(Get()->rightMod);
    }

    DataBreakdown<Build::Package<::Atmos::Ent::MovementComponent>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        upMod("Up Mod", this),
        downMod("Down Mod", this),
        leftMod("Left Mod", this),
        rightMod("Right Mod", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::MovementComponent>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        upMod(std::move(arg.upMod), this),
        downMod(std::move(arg.downMod), this),
        leftMod(std::move(arg.leftMod), this),
        rightMod(std::move(arg.rightMod), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::MovementComponent>>& DataBreakdown<Build::Package<::Atmos::Ent::MovementComponent>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        upMod = std::move(arg.upMod);
        downMod = std::move(arg.downMod);
        leftMod = std::move(arg.leftMod);
        rightMod = std::move(arg.rightMod);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage>::OnTypeChanged(const DataBreakdownEditArgs &args)
    {
        typedef ::Atmos::Ent::SenseComponent::ModulatorEntryType Type;
        Build::Package<String> packageUse;
        switch (type.GetAsEnum())
        {
        case Type::SPRITE:
            packageUse.value = ::Atmos::Modulator::Description::Sprite.name;
            break;
        case Type::SOUND:
            packageUse.value = ::Atmos::Modulator::Description::Sound.name;
            break;
        case Type::AV_EFFECT:
            packageUse.value = ::Atmos::Modulator::Description::AVEffect.name;
            break;
        }

        generatorRoute.prototype.ForceEdit(std::move(packageUse));
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage>::AddAllChildren()
    {
        AddChild(objectID);
        AddChild(type);
        AddChild(generatorRoute);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage>::SubscribeEvents()
    {
        type.edited.Subscribe(&DataBreakdown::OnTypeChanged, *this);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage>::SetupImpl()
    {
        objectID.Setup(Get()->objectID);
        type.Setup(Get()->type);

        // Setup generator route
        generatorRoute.Setup(Get()->generatorRoute);
        StringGroup stringGroup;
        stringGroup.push_back(::Atmos::Modulator::Description::Sprite.name);
        generatorRoute.SetNameGroup(stringGroup);
    }
    
    DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        objectID("Object ID", this),
        type("Type", this),
        generatorRoute("Generator", this)
    {
        AddAllChildren();
        SubscribeEvents();
        generatorRoute.SetAddCategory(false);
        generatorRoute.SetAddTreePiece(false);
        generatorRoute.prototype.SetInvisible(true);
    }

    DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        objectID(std::move(arg.objectID), this),
        type(std::move(arg.type), this),
        generatorRoute(std::move(arg.generatorRoute), this)
    {
        AddAllChildren();
        SubscribeEvents();
        generatorRoute.SetAddCategory(false);
        generatorRoute.SetAddTreePiece(false);
        generatorRoute.prototype.SetInvisible(true);
    }

    DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage>& DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorEntryPackage>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        objectID = std::move(arg.objectID);
        type = std::move(arg.type);
        generatorRoute = std::move(arg.generatorRoute);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorPackPackage>::AddAllChildren()
    {
        AddChild(name);
        AddChild(entries);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorPackPackage>::SetupImpl()
    {
        name.Setup(Get()->name);
        entries.Setup(Get()->entries);
    }

    DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorPackPackage>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        name("Name", this),
        entries("Entries", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorPackPackage>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        name(std::move(arg.name), this),
        entries(std::move(arg.entries), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorPackPackage>& DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>::ModulatorPackPackage>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        name = std::move(arg.name);
        entries = std::move(arg.entries);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>>::AddAllChildren()
    {
        AddChild(sprites);
        AddChild(sounds);
        AddChild(avEffects);
        AddChild(modulatorPacks);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>>::SetupImpl()
    {
        sprites.Setup(Get()->sprites);
        sounds.Setup(Get()->sounds);
        avEffects.Setup(Get()->avEffects);
        modulatorPacks.Setup(Get()->modulatorPacks);
    }

    DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        sprites("Sprites", this),
        sounds("Sounds", this),
        avEffects("AV Effects", this),
        modulatorPacks("Modulators", this)
    {
        AddAllChildren();
        sprites.SetPrependEntryName("Sprite");
        sounds.SetPrependEntryName("Sound");
        avEffects.SetPrependEntryName("AVEffect");
        modulatorPacks.SetPrependEntryName("Modulator");
    }

    DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        sprites(std::move(arg.sprites), this),
        sounds(std::move(arg.sounds), this),
        avEffects(std::move(arg.avEffects), this),
        modulatorPacks(std::move(arg.modulatorPacks), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>>& DataBreakdown<Build::Package<::Atmos::Ent::SenseComponent>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        sprites = std::move(arg.sprites);
        sounds = std::move(arg.sounds);
        avEffects = std::move(arg.avEffects);
        modulatorPacks = std::move(arg.modulatorPacks);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::Entity>>::AddAllChildren()
    {
        AddChild(id);
        AddChild(generalComponent);

        AddChild(actionComponent);
        AddChild(aiComponent);
        AddChild(avatarComponent);
        AddChild(characterComponent);
        AddChild(combatComponent);
        AddChild(dialogueComponent);
        AddChild(inventoryComponent);
        AddChild(movementComponent);
        AddChild(senseComponent);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::Entity>>::SubscribeEvents()
    {
        senseComponent.valid.edited.Subscribe(&DataBreakdown::OnSenseComponentValid, *this);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::Entity>>::CheckSenseComponentSubscribe()
    {
        senseConnections.Clear();
        if (senseComponent.IsValid())
        {
            senseConnections.Add(senseComponent.wrapped.sprites.added.Subscribe(&DataBreakdown::OnSpriteAdded, *this));
            senseConnections.Add(senseComponent.wrapped.sprites.postRemove.Subscribe(&DataBreakdown::OnSpriteRemoved, *this));
        }
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::Entity>>::OnSenseComponentValid(const DataBreakdownEditArgs &args)
    {
        CheckSenseComponentSubscribe();
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::Entity>>::OnSpriteAdded(const DataBreakdownAddArgs &args)
    {
        auto spriteBreakdown = static_cast<DataBreakdown<Build::Package<::Atmos::Sprite>>*>(args.Added());
        spriteBreakdown->edited.Subscribe(&DataBreakdown::OnSpriteEdited, *this);
        EntityViewManager::Evaluate(Get()->generalComponent.position);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::Entity>>::OnSpriteRemoved(const DataBreakdownPostRemoveArgs &args)
    {
        EntityViewManager::Evaluate(Get()->generalComponent.position);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::Entity>>::OnSpriteEdited(const DataBreakdownEditArgs &args)
    {
        EntityViewManager::Evaluate(Get()->generalComponent.position);
    }

    void DataBreakdown<Build::Package<::Atmos::Ent::Entity>>::SetupImpl()
    {
        actionComponent.Setup(Get()->actionComponent);
        aiComponent.Setup(Get()->aiComponent);
        avatarComponent.Setup(Get()->avatarComponent);
        characterComponent.Setup(Get()->characterComponent);
        combatComponent.Setup(Get()->combatComponent);
        dialogueComponent.Setup(Get()->dialogueComponent);
        generalComponent.Setup(Get()->generalComponent);
        inventoryComponent.Setup(Get()->inventoryComponent);
        movementComponent.Setup(Get()->movementComponent);
        senseComponent.Setup(Get()->senseComponent);
        id.Setup(Get()->id);

        CheckSenseComponentSubscribe();
    }

    bool DataBreakdown<Build::Package<::Atmos::Ent::Entity>>::IgnoreNameForKeyImpl() const
    {
        return true;
    }

    DataBreakdown<Build::Package<::Atmos::Ent::Entity>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        actionComponent("Action Component", this),
        aiComponent("AI Component", this),
        avatarComponent("Avatar Component", this),
        characterComponent("Character Component", this),
        combatComponent("Combat Component", this),
        dialogueComponent("Dialogue Component", this),
        generalComponent("General Component", this),
        inventoryComponent("Inventory Component", this),
        movementComponent("Movement Component", this),
        senseComponent("Sense Component", this),
        id("ID", this)
    {
        AddAllChildren();
        SubscribeEvents();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::Entity>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        actionComponent(std::move(arg.actionComponent), this),
        aiComponent(std::move(arg.aiComponent), this),
        avatarComponent(std::move(arg.avatarComponent), this),
        characterComponent(std::move(arg.characterComponent), this),
        combatComponent(std::move(arg.combatComponent), this),
        dialogueComponent(std::move(arg.dialogueComponent), this),
        generalComponent(std::move(arg.generalComponent), this),
        inventoryComponent(std::move(arg.inventoryComponent), this),
        movementComponent(std::move(arg.movementComponent), this),
        senseComponent(std::move(arg.senseComponent), this),
        id(std::move(arg.id), this)
    {
        AddAllChildren();
        SubscribeEvents();
    }

    DataBreakdown<Build::Package<::Atmos::Ent::Entity>>& DataBreakdown<Build::Package<::Atmos::Ent::Entity>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
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
}