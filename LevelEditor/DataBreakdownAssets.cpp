
#include "DataBreakdownAssets.h"

#include "Settings.h"
#include "InternalShaders.h"
#include <wx/filepicker.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/textdlg.h>

#include <Atmos/FalconScriptUtility.h>
#include <falcon/error.h>

namespace Creation
{
    void DataBreakdown<Build::Package<::Atmos::AudioAsset>>::AddAllChildren()
    {
        AddChild(path);
        AddChild(id);
    }

    void DataBreakdown<Build::Package<::Atmos::AudioAsset>>::SetupImpl()
    {
        id.Setup(Get()->id);
        path.Setup(Get()->path);
    }

    DataBreakdown<Build::Package<::Atmos::AudioAsset>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        id("ID", this),
        path("Path", this)
    {
        AddAllChildren();
        path.SetDefaultFilePath(Settings::GetAudioAssetPath());
        path.SetWildcard("WAV and OGG files (*.wav;*.ogg)|*.wav;*.ogg");
    }

    DataBreakdown<Build::Package<::Atmos::AudioAsset>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        id(std::move(arg.id), this),
        path(std::move(arg.path), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::AudioAsset>>& DataBreakdown<Build::Package<::Atmos::AudioAsset>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        id = std::move(arg.id);
        path = std::move(arg.path);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::ImageAsset>>::AddAllChildren()
    {
        AddChild(path);
        AddChild(id);
        AddChild(columns);
        AddChild(rows);
    }

    void DataBreakdown<Build::Package<::Atmos::ImageAsset>>::SetupImpl()
    {
        id.Setup(Get()->id);
        path.Setup(Get()->path);
        columns.Setup(Get()->columns);
        rows.Setup(Get()->rows);
    }

    DataBreakdown<Build::Package<::Atmos::ImageAsset>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        id("ID", this),
        path("Path", this),
        columns("Columns", this),
        rows("Rows", this)
    {
        AddAllChildren();
        path.SetDefaultFilePath(Settings::GetImageAssetPath());
        path.SetWildcard("PNG files (*.png)|*.png");
    }

    DataBreakdown<Build::Package<::Atmos::ImageAsset>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        id(std::move(arg.id), this),
        path(std::move(arg.path), this),
        columns(std::move(arg.columns), this),
        rows(std::move(arg.rows), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::ImageAsset>>& DataBreakdown<Build::Package<::Atmos::ImageAsset>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        id = std::move(arg.id);
        path = std::move(arg.path);
        columns = std::move(arg.columns);
        rows = std::move(arg.rows);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Material>>::AddAllChildren()
    {
        AddChild(name);
        AddChild(id);

        AddChild(xVisual);
        AddChild(xNormal);
        AddChild(xHeight);
        AddChild(yVisual);
        AddChild(yNormal);
        AddChild(yHeight);
        AddChild(zVisual);
        AddChild(zNormal);
        AddChild(zHeight);

        AddChild(shader);
    }

    void DataBreakdown<Build::Package<::Atmos::Material>>::SetupImpl()
    {
        id.Setup(Get()->id);
        name.Setup(Get()->name);

        xVisual.Setup(Get()->xVisual);
        xNormal.Setup(Get()->xNormal);
        xHeight.Setup(Get()->xHeight);
        yVisual.Setup(Get()->yVisual);
        yNormal.Setup(Get()->yNormal);
        yHeight.Setup(Get()->yHeight);
        zVisual.Setup(Get()->zVisual);
        zNormal.Setup(Get()->zNormal);
        zHeight.Setup(Get()->zHeight);

        shader.Setup(Get()->shader);
    }

    DataBreakdown<Build::Package<::Atmos::Material>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        id("ID", this),
        name("Name", this),
        xVisual("X Visual", this), xNormal("X Normal", this), xHeight("X Height", this),
        yVisual("Y Visual", this), yNormal("Y Normal", this), yHeight("Y Height", this),
        zVisual("Z Visual", this), zNormal("Z Normal", this), zHeight("Z Height", this),
        shader("Shader", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Material>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        id(std::move(arg.id), this),
        name(std::move(arg.name), this),
        xVisual(std::move(arg.xVisual), this), xNormal(std::move(arg.xNormal), this), xHeight(std::move(arg.xHeight), this),
        yVisual(std::move(arg.yVisual), this), yNormal(std::move(arg.yNormal), this), yHeight(std::move(arg.yHeight), this),
        zVisual(std::move(arg.zVisual), this), zNormal(std::move(arg.zNormal), this), zHeight(std::move(arg.zHeight), this),
        shader(std::move(arg.shader), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Material>>& DataBreakdown<Build::Package<::Atmos::Material>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
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

    void DataBreakdown<Build::Package<::Atmos::ScriptModuleBase>>::AddAllChildren()
    {
        AddChild(path);
        AddChild(id);
        AddChild(isModule);
        AddChild(dependencies);
    }

    void DataBreakdown<Build::Package<::Atmos::ScriptModuleBase>>::SetupImpl()
    {
        id.Setup(Get()->id);
        path.Setup(Get()->path);
        isModule.Setup(Get()->isModule);
        dependencies.Setup(Get()->dependencies);
    }

    DataBreakdown<Build::Package<::Atmos::ScriptModuleBase>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        id("ID", this),
        path("Path", this),
        isModule("Is Module", this),
        dependencies("Dependencies", this)
    {
        AddAllChildren();
        path.SetDefaultFilePath(Settings::GetScriptAssetPath());
        path.SetWildcard("FAL files (*.fal)|*.fal");
        dependencies.SetPrependEntryName("Dependency");
    }

    DataBreakdown<Build::Package<::Atmos::ScriptModuleBase>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        id(std::move(arg.id), this),
        path(std::move(arg.path), this),
        isModule(std::move(arg.isModule), this),
        dependencies(std::move(arg.dependencies), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::ScriptModuleBase>>& DataBreakdown<Build::Package<::Atmos::ScriptModuleBase>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        id = std::move(arg.id);
        path = std::move(arg.path);
        isModule = std::move(arg.isModule);
        dependencies = std::move(arg.dependencies);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::ShaderAsset>>::AddAllChildren()
    {
        AddChild(path);
        AddChild(id);
    }

    void DataBreakdown<Build::Package<::Atmos::ShaderAsset>>::SetupImpl()
    {
        id.Setup(Get()->id);
        path.Setup(Get()->path);
    }

    DataBreakdown<Build::Package<::Atmos::ShaderAsset>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        id("ID", this),
        path("Path", this)
    {
        AddAllChildren();
        path.SetDefaultFilePath(Settings::GetShaderAssetPath());
        path.SetWildcard("FX files (*.fx)|*.fx");
    }

    DataBreakdown<Build::Package<::Atmos::ShaderAsset>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        id(std::move(arg.id), this),
        path(std::move(arg.path), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::ShaderAsset>>& DataBreakdown<Build::Package<::Atmos::ShaderAsset>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        id = std::move(arg.id);
        path = std::move(arg.path);
        return *this;
    }
}