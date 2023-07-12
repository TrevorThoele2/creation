
#include "QuestData.h"

namespace Creation
{
    Data<::Atmos::Quest::Part::Type>::Data(ValueT value, StringT &&string) : DataBase(value, std::move(string))
    {}

    DataManager<::Atmos::Quest::Part::Type>::DataManager()
    {
        Add(DataT(DataT::ValueT::WAR, "War"));
        Add(DataT(DataT::ValueT::DIPLOMACY, "Diplomacy"));
        Add(DataT(DataT::ValueT::GATHER, "Gather"));
        Add(DataT(DataT::ValueT::EXPLORE, "Explore"));
        Add(DataT(DataT::ValueT::MISC, "Misc"));
    }
}