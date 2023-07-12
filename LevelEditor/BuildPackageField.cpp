
#include "BuildPackageField.h"

#include "BuildPackageTile.h"

namespace Creation
{
    namespace Build
    {
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Field>)
        {
            scribe(id);
            scribe(tiles);
            scribe(entities);
        }

        Package<::Atmos::Field>::Package(Package &&arg) : id(std::move(arg.id)), tiles(std::move(arg.tiles)), entities(std::move(arg.entities))
        {}

        Package<::Atmos::Field>& Package<::Atmos::Field>::operator=(Package &&arg)
        {
            id = std::move(arg.id);
            tiles = std::move(arg.tiles);
            entities = std::move(arg.entities);
            return *this;
        }

        bool Package<::Atmos::Field>::operator==(const Package &arg) const
        {
            return id == arg.id && tiles == arg.tiles && entities == arg.entities;
        }

        bool Package<::Atmos::Field>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        template<class CompT>
        void EntityComponentCreator(::Atmos::Entity ent, ::Atmos::EntityManager &manager, const Package<::Atmos::Optional<Package<CompT>>> &package)
        {
            auto &built = package.Build();
            if (!built)
                return;

            manager.CreateComponent<CompT>(ent).second = std::move(built->Build());
        }

        Package<::Atmos::Field>::BuildT Package<::Atmos::Field>::Build() const
        {
            BuildT ret(id.Build());
            for (auto &loop : tiles.value)
                ret.tiles.Add(loop.Build());

            for (auto &loop : entities.value)
            {
                ::Atmos::Entity e = ret.entities.CreateEntity(loop.generalComponent.name.Build(), loop.generalComponent.position.Build());

                EntityComponentCreator(e, ret.entities, loop.actionComponent);
                EntityComponentCreator(e, ret.entities, loop.aiComponent);
                EntityComponentCreator(e, ret.entities, loop.avatarComponent);
                EntityComponentCreator(e, ret.entities, loop.characterComponent);
                EntityComponentCreator(e, ret.entities, loop.combatComponent);
                EntityComponentCreator(e, ret.entities, loop.dialogueComponent);
                *ret.entities.FindComponent<::Atmos::Ent::GeneralComponent>(e) = loop.generalComponent.Build();
                EntityComponentCreator(e, ret.entities, loop.inventoryComponent);
                EntityComponentCreator(e, ret.entities, loop.movementComponent);
                EntityComponentCreator(e, ret.entities, loop.senseComponent);
            }

            return ret;
        }
    }
}