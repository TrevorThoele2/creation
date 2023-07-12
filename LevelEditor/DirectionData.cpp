
#include "DirectionData.h"

namespace Creation
{
    Data<::Atmos::Direction::ValueT>::Data(ValueT value, StringT &&string) : DataBase(value, std::move(string))
    {}

    DataManager<::Atmos::Direction::ValueT>::DataManager()
    {
        Add(DataT(Atmos::Direction::ValueT::UP, "Up"));
        Add(DataT(Atmos::Direction::ValueT::DOWN, "Down"));
        Add(DataT(Atmos::Direction::ValueT::LEFT, "Left"));
        Add(DataT(Atmos::Direction::ValueT::RIGHT, "Right"));
    }
}