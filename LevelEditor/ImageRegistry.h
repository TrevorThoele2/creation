#pragma once

#include <unordered_map>

#include "ImageAsset.h"

#include <Atmos/FilePath.h>

namespace Creation
{
    class ImageRegistry
    {
    public:
        typedef ::Atmos::FileName FileName;
    private:
        ImageRegistry() = default;
        ImageRegistry(const ImageRegistry &arg) = delete;
        ImageRegistry& operator=(const ImageRegistry &arg) = delete;
        std::unordered_map<FileName, ImageAsset> map;
    public:
        static ImageRegistry& Instance();

        static void Add(ImageAsset &&add);
        static void Remove(const FileName &remove);
        static const ImageAsset* Find(const FileName &name);
    };
}