
#include "InternalShaders.h"
#include <Atmos/ShaderRegistry.h>

namespace Creation
{
    std::vector<InternalShaders::FilePath> InternalShaders::filePaths;

    InternalShaders& InternalShaders::Instance()
    {
        static InternalShaders instance;
        return instance;
    }

    void InternalShaders::Add(FilePath &&path)
    {
        filePaths.push_back(std::move(path));
    }

    void InternalShaders::ConstructAll()
    {
        ID id = startID;
        for (auto &loop : filePaths)
        {
            Atmos::ShaderRegistry::Register(id, loop);
            ++id;
        }
    }

    void InternalShaders::DeconstructAll()
    {
        for (auto &loop : filePaths)
            Atmos::ShaderRegistry::Remove(loop);
    }
}