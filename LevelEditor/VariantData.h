#pragma once

#include "DataBase.h"
#include <Atmos/Variant.h>

namespace Creation
{
    template<>
    class Data<::Atmos::Variant::Type> : public DataBase<::Atmos::Variant::Type>
    {
    public:
        Data(ValueT value, StringT &&string);
    };

    template<>
    class DataManager<::Atmos::Variant::Type> : public DataManagerBase<::Atmos::Variant::Type, DataManager<::Atmos::Variant::Type>>
    {
    private:
        friend BaseT;

        DataManager();
    };
}