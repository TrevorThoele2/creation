#pragma once

#include "DataBreakdownBase.h"

#include "BuildPackageOffset.h"

namespace Creation
{
    template<class T, class Position>
    class DataBreakdown<Build::Package<::Atmos::ObjectOffsetHandle<T, Position>>> : public DataBreakdownBase<Build::Package<::Atmos::ObjectOffsetHandle<T, Position>>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<typename BuildT::ObjectT>> wrapped;
        DataBreakdown<Build::Package<typename ::Atmos::IDManagerBase::ID>> id;
        DataBreakdown<Build::Package<typename BuildT::OffsetValueT>> xOffset;
        DataBreakdown<Build::Package<typename BuildT::OffsetValueT>> yOffset;
        DataBreakdown<Build::Package<typename BuildT::OffsetValueT>> zOffset;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<class T, class Position>
    void DataBreakdown<Build::Package<::Atmos::ObjectOffsetHandle<T, Position>>>::AddAllChildren()
    {
        AddChild(wrapped);
        AddChild(id);
        AddChild(xOffset);
        AddChild(yOffset);
        AddChild(zOffset);
    }

    template<class T, class Position>
    void DataBreakdown<Build::Package<::Atmos::ObjectOffsetHandle<T, Position>>>::SetupImpl()
    {
        wrapped.Setup(Get()->wrapped);
        id.Setup(Get()->id);
        xOffset.Setup(Get()->xOffset);
        yOffset.Setup(Get()->yOffset);
        zOffset.Setup(Get()->zOffset);
    }

    template<class T, class Position>
    DataBreakdown<Build::Package<::Atmos::ObjectOffsetHandle<T, Position>>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        wrapped("Wrapped", this),
        id("ID", this),
        xOffset("X Offset", this),
        yOffset("Y Offset", this),
        zOffset("Z Offset", this)
    {
        AddAllChildren();
        wrapped.SetAddCategory(false);
        wrapped.SetAddTreePiece(false);
    }

    template<class T, class Position>
    DataBreakdown<Build::Package<::Atmos::ObjectOffsetHandle<T, Position>>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        wrapped(std::move(arg.wrapped), this),
        id(std::move(arg.id), this),
        xOffset(std::move(arg.xOffset), this),
        yOffset(std::move(arg.yOffset), this),
        zOffset(std::move(arg.zOffset), this)
    {
        AddAllChildren();
    }

    template<class T, class Position>
    DataBreakdown<Build::Package<::Atmos::ObjectOffsetHandle<T, Position>>>& DataBreakdown<Build::Package<::Atmos::ObjectOffsetHandle<T, Position>>>::operator=(DataBreakdown &&arg)
    {
        PackageBase::operator=(std::move(arg));
        id = std::move(arg.id);
        wrapped = std::move(arg.wrapped);
        xOffset = std::move(arg.xOffset);
        yOffset = std::move(arg.yOffset);
        zOffset = std::move(arg.zOffset);
        return *this;
    }
}