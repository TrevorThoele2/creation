
#include "VariantData.h"

namespace Creation
{
    Data<::Atmos::Variant::Type>::Data(ValueT value, StringT &&string) : DataBase(value, std::move(string))
    {}

    DataManager<::Atmos::Variant::Type>::DataManager()
    {
        Add(DataT(::Atmos::Variant::Type::BOOL, "Bool"));
        Add(DataT(::Atmos::Variant::Type::INT_8, "Int 8"));
        Add(DataT(::Atmos::Variant::Type::INT_16, "Int 16"));
        Add(DataT(::Atmos::Variant::Type::INT_32, "Int 32"));
        Add(DataT(::Atmos::Variant::Type::INT_64, "Int 64"));
        Add(DataT(::Atmos::Variant::Type::UINT_8, "Unsigned Int 8"));
        Add(DataT(::Atmos::Variant::Type::UINT_16, "Unsigned Int 16"));
        Add(DataT(::Atmos::Variant::Type::UINT_32, "Unsigned Int 32"));
        Add(DataT(::Atmos::Variant::Type::UINT_64, "Unsigned Int 64"));
        Add(DataT(::Atmos::Variant::Type::FLOAT, "Float"));
        Add(DataT(::Atmos::Variant::Type::DOUBLE, "Double"));
        Add(DataT(::Atmos::Variant::Type::FIXED_64, "Fixed 64"));
        Add(DataT(::Atmos::Variant::Type::STRING, "String"));
        Add(DataT(::Atmos::Variant::Type::POSITION_2D, "Position 2D"));
        Add(DataT(::Atmos::Variant::Type::POSITION_3D, "Position 3D"));
        Add(DataT(::Atmos::Variant::Type::GRID_POSITION, "Grid Position"));
        Add(DataT(::Atmos::Variant::Type::VECTOR, "Vector"));
    }
}