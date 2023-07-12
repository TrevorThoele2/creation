#pragma once

#include "BuildPackage.h"
#include "BuildPackageList.h"
#include "BuildPackageGeneral.h"
#include "BuildPackageNameValuePair.h"

#include <Atmos/AudioRegistry.h>
#include <Atmos/ImageRegistry.h>
#include <Atmos/MaterialRegistry.h>
#include <Atmos/ScriptRegistry.h>
#include <Atmos/ShaderRegistry.h>

namespace Creation
{
    namespace Build
    {
        template<>
        class Package<::Atmos::AudioAsset> : public PackageBase
        {
        public:
            typedef ::Atmos::AudioAsset BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<BuildT::ID> id;
            Package<::Atmos::FilePath> path;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            ::Atmos::AssetReference<BuildT> Build() const;
        };

        template<>
        class Package<::Atmos::ImageAsset> : public PackageBase
        {
        public:
            typedef ::Atmos::ImageAsset BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<BuildT::ID> id;
            Package<::Atmos::FilePath> path;
            Package<BuildT::GridDimension> columns;
            Package<BuildT::GridDimension> rows;

            Package();
            Package(const Package &arg) = default;
            Package(Package &&arg);
            Package& operator=(const Package &arg) = default;
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            ::Atmos::AssetReference<BuildT> Build() const;
            BUILD_PACKAGE_DEFAULT_CLONE;
        };

        template<>
        class Package<::Atmos::Material> : public PackageBase
        {
        public:
            typedef ::Atmos::Material BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<BuildT::ID> id;
            Package<::Atmos::Name> name;

            Package<::Atmos::AssetReference<::Atmos::ImageAsset>> xVisual;
            Package<::Atmos::AssetReference<::Atmos::ImageAsset>> xNormal;
            Package<::Atmos::AssetReference<::Atmos::ImageAsset>> xHeight;
            Package<::Atmos::AssetReference<::Atmos::ImageAsset>> yVisual;
            Package<::Atmos::AssetReference<::Atmos::ImageAsset>> yNormal;
            Package<::Atmos::AssetReference<::Atmos::ImageAsset>> yHeight;
            Package<::Atmos::AssetReference<::Atmos::ImageAsset>> zVisual;
            Package<::Atmos::AssetReference<::Atmos::ImageAsset>> zNormal;
            Package<::Atmos::AssetReference<::Atmos::ImageAsset>> zHeight;

            Package<::Atmos::AssetReference<::Atmos::ShaderAsset>> shader;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            ::Atmos::AssetReference<BuildT> Build() const;
        };

        template<>
        class Package<::Atmos::ScriptModuleBase> : public PackageBase
        {
        public:
            typedef ::Atmos::ScriptModuleBase BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<BuildT::ID> id;
            Package<::Atmos::FilePath> path;
            Package<bool> isModule;
            Package<::Atmos::RandomAccessSequence<Package<::Atmos::AssetReference<::Atmos::ScriptModuleBase>>>> dependencies;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            ::Atmos::AssetReference<BuildT> Build() const;
        };

        template<>
        class Package<::Atmos::ShaderAsset> : public PackageBase
        {
        public:
            typedef ::Atmos::ShaderAsset BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<BuildT::ID> id;
            Package<::Atmos::FilePath> path;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            ::Atmos::AssetReference<BuildT> Build() const;
        };

        template<>
        class Package<::Atmos::Script::Instance> : public PackageBase
        {
        public:
            typedef ::Atmos::Script::Instance BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::AssetReference<::Atmos::ScriptModuleBase>> asset;

            Package<::Atmos::RandomAccessSequence<Package<::Atmos::ScriptItem>>> globalItems;

            Package<BuildT::SymbolName> executeName;
            Package<::Atmos::RandomAccessSequence<Package<::Atmos::ScriptItem>>> parameters;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };
    }
}