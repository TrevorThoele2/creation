#pragma once

#include "DataBreakdownAssetReference.h"
#include "DataBreakdownNameValuePair.h"
#include "DataBreakdownGeneral.h"

namespace Creation
{
    template<>
    class DataBreakdown<Build::Package<::Atmos::Script::Instance>> : public DataBreakdownBase<Build::Package<::Atmos::Script::Instance>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::AssetReference<::Atmos::ScriptModuleBase>>> asset;

        DataBreakdownList<Build::Package<::Atmos::ScriptItem>> globalItems;

        DataBreakdown<Build::Package<BuildT::SymbolName>> executeName;
        DataBreakdownList<Build::Package<::Atmos::ScriptItem>> parameters;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };
}