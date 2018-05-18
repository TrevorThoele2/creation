#include "InputBuildFile.h"

#include <Atmos/FileHeader.h>
#include "BuildFileSignature.h"

namespace Creation::Build
{
    InputFile::InputFile(const File::Path& filePath) :
        file(filePath),
        archive(file)
    {
        Load();
    }

    std::optional<Field> InputFile::Field(Atmos::World::FieldID id)
    {
        auto found = data.fields.find(id);
        return found == data.fields.end() ? std::optional<Creation::Field>{} : found->second;
    }

    Assets InputFile::Assets()
    {
        return data.assets;
    }

    std::vector<Atmos::World::FieldID> InputFile::AllIDs() const
    {
        std::vector<Atmos::World::FieldID> returnValue;
        for (auto& field : data.fields)
            returnValue.push_back(field.first);
        return returnValue;
    }

    void InputFile::Load()
    {
        Inscription::Format::InputJson format(data, archive);
    }
}

namespace Inscription
{
    void Scribe<Creation::Build::InputFile::Data>::Scriven(ObjectT& object, Inscription::Format::Json& format)
    {
        if (format.IsInput())
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