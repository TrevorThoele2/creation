
#include "BuildPackageAsset.h"

namespace Creation
{
    namespace Build
    {
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::AudioAsset>)
        {
            scribe(id);
            scribe(path);
        }

        Package<::Atmos::AudioAsset>::Package(Package &&arg) : id(std::move(arg.id)), path(std::move(arg.path))
        {}

        Package<::Atmos::AudioAsset>& Package<::Atmos::AudioAsset>::operator=(Package &&arg)
        {
            id = std::move(arg.id);
            path = std::move(arg.path);
            return *this;
        }

        bool Package<::Atmos::AudioAsset>::operator==(const Package &arg) const
        {
            return id == arg.id && path == arg.path;
        }

        bool Package<::Atmos::AudioAsset>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        ::Atmos::AssetReference<Package<::Atmos::AudioAsset>::BuildT> Package<::Atmos::AudioAsset>::Build() const
        {
            if (id.Build() == BuildT::nullID)
                return ::Atmos::AssetRegistry<BuildT>::Register(path.Build()).second;
            else
                return ::Atmos::AssetRegistry<BuildT>::Register(id.Build(), path.Build()).second;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::ImageAsset>)
        {
            scribe(id);
            scribe(path);
            scribe(columns);
            scribe(rows);
        }

        Package<::Atmos::ImageAsset>::Package()
        {
            columns.value = 1;
            rows.value = 1;
        }

        Package<::Atmos::ImageAsset>::Package(Package &&arg) : id(std::move(arg.id)), path(std::move(arg.path)), columns(std::move(arg.columns)), rows(std::move(arg.rows))
        {}

        Package<::Atmos::ImageAsset>& Package<::Atmos::ImageAsset>::operator=(Package &&arg)
        {
            id = std::move(arg.id);
            path = std::move(arg.path);
            return *this;
        }

        bool Package<::Atmos::ImageAsset>::operator==(const Package &arg) const
        {
            return id == arg.id && path == arg.path;
        }

        bool Package<::Atmos::ImageAsset>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        ::Atmos::AssetReference<Package<::Atmos::ImageAsset>::BuildT> Package<::Atmos::ImageAsset>::Build() const
        {
            if (id.Build() == BuildT::nullID)
                return ::Atmos::AssetRegistry<BuildT>::Register(path.Build(), columns.Build(), rows.Build()).second;
            else
                return ::Atmos::AssetRegistry<BuildT>::Register(id.Build(), path.Build(), columns.Build(), rows.Build()).second;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Material>)
        {
            scribe(id);
            scribe(name);

            scribe(xVisual, xNormal, xHeight);
            scribe(yVisual, yNormal, yHeight);
            scribe(zVisual, zNormal, zHeight);

            scribe(shader);
        }

        Package<::Atmos::Material>::Package(Package &&arg) : id(std::move(arg.id)), name(std::move(arg.name)),
            xVisual(std::move(arg.xVisual)), xNormal(std::move(arg.xNormal)), xHeight(std::move(arg.xHeight)),
            yVisual(std::move(arg.yVisual)), yNormal(std::move(arg.yNormal)), yHeight(std::move(arg.yHeight)),
            zVisual(std::move(arg.zVisual)), zNormal(std::move(arg.zNormal)), zHeight(std::move(arg.zHeight)),
            shader(std::move(arg.shader))
        {}

        Package<::Atmos::Material>& Package<::Atmos::Material>::operator=(Package &&arg)
        {
            id = std::move(arg.id);
            name = std::move(arg.name);
            xVisual = std::move(arg.xVisual);
            xNormal = std::move(arg.xNormal);
            xHeight = std::move(arg.xHeight);
            yVisual = std::move(arg.yVisual);
            yNormal = std::move(arg.yNormal);
            yHeight = std::move(arg.yHeight);
            zVisual = std::move(arg.zVisual);
            zNormal = std::move(arg.zNormal);
            zHeight = std::move(arg.zHeight);
            shader = std::move(arg.shader);
            return *this;
        }

        bool Package<::Atmos::Material>::operator==(const Package &arg) const
        {
            return id == arg.id && name == arg.name &&
                xVisual == arg.xVisual && xNormal == arg.xNormal && xHeight == arg.xHeight &&
                yVisual == arg.yVisual && yNormal == arg.yNormal && yHeight == arg.yHeight &&
                zNormal == arg.zNormal && zHeight == arg.zHeight && zVisual == arg.zVisual &&
                shader == arg.shader;
        }

        bool Package<::Atmos::Material>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        ::Atmos::AssetReference<Package<::Atmos::Material>::BuildT> Package<::Atmos::Material>::Build() const
        {
            ::Atmos::AssetReference<BuildT> ret;
            if (id.Build() == BuildT::nullID)
                ret = ::Atmos::AssetRegistry<BuildT>::Register(name.Build()).second;
            else
                ret = ::Atmos::AssetRegistry<BuildT>::Register(id.Build(), name.Build()).second;

            auto casted = const_cast<BuildT*>(ret.Get());
            casted->SetXVisual(xVisual.Build());
            casted->SetXNormal(xNormal.Build());
            casted->SetXHeight(xHeight.Build());
            casted->SetYVisual(yVisual.Build());
            casted->SetYNormal(xNormal.Build());
            casted->SetYHeight(xHeight.Build());
            casted->SetZVisual(zVisual.Build());
            casted->SetZNormal(xNormal.Build());
            casted->SetZHeight(xHeight.Build());
            
            casted->SetShader(shader.Build());
            return ret;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::ScriptModuleBase>)
        {
            scribe(id);
            scribe(path);
            scribe(isModule);
            scribe(dependencies);
        }

        Package<::Atmos::ScriptModuleBase>::Package(Package &&arg) : id(std::move(arg.id)), path(std::move(arg.path)), isModule(std::move(arg.isModule)), dependencies(std::move(arg.dependencies))
        {}

        Package<::Atmos::ScriptModuleBase>& Package<::Atmos::ScriptModuleBase>::operator=(Package &&arg)
        {
            id = std::move(arg.id);
            path = std::move(arg.path);
            isModule = std::move(arg.isModule);
            dependencies = std::move(arg.dependencies);
            return *this;
        }

        bool Package<::Atmos::ScriptModuleBase>::operator==(const Package &arg) const
        {
            return id == arg.id && path == arg.path && isModule == arg.isModule && dependencies == arg.dependencies;
        }

        bool Package<::Atmos::ScriptModuleBase>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        ::Atmos::AssetReference<Package<::Atmos::ScriptModuleBase>::BuildT> Package<::Atmos::ScriptModuleBase>::Build() const
        {
            BuildT::Dependencies madeDependencies;
            for (auto &loop : dependencies.value)
                madeDependencies.push_back(const_cast<::Atmos::ScriptModule*>(static_cast<const ::Atmos::ScriptModule*>(loop.Build().Get())));

            if (isModule.Build())
            {
                if (id.Build() == BuildT::nullID)
                    return ::Atmos::AssetRegistry<BuildT>::RegisterModule(path.Build()).second;
                else
                    return ::Atmos::AssetRegistry<BuildT>::RegisterModule(id.Build(), path.Build()).second;
            }
            else
            {
                if (id.Build() == BuildT::nullID)
                    return ::Atmos::AssetRegistry<BuildT>::RegisterScript(std::move(madeDependencies), path.Build()).second;
                else
                    return ::Atmos::AssetRegistry<BuildT>::RegisterScript(id.Build(), std::move(madeDependencies), path.Build()).second;
            }
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::ShaderAsset>)
        {
            scribe(id);
            scribe(path);
        }

        Package<::Atmos::ShaderAsset>::Package(Package &&arg) : id(std::move(arg.id)), path(std::move(arg.path))
        {}

        Package<::Atmos::ShaderAsset>& Package<::Atmos::ShaderAsset>::operator=(Package &&arg)
        {
            id = std::move(arg.id);
            path = std::move(arg.path);
            return *this;
        }

        bool Package<::Atmos::ShaderAsset>::operator==(const Package &arg) const
        {
            return id == arg.id && path == arg.path;
        }

        bool Package<::Atmos::ShaderAsset>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        ::Atmos::AssetReference<Package<::Atmos::ShaderAsset>::BuildT> Package<::Atmos::ShaderAsset>::Build() const
        {
            if (id.Build() == BuildT::nullID)
                return ::Atmos::AssetRegistry<BuildT>::Register(path.Build()).second;
            else
                return ::Atmos::AssetRegistry<BuildT>::Register(id.Build(), path.Build()).second;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Script::Instance>)
        {
            scribe(globalItems);
            scribe(executeName);
            scribe(parameters);
        }

        Package<::Atmos::Script::Instance>::Package(Package &&arg) : globalItems(std::move(arg.globalItems)), executeName(std::move(arg.executeName)), parameters(std::move(arg.parameters))
        {}

        Package<::Atmos::Script::Instance> & Package<::Atmos::Script::Instance>::operator=(Package &&arg)
        {
            globalItems = std::move(arg.globalItems);
            executeName = std::move(arg.executeName);
            parameters = std::move(arg.parameters);
            return *this;
        }

        bool Package<::Atmos::Script::Instance>::operator==(const Package &arg) const
        {
            return globalItems == arg.globalItems && executeName == arg.executeName && parameters == arg.parameters;
        }

        bool Package<::Atmos::Script::Instance>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Script::Instance>::BuildT Package<::Atmos::Script::Instance>::Build() const
        {
            BuildT ret;
            auto &builtScript = asset.Build();
            if (!builtScript->IsScript())
                ::Atmos::ErrorHandler::Log("A script instance's script was a script module.",
                    ::Atmos::ErrorHandler::Severity::ERROR_SEVERE,
                    ::Atmos::ErrorHandler::NameValueVector{ ::Atmos::NameValuePair("Asset Name", asset.name.Build()) });
            ret.Set(*static_cast<const ::Atmos::Script*>(asset.Build().Get()));
            for (auto &loop : globalItems.value)
                ret.AddGlobalItem(loop.Build());
            ret.SetExecuteName(executeName.Build());
            for (auto &loop : parameters.value)
                ret.AddParameter(loop.Build());
            return ret;
        }
    }
}