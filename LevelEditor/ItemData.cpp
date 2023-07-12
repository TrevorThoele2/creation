
#include "ItemData.h"

namespace Creation
{
    Data<::Atmos::Item::Flag>::Data(ValueT value, StringT &&string) : DataBase(value, std::move(string))
    {}

    DataManager<::Atmos::Item::Flag>::DataManager()
    {
        Add(DataT(DataT::ValueT::KEY, "Key"));
        Add(DataT(DataT::ValueT::TEMPORARY, "Temporary"));
    }
}