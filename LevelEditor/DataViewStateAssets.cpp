
#include "DataViewStateAssets.h"

#include "MainFrame.h"
#include "Viewport.h"
#include "CurrentWorld.h"
#include "TileViewManager.h"
#include <Atmos/ImageRegistry.h>

#include <wx/treectrl.h>

namespace Creation
{
    void DataViewStateAssets::OnImageCreated(const DataBreakdownAddArgs &args)
    {
        auto casted = static_cast<ImageBreakdown::BreakdownT*>(args.Added());
        ::Atmos::ImageRegistry::Register(casted->Get()->path.Build(), casted->Get()->columns.Build(), casted->Get()->rows.Build());
        casted->columns.edited.Subscribe(&DataViewStateAssets::OnImageDimensionsEdited, *this);
        casted->rows.edited.Subscribe(&DataViewStateAssets::OnImageDimensionsEdited, *this);
        casted->path.edited.Subscribe(&DataViewStateAssets::OnImagePathEdited, *this);
    }

    void DataViewStateAssets::OnImageRemoved(const DataBreakdownPreRemoveArgs &args)
    {
        ::Atmos::ImageRegistry::Remove(static_cast<ImageBreakdown::BreakdownT*>(args.ToBeRemoved())->Get()->path.Build().GetFileName());
    }

    void DataViewStateAssets::OnImageDimensionsEdited(const DataBreakdownEditArgs &args)
    {
        auto castedHandler = static_cast<ImageBreakdown::BreakdownT*>(static_cast<DataBreakdown<Build::Package<::Atmos::FilePath>>*>(args.Handler())->GetParent());
        auto found = const_cast<::Atmos::ImageAsset*>(::Atmos::ImageRegistry::Find(castedHandler->path.Get()->Build().GetFileName()).Get());
        if (!found)
            return;

        found->SetColumns(castedHandler->columns.Get()->Build());
        found->SetRows(castedHandler->rows.Get()->Build());
        TileViewManager::RecalculateAllSprites();
    }

    void DataViewStateAssets::OnImagePathEdited(const DataBreakdownEditArgs &args)
    {
        ::Atmos::ImageRegistry::Remove(static_cast<Build::Package<::Atmos::FilePath>*>(args.Prev())->Build().GetFileName());
        auto castedHandler = static_cast<ImageBreakdown::BreakdownT*>(static_cast<DataBreakdown<Build::Package<::Atmos::FilePath>>*>(args.Handler())->GetParent());
        ::Atmos::FilePath path(castedHandler->Get()->path.Build());
        auto registeredImage = ::Atmos::ImageRegistry::Register(path, castedHandler->Get()->columns.Build(), castedHandler->Get()->rows.Build()).second;
        // Patch the materials using that image
        for (auto &loop : CurrentWorld::globals.materialPackage.value)
        {
            if (loop.xVisual.name.Build() == path.GetFileName())
            {
                const_cast<::Atmos::Material*>(::Atmos::MaterialRegistry::Find(loop.name.Build()).Get())->SetXVisual(registeredImage);
            }
        }
    }

    void DataViewStateAssets::OnMaterialCreated(const DataBreakdownAddArgs &args)
    {
        auto casted = static_cast<MaterialBreakdown::BreakdownT*>(args.Added());
        auto focusedMat = const_cast<::Atmos::Material*>(::Atmos::MaterialRegistry::Register(casted->name.Get()->Build()).second.Get());
        if (focusedMat)
            SetupMaterial(casted, focusedMat);
        casted->edited.Subscribe(&DataViewStateAssets::OnMaterialEdited, *this);
        casted->name.edited.Subscribe(&DataViewStateAssets::OnMaterialNameEdited, *this);
    }

    void DataViewStateAssets::OnMaterialRemoved(const DataBreakdownPreRemoveArgs &args)
    {
        ::Atmos::ImageRegistry::Remove(static_cast<MaterialBreakdown::BreakdownT*>(args.ToBeRemoved())->Get()->name.Build());
    }

    void DataViewStateAssets::OnMaterialEdited(const DataBreakdownEditArgs &args)
    {
        auto casted = static_cast<MaterialBreakdown::BreakdownT*>(args.Handler());
        auto focusedMat = const_cast<::Atmos::Material*>(::Atmos::MaterialRegistry::Find(casted->name.Get()->Build()).Get());
        if(focusedMat)
            SetupMaterial(casted, focusedMat);

        onMaterialEdited(args);
    }

    void DataViewStateAssets::OnMaterialNameEdited(const DataBreakdownEditArgs &args)
    {
        auto prevName = static_cast<Build::Package<::Atmos::Name>*>(args.Prev());
        auto currentName = static_cast<Build::Package<::Atmos::Name>*>(args.Current());

        // Find previous entry
        auto found = ::Atmos::MaterialRegistry::Find(prevName->Build());
        // Make new entry and move previous entry into new one
        ::Atmos::Material *newMat = const_cast<::Atmos::Material*>(::Atmos::MaterialRegistry::Register(currentName->Build()).second.Get());
        if(found)
            SetupMaterial(newMat, *found);
        // Delete previous entry
        ::Atmos::MaterialRegistry::Remove(prevName->Build());
    }

    void DataViewStateAssets::SetupMaterial(MaterialBreakdown::BreakdownT *breakdown, ::Atmos::Material *mat)
    {
        mat->SetXVisual(breakdown->xVisual.Get()->Build());
        mat->SetXNormal(breakdown->xNormal.Get()->Build());
        mat->SetXHeight(breakdown->xHeight.Get()->Build());
        mat->SetYVisual(breakdown->yVisual.Get()->Build());
        mat->SetYNormal(breakdown->yNormal.Get()->Build());
        mat->SetYHeight(breakdown->yHeight.Get()->Build());
        mat->SetZVisual(breakdown->zVisual.Get()->Build());
        mat->SetZNormal(breakdown->zNormal.Get()->Build());
        mat->SetZHeight(breakdown->zHeight.Get()->Build());
        mat->SetShader(breakdown->shader.Get()->Build());
    }

    void DataViewStateAssets::SetupMaterial(::Atmos::Material *setup, const ::Atmos::Material &from)
    {
        setup->SetXVisual(from.GetXVisual());
        setup->SetXNormal(from.GetXNormal());
        setup->SetXHeight(from.GetXHeight());
        setup->SetYVisual(from.GetYVisual());
        setup->SetYNormal(from.GetYNormal());
        setup->SetYHeight(from.GetYHeight());
        setup->SetZVisual(from.GetZVisual());
        setup->SetZNormal(from.GetZNormal());
        setup->SetZHeight(from.GetZHeight());
        setup->SetShader(from.GetShader());
    }

    void DataViewStateAssets::SetupBreakdowns()
    {
        audios.Setup(CurrentWorld::globals.audioPackage);
        audios.SetNiceNameFunctions(AudioBreakdown::NiceNameExtractorFunction(static_cast<String(*)(AudioBreakdown::BreakdownT&)>([](AudioBreakdown::BreakdownT &breakdown) { return breakdown.path.Get()->Build().GetFileName().GetValue(); })),
            AudioBreakdown::NiceNameGetEventFunction(static_cast<Event<const DataBreakdownEditArgs&>*(*)(AudioBreakdown::BreakdownT&)>([](AudioBreakdown::BreakdownT &breakdown) -> Event<const DataBreakdownEditArgs&>* { return &breakdown.path.edited; })),
            AudioBreakdown::NameSetFunction(static_cast<void(*)(AudioBreakdown::BreakdownT&, const String&)>([](AudioBreakdown::BreakdownT &breakdown, const String &str) {})));
        audios.SetAddChildrenToProperties(false);
        images.Setup(CurrentWorld::globals.imagePackage);
        images.SetNiceNameFunctions(ImageBreakdown::NiceNameExtractorFunction(static_cast<String(*)(ImageBreakdown::BreakdownT&)>([](ImageBreakdown::BreakdownT &breakdown) { return breakdown.path.Get()->Build().GetFileName().GetValue(); })),
            ImageBreakdown::NiceNameGetEventFunction(static_cast<Event<const DataBreakdownEditArgs&>*(*)(ImageBreakdown::BreakdownT&)>([](ImageBreakdown::BreakdownT &breakdown) { return &breakdown.path.edited; })),
            ImageBreakdown::NameSetFunction(static_cast<void(*)(ImageBreakdown::BreakdownT&, const String&)>([](ImageBreakdown::BreakdownT &breakdown, const String &str) {})));
        images.SetAddChildrenToProperties(false);
        materials.Setup(CurrentWorld::globals.materialPackage);
        materials.SetNiceNameFunctions(MaterialBreakdown::NiceNameExtractorFunction(static_cast<String(*)(MaterialBreakdown::BreakdownT&)>([](MaterialBreakdown::BreakdownT &breakdown) { return breakdown.name.Get()->Build(); })),
            MaterialBreakdown::NiceNameGetEventFunction(static_cast<Event<const DataBreakdownEditArgs&>*(*)(MaterialBreakdown::BreakdownT&)>([](MaterialBreakdown::BreakdownT &breakdown) { return &breakdown.name.edited; })),
            MaterialBreakdown::NameSetFunction(static_cast<void(*)(MaterialBreakdown::BreakdownT&, const String&)>([](MaterialBreakdown::BreakdownT &breakdown, const String &str) {})));
        materials.SetAddChildrenToProperties(false);
        scripts.Setup(CurrentWorld::globals.scriptPackage);
        scripts.SetNiceNameFunctions(ScriptBreakdown::NiceNameExtractorFunction(static_cast<String(*)(ScriptBreakdown::BreakdownT&)>([](ScriptBreakdown::BreakdownT &breakdown) { return breakdown.path.Get()->Build().GetFileName().GetValue(); })),
            ScriptBreakdown::NiceNameGetEventFunction(static_cast<Event<const DataBreakdownEditArgs&>*(*)(ScriptBreakdown::BreakdownT&)>([](ScriptBreakdown::BreakdownT &breakdown) { return &breakdown.path.edited; })),
            ScriptBreakdown::NameSetFunction(static_cast<void(*)(ScriptBreakdown::BreakdownT&, const String&)>([](ScriptBreakdown::BreakdownT &breakdown, const String &str) {})));
        scripts.SetAddChildrenToProperties(false);
        shaders.Setup(CurrentWorld::globals.shaderPackage);
        shaders.SetNiceNameFunctions(ShaderBreakdown::NiceNameExtractorFunction(static_cast<String(*)(ShaderBreakdown::BreakdownT&)>([](ShaderBreakdown::BreakdownT &breakdown) { return breakdown.path.Get()->Build().GetFileName().GetValue(); })),
            ShaderBreakdown::NiceNameGetEventFunction(static_cast<Event<const DataBreakdownEditArgs&>*(*)(ShaderBreakdown::BreakdownT&)>([](ShaderBreakdown::BreakdownT &breakdown) { return &breakdown.path.edited; })),
            ShaderBreakdown::NameSetFunction(static_cast<void(*)(ShaderBreakdown::BreakdownT&, const String&)>([](ShaderBreakdown::BreakdownT &breakdown, const String &str) {})));
        shaders.SetAddChildrenToProperties(false);
    }

    void DataViewStateAssets::StartImpl()
    {
        
    }

    void DataViewStateAssets::StopImpl()
    {

    }

    void DataViewStateAssets::SelectImpl(wxTreeItemId id)
    {
        
    }

    void DataViewStateAssets::DeselectImpl(wxTreeItemId id)
    {
        
    }

    void DataViewStateAssets::DeselectAllImpl()
    {
        GetMainFrame()->GetDataView()->Deselect(audios.GetTreeItemID());
        GetMainFrame()->GetDataView()->Deselect(images.GetTreeItemID());
        GetMainFrame()->GetDataView()->Deselect(materials.GetTreeItemID());
        GetMainFrame()->GetDataView()->Deselect(scripts.GetTreeItemID());
        GetMainFrame()->GetDataView()->Deselect(shaders.GetTreeItemID());
    }

    void DataViewStateAssets::AddImpl()
    {

    }

    void DataViewStateAssets::RemoveImpl()
    {

    }

    void DataViewStateAssets::CreateBreakdownsFromScratchImpl()
    {
        audios.CreateBreakdowns();
        images.CreateBreakdowns();
        materials.CreateBreakdowns();
        scripts.CreateBreakdowns();
        shaders.CreateBreakdowns();
    }

    void DataViewStateAssets::DestroyBreakdownsImpl()
    {
        audios.DestroyBreakdowns();
        images.DestroyBreakdowns();
        materials.DestroyBreakdowns();
        scripts.DestroyBreakdowns();
        shaders.DestroyBreakdowns();
    }

    void DataViewStateAssets::CreateTreePiecesImpl()
    {
        audios.CreateTreePiece(TreeRootID());
        images.CreateTreePiece(TreeRootID());
        materials.CreateTreePiece(TreeRootID());
        scripts.CreateTreePiece(TreeRootID());
        shaders.CreateTreePiece(TreeRootID());
        Tree()->UnselectAll();
    }

    void DataViewStateAssets::CreateEditorPropertiesImpl()
    {
        audios.CreateEditorProperties(nullptr);
        images.CreateEditorProperties(nullptr);
        materials.CreateEditorProperties(nullptr);
        scripts.CreateEditorProperties(nullptr);
        shaders.CreateEditorProperties(nullptr);

        GetMainFrame()->GetDataView()->PropertyGrid()->FitColumns();
    }

    void DataViewStateAssets::DestroyEditorPropertiesImpl(bool destroyTreeItems)
    {
        audios.DestroyEditorProperties(destroyTreeItems);
        images.DestroyEditorProperties(destroyTreeItems);
        materials.DestroyEditorProperties(destroyTreeItems);
        scripts.DestroyEditorProperties(destroyTreeItems);
        shaders.DestroyEditorProperties(destroyTreeItems);
    }

    DataViewStateAssets::Type DataViewStateAssets::GetTypeImpl() const
    {
        return type;
    }

    DataViewStateAssets::DataViewStateAssets(DataView *dataView) : DataViewState(dataView),
        audios("Audio Registry", nullptr),
        images("Image Registry", nullptr),
        materials("Material Registry", nullptr),
        scripts("Script Registry", nullptr),
        shaders("Shader Registry", nullptr)
    {
        SetupBreakdowns();
        images.added.Subscribe(&DataViewStateAssets::OnImageCreated, *this);
        images.preRemove.Subscribe(&DataViewStateAssets::OnImageRemoved, *this);
        materials.added.Subscribe(&DataViewStateAssets::OnMaterialCreated, *this);
        materials.preRemove.Subscribe(&DataViewStateAssets::OnMaterialRemoved, *this);
        audios.SetPrependEntryName("Audio");
        images.SetPrependEntryName("Image");
        materials.SetPrependEntryName("Material");
        scripts.SetPrependEntryName("Script");
        shaders.SetPrependEntryName("Shader");
    }

    void DataViewStateAssets::SetAudios(const AudioBreakdown::ListT &set)
    {
        audios.Edit(set);
    }

    void DataViewStateAssets::SetAudios(AudioBreakdown::ListT &&set)
    {
        audios.Edit(std::move(set));
    }

    void DataViewStateAssets::SetImages(const ImageBreakdown::ListT &set)
    {
        images.Edit(set);
    }

    void DataViewStateAssets::SetImages(ImageBreakdown::ListT &&set)
    {
        images.Edit(std::move(set));
    }

    void DataViewStateAssets::SetMaterials(const MaterialBreakdown::ListT &set)
    {
        materials.Edit(set);
    }

    void DataViewStateAssets::SetMaterials(MaterialBreakdown::ListT &&set)
    {
        materials.Edit(std::move(set));
    }

    void DataViewStateAssets::SetScripts(const ScriptBreakdown::ListT &set)
    {
        scripts.Edit(set);
    }

    void DataViewStateAssets::SetScripts(ScriptBreakdown::ListT &&set)
    {
        scripts.Edit(std::move(set));
    }

    void DataViewStateAssets::SetShaders(const ShaderBreakdown::ListT &set)
    {
        shaders.Edit(set);
    }

    void DataViewStateAssets::SetShaders(ShaderBreakdown::ListT &&set)
    {
        shaders.Edit(std::move(set));
    }

    String DataViewStateAssets::GetTreeString()
    {
        return "Assets";
    }
}