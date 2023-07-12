#pragma once

#include "DataBase.h"
#include <Atmos/Direction.h>

namespace Creation
{
    template<>
    class Data<::Atmos::Direction::ValueT> : public DataBase<::Atmos::Direction::ValueT>
    {
    public:
        Data(ValueT value, StringT &&string);
    };

    template<>
    class DataManager<::Atmos::Direction::ValueT> : public DataManagerBase<::Atmos::Direction::ValueT, DataManager<::Atmos::Direction::ValueT>>
    {
    private:
        friend BaseT;

        DataManager();
    };
}