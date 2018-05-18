#pragma once

#include <optional>

#include "Field.h"
#include "Assets.h"
#include "FilePath.h"

#include <Inscription/InputTextArchive.h>
#include <Inscription/InputJsonFormat.h>
#include <Atmos/VersionUserContext.h>

namespace Creation::Build
{
    class InputFile
    {
    public:
        explicit InputFile(const File::Path& filePath);

        std::optional<Field> Field(Atmos::World::FieldID id);
        Assets Assets();
        [[nodiscard]] std::vector<Atmos::World::FieldID> AllIDs() const;
    private:
        Inscription::File::InputText file;
        Inscription::Archive::InputText archive;

        struct Data
        {
            Atmos::VersionUserContext versionUserContext;
            std::unordered_map<Atmos::World::FieldID, Creation::Field> fields;
            Creation::Assets assets;
        };

        Data data;
    private:
        void Load();
    private:
        INSCRIPTION_ACCESS;
    };
}

namespace Inscription
{
    template<>
    class Scribe<Creation::Build::InputFile::Data> final
    {
    public:
        using ObjectT = Creation::Build::InputFile::Data;
    public:
        void Scriven(ObjectT& object, Inscription::Format::Json& format);
    };

    template<class Format>
    struct ScribeTraits<Creation::Build::InputFile::Data, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Build::InputFile::Data>;
    };
}