
#include "EntityData.h"

namespace Creation
{
    Data<::Atmos::Ent::CharacterComponent::Type>::Data(ValueT value, StringT &&string) : DataBase(value, std::move(string))
    {}

    DataManager<::Atmos::Ent::CharacterComponent::Type>::DataManager()
    {
        Add(DataT(DataT::ValueT::PLAYER, "Player"));
        Add(DataT(DataT::ValueT::NPC, "NPC"));
    }

    Data<::Atmos::Ent::ActionComponent::Activator>::Data(ValueT value, StringT &&string) : DataBase(value, std::move(string))
    {}

    DataManager<::Atmos::Ent::ActionComponent::Activator>::DataManager()
    {
        Add(DataT(DataT::ValueT::ENTER_TILE, "Enter Tile"));
        Add(DataT(DataT::ValueT::USE_ON, "Use On"));
        Add(DataT(DataT::ValueT::ENTER_FIELD, "Enter Field"));
    }

    Data<::Atmos::Ent::SenseComponent::ModulatorEntryType>::Data(ValueT value, StringT &&string) : DataBase(value, std::move(string))
    {}

    DataManager<::Atmos::Ent::SenseComponent::ModulatorEntryType>::DataManager()
    {
        Add(DataT(DataT::ValueT::SPRITE, "Sprite"));
        Add(DataT(DataT::ValueT::SOUND, "Sound"));
        Add(DataT(DataT::ValueT::AV_EFFECT, "AV Effect"));
    }
}