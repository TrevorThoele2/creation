
#include "EntityCreator.h"

#include "Entity.h"

#include "DataViewStateEntities.h"

#include "MainFrame.h"

namespace Creation
{
    /*
    EntityCreator::EntityCreator()
    {}

    EntityCreator::EntityCreator(::Atmos::Entity entity)
    {
        name = *GetCurrentEntities()->GetName(entity);
        position = *GetCurrentEntities()->GetPosition(entity);
        ::function::IterateRange<ComponentType, TupleIterator, SENSE, ACTION>(tuple, entity);
    }

    EntityCreator::EntityCreator(const String &name, const ::Atmos::GridPosition &position) : name(name), position(position)
    {}

    EntityCreator::EntityCreator(const EntityCreator &arg) : name(arg.name), position(arg.position), tuple(arg.tuple)
    {}

    EntityCreator::EntityCreator(EntityCreator &&arg) : name(std::move(arg.name)), position(std::move(arg.position)), tuple(std::move(arg.tuple))
    {}

    EntityCreator& EntityCreator::operator=(const EntityCreator &arg)
    {
        name = arg.name;
        position = arg.position;
        tuple = arg.tuple;
        return *this;
    }

    EntityCreator& EntityCreator::operator=(EntityCreator &&arg)
    {
        name = std::move(arg.name);
        position = std::move(arg.position);
        tuple = std::move(arg.tuple);
        return *this;
    }

    EntityCreator& EntityCreator::operator=(::Atmos::Entity entity)
    {
        *this = EntityCreator(entity);
        return *this;
    }

    ::Atmos::Entity EntityCreator::Create() const
    {
        auto entity = GetCurrentEntities()->CreateEntity(GetEntityNameDuplicates(name), position);
        ::function::IterateRange<ComponentType, CreatorImpl, SENSE, ACTION>(tuple, entity);
        GetMainFrame()->GetDataView()->GetState<DataViewStateEntities>()->Add(entity);
        return entity;
    }

    void EntityCreator::SetPosition(const Atmos::GridPosition &set)
    {
        position = set;
    }

    const String& EntityCreator::GetName() const
    {
        return name;
    }
    */
}