#pragma once

#include <unordered_map>
#include "DataBase.h"
#include <Atmos/ActionParameter.h>
#include <Atmos/Action.h>
#include <Function/Enum.h>

namespace Creation
{
    template<>
    class Data<::Atmos::Action>
    {
    public:
        typedef std::string Name;
        typedef std::vector<Name> ParameterNames;
    private:
        ::Atmos::Action::ID id;
        Name name;
        std::vector<Name> parameterNames;
    public:
        Data(::Atmos::Action::ID id, Name &&name, std::vector<Name> &&parameterNames);
        ::Atmos::Action::ID GetID() const;
        const Name& GetName() const;
        const ParameterNames& GetParameters() const;
    };

    template<>
    class DataManager<::Atmos::Action>
    {
    public:
        typedef Data<::Atmos::Action> DataT;
        typedef std::unordered_map<::Atmos::Act::ID, DataT> Container;
    private:
        Container container;
        DataManager();

        static DataManager& Instance();
    public:
        static Container& Get();
        static DataT* FindFromString(const ::Atmos::String &string);
        static DataT* FindFromID(::Atmos::Act::ID id);
    };

    typedef ::function::EnumIterationTraits<Atmos::Variant::Type, Atmos::Variant::Type::BOOL, Atmos::Variant::Type::VECTOR> ActionParameterIterationTraits;
}