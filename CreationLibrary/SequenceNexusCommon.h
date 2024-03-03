#pragma once

#include "Nexus.h"
#include "NexusNode.h"
#include "HasLabelConstructor.h"

#include "TreeElement.h"

#include "NexusHistory.h"

#include "Event.h"

#include <Arca/Reliquary.h>

namespace Creation::Editing
{
    class UI;

    template<class Data>
    class SequenceNexusCommon : public SequenceNexusBase
    {
    public:
        using DataT = std::list<Data>;
        using ChildData = Data;
        using ChildNexus = Nexus<ChildData>;
        using ChildNexusPtr = std::unique_ptr<ChildNexus>;

        using LabelRetriever = std::function<String()>;
    private:
        using ChildNexi = std::list<ChildNexusPtr>;
    public:
        using iterator = typename ChildNexi::iterator;
        using const_iterator = typename ChildNexi::const_iterator;
    public:
        Event<DataT> onDataChanged;
    public:
        SequenceNexusCommon(
            DataT& data,
            NexusNode* parent,
            NexusHistory nexusHistory,
            UI& ui,
            Arca::Reliquary& reliquary,
            const String& label);
        SequenceNexusCommon(
            DataT& data,
            NexusNode* parent,
            NexusHistory nexusHistory,
            UI& ui,
            Arca::Reliquary& reliquary,
            const String& label,
            LabelRetriever&& childLabelRetriever);
        SequenceNexusCommon(SequenceNexusCommon&& arg, NexusNode* parent);
        SequenceNexusCommon(const SequenceNexusCommon& arg) = delete;
        SequenceNexusCommon(SequenceNexusCommon&& arg) noexcept = default;
        ~SequenceNexusCommon();
        SequenceNexusCommon& operator=(SequenceNexusCommon&& arg) noexcept = default;

        NexusNode* Add() final;
        void Remove(NexusNode& nexus) final;

        ChildNexus& Add(const ChildData& data);
        void Remove(const ChildData& data);

        NexusNode* Reinstate(PackagedData&& data) final;
        [[nodiscard]] PackagedData Release(NexusNode& nexus) final;

        void ChangeData(const DataT& data);
        [[nodiscard]] DataT& CurrentData();
        [[nodiscard]] const DataT& CurrentData() const;

        [[nodiscard]] NexusNode* Parent() final;
        [[nodiscard]] const NexusNode* Parent() const final;

        void CreateTreeElement(PropertiesTree& tree) final;
        void DestroyTreeElement() override;
        [[nodiscard]] TreeElementBase* TreeElement() final;

        void CreateWorldElement() final;
        void DestroyWorldElement() final;
        [[nodiscard]] WorldElementBase* WorldElement() final;

        void Select() final;
        void Deselect() final;
        [[nodiscard]] bool IsSelected() const final;

        [[nodiscard]] std::vector<NexusNode*> Children() final;

        [[nodiscard]] String Label() const final;

        [[nodiscard]] iterator begin();
        [[nodiscard]] const_iterator begin() const;
        [[nodiscard]] iterator end();
        [[nodiscard]] const_iterator end() const;
    private:
        DataT* data;
    private:
        NexusNode* parent;
        String label;

        bool isSelected = false;
    private:
        ChildNexi childNexi;
        LabelRetriever childLabelRetriever;
        std::unordered_map<ChildNexus*, ScopedEventConnection> childEvents;

        typename ChildNexi::iterator CreateNewChild(ChildData data);
        template<class U, std::enable_if_t<has_label_constructor_v<U>, int> = 0>
        typename ChildNexi::iterator EmplaceBackChild(ChildData& data);
        template<class U, std::enable_if_t<!has_label_constructor_v<U>, int> = 0>
        typename ChildNexi::iterator EmplaceBackChild(ChildData& data);
        typename ChildNexi::iterator FindChild(ChildNexus& child);
        typename ChildNexi::iterator FindChild(const ChildData& childData);
        void RemoveChild(typename ChildNexi::iterator child);
        typename ChildNexi::iterator ReinstateChild(PackagedData&& nexus);
        PackagedData ReleaseChild(typename ChildNexi::iterator child);

        typename DataT::iterator FindChildData(ChildData& data);

        void SubscribeOnDataChanged(ChildNexus& child);
    private:
        struct TreeElementAssembly
        {
            Editing::TreeElement<DataT> value;
            PropertiesTree* tree;
            TreeElementAssembly(Nexus<DataT>& nexus, const String& label, PropertiesTree& tree);
        };

        std::unique_ptr<TreeElementAssembly> treeElementAssembly;
    private:
        NexusHistory nexusHistory;
        UI* ui;
        Arca::Reliquary* reliquary;
    };

    template<class Data>
    SequenceNexusCommon<Data>::SequenceNexusCommon(
        DataT& data,
        NexusNode* parent,
        NexusHistory nexusHistory,
        UI& ui,
        Arca::Reliquary& reliquary,
        const String& label)
        :
        SequenceNexusCommon(data, parent, nexusHistory, ui, reliquary, label, []() { return "Entry"; })
    {}

    template<class Data>
    SequenceNexusCommon<Data>::SequenceNexusCommon(
        DataT& data,
        NexusNode* parent,
        NexusHistory nexusHistory,
        UI& ui,
        Arca::Reliquary& reliquary,
        const String& label,
        LabelRetriever&& childLabelRetriever)
        :
        data(&data),
        parent(parent),
        label(label),
        childLabelRetriever(std::move(childLabelRetriever)),
        nexusHistory(nexusHistory),
        ui(&ui),
        reliquary(&reliquary)
    {
        for (auto& datum : *this->data)
        {
            auto newChild = EmplaceBackChild<ChildData>(datum);
            SubscribeOnDataChanged(*newChild->get());
        }
    }

    template<class Data>
    SequenceNexusCommon<Data>::SequenceNexusCommon(SequenceNexusCommon&& arg, NexusNode* parent) :
        data(std::move(arg.data)),
        parent(parent),
        label(std::move(arg.label)),
        childLabelRetriever(std::move(arg.childLabelRetriever)),
        nexusHistory(std::move(arg.nexusHistory)),
        ui(arg.ui),
        reliquary(std::move(arg.reliquary))
    {}

    template<class Data>
    SequenceNexusCommon<Data>::~SequenceNexusCommon()
    {
        childNexi.clear();
    }

    template<class Data>
    NexusNode* SequenceNexusCommon<Data>::Add()
    {
        return &Add({});
    }

    template<class Data>
    void SequenceNexusCommon<Data>::Remove(NexusNode& nexus)
    {
        auto castedNexus = dynamic_cast<ChildNexus*>(&nexus);
        if (!castedNexus)
            return;

        Remove(castedNexus->CurrentData());
    }

    template<class Data>
    auto SequenceNexusCommon<Data>::Add(const ChildData& data) -> ChildNexus&
    {
        CreateNewChild(data);
        return *childNexi.back();
    }

    template<class Data>
    void SequenceNexusCommon<Data>::Remove(const ChildData& data)
    {
        auto focusedChild = FindChild(data);
        RemoveChild(focusedChild);
    }

    template<class Data>
    NexusNode* SequenceNexusCommon<Data>::Reinstate(PackagedData&& data)
    {
        if (data.Type() != typeid(ChildData))
            return nullptr;

        return ReinstateChild(std::move(data))->get();
    }

    template<class Data>
    PackagedData SequenceNexusCommon<Data>::Release(NexusNode& nexus)
    {
        auto castedNexus = dynamic_cast<ChildNexus*>(&nexus);
        if (!castedNexus)
            return {};

        auto focusedChild = FindChild(*castedNexus);
        return ReleaseChild(focusedChild);
    }

    template<class Data>
    void SequenceNexusCommon<Data>::ChangeData(const DataT& data)
    {
        childNexi.clear();
        *this->data = data;
        for (auto& datum : *this->data)
            CreateNewChild(datum);
        onDataChanged(*this->data);
    }

    template<class Data>
    auto SequenceNexusCommon<Data>::CurrentData() -> DataT&
    {
        return *data;
    }

    template<class Data>
    auto SequenceNexusCommon<Data>::CurrentData() const -> const DataT&
    {
        return *data;
    }

    template<class Data>
    NexusNode* SequenceNexusCommon<Data>::Parent()
    {
        return parent;
    }

    template<class Data>
    const NexusNode* SequenceNexusCommon<Data>::Parent() const
    {
        return parent;
    }

    template<class Data>
    void SequenceNexusCommon<Data>::CreateTreeElement(PropertiesTree& tree)
    {
        treeElementAssembly = std::make_unique<TreeElementAssembly>(
            static_cast<Nexus<DataT>&>(*this), label, tree);
    }

    template<class Data>
    void SequenceNexusCommon<Data>::DestroyTreeElement()
    {
        treeElementAssembly.reset();
    }

    template<class Data>
    TreeElementBase* SequenceNexusCommon<Data>::TreeElement()
    {
        return treeElementAssembly ? &treeElementAssembly->value : nullptr;
    }

    template<class Data>
    void SequenceNexusCommon<Data>::CreateWorldElement()
    {
        for (auto& child : childNexi)
            child->CreateWorldElement();
    }

    template<class Data>
    void SequenceNexusCommon<Data>::DestroyWorldElement()
    {
        for (auto& child : childNexi)
            child->DestroyWorldElement();
    }

    template<class Data>
    WorldElementBase* SequenceNexusCommon<Data>::WorldElement()
    {
        return nullptr;
    }

    template<class Data>
    void SequenceNexusCommon<Data>::Select()
    {
        if (isSelected)
            return;
        
        isSelected = true;
    }

    template<class Data>
    void SequenceNexusCommon<Data>::Deselect()
    {
        if (!isSelected)
            return;
        
        isSelected = false;
    }

    template<class Data>
    bool SequenceNexusCommon<Data>::IsSelected() const
    {
        return isSelected;
    }

    template<class Data>
    std::vector<NexusNode*> SequenceNexusCommon<Data>::Children()
    {
        std::vector<NexusNode*> returnValue;
        returnValue.reserve(childNexi.size());
        for (auto& child : childNexi)
            returnValue.push_back(child.get());
        return returnValue;
    }

    template<class Data>
    String SequenceNexusCommon<Data>::Label() const
    {
        return label;
    }

    template<class Data>
    auto SequenceNexusCommon<Data>::begin() -> iterator
    {
        return childNexi.begin();
    }

    template<class Data>
    auto SequenceNexusCommon<Data>::begin() const -> const_iterator
    {
        return childNexi.begin();
    }

    template<class Data>
    auto SequenceNexusCommon<Data>::end() -> iterator
    {
        return childNexi.end();
    }

    template<class Data>
    auto SequenceNexusCommon<Data>::end() const -> const_iterator
    {
        return childNexi.end();
    }

    template<class Data>
    auto SequenceNexusCommon<Data>::CreateNewChild(ChildData data) -> typename ChildNexi::iterator
    {
        this->data->push_back(data);
        auto& newData = this->data->back();
        auto newChild = EmplaceBackChild<ChildData>(newData);
        if (treeElementAssembly)
            OverNexusThenChildren(**newChild, [this](NexusNode& node)
                {
                    node.CreateTreeElement(*treeElementAssembly->tree);
                    node.CreateWorldElement();
                });
        SubscribeOnDataChanged(*newChild->get());
        onDataChanged(*this->data);
        return newChild;
    }

    template<class Data>
    template<class U, std::enable_if_t<has_label_constructor_v<U>, int>>
    auto SequenceNexusCommon<Data>::EmplaceBackChild(ChildData& data) -> typename ChildNexi::iterator
    {
        childNexi.push_back(std::make_unique<ChildNexus>(
            data, this, nexusHistory, *ui, *reliquary, childLabelRetriever()));
        return --childNexi.end();
    }

    template<class Data>
    template<class U, std::enable_if_t<!has_label_constructor_v<U>, int>>
    auto SequenceNexusCommon<Data>::EmplaceBackChild(ChildData& data) -> typename ChildNexi::iterator
    {
        childNexi.push_back(std::make_unique<ChildNexus>(data, this, nexusHistory, *ui, *reliquary));
        return --childNexi.end();
    }

    template<class Data>
    auto SequenceNexusCommon<Data>::FindChild(ChildNexus& child) -> typename ChildNexi::iterator
    {
        for (auto currentChild = childNexi.begin(); currentChild != childNexi.end(); ++currentChild)
            if (currentChild->get() == &child)
                return currentChild;

        return childNexi.end();
    }

    template<class Data>
    auto SequenceNexusCommon<Data>::FindChild(const ChildData& childData) -> typename ChildNexi::iterator
    {
        for (auto currentChild = childNexi.begin(); currentChild != childNexi.end(); ++currentChild)
            if (&(*currentChild)->CurrentData() == &childData)
                return currentChild;

        return childNexi.end();
    }

    template<class Data>
    void SequenceNexusCommon<Data>::RemoveChild(typename ChildNexi::iterator child)
    {
        if (child == childNexi.end())
            return;

        OverNexusThenChildren(**child, [](NexusNode& node)
            {
                node.DestroyTreeElement();
                node.DestroyWorldElement();
            });
        childEvents.erase(child->get());
        auto childData = FindChildData((*child)->CurrentData());
        data->erase(childData);
        childNexi.erase(child);
        onDataChanged(*this->data);
    }

    template<class Data>
    auto SequenceNexusCommon<Data>::ReinstateChild(PackagedData&& nexus) -> typename ChildNexi::iterator
    {
        data->push_back(nexus.As<ChildData>());
        EmplaceBackChild<ChildData>(data->back());
        auto newChild = --childNexi.end();
        if (treeElementAssembly)
            OverNexusThenChildren(**newChild, [this](NexusNode& node)
                {
                    node.CreateTreeElement(*treeElementAssembly->tree);
                    node.CreateWorldElement();
                });
        onDataChanged(*this->data);
        SubscribeOnDataChanged(*newChild->get());
        return newChild;
    }

    template<class Data>
    auto SequenceNexusCommon<Data>::ReleaseChild(typename ChildNexi::iterator child) -> PackagedData
    {
        if (child == childNexi.end())
            return {};

        OverChildrenThenNexus(**child, [](NexusNode& node)
            {
                node.DestroyTreeElement();
                node.DestroyWorldElement();
            });
        auto childData = FindChildData((*child)->CurrentData());
        auto packaged = PackagedData(*childData);
        data->erase(childData);
        childEvents.erase(child->get());
        childNexi.erase(child);
        onDataChanged(*this->data);
        return packaged;
    }

    template<class Data>
    auto SequenceNexusCommon<Data>::FindChildData(ChildData& data) -> typename DataT::iterator
    {
        for (auto currentData = this->data->begin(); currentData != this->data->end(); ++currentData)
            if (&*currentData == &data)
                return currentData;

        return this->data->end();
    }

    template<class Data>
    void SequenceNexusCommon<Data>::SubscribeOnDataChanged(ChildNexus& child)
    {
        auto function = [this](ChildData)
        {
            onDataChanged(*this->data);
        };

        childEvents.emplace(
            &child,
            child.onDataChanged.Subscribe(function));
    }

    template<class Data>
    SequenceNexusCommon<Data>::TreeElementAssembly::TreeElementAssembly(
        Nexus<DataT>& nexus, const String& label, PropertiesTree& tree)
        :
        value(nexus, label, tree), tree(&tree)
    {}
}