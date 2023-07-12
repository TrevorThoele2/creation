
#include "DataBreakdownBase.h"

namespace Creation
{
    DataBreakdownCommon* DataBreakdownPreEditArgs::Handler() const
    {
        return handler;
    }

    Build::PackageBase* DataBreakdownPreEditArgs::Current() const
    {
        return current.get();
    }

    Build::PackageBase* DataBreakdownPreEditArgs::Proposed() const
    {
        return proposed.get();
    }

    void DataBreakdownPreEditArgs::Reject(bool set)
    {
        reject = set;
    }

    bool DataBreakdownPreEditArgs::Reject() const
    {
        return reject;
    }

    DataBreakdownCommon* DataBreakdownEditArgs::Handler() const
    {
        return handler;
    }

    Build::PackageBase* DataBreakdownEditArgs::Prev() const
    {
        return prev.get();
    }

    Build::PackageBase* DataBreakdownEditArgs::Current() const
    {
        return current.get();
    }

    DataBreakdownAddArgs::DataBreakdownAddArgs(DataBreakdownCommon &handler, DataBreakdownCommon *added) : handler(&handler), added(added)
    {}

    DataBreakdownCommon* DataBreakdownAddArgs::Handler() const
    {
        return handler;
    }

    DataBreakdownCommon* DataBreakdownAddArgs::Added() const
    {
        return added;
    }

    DataBreakdownPreRemoveArgs::DataBreakdownPreRemoveArgs(DataBreakdownCommon &handler, DataBreakdownCommon *toBeRemoved) : handler(&handler), toBeRemoved(toBeRemoved)
    {}

    DataBreakdownCommon* DataBreakdownPreRemoveArgs::Handler() const
    {
        return handler;
    }

    DataBreakdownCommon* DataBreakdownPreRemoveArgs::ToBeRemoved() const
    {
        return toBeRemoved;
    }

    DataBreakdownCommon* DataBreakdownPostRemoveArgs::Handler() const
    {
        return handler;
    }

    Build::PackageBase* DataBreakdownPostRemoveArgs::Package() const
    {
        return package.get();
    }
}