#pragma once

#include "AssetData.h"
#include <Atmos/ScriptAsset.h>

#include "Settings.h"

namespace Creation::Editing
{
    namespace Data
    {
        class ScriptAsset
        {
        public:
            File::Path filePath;
        public:
            ScriptAsset() = default;
            ScriptAsset(const ScriptAsset& arg) = default;
            ScriptAsset& operator=(const ScriptAsset& arg) = default;

            void Build(Build::Context& context) const;
        private:
            INSCRIPTION_ACCESS;
        };
    }

    template<>
    class NexusBatch<Data::ScriptAsset> final : public NexusBatchCommon<Data::ScriptAsset>
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
    class Nexus<Data::ScriptAsset> final : public EditableAssetNexusCommon<Data::ScriptAsset>
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
    class Scribe<Creation::Editing::Data::ScriptAsset> final
    {
    public:
        using ObjectT = Creation::Editing::Data::ScriptAsset;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            if (format.IsOutput())
            {
                auto relative = std::filesystem::relative(object.filePath, Creation::settings.scriptAssetPath);
                format("filePath", relative);
            }
            else
            {
                Atmos::File::Path relative;
                format("filePath", relative);

                object.filePath = Creation::settings.scriptAssetPath / relative;
            }
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Editing::Data::ScriptAsset, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Editing::Data::ScriptAsset>;
    };
}