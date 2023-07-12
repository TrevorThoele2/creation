#pragma once

#include "DataBreakdownBase.h"

#include "BuildPackageRegistryReference.h"

#include "StringButtonProperty.h"

#include <Atmos/Ability.h>
#include <Atmos/CharacterClass.h>
#include <Atmos/Item.h>
#include <Atmos/Quest.h>
#include <Atmos/Spell.h>
#include <Atmos/StatusEffect.h>

namespace Creation
{
    template<class T>
    struct RegistryObjectReferenceTraits;
    template<>
    struct RegistryObjectReferenceTraits<::Atmos::Ability>
    {
        typedef Build::Package<::Atmos::Ability> PackageT;
        static const Build::Package<::Atmos::RandomAccessSequence<PackageT>>& Sequence();
    };

    template<>
    struct RegistryObjectReferenceTraits<::Atmos::CharacterClass>
    {
        typedef Build::Package<::Atmos::CharacterClass> PackageT;
        static const Build::Package<::Atmos::RandomAccessSequence<PackageT>>& Sequence();
    };

    template<>
    struct RegistryObjectReferenceTraits<::Atmos::Item>
    {
        typedef Build::Package<::Atmos::Item> PackageT;
        static const Build::Package<::Atmos::RandomAccessSequence<PackageT>>& Sequence();
    };

    template<>
    struct RegistryObjectReferenceTraits<::Atmos::Quest>
    {
        typedef Build::Package<::Atmos::Quest> PackageT;
        static const Build::Package<::Atmos::RandomAccessSequence<PackageT>>& Sequence();
    };

    template<>
    struct RegistryObjectReferenceTraits<::Atmos::Spell>
    {
        typedef Build::Package<::Atmos::Spell> PackageT;
        static const Build::Package<::Atmos::RandomAccessSequence<PackageT>>& Sequence();
    };

    template<>
    struct RegistryObjectReferenceTraits<::Atmos::StatusEffect>
    {
        typedef Build::Package<::Atmos::StatusEffect> PackageT;
        static const Build::Package<::Atmos::RandomAccessSequence<PackageT>>& Sequence();
    };

    template<class T>
    class DataBreakdown<Build::Package<::Atmos::RegistryObjectReference<T>>> : public DataBreakdownBase<Build::Package<::Atmos::RegistryObjectReference<T>>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        typedef RegistryObjectReferenceTraits<T> TraitsT;

        wxStringProperty *prop;

        void OnPropertyGridChanged(wxPropertyGridEvent &e);
        void OnStringPropertyChanged(const String &str);

        void CreateEditorPropertiesImpl(const ChildReference &afterThis) override final;
        void UpdateEditorPropertiesImpl(DataViewSelection::Group &selected) override final;
        void DestroyEditorPropertiesImpl(bool destroyTreeItem) override final;
        void SetEditableImpl(bool set) override final;
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<class T>
    void DataBreakdown<Build::Package<::Atmos::RegistryObjectReference<T>>>::OnPropertyGridChanged(wxPropertyGridEvent &e)
    {
        if (e.GetProperty() != prop)
        {
            e.Skip();
            return;
        }

        PackageT nPackage;
        nPackage.name.value = prop->GetValue().GetString();
        ChangePackage<DataBreakdown>(nPackage);

        e.Skip();
    }

    template<class T>
    void DataBreakdown<Build::Package<::Atmos::RegistryObjectReference<T>>>::OnStringPropertyChanged(const String &str)
    {
        PackageT nPackage;
        nPackage.name.value = str;
        ChangePackage<DataBreakdown>(nPackage);
    }

    template<class T>
    void DataBreakdown<Build::Package<::Atmos::RegistryObjectReference<T>>>::CreateEditorPropertiesImpl(const ChildReference &afterThis)
    {
        prop = CreatePropertyEmplace<wxStringProperty>("Value", afterThis);
        prop->Enable(IsEditable());
        auto underlyingProp = new StringButtonProperty();
        for (auto &loop : TraitsT::Sequence().value)
            underlyingProp->AddString(loop.name.Build());
        PropertyGrid()->SetPropertyEditor(prop, underlyingProp);
        PropertyGrid()->Bind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
        underlyingProp->onChanged.Subscribe(&DataBreakdown::OnStringPropertyChanged, *this);
    }

    template<class T>
    void DataBreakdown<Build::Package<::Atmos::RegistryObjectReference<T>>>::UpdateEditorPropertiesImpl(DataViewSelection::Group &selected)
    {
        prop->Enable(IsEditable());

        prop->SetValue(static_cast<DataBreakdown*>(*selected.begin())->Get()->name.value);
        for (auto loop = ++selected.begin(); loop != selected.end(); ++loop)
        {
            if (static_cast<DataBreakdown*>(*loop)->Get()->name.value != prop->GetValue().GetString())
            {
                prop->SetValue("");
                return;
            }
        }
    }

    template<class T>
    void DataBreakdown<Build::Package<::Atmos::RegistryObjectReference<T>>>::DestroyEditorPropertiesImpl(bool destroyTreeItem)
    {
        DestroyProperty(prop);
        PropertyGrid()->Unbind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
    }

    template<class T>
    void DataBreakdown<Build::Package<::Atmos::RegistryObjectReference<T>>>::SetEditableImpl(bool set)
    {
        if (prop)
            prop->Enable(set);
    }

    template<class T>
    DataBreakdown<Build::Package<::Atmos::RegistryObjectReference<T>>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent), prop(nullptr)
    {}

    template<class T>
    DataBreakdown<Build::Package<::Atmos::RegistryObjectReference<T>>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent), prop(std::move(arg.prop))
    {}

    template<class T>
    DataBreakdown<Build::Package<::Atmos::RegistryObjectReference<T>>>& DataBreakdown<Build::Package<::Atmos::RegistryObjectReference<T>>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        prop = std::move(arg.prop);
        return *this;
    }
}