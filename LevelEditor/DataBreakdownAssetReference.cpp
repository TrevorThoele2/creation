
#include "DataBreakdownAssetReference.h"
#include "BuildPackageAsset.h"

namespace Creation
{
    Build::Package<::Atmos::RandomAccessSequence<AssetReferenceTraits<::Atmos::AudioAsset>::PackageT>>& AssetReferenceTraits<::Atmos::AudioAsset>::Sequence()
    {
        return CurrentWorld::globals.audioPackage;
    }

    String AssetReferenceTraits<::Atmos::AudioAsset>::StringGetter(const PackageT &package)
    {
        return package.path.Build().GetFileName();
    }

    Build::Package<::Atmos::RandomAccessSequence<AssetReferenceTraits<::Atmos::ImageAsset>::PackageT>>& AssetReferenceTraits<::Atmos::ImageAsset>::Sequence()
    {
        return CurrentWorld::globals.imagePackage;
    }

    String AssetReferenceTraits<::Atmos::ImageAsset>::StringGetter(const PackageT &package)
    {
        return package.path.Build().GetFileName();
    }

    Build::Package<::Atmos::RandomAccessSequence<AssetReferenceTraits<::Atmos::Material>::PackageT>>& AssetReferenceTraits<::Atmos::Material>::Sequence()
    {
        return CurrentWorld::globals.materialPackage;
    }

    String AssetReferenceTraits<::Atmos::Material>::StringGetter(const PackageT &package)
    {
        return package.name.Build();
    }

    Build::Package<::Atmos::RandomAccessSequence<AssetReferenceTraits<::Atmos::ScriptModuleBase>::PackageT>>& AssetReferenceTraits<::Atmos::ScriptModuleBase>::Sequence()
    {
        return CurrentWorld::globals.scriptPackage;
    }

    String AssetReferenceTraits<::Atmos::ScriptModuleBase>::StringGetter(const PackageT &package)
    {
        return package.path.Build().GetFileName();
    }

    Build::Package<::Atmos::RandomAccessSequence<AssetReferenceTraits<::Atmos::ShaderAsset>::PackageT>>& AssetReferenceTraits<::Atmos::ShaderAsset>::Sequence()
    {
        return CurrentWorld::globals.shaderPackage;
    }

    String AssetReferenceTraits<::Atmos::ShaderAsset>::StringGetter(const PackageT &package)
    {
        return package.path.Build().GetFileName();
    }
}