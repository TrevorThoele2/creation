#pragma once

#include <tuple>

#include <Atmos/Entity.h>

#include <Atmos/ActionComponent.h>
#include <Atmos/BattleComponent.h>
#include <Atmos/AIComponent.h>
#include <Atmos/AvatarComponent.h>
#include <Atmos/CharacterComponent.h>
#include <Atmos/CombatComponent.h>
#include <Atmos/DialogueComponent.h>
#include <Atmos/GeneralComponent.h>
#include <Atmos/InventoryComponent.h>
#include <Atmos/MovementComponent.h>
#include <Atmos/SenseComponent.h>

#include "CurrentWorld.h"
#include "String.h"
#include "Optional.h"

#include <Function/Generator.h>

namespace Creation
{
    /*
    class EntityCreator
    {
    private:
        enum ComponentType
        {
            ACTION,
            BATTLE,
            AI,
            AVATAR,
            CHARACTER,
            COMBAT,
            DIALOGUE,
            INVENTORY,
            MOVEMENT,
            SENSE
        };

        template<ComponentType t>
        struct ComponentTraits;

        template<> struct ComponentTraits<ComponentType::ACTION> { typedef ::Atmos::Ent::ActionComponent CompT; };
        template<> struct ComponentTraits<ComponentType::BATTLE> { typedef ::Atmos::Ent::BattleComponent CompT; };
        template<> struct ComponentTraits<ComponentType::AI> { typedef ::Atmos::Ent::AIComponent CompT; };
        template<> struct ComponentTraits<ComponentType::AVATAR> { typedef ::Atmos::Ent::AvatarComponent CompT; };
        template<> struct ComponentTraits<ComponentType::CHARACTER> { typedef ::Atmos::Ent::CharacterComponent CompT; };
        template<> struct ComponentTraits<ComponentType::COMBAT> { typedef ::Atmos::Ent::CombatComponent CompT; };
        template<> struct ComponentTraits<ComponentType::DIALOGUE> { typedef ::Atmos::Ent::DialogueComponent CompT; };
        template<> struct ComponentTraits<ComponentType::INVENTORY> { typedef ::Atmos::Ent::InventoryComponent CompT; };
        template<> struct ComponentTraits<ComponentType::MOVEMENT> { typedef ::Atmos::Ent::MovementComponent CompT; };
        template<> struct ComponentTraits<ComponentType::SENSE> { typedef ::Atmos::Ent::SenseComponent CompT; };

        template<ComponentType t>
        struct TupleIterator
        {
            typedef ComponentTraits<t> TraitsT;
            typedef Optional<typename TraitsT::CompT> Type;
            template<class... Args>
            static void Do(std::tuple<Args...> &tuple, ::Atmos::Entity entity)
            {
                auto found = GetCurrentEntities()->FindComponent<typename Type::ValueT>(entity);
                if (found)
                    std::get<t>(tuple).Set(*found);
                else
                    std::get<t>(tuple).Reset();
            }
        };

        template<ComponentType t>
        struct CreatorImpl
        {
            typedef ComponentTraits<t> TraitsT;
            typedef Optional<typename TraitsT::CompT> Type;
            template<class... Args>
            static void Do(const std::tuple<Args...> &tuple, ::Atmos::Entity entity)
            {
                auto &got = std::get<t>(tuple);
                if(got.IsValid())
                    GetCurrentEntities()->CreateComponent<typename Type::ValueT>(entity, got);
            }
        };

        String name;
        ::Atmos::GridPosition position;
        ::function::TypeGeneratorRangeIterate<ComponentType, std::tuple, TupleIterator>::Forward<ACTION, SENSE, true> tuple;
    public:
        EntityCreator();
        EntityCreator(::Atmos::Entity entity);
        EntityCreator(const String &name, const ::Atmos::GridPosition &position);
        EntityCreator(const EntityCreator &arg);
        EntityCreator(EntityCreator &&arg);
        EntityCreator& operator=(const EntityCreator &arg);
        EntityCreator& operator=(EntityCreator &&arg);
        EntityCreator& operator=(::Atmos::Entity entity);

        ::Atmos::Entity Create() const;

        void SetPosition(const Atmos::GridPosition &set);
        const String& GetName() const;
    };
    */
}