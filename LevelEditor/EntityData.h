#pragma once

#include "DataBase.h"
#include <Atmos/CharacterComponent.h>
#include <Atmos/ActionComponent.h>

namespace Creation
{
    template<>
    class Data<::Atmos::Ent::CharacterComponent::Type> : public DataBase<::Atmos::Ent::CharacterComponent::Type>
    {
    public:
        Data(ValueT value, StringT &&string);
    };

    template<>
    class DataManager<::Atmos::Ent::CharacterComponent::Type> : public DataManagerBase<::Atmos::Ent::CharacterComponent::Type, DataManager<::Atmos::Ent::CharacterComponent::Type>>
    {
    private:
        friend BaseT;

        DataManager();
    };

    template<>
    class Data<::Atmos::Ent::ActionComponent::Activator> : public DataBase<::Atmos::Ent::ActionComponent::Activator>
    {
    public:
        Data(ValueT value, StringT &&string);
    };

    template<>
    class DataManager<::Atmos::Ent::ActionComponent::Activator> : public DataManagerBase<::Atmos::Ent::ActionComponent::Activator, DataManager<::Atmos::Ent::ActionComponent::Activator>>
    {
    private:
        friend BaseT;

        DataManager();
    };

    template<>
    class Data<::Atmos::Ent::SenseComponent::ModulatorEntryType> : public DataBase<::Atmos::Ent::SenseComponent::ModulatorEntryType>
    {
    public:
        Data(ValueT value, StringT &&string);
    };

    template<>
    class DataManager<::Atmos::Ent::SenseComponent::ModulatorEntryType> : public DataManagerBase<::Atmos::Ent::SenseComponent::ModulatorEntryType, DataManager<::Atmos::Ent::SenseComponent::ModulatorEntryType>>
    {
    private:
        friend BaseT;

        DataManager();
    };
}