#include "OutputBuildFile.h"

#include <Atmos/FileHeader.h>
#include "BuildFileSignature.h"

namespace Creation::Build
{
    OutputFile::OutputFile(const File::Path& filePath) :
        file(filePath),
        archive(file)
    {}

    void OutputFile::Add(Field& save)
    {
        data.fields.emplace(save.id, save);
    }

    void OutputFile::Set(Assets& set)
    {
        data.assets = set;
    }

    void OutputFile::Save()
    {
        Inscription::Format::OutputJson format(data, archive);
    }
}

namespace Inscription
{
    void Scribe<Creation::Build::OutputFile::Data>::Scriven(ObjectT& object, Inscription::Format::Json& format)
    {
        if (format.IsOutput())
        {
            auto header = Atmos::FileHeader();
            header.expectedSignature = Creation::Build::fileSignature;

            format("header", header);

            object.versionUserContext.inscriptionVersion = header.inscriptionVersion;
            object.versionUserContext.clientVersion = header.clientVersion;

            format.EmplaceUserContext(&object.versionUserContext);

            format("fields", object.fields);
            format("assets", object.assets);
        }
    }
}