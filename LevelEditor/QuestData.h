#pragma once

#include "DataBase.h"
#include <Atmos/Quest.h>

namespace Creation
{
    template<>
    class Data<::Atmos::Quest::Part::Type> : public DataBase<::Atmos::Quest::Part::Type>
    {
    public:
        Data(ValueT value, StringT &&string);
    };

    template<>
    class DataManager<::Atmos::Quest::Part::Type> : public DataManagerBase<::Atmos::Quest::Part::Type, DataManager<::Atmos::Quest::Part::Type>>
    {
    private:
        friend BaseT;

        DataManager();
    };
}