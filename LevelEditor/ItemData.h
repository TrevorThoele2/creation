#pragma once

#include "DataBase.h"
#include <Atmos/Item.h>

namespace Creation
{
    template<>
    class Data<::Atmos::Item::Flag> : public DataBase<::Atmos::Item::Flag>
    {
    public:
        Data(ValueT value, StringT &&string);
    };

    template<>
    class DataManager<::Atmos::Item::Flag> : public DataManagerBase<::Atmos::Item::Flag, DataManager<::Atmos::Item::Flag>>
    {
    private:
        friend BaseT;

        DataManager();
    };
}