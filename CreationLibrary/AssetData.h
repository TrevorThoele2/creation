#pragma once

#include "DataIncludes.h"
#include "FilePathData.h"
#include "StringData.h"

namespace Creation::Editing
{
    class AssetSelectorProperty : public TerminalProperty<String>
    {
    public:
        using RetrieveChoices = std::function<std::vector<String>()>;
    public:
        AssetSelectorProperty(
            const String& name,
            const String& label,
            wxPGProperty* parentProperty,
            wxPropertyGrid& grid,
            const NexusHistory& nexusHistory,
            UI& ui,
            const String& assetType,
            const RetrieveChoices& retrieveChoices);
        AssetSelectorProperty(AssetSelectorProperty&& arg) noexcept = default;
    protected:
        [[nodiscard]] DataT ValueFromProperty() const override;
        [[nodiscard]] wxVariant VariantFromData(const DataT& data) override;
    private:
        wxStringProperty* property = nullptr;
        String assetType;
        RetrieveChoices retrieveChoices;

        void OnButton();
    };

    template<class Data>
    class EditableAssetNexusCommon : public EditableNexusCommon<Data>
    {
    private:
        using BaseT = EditableNexusCommon<Data>;
    public:
        using DataT = typename BaseT::DataT;

        using BatchT = typename BaseT::BatchT;
    public:
        using BaseT::BaseT;

        using BaseT::CurrentData;

        using BaseT::Label;
    protected:
        using BaseT::ChangeLabel;

        void OnLabelChanged();

        [[nodiscard]] virtual String CalculateLabel(const DataT& data) const = 0;
    };

    template<class Data>
    void EditableAssetNexusCommon<Data>::OnLabelChanged()
    {
        const auto label = CalculateLabel(CurrentData());
        ChangeLabel(label);
    }

    [[nodiscard]] String FileAssetName(const File::Path& filePath);

    template<class AssetData, class Root>
    [[nodiscard]] std::vector<String> AllFileAssetNames(Root& root)
    {
        const auto children = root.Children();

        std::vector<String> returnValue;
        returnValue.reserve(children.size());
        for (auto& child : children)
        {
            const auto asset = dynamic_cast<Nexus<AssetData>*>(child);
            returnValue.push_back(FileAssetName(asset->CurrentData().filePath));
        }

        std::sort(returnValue.begin(), returnValue.end());

        return returnValue;
    }

    [[nodiscard]] std::vector<String> AllAudioAssetNames(UI& ui);
    [[nodiscard]] std::vector<String> AllFontAssetNames(UI& ui);
    [[nodiscard]] std::vector<String> AllImageAssetNames(UI& ui);
    [[nodiscard]] std::vector<String> AllMaterialAssetNames(UI& ui);
    [[nodiscard]] std::vector<String> AllScriptAssetNames(UI& ui);
    [[nodiscard]] std::vector<String> AllShaderAssetNames(UI& ui);
}