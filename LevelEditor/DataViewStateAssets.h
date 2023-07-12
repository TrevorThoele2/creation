#pragma once

#include <memory>
#include "DataViewState.h"
#include "DataBreakdownAssets.h"

namespace Creation
{
    class DataViewStateAssets : public DataViewState
    {
    public:
        static constexpr const Type type = Type::ASSETS;
    private:
        typedef DataBreakdownList<Build::Package<::Atmos::AudioAsset>> AudioBreakdown;
        typedef DataBreakdownList<Build::Package<::Atmos::ImageAsset>> ImageBreakdown;
        typedef DataBreakdownList<Build::Package<::Atmos::Material>> MaterialBreakdown;
        typedef DataBreakdownList<Build::Package<::Atmos::ScriptModuleBase>> ScriptBreakdown;
        typedef DataBreakdownList<Build::Package<::Atmos::ShaderAsset>> ShaderBreakdown;

        void OnImageCreated(const DataBreakdownAddArgs &args);
        void OnImageRemoved(const DataBreakdownPreRemoveArgs &args);
        void OnImageDimensionsEdited(const DataBreakdownEditArgs &args);
        void OnImagePathEdited(const DataBreakdownEditArgs &args);

        void OnMaterialCreated(const DataBreakdownAddArgs &args);
        void OnMaterialRemoved(const DataBreakdownPreRemoveArgs &args);
        void OnMaterialEdited(const DataBreakdownEditArgs &args);
        void OnMaterialNameEdited(const DataBreakdownEditArgs &args);
        void SetupMaterial(MaterialBreakdown::BreakdownT *breakdown, ::Atmos::Material *mat);
        void SetupMaterial(::Atmos::Material *setup, const ::Atmos::Material &from);

        void SetupBreakdowns();

        // DataViewState overrides
        void StartImpl() override final;
        void StopImpl() override final;

        void SelectImpl(wxTreeItemId id) override final;
        void DeselectImpl(wxTreeItemId id) override final;
        void DeselectAllImpl() override final;
        void AddImpl() override final;
        void RemoveImpl() override final;

        void CreateBreakdownsFromScratchImpl() override final;
        void DestroyBreakdownsImpl() override final;
        void CreateTreePiecesImpl() override final;
        void CreateEditorPropertiesImpl() override final;
        void DestroyEditorPropertiesImpl(bool destroyTreeItems) override final;

        Type GetTypeImpl() const override final;
    private:
        AudioBreakdown audios;
        ImageBreakdown images;
        MaterialBreakdown materials;
        ScriptBreakdown scripts;
        ShaderBreakdown shaders;
    public:
        Event<const DataBreakdownEditArgs&> onMaterialEdited;

        DataViewStateAssets(DataView *dataView);

        void SetAudios(const AudioBreakdown::ListT &set);
        void SetAudios(AudioBreakdown::ListT &&set);
        void SetImages(const ImageBreakdown::ListT &set);
        void SetImages(ImageBreakdown::ListT &&set);
        void SetMaterials(const MaterialBreakdown::ListT &set);
        void SetMaterials(MaterialBreakdown::ListT &&set);
        void SetScripts(const ScriptBreakdown::ListT &set);
        void SetScripts(ScriptBreakdown::ListT &&set);
        void SetShaders(const ShaderBreakdown::ListT &set);
        void SetShaders(ShaderBreakdown::ListT &&set);

        static String GetTreeString();
    };
}