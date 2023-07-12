
#include "EquipSlotData.h"

namespace Creation
{
    Data<::Atmos::EquipSlot>::Data(ValueT value, StringT &&string) : DataBase(value, std::move(string))
    {}

    DataManager<::Atmos::EquipSlot>::DataManager()
    {
        Add(DataT(Atmos::EquipSlot::MAINHAND, "Main Hand"));
        Add(DataT(Atmos::EquipSlot::OFFHAND, "Off Hand"));
        Add(DataT(Atmos::EquipSlot::HEAD, "Head"));
        Add(DataT(Atmos::EquipSlot::BODY, "Body"));
        Add(DataT(Atmos::EquipSlot::LEGS, "Legs"));
        Add(DataT(Atmos::EquipSlot::FEET, "Feet"));
        Add(DataT(Atmos::EquipSlot::HANDS, "Hands"));
        Add(DataT(Atmos::EquipSlot::BACK, "Back"));
        Add(DataT(Atmos::EquipSlot::AMMO, "Ammo"));
    }
}