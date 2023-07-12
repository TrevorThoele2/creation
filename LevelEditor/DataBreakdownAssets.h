#pragma once

#include "DataBreakdownGeneral.h"
#include "DataBreakdownAssetReference.h"

#include "BuildPackageAsset.h"

#include "StringButtonProperty.h"

#include "WorldGlobals.h"
#include "CurrentWorld.h"

namespace Creation
{
    template<>
    class DataBreakdown<Build::Package<::Atmos::AudioAsset>> : public DataBreakdownBase<Build::Package<::Atmos::AudioAsset>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<BuildT::ID>> id;
        DataBreakdown<Build::Package<::Atmos::FilePath>> path;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::ImageAsset>> : public DataBreakdownBase<Build::Package<::Atmos::ImageAsset>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<BuildT::ID>> id;
        DataBreakdown<Build::Package<::Atmos::FilePath>> path;
        DataBreakdown<Build::Package<BuildT::GridDimension>> columns;
        DataBreakdown<Build::Package<BuildT::GridDimension>> rows;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Material>> : public DataBreakdownBase<Build::Package<::Atmos::Material>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<BuildT::ID>> id;
        DataBreakdown<Build::Package<::Atmos::Name>> name;

        DataBreakdown<Build::Package<::Atmos::AssetReference<::Atmos::ImageAsset>>> xVisual;
        DataBreakdown<Build::Package<::Atmos::AssetReference<::Atmos::ImageAsset>>> xNormal;
        DataBreakdown<Build::Package<::Atmos::AssetReference<::Atmos::ImageAsset>>> xHeight;
        DataBreakdown<Build::Package<::Atmos::AssetReference<::Atmos::ImageAsset>>> yVisual;
        DataBreakdown<Build::Package<::Atmos::AssetReference<::Atmos::ImageAsset>>> yNormal;
        DataBreakdown<Build::Package<::Atmos::AssetReference<::Atmos::ImageAsset>>> yHeight;
        DataBreakdown<Build::Package<::Atmos::AssetReference<::Atmos::ImageAsset>>> zVisual;
        DataBreakdown<Build::Package<::Atmos::AssetReference<::Atmos::ImageAsset>>> zNormal;
        DataBreakdown<Build::Package<::Atmos::AssetReference<::Atmos::ImageAsset>>> zHeight;

        DataBreakdown<Build::Package<::Atmos::AssetReference<::Atmos::ShaderAsset>>> shader;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::ScriptModuleBase>> : public DataBreakdownBase<Build::Package<::Atmos::ScriptModuleBase>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<BuildT::ID>> id;
        DataBreakdown<Build::Package<::Atmos::FilePath>> path;
        DataBreakdown<Build::Package<bool>> isModule;
        DataBreakdownList<Build::Package<::Atmos::AssetReference<::Atmos::ScriptModuleBase>>> dependencies;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::ShaderAsset>> : public DataBreakdownBase<Build::Package<::Atmos::ShaderAsset>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<BuildT::ID>> id;
        DataBreakdown<Build::Package<::Atmos::FilePath>> path;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };
}