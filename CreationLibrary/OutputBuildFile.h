#pragma once

#include "Field.h"
#include "Assets.h"
#include "FilePath.h"

#include <Inscription/OutputTextArchive.h>
#include <Inscription/OutputJsonFormat.h>
#include <Atmos/VersionUserContext.h>

namespace Creation::Build
{
    class OutputFile
    {
    public:
        explicit OutputFile(const File::Path& filePath);

        void Add(Field& save);
        void Set(Assets& set);
        void Save();
    private:
        Inscription::File::OutputText file;
        Inscription::Archive::OutputText archive;

        struct Data
        {
            Atmos::VersionUserContext versionUserContext;
            std::unordered_map<Atmos::World::FieldID, Field> fields;
            Assets assets;
        };

        Data data;
    private:
        INSCRIPTION_ACCESS;
    };
}

namespace Inscription
{
    template<>
    class Scribe<Creation::Build::OutputFile::Data> final
    {
    public:
        using ObjectT = Creation::Build::OutputFile::Data;
    public:
        void Scriven(ObjectT& object, Inscription::Format::Json& format);
    };

    template<class Format>
    struct ScribeTraits<Creation::Build::OutputFile::Data, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Build::OutputFile::Data>;
    };
}