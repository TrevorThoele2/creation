#pragma once

#include <unordered_set>
#include "Selectable.h"
#include "Optional.h"

namespace Creation
{
    class SelectionBase;
    class SelectionHandler
    {
    private:
        static std::unordered_set<SelectionBase*> selections;
    public:
        static void Add(SelectionBase &add);
        static void Remove(SelectionBase &remove);
        static void ClearAll();

        static void TemporaryDeconstruct();
        static void Reconstruct();
    };

    class SelectionBase
    {
    protected:
        SelectionBase();
        ~SelectionBase();
    public:
        virtual void Clear() = 0;
        virtual void TemporaryDeconstruct() = 0;
        virtual void Reconstruct() = 0;
    };

    template<class T>
    class SingleSelection : public SelectionBase
    {
    public:
        typedef Selectable<T> SelectableT;
    private:
        Optional<SelectableT> wrapped;

        SingleSelection(const SingleSelection &arg) = delete;
        SingleSelection& operator=(const SingleSelection &arg) = delete;
    public:
        SingleSelection() = default;
        SingleSelection(SingleSelection &&arg);
        SingleSelection& operator=(SingleSelection &&arg);

        explicit operator bool() const;

        SelectableT* operator->();
        const SelectableT* operator->() const;
        SelectableT& operator*();
        const SelectableT& operator*() const;
        SelectableT& Get();
        const SelectableT& Get() const;

        void Set(SelectableT &&set);
        void Reset();
        bool IsValid() const;

        void Clear() override;
        void TemporaryDeconstruct() override;
        void Reconstruct() override;
    };

    template<class T>
    SingleSelection<T>::SingleSelection(SingleSelection &&arg) : wrapped(std::move(arg.wrapped))
    {}

    template<class T>
    SingleSelection<T>& SingleSelection<T>::operator=(SingleSelection &&arg)
    {
        wrapped = std::move(arg.wrapped);
        return *this;
    }

    template<class T>
    SingleSelection<T>::operator bool() const
    {
        return IsValid();
    }

    template<class T>
    typename SingleSelection<T>::SelectableT* SingleSelection<T>::operator->()
    {
        return &Get();
    }

    template<class T>
    typename const SingleSelection<T>::SelectableT* SingleSelection<T>::operator->() const
    {
        return &Get();
    }

    template<class T>
    typename SingleSelection<T>::SelectableT& SingleSelection<T>::operator*()
    {
        return Get();
    }

    template<class T>
    typename const SingleSelection<T>::SelectableT& SingleSelection<T>::operator*() const
    {
        return Get();
    }

    template<class T>
    typename SingleSelection<T>::SelectableT& SingleSelection<T>::Get()
    {
        return wrapped.Get();
    }

    template<class T>
    typename const SingleSelection<T>::SelectableT& SingleSelection<T>::Get() const
    {
        return wrapped.Get();
    }

    template<class T>
    void SingleSelection<T>::Set(SelectableT &&set)
    {
        wrapped.Set(std::move(set));
    }

    template<class T>
    void SingleSelection<T>::Reset()
    {
        wrapped.Reset();
    }

    template<class T>
    bool SingleSelection<T>::IsValid() const
    {
        return wrapped.IsValid();
    }

    template<class T>
    void SingleSelection<T>::Clear()
    {
        Reset();
    }

    template<class T>
    void SingleSelection<T>::TemporaryDeconstruct()
    {
        if (IsValid())
            wrapped->Deselect();
    }

    template<class T>
    void SingleSelection<T>::Reconstruct()
    {
        if (IsValid())
            wrapped->Select();
    }

    template<class T>
    class Selection : public SelectionBase
    {
    public:
        typedef Selectable<T> SelectableT;
    private:
        typedef std::unordered_set<SelectableT> Container;
    private:
        template<class ItrT>
        class IteratorBase : public std::iterator<typename Container::iterator::iterator_category, SelectableT>
        {
        private:
            friend class Selection<T>;
        private:
            ItrT wrap;
            IteratorBase(ItrT wrap) : wrap(wrap) {}
        public:
            value_type& operator*() { return const_cast<SelectableT&>(*wrap); }
            value_type& operator->() { return const_cast<SelectableT&>(*wrap); }
            bool operator==(const IteratorBase &arg) const { return wrap == arg.wrap; }
            bool operator!=(const IteratorBase &arg) const { return !(*this == arg); }
            IteratorBase& operator++ () { wrap++; return *this; }
            IteratorBase operator++ (int) { auto save = *this; return ++wrap; return save; }
        };
    public:
        typedef IteratorBase<typename Container::iterator> iterator;
        typedef IteratorBase<typename Container::const_iterator> const_iterator;
        typedef typename Container::size_type size_type;
    private:
        Container container;
    public:
        bool Add(T *add);
        iterator Remove(iterator remove);
        void Clear() override;
        bool Empty() const;
        bool IsHere(SelectableT &check) const;
        bool IsHere(typename SelectableT::WrappedT &check) const;

        void TemporaryDeconstruct() override;
        void Reconstruct() override;

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        size_type size() const;
    };

    template<class T>
    bool Selection<T>::Add(T *add)
    {
        if (!add)
            return false;

        SelectableT made(*add);
        auto found = container.find(made);
        if (found != container.end())
            return false;

        made.Select();
        container.emplace(std::move(made));
        return true;
    }

    template<class T>
    typename Selection<T>::iterator Selection<T>::Remove(iterator remove)
    {
        return container.erase(remove.wrap);
    }

    template<class T>
    void Selection<T>::Clear()
    {
        for (auto &loop : *this)
            loop.Deselect();

        container.clear();
    }

    template<class T>
    bool Selection<T>::Empty() const
    {
        return container.empty();
    }

    template<class T>
    bool Selection<T>::IsHere(SelectableT &check) const
    {
        return container.find(check) != container.end();
    }

    template<class T>
    bool Selection<T>::IsHere(typename SelectableT::WrappedT &check) const
    {
        return container.find(check) != container.end();
    }

    template<class T>
    void Selection<T>::TemporaryDeconstruct()
    {
        for (auto &loop : container)
            const_cast<SelectableT&>(loop).Deselect();
    }

    template<class T>
    void Selection<T>::Reconstruct()
    {
        for (auto &loop : container)
            const_cast<SelectableT&>(loop).Select();
    }

    template<class T>
    typename Selection<T>::iterator Selection<T>::begin()
    {
        return container.begin();
    }

    template<class T>
    typename Selection<T>::iterator Selection<T>::end()
    {
        return container.end();
    }

    template<class T>
    typename Selection<T>::const_iterator Selection<T>::begin() const
    {
        return container.begin();
    }

    template<class T>
    typename Selection<T>::const_iterator Selection<T>::end() const
    {
        return container.end();
    }

    template<class T>
    typename Selection<T>::size_type Selection<T>::size() const
    {
        return container.size();
    }
}