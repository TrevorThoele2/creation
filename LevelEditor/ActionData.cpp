
#include "ActionData.h"

namespace Creation
{
    Data<::Atmos::Action>::Data(::Atmos::Action::ID id, Name &&name, std::vector<Name> &&parameterNames) : id(id), name(std::move(name)), parameterNames(std::move(parameterNames))
    {}

    ::Atmos::Action::ID Data<::Atmos::Action>::GetID() const
    {
        return id;
    }

    const Data<::Atmos::Action>::Name& Data<::Atmos::Action>::GetName() const
    {
        return name;
    }

    const Data<::Atmos::Action>::ParameterNames& Data<::Atmos::Action>::GetParameters() const
    {
        return parameterNames;
    }

    DataManager<::Atmos::Action>::DataManager()
    {
        typedef DataT::Name Name;
        typedef DataT::ParameterNames ParameterNames;
        // 1 (Talk to)
        {
            ParameterNames parameters;
            parameters.push_back("Entity Name");

            container.emplace(1, DataT(1, "Talk To", std::move(parameters)));
        }
    }

    DataManager<::Atmos::Action>& DataManager<::Atmos::Action>::Instance()
    {
        static DataManager instance;
        return instance;
    }

    DataManager<::Atmos::Action>::Container& DataManager<::Atmos::Action>::Get()
    {
        return Instance().container;
    }

    DataManager<::Atmos::Action>::DataT* DataManager<::Atmos::Action>::FindFromString(const ::Atmos::String &string)
    {
        for (auto &loop : Get())
        {
            if (loop.second.GetName() == string)
                return &loop.second;
        }

        return nullptr;
    }

    DataManager<::Atmos::Action>::DataT* DataManager<::Atmos::Action>::FindFromID(::Atmos::Act::ID id)
    {
        auto &container = Get();
        auto found = container.find(id);
        if (found == container.end())
            return nullptr;
        else
            return &found->second;
    }
}