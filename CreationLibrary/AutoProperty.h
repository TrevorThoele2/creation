#pragma once

#include <memory>
#include "Nexus.h"

namespace Creation::Editing::Data
{
    template<class Data>
    class AutoProperty
    {
    private:
        static_assert(std::is_class_v<Data>, "AutoProperty can only work with class types.");
    public:
        using DataT = Data;
        using Nexus = Nexus<DataT>;

        template<class Child>
        AutoProperty(
            Child& child,
            typename Child::Nexus Nexus::* childNexusRetriever);
        AutoProperty(const AutoProperty& arg);
        AutoProperty(AutoProperty&& arg) noexcept = default;
        AutoProperty& operator=(const AutoProperty& arg);
        AutoProperty& operator=(AutoProperty&& arg) noexcept = default;

        void DecomposeAddNexus(Nexus& add);
        void DecomposeRemoveNexus(Nexus& remove);
    private:
        class Base
        {
        public:
            virtual ~Base() = 0;

            [[nodiscard]] virtual std::unique_ptr<Base> Clone() const = 0;

            virtual void DecomposeAddNexus(Nexus& add) = 0;
            virtual void DecomposeRemoveNexus(Nexus& remove) = 0;
        };

        std::unique_ptr<Base> base;

        template<class Child>
        class Derived final : public Base
        {
        public:
            using ChildNexus = typename Child::Nexus;
            using ChildNexusRetriever = ChildNexus Nexus::*;

            Derived(
                Child& child,
                ChildNexusRetriever childNexusRetriever);

            [[nodiscard]] std::unique_ptr<Base> Clone() const override;
        private:
            Child* child;
            ChildNexusRetriever childNexusRetriever;
        private:
            void DecomposeAddNexus(Nexus& add) override;
            void DecomposeRemoveNexus(Nexus& remove) override;
        };
    };

    template<class Data>
    template<class Child>
    AutoProperty<Data>::AutoProperty(
        Child& child,
        typename Child::Nexus Nexus::* childNexusRetriever)
        :
        base(std::make_unique<Derived<Child>>(child, childNexusRetriever))
    {}

    template<class Data>
    AutoProperty<Data>::AutoProperty(const AutoProperty& arg) : base(arg.base ? arg.base->Clone() : nullptr)
    {}

    template<class Data>
    AutoProperty<Data>& AutoProperty<Data>::operator=(const AutoProperty& arg)
    {
        base = arg.base ? arg.base->Clone() : nullptr;
        return *this;
    }

    template<class Data>
    void AutoProperty<Data>::DecomposeAddNexus(Nexus& add)
    {
        base->DecomposeAddNexus(add);
    }

    template<class Data>
    void AutoProperty<Data>::DecomposeRemoveNexus(Nexus& remove)
    {
        base->DecomposeRemoveNexus(remove);
    }

    template <class Data>
    AutoProperty<Data>::Base::~Base() = default;

    template<class Data>
    template<class Child>
    AutoProperty<Data>::Derived<Child>::Derived(
        Child& child,
        ChildNexusRetriever childNexusRetriever)
        :
        child(&child),
        childNexusRetriever(childNexusRetriever)
    {}

    template<class Data>
    template<class Child>
    auto AutoProperty<Data>::Derived<Child>::Clone() const -> std::unique_ptr<Base>
    {
        return std::make_unique<Derived<Child>>(*this);
    }

    template<class Data>
    template<class Child>
    void AutoProperty<Data>::Derived<Child>::DecomposeAddNexus(Nexus& add)
    {
        child->AddNexus(add.*childNexusRetriever);
    }

    template<class Data>
    template<class Child>
    void AutoProperty<Data>::Derived<Child>::DecomposeRemoveNexus(Nexus& remove)
    {
        child->RemoveNexus(remove.*childNexusRetriever);
    }
}