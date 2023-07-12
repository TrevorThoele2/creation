#pragma once

#include <memory>
#include <Atmos/FilePath.h>

namespace Creation
{
    class ImageAsset
    {
    public:
        typedef ::Atmos::FileName FileName;
        typedef unsigned int Dimension;
    public:
        class Data
        {
        private:
            ImageAsset *owner;
            friend ImageAsset;
        public:
            virtual ~Data() = 0 {}
            ImageAsset* GetOwner() const;
        };
    private:
        Dimension width, height;
        FileName name;

        std::unique_ptr<Data> data;

        ImageAsset(const ImageAsset &arg) = delete;
        ImageAsset& operator=(const ImageAsset &arg) = delete;

        void SetData(Data *set);
        void SetData(std::unique_ptr<Data> &&set);
    public:
        ImageAsset(Data *data, const FileName &fileName, Dimension width, Dimension height);
        ImageAsset(ImageAsset &&arg);
        ImageAsset& operator=(ImageAsset &&arg);

        bool operator==(const ImageAsset &arg) const;
        bool operator!=(const ImageAsset &arg) const;

        Data* GetData() const;
        template<class DataT>
        DataT* GetData() const;

        Dimension GetWidth() const;
        Dimension GetHeight() const;
        const FileName& GetFileName() const;
    };

    template<class DataT>
    DataT* ImageAsset::GetData() const
    {
        return static_cast<DataT*>(data.get());
    }
}