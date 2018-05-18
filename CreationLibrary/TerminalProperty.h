#pragma once

#include <unordered_set>
#include "PropertyName.h"
#include "Nexus.h"
#include "NexusHistory.h"

namespace Creation::Editing
{
    class UI;

    template<class Data>
    class TerminalProperty
    {
    public:
        using DataT = Data;

        using Nexus = Editing::Nexus<DataT>;
        using NexusSet = std::unordered_set<Nexus*>;
    public:
        virtual ~TerminalProperty() = 0;

        void AddNexus(Nexus& add);
        void RemoveNexus(Nexus& remove);

        [[nodiscard]] wxPGProperty* WxProperty();
    protected:
        TerminalProperty(
            const String& label,
            wxPGProperty* property,
            wxPGProperty* parentProperty,
            wxPropertyGrid& grid,
            const NexusHistory& nexusHistory,
            UI& ui);
        TerminalProperty(TerminalProperty&& arg) noexcept;
    protected:
        [[nodiscard]] virtual DataT ValueFromProperty() const = 0;
        [[nodiscard]] virtual wxVariant VariantFromData(const DataT& data) = 0;
    protected:
        void SetPropertyValue(const DataT& data);
        [[nodiscard]] UI& OwningUI();
    private:
        UI* ui;

        wxPGProperty* property;

        wxPropertyGrid* grid;

        NexusSet nexusSet;
        NexusHistory nexusHistory;

        std::unordered_map<NexusNode*, ScopedEventConnection> nexiConnections;

        void SetNexiData(const DataT& data);
        [[nodiscard]] const NexusSet& CurrentNexusSet() const;
    private:
        void OnPropertyChanged(wxPropertyGridEvent& e);
        void SetPropertyValue();
    };

    template<class Data>
    TerminalProperty<Data>::~TerminalProperty()
    {
        if (property)
        {
            grid->DeleteProperty(property);
            property = nullptr;
        }
    }

    template<class Data>
    void TerminalProperty<Data>::AddNexus(Nexus& add)
    {
        nexusSet.emplace(&add);
        nexiConnections.emplace(&add, add.onDataChanged.Subscribe([this](auto) { SetPropertyValue(); }));
        SetPropertyValue();
    }

    template<class Data>
    void TerminalProperty<Data>::RemoveNexus(Nexus& remove)
    {
        nexusSet.erase(&remove);
        nexiConnections.erase(&remove);
        SetPropertyValue();
    }

    template<class Data>
    wxPGProperty* TerminalProperty<Data>::WxProperty()
    {
        return property;
    }

    template<class Data>
    TerminalProperty<Data>::TerminalProperty(
        const String& label,
        wxPGProperty* property,
        wxPGProperty* parentProperty,
        wxPropertyGrid& grid,
        const NexusHistory& nexusHistory,
        UI& ui)
        :
        property(property),
        grid(&grid),
        nexusHistory(nexusHistory),
        ui(&ui)
    {
        grid.Bind(wxEVT_PG_CHANGED, &TerminalProperty::OnPropertyChanged, this);
        SetPropertyValue();
        if (parentProperty)
            grid.AppendIn(parentProperty, property);
        else
            grid.AppendIn(grid.GetRoot(), property);
    }

    template<class Data>
    TerminalProperty<Data>::TerminalProperty(TerminalProperty&& arg) noexcept :
        property(arg.property),
        grid(arg.grid),
        nexusHistory(arg.nexusHistory),
        ui(arg.ui)
    {}

    template<class Data>
    void TerminalProperty<Data>::SetPropertyValue(const DataT& data)
    {
        SetNexiData(data);
        SetPropertyValue();
    }

    template<class Data>
    UI& TerminalProperty<Data>::OwningUI()
    {
        return *ui;
    }

    template<class Data>
    void TerminalProperty<Data>::SetNexiData(const DataT& data)
    {
        auto currentNexusSet = CurrentNexusSet();
        std::vector<NexusHistory::Delta<Data>> nexusChanges;
        for (auto& nexus : currentNexusSet)
            nexusChanges.emplace_back(nexus, data);
        nexusHistory.ChangeData(nexusChanges);
    }

    template<class Data>
    auto TerminalProperty<Data>::CurrentNexusSet() const -> const NexusSet&
    {
        return nexusSet;
    }

    template<class Data>
    void TerminalProperty<Data>::OnPropertyChanged(wxPropertyGridEvent& e)
    {
        if (e.GetProperty() != property)
        {
            e.Skip();
            return;
        }

        const auto value = ValueFromProperty();
        SetNexiData(value);
    }

    template<class Data>
    void TerminalProperty<Data>::SetPropertyValue()
    {
        auto& nexusSet = CurrentNexusSet();
        if (nexusSet.empty())
        {
            property->SetValueToUnspecified();
            return;
        }

        const auto& standardData = (*nexusSet.begin())->CurrentData();
        for (auto& nexus : nexusSet)
        {
            if (nexus->CurrentData() != standardData)
            {
                property->SetValueToUnspecified();
                return;
            }
        }

        property->SetValue(VariantFromData(standardData));
    }
}