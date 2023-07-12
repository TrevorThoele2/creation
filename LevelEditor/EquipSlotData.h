#pragma once

#include "DataBase.h"
#include <Atmos/EquipSlot.h>

namespace Creation
{
    template<>
    class Data<::Atmos::EquipSlot> : public DataBase<::Atmos::EquipSlot>
    {
    public:
        Data(ValueT value, StringT &&string);
    };

    template<>
    class DataManager<::Atmos::EquipSlot> : public DataManagerBase<::Atmos::EquipSlot, DataManager<::Atmos::EquipSlot>>
    {
    private:
        friend BaseT;

        DataManager();
    };
}