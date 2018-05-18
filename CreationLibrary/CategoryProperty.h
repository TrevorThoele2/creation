#pragma once

#include <unordered_set>
#include "PropertyName.h"
#include "Nexus.h"
#include "AutoProperty.h"

namespace Creation::Editing
{
    class UI;

    template<class Data>
    class CategoryProperty
    {
    public:
        using DataT = Data;

        using Nexus = Nexus<DataT>;
        using NexusSet = std::unordered_set<Nexus*>;
    public:
        void AddNexus(Nexus& add);
        void RemoveNexus(Nexus& remove);

        [[nodiscard]] wxPGProperty* WxProperty();
    public:
        CategoryProperty(const String& name, const String& label, wxPGProperty* parentProperty, wxPropertyGrid& grid, UI& ui);
        CategoryProperty(CategoryProperty&& arg) noexcept;
        ~CategoryProperty();
    protected:
        [[nodiscard]] UI& OwningUI();

        template<class Child>
        void Auto(Child& child, typename Child::Nexus Nexus::* childNexusRetriever);
    private:
        UI* ui;
        NexusSet nexusSet;

        wxPropertyCategory* category;
        wxPropertyGrid* grid;
    private:
        std::vector<Editing::Data::AutoProperty<DataT>> autoProperties;
    };

    template<class Data>
    void CategoryProperty<Data>::AddNexus(Nexus& add)
    {
        nexusSet.emplace(&add);
        for (auto& property : autoProperties)
            property.DecomposeAddNexus(add);
    }

    template<class Data>
    void CategoryProperty<Data>::RemoveNexus(Nexus& remove)
    {
        nexusSet.erase(&remove);
        for (auto& property : autoProperties)
            property.DecomposeRemoveNexus(remove);
    }

    template<class Data>
    wxPGProperty* CategoryProperty<Data>::WxProperty()
    {
        return category;
    }

    template<class Data>
    CategoryProperty<Data>::CategoryProperty(const String& name, const String& label, wxPGProperty* parentProperty, wxPropertyGrid& grid, UI& ui) :
        category(new wxPropertyCategory(label, PropertyName(name, parentProperty))), grid(&grid), ui(&ui)
    {
        if (parentProperty)
            grid.AppendIn(parentProperty, category);
        else
            grid.Append(category);
    }

    template<class Data>
    CategoryProperty<Data>::CategoryProperty(CategoryProperty&& arg) noexcept :
        nexusSet(std::move(arg.nexusSet)),
        category(arg.category),
        grid(arg.grid),
        ui(arg.ui)
    {}

    template<class Data>
    CategoryProperty<Data>::~CategoryProperty()
    {
        if (category)
        {
            grid->DeleteProperty(category);
            category = nullptr;
        }
    }

    template<class Data>
    UI& CategoryProperty<Data>::OwningUI()
    {
        return *ui;
    }

    template<class Data>
    template<class Child>
    void CategoryProperty<Data>::Auto(Child& child, typename Child::Nexus Nexus::* childNexusRetriever)
    {
        autoProperties.emplace_back(child, childNexusRetriever);
    }
}