
#include "ImageRegistry.h"

namespace Creation
{
    ImageRegistry& ImageRegistry::Instance()
    {
        static ImageRegistry instance;
        return instance;
    }

    void ImageRegistry::Add(ImageAsset &&add)
    {
        Instance().map.emplace(add.GetFileName(), std::move(add));
    }

    void ImageRegistry::Remove(const FileName &remove)
    {
        Instance().map.erase(remove);
    }

    const ImageAsset* ImageRegistry::Find(const FileName &name)
    {
        auto &map = Instance().map;
        auto found = map.find(name);
        if (found == map.end())
            return nullptr;

        return &found->second;
    }
}