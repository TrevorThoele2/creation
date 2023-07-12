#pragma once

#include "DataBreakdownGeneral.h"
#include "DataBreakdownAssetReference.h"
#include "DataBreakdownColor.h"

#include "SpriteView.h"

namespace Creation
{
    typedef DataBreakdown<Build::Package<::Atmos::AssetReference<::Atmos::Material>>> TestT;
    extern TestT t;

    template<>
    class DataBreakdown<Build::Package<::Atmos::Sprite>> : public DataBreakdownBase<Build::Package<::Atmos::Sprite>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        std::vector<::Atmos::EventAnyConnection> connections;

        void OnEdited(const DataBreakdownEditArgs &args);

        void SubscribeEvents();
        void ClearEvents();
        void UpdateDisplay();

        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::AssetReference<::Atmos::Material>>> material;
        DataBreakdown<Build::Package<::Atmos::AssetReference<::Atmos::ShaderAsset>>> shaderPatch;
        DataBreakdown<Build::Package<BuildT::Index>> index;
        DataBreakdown<Build::Package<::Atmos::Color>> color;
        DataBreakdown<Build::Package<::Atmos::Size3D::ValueT>> xScaler;
        DataBreakdown<Build::Package<::Atmos::Size3D::ValueT>> yScaler;
        DataBreakdown<Build::Package<::Atmos::Size3D::ValueT>> zScaler;
        DataBreakdown<Build::Package<::Atmos::Angle>> xRotation;
        DataBreakdown<Build::Package<::Atmos::Angle>> yRotation;
        DataBreakdown<Build::Package<::Atmos::Angle>> zRotation;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Sound>> : public DataBreakdownBase<Build::Package<::Atmos::Sound>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::AssetReference<::Atmos::AudioAsset>>> audio;
        DataBreakdown<Build::Package<::Atmos::Position3D>> position;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };
}