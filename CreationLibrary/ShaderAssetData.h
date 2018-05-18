#pragma once

#include "AssetData.h"
#include <Atmos/ShaderAsset.h>

#include "StringData.h"

#include "Settings.h"

namespace Creation::Editing
{
    namespace Data
    {
        class ShaderAsset
        {
        public:
            File::Path filePath;
        public:
            ShaderAsset() = default;
            ShaderAsset(const File::Path& filePath);
            ShaderAsset(const ShaderAsset& arg) = default;
            ShaderAsset& operator=(const ShaderAsset& arg) = default;

            void Build(Build::Context& context) const;
        private:
            INSCRIPTION_ACCESS;
        };
    }

    template<>
    class NexusBatch<Data::ShaderAsset> final : public NexusBatchCommon<Data::ShaderAsset>
    {
    public:
        Property<File::Path> filePath;
    public:
        NexusBatch(wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui);
        NexusBatch(NexusBatch&& arg) noexcept;
    private:
        void SetupProperties();
    };

    template<>
    class WorldElement<Data::ShaderAsset> final : public WorldElementCommon<Data::ShaderAsset>
    {
    public:
        WorldElement(Nexus& nexus, Arca::Reliquary& reliquary);
        WorldElement(WorldElement&& arg) noexcept = default;
        ~WorldElement();
    protected:
        void OnDataChanged(DataT data) override;
    private:
        using Object = Atmos::Asset::Shader;
        using Index = Arca::Index<Object>;

        Index object;

        Index CreateObject(DataT data);
        void DestroyObject(Index index);
    private:
        [[nodiscard]] static Arca::Index<Atmos::Asset::Shader> CreateAtmos(
            Data::ShaderAsset data, Arca::Reliquary& reliquary);
    };

    template<>
    class Nexus<Data::ShaderAsset> final : public EditableAssetNexusCommon<Data::ShaderAsset>
    {
    public:
        Nexus<File::Path> filePath;
    public:
        Nexus(
            DataT& data,
            NexusNode* parent,
            NexusHistory nexusHistory,
            UI& ui,
            Arca::Reliquary& reliquary);
        Nexus(Nexus&& arg, NexusNode* parent) noexcept;
        Nexus(Nexus&& arg) noexcept = default;
    protected:
        [[nodiscard]] String CalculateLabel(const DataT& data) const override;
    private:
        void SetupChildren();
    };
}

namespace Inscription
{
    template<>
    class Scribe<Creation::Editing::Data::ShaderAsset> final
    {
    public:
        using ObjectT = Creation::Editing::Data::ShaderAsset;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            if (format.IsOutput())
            {
                auto relative = std::filesystem::relative(object.filePath, Creation::settings.shaderAssetPath);
                format("filePath", relative);
            }
            else
            {
                Atmos::File::Path relative;
                format("filePath", relative);

                object.filePath = Creation::settings.shaderAssetPath / relative;
            }
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Editing::Data::ShaderAsset, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Editing::Data::ShaderAsset>;
    };
}