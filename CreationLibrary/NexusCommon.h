#pragma once

#include "NexusNode.h"
#include "AutoNexusHandler.h"
#include "TreeElement.h"
#include "WorldElement.h"

#include "NexusHistory.h"

#include "Event.h"

#include <Chroma/IsComplete.h>

namespace Creation::Editing
{
    class UI;

    template<class Data, bool HasTreeElement = false>
    class NexusCommon : public NexusNode
    {
    public:
        using DataT = Data;

        using LabelRetriever = std::function<String()>;
    public:
        Event<DataT> onDataChanged;
    public:
        NexusCommon(
            DataT& data,
            NexusNode* parent,
            NexusHistory nexusHistory,
            UI& ui,
            Arca::Reliquary& reliquary,
            const String& label);
        NexusCommon(NexusCommon&& arg, NexusNode* parent) noexcept;
        NexusCommon(const NexusCommon& arg) = delete;
        NexusCommon(NexusCommon&& arg) noexcept = default;
        NexusCommon& operator=(NexusCommon && arg) noexcept = default;
        virtual ~NexusCommon() = 0;

        void ChangeData(DataT data);
        [[nodiscard]] DataT& CurrentData();
        [[nodiscard]] const DataT& CurrentData() const;

        [[nodiscard]] NexusNode* Parent() final;
        [[nodiscard]] const NexusNode* Parent() const final;

        void CreateTreeElement(PropertiesTree& tree) final;
        void DestroyTreeElement() final;
        [[nodiscard]] TreeElementBase* TreeElement() final;

        void CreateWorldElement() final;
        void DestroyWorldElement() final;
        [[nodiscard]] WorldElementBase* WorldElement() final;

        void Select() final;
        void Deselect() final;
        [[nodiscard]] bool IsSelected() const final;

        [[nodiscard]] std::vector<NexusNode*> Children() final;

        [[nodiscard]] String Label() const final;
    protected:
        void ChangeLabel(const String& label);

        [[nodiscard]] UI& OwningUI();
        [[nodiscard]] const NexusHistory& RetrieveNexusHistory() const;
    protected:
        using AutoHandler = std::conditional_t<
            std::is_class_v<Data>,
            AutoNexusHandler<Data>,
            NullAutoNexusHandler<Data>>;
        AutoHandler autoHandler;
    private:
        DataT* data;
    private:
        NexusNode* parent;
        String label;

        bool isSelected = false;
    private:
        std::unique_ptr<Editing::TreeElement<DataT>> treeElement;
        std::optional<Editing::WorldElement<DataT>> worldElement;
    private:
        UI* ui;
        NexusHistory nexusHistory;
    private:
        Arca::Reliquary* reliquary;
    };

    template<class Data, bool HasTreeElement>
    NexusCommon<Data, HasTreeElement>::NexusCommon(
        DataT& data,
        NexusNode* parent,
        NexusHistory nexusHistory,
        UI& ui,
        Arca::Reliquary& reliquary,
        const String& label)
        :
        data(&data),
        parent(parent),
        label(label),
        worldElement({ static_cast<Nexus<DataT>&>(*this), reliquary }),
        nexusHistory(nexusHistory),
        ui(&ui),
        reliquary(&reliquary)
    {}

    template<class Data, bool HasTreeElement>
    NexusCommon<Data, HasTreeElement>::NexusCommon(NexusCommon&& arg, NexusNode* parent) noexcept :
        data(std::move(arg.data)),
        parent(parent),
        label(std::move(arg.label)),
        treeElement(std::move(arg.treeElement)),
        worldElement(std::move(arg.worldElement)),
        nexusHistory(std::move(arg.nexusHistory)),
        ui(arg.ui)
    {}

    template<class Data, bool HasTreeElement>
    NexusCommon<Data, HasTreeElement>::~NexusCommon() = default;

    template<class Data, bool HasTreeElement>
    void NexusCommon<Data, HasTreeElement>::ChangeData(DataT data)
    {
        *this->data = data;
        autoHandler.DecomposeChangeData(*this->data);
        onDataChanged(*this->data);
    }

    template<class Data, bool HasTreeElement>
    auto NexusCommon<Data, HasTreeElement>::CurrentData() -> DataT&
    {
        return *data;
    }

    template<class Data, bool HasTreeElement>
    auto NexusCommon<Data, HasTreeElement>::CurrentData() const -> const DataT&
    {
        return *data;
    }

    template<class Data, bool HasTreeElement>
    NexusNode* NexusCommon<Data, HasTreeElement>::Parent()
    {
        return parent;
    }

    template<class Data, bool HasTreeElement>
    const NexusNode* NexusCommon<Data, HasTreeElement>::Parent() const
    {
        return parent;
    }

    template<class Data, bool HasTreeElement>
    void NexusCommon<Data, HasTreeElement>::CreateTreeElement(PropertiesTree& tree)
    {
        if (HasTreeElement)
            treeElement = std::make_unique<Editing::TreeElement<DataT>>(static_cast<Nexus<Data>&>(*this), Label(), tree);
    }

    template<class Data, bool HasTreeElement>
    void NexusCommon<Data, HasTreeElement>::DestroyTreeElement()
    {
        treeElement.reset();
    }

    template<class Data, bool HasTreeElement>
    TreeElementBase* NexusCommon<Data, HasTreeElement>::TreeElement()
    {
        return treeElement.get();
    }

    template<class Data, bool HasTreeElement>
    void NexusCommon<Data, HasTreeElement>::CreateWorldElement()
    {
        worldElement.emplace(static_cast<Nexus<DataT>&>(*this), *reliquary);
    }

    template<class Data, bool HasTreeElement>
    void NexusCommon<Data, HasTreeElement>::DestroyWorldElement()
    {
        worldElement.reset();
    }

    template<class Data, bool HasTreeElement>
    WorldElementBase* NexusCommon<Data, HasTreeElement>::WorldElement()
    {
        return worldElement ? &worldElement.value() : nullptr;
    }

    template<class Data, bool HasTreeElement>
    void NexusCommon<Data, HasTreeElement>::Select()
    {
        if (!isSelected)
        {
            if (worldElement)
                worldElement->Select();
            isSelected = true;
        }
    }

    template<class Data, bool HasTreeElement>
    void NexusCommon<Data, HasTreeElement>::Deselect()
    {
        if (isSelected)
        {
            if (worldElement)
                worldElement->Deselect();
            isSelected = false;
        }
    }

    template<class Data, bool HasTreeElement>
    bool NexusCommon<Data, HasTreeElement>::IsSelected() const
    {
        return isSelected;
    }

    template<class Data, bool HasTreeElement>
    std::vector<NexusNode*> NexusCommon<Data, HasTreeElement>::Children()
    {
        return autoHandler.AllAutoNexi();
    }

    template<class Data, bool HasTreeElement>
    String NexusCommon<Data, HasTreeElement>::Label() const
    {
        return label;
    }

    template<class Data, bool HasTreeElement>
    void NexusCommon<Data, HasTreeElement>::ChangeLabel(const String& label)
    {
        this->label = label;
        if (treeElement)
            treeElement->ChangeLabel(label);
    }

    template<class Data, bool HasTreeElement>
    UI& NexusCommon<Data, HasTreeElement>::OwningUI()
    {
        return *ui;
    }

    template<class Data, bool HasTreeElement>
    const NexusHistory& NexusCommon<Data, HasTreeElement>::RetrieveNexusHistory() const
    {
        return nexusHistory;
    }
}