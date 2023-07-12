
#include "DataBreakdownVariant.h"

namespace Creation
{
    DataBreakdown<Build::Package<::Atmos::Variant>>::U::U() : boolProp("Bool", nullptr)
    {}

    DataBreakdown<Build::Package<::Atmos::Variant>>::U::U(BoolBreakdownT &&boolProp) : boolProp(std::move(boolProp))
    {}

    DataBreakdown<Build::Package<::Atmos::Variant>>::U::U(Int8BreakdownT &&int8Prop) : int8Prop(std::move(int8Prop))
    {}

    DataBreakdown<Build::Package<::Atmos::Variant>>::U::U(Int16BreakdownT &&int16Prop) : int16Prop(std::move(int16Prop))
    {}

    DataBreakdown<Build::Package<::Atmos::Variant>>::U::U(Int32BreakdownT &&int32Prop) : int32Prop(std::move(int32Prop))
    {}

    DataBreakdown<Build::Package<::Atmos::Variant>>::U::U(Int64BreakdownT &&int64Prop) : int64Prop(std::move(int64Prop))
    {}

    DataBreakdown<Build::Package<::Atmos::Variant>>::U::U(UInt8BreakdownT &&uint8Prop) : uint8Prop(std::move(uint8Prop))
    {}

    DataBreakdown<Build::Package<::Atmos::Variant>>::U::U(UInt16BreakdownT &&uint16Prop) : uint16Prop(std::move(uint16Prop))
    {}

    DataBreakdown<Build::Package<::Atmos::Variant>>::U::U(UInt32BreakdownT &&uint32Prop) : uint32Prop(std::move(uint32Prop))
    {}

    DataBreakdown<Build::Package<::Atmos::Variant>>::U::U(UInt64BreakdownT &&uint64Prop) : uint64Prop(std::move(uint64Prop))
    {}

    DataBreakdown<Build::Package<::Atmos::Variant>>::U::U(FloatBreakdownT &&floatProp) : floatProp(std::move(floatProp))
    {}

    DataBreakdown<Build::Package<::Atmos::Variant>>::U::U(DoubleBreakdownT &&doubleProp) : doubleProp(std::move(doubleProp))
    {}

    DataBreakdown<Build::Package<::Atmos::Variant>>::U::U(Fixed64BreakdownT &&fixed64Prop) : fixed64Prop(std::move(fixed64Prop))
    {}

    DataBreakdown<Build::Package<::Atmos::Variant>>::U::U(StringBreakdownT &&stringProp) : stringProp(std::move(stringProp))
    {}

    DataBreakdown<Build::Package<::Atmos::Variant>>::U::U(Position3DBreakdownT &&position3DProp) : position3DProp(std::move(position3DProp))
    {}

    DataBreakdown<Build::Package<::Atmos::Variant>>::U::U(GridPositionBreakdownT &&gridPositionProp) : gridPositionProp(std::move(gridPositionProp))
    {}

    void DataBreakdown<Build::Package<::Atmos::Variant>>::SetupImpl()
    {
        type.Setup(typePackage);
    }

    void DataBreakdown<Build::Package<::Atmos::Variant>>::OnTypeChanged(const DataBreakdownEditArgs &args)
    {
        switch (type.GetAsEnum())
        {
        case ::Atmos::Variant::Type::BOOL:
            u.boolProp = MakeBoolBreakdown();
            break;
        case ::Atmos::Variant::Type::INT_8:
            u.int8Prop = MakeInt8Breakdown();
            break;
        case ::Atmos::Variant::Type::INT_16:
            u.int16Prop = MakeInt16Breakdown();
            break;
        case ::Atmos::Variant::Type::INT_32:
            u.int32Prop = MakeInt32Breakdown();
            break;
        case ::Atmos::Variant::Type::INT_64:
            u.int64Prop = MakeInt64Breakdown();
            break;
        case ::Atmos::Variant::Type::UINT_8:
            u.uint8Prop = MakeUInt8Breakdown();
            break;
        case ::Atmos::Variant::Type::UINT_16:
            u.uint16Prop = MakeUInt16Breakdown();
            break;
        case ::Atmos::Variant::Type::UINT_32:
            u.uint32Prop = MakeUInt32Breakdown();
            break;
        case ::Atmos::Variant::Type::UINT_64:
            u.uint64Prop = MakeUInt64Breakdown();
            break;
        case ::Atmos::Variant::Type::FLOAT:
            u.floatProp = MakeFloatBreakdown();
            break;
        case ::Atmos::Variant::Type::DOUBLE:
            u.doubleProp = MakeDoubleBreakdown();
            break;
        case ::Atmos::Variant::Type::FIXED_64:
            u.fixed64Prop = MakeFixed64Breakdown();
            break;
        case ::Atmos::Variant::Type::STRING:
            u.stringProp = MakeStringBreakdown();
            break;
        case ::Atmos::Variant::Type::POSITION_3D:
            u.position3DProp = MakePosition3DBreakdown();
            break;
        case ::Atmos::Variant::Type::GRID_POSITION:
            u.gridPositionProp = MakeGridPositionBreakdown();
            break;
        }
    }

    void DataBreakdown<Build::Package<::Atmos::Variant>>::AddAllChildren()
    {
        AddChild(type);
    }

    void DataBreakdown<Build::Package<::Atmos::Variant>>::SubscribeEvents()
    {
        type.edited.Subscribe(&DataBreakdown::OnTypeChanged, *this);
    }

    void DataBreakdown<Build::Package<::Atmos::Variant>>::MoveU(DataBreakdown &&arg)
    {
        type.Edit(*arg.type.Get());
        switch (type.GetAsEnum())
        {
        case ::Atmos::Variant::Type::BOOL:
            u.boolProp = std::move(arg.u.boolProp);
            break;
        case ::Atmos::Variant::Type::INT_8:
            u.int8Prop = std::move(arg.u.int8Prop);
            break;
        case ::Atmos::Variant::Type::INT_16:
            u.int16Prop = std::move(arg.u.int16Prop);
            break;
        case ::Atmos::Variant::Type::INT_32:
            u.int32Prop = std::move(arg.u.int32Prop);
            break;
        case ::Atmos::Variant::Type::INT_64:
            u.int64Prop = std::move(arg.u.int64Prop);
            break;
        case ::Atmos::Variant::Type::UINT_8:
            u.uint8Prop = std::move(arg.u.uint8Prop);
            break;
        case ::Atmos::Variant::Type::UINT_16:
            u.uint16Prop = std::move(arg.u.uint16Prop);
            break;
        case ::Atmos::Variant::Type::UINT_32:
            u.uint32Prop = std::move(arg.u.uint32Prop);
            break;
        case ::Atmos::Variant::Type::UINT_64:
            u.uint64Prop = std::move(arg.u.uint64Prop);
            break;
        case ::Atmos::Variant::Type::FLOAT:
            u.floatProp = std::move(arg.u.floatProp);
            break;
        case ::Atmos::Variant::Type::DOUBLE:
            u.doubleProp = std::move(arg.u.doubleProp);
            break;
        case ::Atmos::Variant::Type::FIXED_64:
            u.fixed64Prop = std::move(arg.u.fixed64Prop);
            break;
        case ::Atmos::Variant::Type::STRING:
            u.stringProp = std::move(arg.u.stringProp);
            break;
        case ::Atmos::Variant::Type::POSITION_3D:
            u.position3DProp = std::move(arg.u.position3DProp);
            break;
        case ::Atmos::Variant::Type::GRID_POSITION:
            u.gridPositionProp = std::move(arg.u.gridPositionProp);
            break;
        }
    }

    DataBreakdown<Build::Package<::Atmos::Variant>>::BoolBreakdownT DataBreakdown<Build::Package<::Atmos::Variant>>::MakeBoolBreakdown()
    {
        return BoolBreakdownT(DataManager<BuildT::Type>::FindFromValue(BuildT::Type::BOOL)->GetString(), this);
    }

    DataBreakdown<Build::Package<::Atmos::Variant>>::Int8BreakdownT DataBreakdown<Build::Package<::Atmos::Variant>>::MakeInt8Breakdown()
    {
        return Int8BreakdownT(DataManager<BuildT::Type>::FindFromValue(BuildT::Type::INT_8)->GetString(), this);
    }

    DataBreakdown<Build::Package<::Atmos::Variant>>::Int16BreakdownT DataBreakdown<Build::Package<::Atmos::Variant>>::MakeInt16Breakdown()
    {
        return Int16BreakdownT(DataManager<BuildT::Type>::FindFromValue(BuildT::Type::INT_16)->GetString(), this);
    }

    DataBreakdown<Build::Package<::Atmos::Variant>>::Int32BreakdownT DataBreakdown<Build::Package<::Atmos::Variant>>::MakeInt32Breakdown()
    {
        return Int32BreakdownT(DataManager<BuildT::Type>::FindFromValue(BuildT::Type::INT_32)->GetString(), this);
    }

    DataBreakdown<Build::Package<::Atmos::Variant>>::Int64BreakdownT DataBreakdown<Build::Package<::Atmos::Variant>>::MakeInt64Breakdown()
    {
        return Int64BreakdownT(DataManager<BuildT::Type>::FindFromValue(BuildT::Type::INT_64)->GetString(), this);
    }

    DataBreakdown<Build::Package<::Atmos::Variant>>::UInt8BreakdownT DataBreakdown<Build::Package<::Atmos::Variant>>::MakeUInt8Breakdown()
    {
        return UInt8BreakdownT(DataManager<BuildT::Type>::FindFromValue(BuildT::Type::UINT_8)->GetString(), this);
    }

    DataBreakdown<Build::Package<::Atmos::Variant>>::UInt16BreakdownT DataBreakdown<Build::Package<::Atmos::Variant>>::MakeUInt16Breakdown()
    {
        return UInt16BreakdownT(DataManager<BuildT::Type>::FindFromValue(BuildT::Type::UINT_16)->GetString(), this);
    }

    DataBreakdown<Build::Package<::Atmos::Variant>>::UInt32BreakdownT DataBreakdown<Build::Package<::Atmos::Variant>>::MakeUInt32Breakdown()
    {
        return UInt32BreakdownT(DataManager<BuildT::Type>::FindFromValue(BuildT::Type::UINT_32)->GetString(), this);
    }

    DataBreakdown<Build::Package<::Atmos::Variant>>::UInt64BreakdownT DataBreakdown<Build::Package<::Atmos::Variant>>::MakeUInt64Breakdown()
    {
        return UInt64BreakdownT(DataManager<BuildT::Type>::FindFromValue(BuildT::Type::UINT_64)->GetString(), this);
    }

    DataBreakdown<Build::Package<::Atmos::Variant>>::FloatBreakdownT DataBreakdown<Build::Package<::Atmos::Variant>>::MakeFloatBreakdown()
    {
        return FloatBreakdownT(DataManager<BuildT::Type>::FindFromValue(BuildT::Type::FLOAT)->GetString(), this);
    }

    DataBreakdown<Build::Package<::Atmos::Variant>>::DoubleBreakdownT DataBreakdown<Build::Package<::Atmos::Variant>>::MakeDoubleBreakdown()
    {
        return DoubleBreakdownT(DataManager<BuildT::Type>::FindFromValue(BuildT::Type::DOUBLE)->GetString(), this);
    }

    DataBreakdown<Build::Package<::Atmos::Variant>>::Fixed64BreakdownT DataBreakdown<Build::Package<::Atmos::Variant>>::MakeFixed64Breakdown()
    {
        return Fixed64BreakdownT(DataManager<BuildT::Type>::FindFromValue(BuildT::Type::FIXED_64)->GetString(), this);
    }

    DataBreakdown<Build::Package<::Atmos::Variant>>::StringBreakdownT DataBreakdown<Build::Package<::Atmos::Variant>>::MakeStringBreakdown()
    {
        return StringBreakdownT(DataManager<BuildT::Type>::FindFromValue(BuildT::Type::STRING)->GetString(), this);
    }

    DataBreakdown<Build::Package<::Atmos::Variant>>::Position3DBreakdownT DataBreakdown<Build::Package<::Atmos::Variant>>::MakePosition3DBreakdown()
    {
        return Position3DBreakdownT(DataManager<BuildT::Type>::FindFromValue(BuildT::Type::POSITION_3D)->GetString(), this);
    }

    DataBreakdown<Build::Package<::Atmos::Variant>>::GridPositionBreakdownT DataBreakdown<Build::Package<::Atmos::Variant>>::MakeGridPositionBreakdown()
    {
        return GridPositionBreakdownT(DataManager<BuildT::Type>::FindFromValue(BuildT::Type::GRID_POSITION)->GetString(), this);
    }

    DataBreakdown<Build::Package<::Atmos::Variant>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        type("Type", this)
    {
        AddAllChildren();
        SubscribeEvents();
    }

    DataBreakdown<Build::Package<::Atmos::Variant>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent), typePackage(std::move(arg.typePackage)),
        type(std::move(arg.type), this)
    {
        MoveU(std::move(arg));
        AddAllChildren();
        SubscribeEvents();
    }

    DataBreakdown<Build::Package<::Atmos::Variant>>& DataBreakdown<Build::Package<::Atmos::Variant>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        typePackage = std::move(arg.typePackage);
        type = std::move(arg.type);
        MoveU(std::move(arg));
        return *this;
    }

    DataBreakdownCommon* DataBreakdown<Build::Package<::Atmos::Variant>>::GetData()
    {
        switch (type.GetAsEnum())
        {
        case ::Atmos::Variant::Type::BOOL:
            return &u.boolProp;
        case ::Atmos::Variant::Type::INT_8:
            return &u.int8Prop;
        case ::Atmos::Variant::Type::INT_16:
            return &u.int16Prop;
        case ::Atmos::Variant::Type::INT_32:
            return &u.int32Prop;
        case ::Atmos::Variant::Type::INT_64:
            return &u.int64Prop;
        case ::Atmos::Variant::Type::UINT_8:
            return &u.uint8Prop;
        case ::Atmos::Variant::Type::UINT_16:
            return &u.uint16Prop;
        case ::Atmos::Variant::Type::UINT_32:
            return &u.uint32Prop;
        case ::Atmos::Variant::Type::UINT_64:
            return &u.uint64Prop;
        case ::Atmos::Variant::Type::FLOAT:
            return &u.floatProp;
        case ::Atmos::Variant::Type::DOUBLE:
            return &u.doubleProp;
        case ::Atmos::Variant::Type::FIXED_64:
            return &u.fixed64Prop;
        case ::Atmos::Variant::Type::STRING:
            return &u.stringProp;
        case ::Atmos::Variant::Type::POSITION_3D:
            return &u.position3DProp;
        case ::Atmos::Variant::Type::GRID_POSITION:
            return &u.gridPositionProp;
        }

        return nullptr;
    }

    const DataBreakdownCommon* DataBreakdown<Build::Package<::Atmos::Variant>>::GetData() const
    {
        switch (type.GetAsEnum())
        {
        case ::Atmos::Variant::Type::BOOL:
            return &u.boolProp;
        case ::Atmos::Variant::Type::INT_8:
            return &u.int8Prop;
        case ::Atmos::Variant::Type::INT_16:
            return &u.int16Prop;
        case ::Atmos::Variant::Type::INT_32:
            return &u.int32Prop;
        case ::Atmos::Variant::Type::INT_64:
            return &u.int64Prop;
        case ::Atmos::Variant::Type::UINT_8:
            return &u.uint8Prop;
        case ::Atmos::Variant::Type::UINT_16:
            return &u.uint16Prop;
        case ::Atmos::Variant::Type::UINT_32:
            return &u.uint32Prop;
        case ::Atmos::Variant::Type::UINT_64:
            return &u.uint64Prop;
        case ::Atmos::Variant::Type::FLOAT:
            return &u.floatProp;
        case ::Atmos::Variant::Type::DOUBLE:
            return &u.doubleProp;
        case ::Atmos::Variant::Type::FIXED_64:
            return &u.fixed64Prop;
        case ::Atmos::Variant::Type::STRING:
            return &u.stringProp;
        case ::Atmos::Variant::Type::POSITION_3D:
            return &u.position3DProp;
        case ::Atmos::Variant::Type::GRID_POSITION:
            return &u.gridPositionProp;
        }

        return nullptr;
    }
}