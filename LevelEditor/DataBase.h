#pragma once

#include <string>
#include <vector>

namespace Creation
{
    template<class T>
    class DataBase
    {
    public:
        typedef T ValueT;
        typedef std::string StringT;
    private:
        ValueT value;
        StringT string;
    public:
        DataBase(ValueT value, StringT &&string);
        ValueT GetValue() const;
        const StringT& GetString() const;
    };

    template<class T>
    DataBase<T>::DataBase(ValueT value, StringT &&string) : value(value), string(std::move(string))
    {}

    template<class T>
    typename DataBase<T>::ValueT DataBase<T>::GetValue() const
    {
        return value;
    }

    template<class T>
    typename const DataBase<T>::StringT& DataBase<T>::GetString() const
    {
        return string;
    }

    template<class T>
    class Data;

    template<class T, class Mixin>
    class DataManagerBase
    {
    public:
        typedef Data<T> DataT;
        typedef std::vector<DataT> Container;
    private:
        DataManagerBase(const DataManagerBase &arg) = delete;
        DataManagerBase& operator=(const DataManagerBase &arg) = delete;
    protected:
        typedef DataManagerBase BaseT;

        Container container;

        DataManagerBase() = default;
        static Mixin& Instance();

        void Add(DataT &&add);
    public:
        static Container& Get();

        static DataT* FindFromString(typename const DataT::StringT &string);
        static DataT* FindFromValue(typename DataT::ValueT value);
    };

    template<class T, class Mixin>
    Mixin& DataManagerBase<T, Mixin>::Instance()
    {
        static Mixin instance;
        return instance;
    }

    template<class T, class Mixin>
    void DataManagerBase<T, Mixin>::Add(DataT &&add)
    {
        container.push_back(std::move(add));
    }

    template<class T, class Mixin>
    typename DataManagerBase<T, Mixin>::Container& DataManagerBase<T, Mixin>::Get()
    {
        return Instance().container;
    }

    template<class T, class Mixin>
    typename DataManagerBase<T, Mixin>::DataT* DataManagerBase<T, Mixin>::FindFromString(typename const DataT::StringT &string)
    {
        for (auto &loop : Get())
        {
            if (loop.GetString() == string)
                return &loop;
        }

        return nullptr;
    }

    template<class T, class Mixin>
    typename DataManagerBase<T, Mixin>::DataT* DataManagerBase<T, Mixin>::FindFromValue(typename DataT::ValueT value)
    {
        for (auto &loop : Get())
        {
            if (loop.GetValue() == value)
                return &loop;
        }

        return nullptr;
    }

    template<class T>
    class DataManager;
}