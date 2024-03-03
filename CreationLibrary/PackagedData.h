#pragma once

#include <memory>
#include <typeindex>

namespace Creation::Editing
{
    class PackagedData
    {
    public:
        PackagedData();
        template<class Data>
        PackagedData(Data data);

        template<class Data>
        [[nodiscard]] Data As();

        [[nodiscard]] std::type_index Type() const;
    private:
        std::type_index type;
    private:
        class Base
        {
        public:
            virtual ~Base() = 0;
        };

        std::unique_ptr<Base> base;

        template<class Data>
        class Derived final : public Base
        {
        public:
            Data data;
        public:
            Derived(Data data);
        };
    };

    template<class Data>
    PackagedData::PackagedData(Data data) :
        type(typeid(Data)), base(std::make_unique<Derived<Data>>(data))
    {}

    template<class Data>
    Data PackagedData::As()
    {
        return base ? reinterpret_cast<Derived<Data>*>(base.get())->data : Data{};
    }

    template<class Data>
    PackagedData::Derived<Data>::Derived(Data data) :
        data(data)
    {}
}