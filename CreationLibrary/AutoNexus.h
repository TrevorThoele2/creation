#pragma once

#include "Event.h"

namespace Creation::Editing
{
    template<class Data>
    class AutoNexus
    {
    private:
        static_assert(std::is_class_v<Data>, "AutoNexus can only work with class/struct types.");
    public:
        using DataT = Data;

        template<class ChildData>
        AutoNexus(
            Nexus<DataT>& owner,
            Nexus<ChildData>& child,
            ChildData DataT::* childDataRetriever);
        AutoNexus(const AutoNexus& arg);
        AutoNexus(AutoNexus&& arg) noexcept = default;
        AutoNexus& operator=(const AutoNexus& arg);
        AutoNexus& operator=(AutoNexus&& arg) noexcept = default;

        void DecomposeChangeData(DataT& data);

        [[nodiscard]] NexusNode* Node() const;
    private:
        class Base
        {
        public:
            virtual ~Base() = 0;

            [[nodiscard]] virtual std::unique_ptr<Base> Clone() const = 0;

            virtual void DecomposeChangeData(DataT& data) = 0;

            [[nodiscard]] virtual NexusNode* Node() const = 0;
        };

        std::unique_ptr<Base> base;

        template<class ChildData>
        class Derived final : public Base
        {
        public:
            Derived(
                Nexus<DataT>& owner,
                Nexus<ChildData>& child,
                ChildData DataT::* childDataRetriever);

            [[nodiscard]] std::unique_ptr<Base> Clone() const override;

            void DecomposeChangeData(DataT& data) override;

            [[nodiscard]] NexusNode* Node() const override;
        private:
            Nexus<ChildData>* child;
            ChildData DataT::* childDataRetriever;

            ScopedEventConnection onChildDataChangedConnection;
        };
    };

    template<class Data>
    template<class ChildData>
    AutoNexus<Data>::AutoNexus(
        Nexus<Data>& owner,
        Nexus<ChildData>& child,
        ChildData DataT::* childDataRetriever)
        :
        base(std::make_unique<Derived<ChildData>>(owner, child, childDataRetriever))
    {}

    template<class Data>
    AutoNexus<Data>::AutoNexus(const AutoNexus& arg) : base(arg.base ? arg.base->Clone() : nullptr)
    {}

    template<class Data>
    AutoNexus<Data>& AutoNexus<Data>::operator=(const AutoNexus& arg)
    {
        base = arg.base ? arg.base->Clone() : nullptr;
        return *this;
    }

    template<class Data>
    void AutoNexus<Data>::DecomposeChangeData(DataT& data)
    {
        base->DecomposeChangeData(data);
    }

    template<class Data>
    NexusNode* AutoNexus<Data>::Node() const
    {
        return base->Node();
    }

    template <class Data>
    AutoNexus<Data>::Base::~Base() = default;

    template<class Data>
    template<class ChildData>
    AutoNexus<Data>::Derived<ChildData>::Derived(
        Nexus<Data>& owner,
        Nexus<ChildData>& child,
        ChildData DataT::* childDataRetriever)
        :
        child(&child),
        childDataRetriever(childDataRetriever)
    {
        const auto onDataChanged = [&owner](ChildData)
        {
            owner.onDataChanged(owner.CurrentData());
        };
        onChildDataChangedConnection = child.onDataChanged.Subscribe(onDataChanged);
    }

    template<class Data>
    template<class ChildData>
    auto AutoNexus<Data>::Derived<ChildData>::Clone() const -> std::unique_ptr<Base>
    {
        return std::make_unique<Derived>(*this);
    }

    template<class Data>
    template<class ChildData>
    void AutoNexus<Data>::Derived<ChildData>::DecomposeChangeData(DataT& data)
    {
        child->ChangeData(data.*childDataRetriever);
    }

    template<class Data>
    template<class ChildData>
    NexusNode* AutoNexus<Data>::Derived<ChildData>::Node() const
    {
        return child;
    }
}