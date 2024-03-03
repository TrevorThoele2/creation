#pragma once

#include "AssetData.h"
#include <Atmos/AudioAsset.h>

#include "Settings.h"

#include <Inscription/FilePathScribe.h>

namespace Creation::Editing
{
    namespace Data
    {
        class AudioAsset
        {
        public:
            File::Path filePath;
        public:
            AudioAsset() = default;
            AudioAsset(const AudioAsset& arg) = default;
            AudioAsset& operator=(const AudioAsset& arg) = default;

            void Build(Build::Context& context) const;
        private:
            INSCRIPTION_ACCESS;
        };
    }

    template<>
    class NexusBatch<Data::AudioAsset> final : public NexusBatchCommon<Data::AudioAsset>
    {
    public:
        Property<File::Path> filePath;
    public:
        NexusBatch(wxPropertyGrid& grid, NexusHistory nexusHistory, UI& ui);
        NexusBatch(NexusBatch&& arg) noexcept;
    private:
        void SetupProperties();
    };

    template<>
    class Nexus<Data::AudioAsset> final : public EditableAssetNexusCommon<Data::AudioAsset>
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
    class Scribe<Creation::Editing::Data::AudioAsset> final
    {
    public:
        using ObjectT = Creation::Editing::Data::AudioAsset;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            if (format.IsOutput())
            {
                auto relative = std::filesystem::relative(object.filePath, Creation::settings.audioAssetPath);
                format("filePath", relative);
            }
            else
            {
                Atmos::File::Path relative;
                format("filePath", relative);

                object.filePath = Creation::settings.audioAssetPath / relative;
            }
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Editing::Data::AudioAsset, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Editing::Data::AudioAsset>;
    };
}