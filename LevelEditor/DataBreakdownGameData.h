#pragma once

#include "DataBreakdownGeneral.h"
#include "DataBreakdownSenses.h"
#include "DataBreakdownElement.h"
#include "DataBreakdownVariant.h"
#include "DataBreakdownRegistryReference.h"

#include "BuildPackageAction.h"

#include "DirectionData.h"

namespace Creation
{
    template<>
    class DataBreakdown<Build::Package<::Atmos::Direction>> : public DataBreakdownBase<Build::Package<::Atmos::Direction>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdownEnum<BuildT::ValueT> value;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::CharacterClassGroup>> : public DataBreakdownBase<Build::Package<::Atmos::CharacterClassGroup>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdownList<Build::Package<::Atmos::RegistryObjectReference<::Atmos::CharacterClass>>> classes;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Acumen>> : public DataBreakdownBase<Build::Package<::Atmos::Acumen>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<BuildT::ValueT>> value;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Act::Parameter>> : public DataBreakdownBase<Build::Package<::Atmos::Act::Parameter>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Variant>> variant;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Act::Action>> : public DataBreakdownBase<Build::Package<::Atmos::Act::Action>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<BuildT::ID>> id;
        DataBreakdownList<Build::Package<BuildT::Parameter>> parameters;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::ResourceAttributeTable>>> : public DataBreakdownBase<Build::Package<::Atmos::GlobalContext<::Atmos::ResourceAttributeTable>>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> health;
        DataBreakdown<Build::Package<::Atmos::Name>> mana;
        DataBreakdown<Build::Package<::Atmos::Name>> acumen;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::EntryPackage> : public DataBreakdownBase<Build::Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::EntryPackage>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> name;
        DataBreakdown<Build::Package<::Atmos::Name>> niceName;
        DataBreakdown<Build::Package<::Atmos::Name>> opposing;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>> : public DataBreakdownBase<Build::Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdownList<PackageT::EntryPackage> entries;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::Element>>::EntryPackage> : public DataBreakdownBase<Build::Package<::Atmos::GlobalContext<::Atmos::Element>>::EntryPackage>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> name;
        DataBreakdown<Build::Package<::Atmos::Name>> niceName;
        DataBreakdown<Build::Package<::Atmos::Element>> opposing;
        DataBreakdown<Build::Package<::Atmos::Name>> statName;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::GlobalContext<::Atmos::Element>>> : public DataBreakdownBase<Build::Package<::Atmos::GlobalContext<::Atmos::Element>>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> neutral;
        DataBreakdownList<PackageT::EntryPackage> entries;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };
}