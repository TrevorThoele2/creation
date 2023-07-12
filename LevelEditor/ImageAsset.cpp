
#include "ImageAsset.h"

namespace Creation
{
    void ImageAsset::SetData(Data *set)
    {
        if(data)
            data->owner = nullptr;
        data.reset(set);
        data->owner = this;
    }

    void ImageAsset::SetData(std::unique_ptr<Data> &&set)
    {
        if(data)
            data->owner = nullptr;
        data = std::move(set);
        data->owner = this;
    }

    ImageAsset::ImageAsset(Data *data, const FileName &fileName, Dimension width, Dimension height) : data(data), name(fileName), width(width), height(height)
    {}

    ImageAsset::ImageAsset(ImageAsset &&arg) : data(std::move(arg.data)), name(std::move(arg.name)), width(std::move(arg.width)), height(std::move(arg.height))
    {}

    ImageAsset& ImageAsset::operator=(ImageAsset &&arg)
    {
        data = std::move(arg.data);
        name = std::move(arg.name);
        width = std::move(arg.width);
        height = std::move(arg.height);
        return *this;
    }

    bool ImageAsset::operator==(const ImageAsset &arg) const
    {
        return data == arg.data && name == arg.name && width == arg.width && height == arg.height;
    }

    bool ImageAsset::operator!=(const ImageAsset &arg) const
    {
        return !(*this == arg);
    }

    ImageAsset::Data* ImageAsset::GetData() const
    {
        return data.get();
    }

    ImageAsset::Dimension ImageAsset::GetWidth() const
    {
        return width;
    }

    ImageAsset::Dimension ImageAsset::GetHeight() const
    {
        return height;
    }

    const ImageAsset::FileName& ImageAsset::GetFileName() const
    {
        return name;
    }
}