#pragma once

#include "DataBreakdownBase.h"
#include "DataBreakdownGeneral.h"

#include "BuildPackageVariant.h"

#include "VariantData.h"

namespace Creation
{
    template<>
    class DataBreakdown<Build::Package<::Atmos::Variant>> : public DataBreakdownBase<Build::Package<::Atmos::Variant>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        typedef DataBreakdown<Build::Package<::Atmos::VariantTraits<BuildT::Type::BOOL>::T>> BoolBreakdownT;
        typedef DataBreakdown<Build::Package<::Atmos::VariantTraits<BuildT::Type::INT_8>::T>> Int8BreakdownT;
        typedef DataBreakdown<Build::Package<::Atmos::VariantTraits<BuildT::Type::INT_16>::T>> Int16BreakdownT;
        typedef DataBreakdown<Build::Package<::Atmos::VariantTraits<BuildT::Type::INT_32>::T>> Int32BreakdownT;
        typedef DataBreakdown<Build::Package<::Atmos::VariantTraits<BuildT::Type::INT_64>::T>> Int64BreakdownT;
        typedef DataBreakdown<Build::Package<::Atmos::VariantTraits<BuildT::Type::UINT_8>::T>> UInt8BreakdownT;
        typedef DataBreakdown<Build::Package<::Atmos::VariantTraits<BuildT::Type::UINT_16>::T>> UInt16BreakdownT;
        typedef DataBreakdown<Build::Package<::Atmos::VariantTraits<BuildT::Type::UINT_32>::T>> UInt32BreakdownT;
        typedef DataBreakdown<Build::Package<::Atmos::VariantTraits<BuildT::Type::UINT_64>::T>> UInt64BreakdownT;
        typedef DataBreakdown<Build::Package<::Atmos::VariantTraits<BuildT::Type::FLOAT>::T>> FloatBreakdownT;
        typedef DataBreakdown<Build::Package<::Atmos::VariantTraits<BuildT::Type::DOUBLE>::T>> DoubleBreakdownT;
        typedef DataBreakdown<Build::Package<::Atmos::VariantTraits<BuildT::Type::FIXED_64>::T>> Fixed64BreakdownT;
        typedef DataBreakdown<Build::Package<::Atmos::VariantTraits<BuildT::Type::STRING>::T>> StringBreakdownT;
        typedef DataBreakdown<Build::Package<::Atmos::VariantTraits<BuildT::Type::POSITION_3D>::T>> Position3DBreakdownT;
        typedef DataBreakdown<Build::Package<::Atmos::VariantTraits<BuildT::Type::GRID_POSITION>::T>> GridPositionBreakdownT;

        union U
        {
            BoolBreakdownT boolProp;
            Int8BreakdownT int8Prop;
            Int16BreakdownT int16Prop;
            Int32BreakdownT int32Prop;
            Int64BreakdownT int64Prop;
            UInt8BreakdownT uint8Prop;
            UInt16BreakdownT uint16Prop;
            UInt32BreakdownT uint32Prop;
            UInt64BreakdownT uint64Prop;
            FloatBreakdownT floatProp;
            DoubleBreakdownT doubleProp;
            Fixed64BreakdownT fixed64Prop;
            StringBreakdownT stringProp;
            Position3DBreakdownT position3DProp;
            GridPositionBreakdownT gridPositionProp;
            U();
            U(BoolBreakdownT &&boolProp);
            U(Int8BreakdownT &&int8Prop);
            U(Int16BreakdownT &&int16Prop);
            U(Int32BreakdownT &&int32Prop);
            U(Int64BreakdownT &&int64Prop);
            U(UInt8BreakdownT &&uint8Prop);
            U(UInt16BreakdownT &&uint16Prop);
            U(UInt32BreakdownT &&uint32Prop);
            U(UInt64BreakdownT &&uint64Prop);
            U(FloatBreakdownT &&floatProp);
            U(DoubleBreakdownT &&doubleProp);
            U(Fixed64BreakdownT &&fixed64Prop);
            U(StringBreakdownT &&stringProp);
            U(Position3DBreakdownT &&position3DProp);
            U(GridPositionBreakdownT &&gridPositionProp);
            ~U() {}
        };
    private:
        Build::Package<std::underlying_type<::Atmos::Variant::Type>::type> typePackage;

        U u;

        void SetupImpl() override final;

        void OnTypeChanged(const DataBreakdownEditArgs &args);

        void AddAllChildren();
        void SubscribeEvents();
        void MoveU(DataBreakdown &&arg);

        BoolBreakdownT MakeBoolBreakdown();
        Int8BreakdownT MakeInt8Breakdown();
        Int16BreakdownT MakeInt16Breakdown();
        Int32BreakdownT MakeInt32Breakdown();
        Int64BreakdownT MakeInt64Breakdown();
        UInt8BreakdownT MakeUInt8Breakdown();
        UInt16BreakdownT MakeUInt16Breakdown();
        UInt32BreakdownT MakeUInt32Breakdown();
        UInt64BreakdownT MakeUInt64Breakdown();
        FloatBreakdownT MakeFloatBreakdown();
        DoubleBreakdownT MakeDoubleBreakdown();
        Fixed64BreakdownT MakeFixed64Breakdown();
        StringBreakdownT MakeStringBreakdown();
        Position3DBreakdownT MakePosition3DBreakdown();
        GridPositionBreakdownT MakeGridPositionBreakdown();
    public:
        DataBreakdownEnum<BuildT::Type> type;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);

        DataBreakdownCommon* GetData();
        const DataBreakdownCommon* GetData() const;
    };
}