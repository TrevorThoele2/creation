#include "AssetData.h"

#include "SelectAssetDialog.h"
#include "WithButtonEditor.h"
#include "EditingUI.h"

namespace Creation::Editing
{
    AssetSelectorProperty::AssetSelectorProperty(
        const String& name,
        const String& label,
        wxPGProperty* parentProperty,
        wxPropertyGrid& grid,
        const NexusHistory& nexusHistory,
        UI& ui,
        const String& assetType,
        const RetrieveChoices& retrieveChoices)
        :
        TerminalProperty<String>(
            label,
            new wxStringProperty(label, PropertyName(name, parentProperty)),
            parentProperty,
            grid,
            nexusHistory,
            ui),
        assetType(assetType),
        retrieveChoices(retrieveChoices)
    {
        property = static_cast<wxStringProperty*>(WxProperty());

        const auto editor = new WithButtonEditor();
        editor->SetOnButton([this]() { OnButton(); });
        property->SetEditor(editor);
    }

    auto AssetSelectorProperty::ValueFromProperty() const -> DataT
    {
        return String(property->GetValueAsString());
    }

    wxVariant AssetSelectorProperty::VariantFromData(const DataT& data)
    {
        return data;
    }

    void AssetSelectorProperty::OnButton()
    {
        const auto choices = retrieveChoices();

        SelectAssetDialog dialog(choices, WxProperty()->GetGrid(), assetType + " Assets");
        const auto choice = dialog.ShowModal() != wxID_CANCEL
            ? dialog.Selected()
            : std::optional<String>{};
        if (choice)
            SetPropertyValue(*choice);
    }

    std::vector<String> AllAudioAssetNames(UI& ui)
    {
        return AllFileAssetNames<Data::AudioAsset>(ui.AssetsRoot()->audioAssets);
    }

    std::vector<String> AllFontAssetNames(UI& ui)
    {
        return AllFileAssetNames<Data::FontAsset>(ui.AssetsRoot()->fontAssets);
    }

    std::vector<String> AllImageAssetNames(UI& ui)
    {
        return AllFileAssetNames<Data::ImageAsset>(ui.AssetsRoot()->imageAssets);
    }

    std::vector<String> AllMaterialAssetNames(UI& ui)
    {
        const auto children = ui.AssetsRoot()->materialAssets.Children();

        std::vector<String> returnValue;
        returnValue.reserve(children.size());
        for (auto& child : children)
        {
            const auto asset = dynamic_cast<Nexus<Data::MaterialAsset>*>(child);
            returnValue.push_back(FileAssetName(asset->CurrentData().name));
        }

        std::sort(returnValue.begin(), returnValue.end());

        return returnValue;
    }

    std::vector<String> AllScriptAssetNames(UI& ui)
    {
        return AllFileAssetNames<Data::ScriptAsset>(ui.AssetsRoot()->scriptAssets);
    }

    std::vector<String> AllShaderAssetNames(UI& ui)
    {
        return AllFileAssetNames<Data::ScriptAsset>(ui.AssetsRoot()->shaderAssets);
    }

    String FileAssetName(const File::Path& filePath)
    {
        return File::Path(filePath).filename().replace_extension().string();
    }
}