#pragma once

#include <type_traits>

namespace Creation
{
    template<class Wrap>
    class SelectableBase
    {
    public:
        typedef Wrap WrappedT;
    private:
        WrappedT *wrapped;
        bool selected;

        virtual void SelectImpl() = 0;
        virtual void DeselectImpl() = 0;

        SelectableBase(const SelectableBase &arg) = delete;
        SelectableBase& operator=(const SelectableBase &arg) = delete;
    public:
        SelectableBase(WrappedT &wrap) : wrapped(&wrap), selected(false) {}
        SelectableBase(SelectableBase &&arg);
        virtual ~SelectableBase() = 0 {}
        SelectableBase& operator=(SelectableBase &&arg);
        bool operator==(const SelectableBase &arg) const;
        bool operator!=(const SelectableBase &arg) const;

        WrappedT& operator*();
        WrappedT& operator*() const;
        WrappedT* operator->();
        WrappedT* operator->() const;
        WrappedT& GetWrapped();
        const WrappedT& GetWrapped() const;

        void Select();
        void Deselect();
        bool IsSelected() const;
    };

    template<class Wrap>
    SelectableBase<Wrap>::SelectableBase(SelectableBase &&arg) : wrapped(std::move(arg.wrapped)), selected(arg.selected)
    {}

    template<class Wrap>
    SelectableBase<Wrap>& SelectableBase<Wrap>::operator=(SelectableBase &&arg)
    {
        wrapped = std::move(arg.wrapped);
        selected = arg.selected;
        return *this;
    }

    template<class Wrap>
    bool SelectableBase<Wrap>::operator==(const SelectableBase &arg) const
    {
        return wrapped == arg.wrapped;
    }

    template<class Wrap>
    bool SelectableBase<Wrap>::operator!=(const SelectableBase &arg) const
    {
        return !(*this == arg);
    }

    template<class Wrap>
    typename SelectableBase<Wrap>::WrappedT& SelectableBase<Wrap>::operator*()
    {
        return *wrapped;
    }

    template<class Wrap>
    typename SelectableBase<Wrap>::WrappedT& SelectableBase<Wrap>::operator*() const
    {
        return *wrapped;
    }

    template<class Wrap>
    typename SelectableBase<Wrap>::WrappedT* SelectableBase<Wrap>::operator->()
    {
        return wrapped;
    }

    template<class Wrap>
    typename SelectableBase<Wrap>::WrappedT* SelectableBase<Wrap>::operator->() const
    {
        return wrapped;
    }

    template<class Wrap>
    typename SelectableBase<Wrap>::WrappedT& SelectableBase<Wrap>::GetWrapped()
    {
        return *wrapped;
    }

    template<class Wrap>
    typename const SelectableBase<Wrap>::WrappedT& SelectableBase<Wrap>::GetWrapped() const
    {
        return *wrapped;
    }

    template<class Wrap>
    void SelectableBase<Wrap>::Select()
    {
        if (selected)
            return;

        selected = true;
        SelectImpl();
    }

    template<class Wrap>
    void SelectableBase<Wrap>::Deselect()
    {
        if (!selected)
            return;

        selected = false;
        DeselectImpl();
    }

    template<class Wrap>
    bool SelectableBase<Wrap>::IsSelected() const
    {
        return selected;
    }

    template<class Wrap>
    class Selectable;
}

#define DEFINE_SELECTABLE_HASH_REF(wrapT)                                                                                           \
namespace std                                                                                                                       \
{                                                                                                                                   \
    template<>                                                                                                                      \
    struct hash<Creation::Selectable<wrapT>>                                                                                     \
    {                                                                                                                               \
        typedef Creation::Selectable<wrapT> argument_type;                                                                       \
        typedef std::size_t result_type;                                                                                            \
                                                                                                                                    \
        result_type operator()(const argument_type &arg) const                                                                      \
        {                                                                                                                           \
            const result_type first(std::hash<const std::remove_reference<argument_type::WrappedT>::type*>()(&arg.GetWrapped()));   \
            return first;                                                                                                           \
        }                                                                                                                           \
    };                                                                                                                              \
}

#define DEFINE_SELECTABLE_HASH_PTR(wrapT)                                                       \
namespace std                                                                                   \
{                                                                                               \
    template<>                                                                                  \
    struct hash<Creation::Selectable<wrapT>>                                                 \
    {                                                                                           \
        typedef Creation::Selectable<wrapT> argument_type;                                   \
        typedef std::size_t result_type;                                                        \
                                                                                                \
        result_type operator()(const argument_type &arg) const                                  \
        {                                                                                       \
            const result_type first(std::hash<argument_type::WrappedT>()(arg.GetWrapped()));    \
            return first;                                                                       \
        }                                                                                       \
    };                                                                                          \
}