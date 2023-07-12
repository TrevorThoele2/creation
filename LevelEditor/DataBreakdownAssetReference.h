#pragma once

#include "DataBreakdownBase.h"
#include "CurrentWorld.h"

#include "StringButtonProperty.h"

#include <Atmos/AudioAsset.h>
#include <Atmos/ImageAsset.h>
#include <Atmos/Material.h>
#include <Atmos/Script.h>
#include <Atmos/ShaderAsset.h>

namespace Creation
{
    template<class T>
    struct AssetReferenceTraits;
    template<>
    struct AssetReferenceTraits<::Atmos::AudioAsset>
    {
        typedef Build::Package<::Atmos::AudioAsset> PackageT;
        static Build::Package<::Atmos::RandomAccessSequence<PackageT>>& Sequence();
        static String StringGetter(const PackageT &package);
    };

    template<>
    struct AssetReferenceTraits<::Atmos::ImageAsset>
    {
        typedef Build::Package<::Atmos::ImageAsset> PackageT;
        static Build::Package<::Atmos::RandomAccessSequence<PackageT>>& Sequence();
        static String StringGetter(const PackageT &package);
    };

    template<>
    struct AssetReferenceTraits<::Atmos::Material>
    {
        typedef Build::Package<::Atmos::Material> PackageT;
        static Build::Package<::Atmos::RandomAccessSequence<PackageT>>& Sequence();
        static String StringGetter(const PackageT &package);
    };

    template<>
    struct AssetReferenceTraits<::Atmos::ScriptModuleBase>
    {
        typedef Build::Package<::Atmos::ScriptModuleBase> PackageT;
        static Build::Package<::Atmos::RandomAccessSequence<PackageT>>& Sequence();
        static String StringGetter(const PackageT &package);
    };

    template<>
    struct AssetReferenceTraits<::Atmos::ShaderAsset>
    {
        typedef Build::Package<::Atmos::ShaderAsset> PackageT;
        static Build::Package<::Atmos::RandomAccessSequence<PackageT>>& Sequence();
        static String StringGetter(const PackageT &package);
    };

    template<class T>
    class DataBreakdown<Build::Package<::Atmos::AssetReference<T>>> : public DataBreakdownBase<Build::Package<::Atmos::AssetReference<T>>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        typedef AssetReferenceTraits<T> TraitsT;

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
    void DataBreakdown<Build::Package<::Atmos::AssetReference<T>>>::OnPropertyGridChanged(wxPropertyGridEvent &e)
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
    void DataBreakdown<Build::Package<::Atmos::AssetReference<T>>>::OnStringPropertyChanged(const String &str)
    {
        PackageT nPackage;
        nPackage.name.value = str;
        ChangePackage<DataBreakdown>(nPackage);
    }

    template<class T>
    void DataBreakdown<Build::Package<::Atmos::AssetReference<T>>>::CreateEditorPropertiesImpl(const ChildReference &afterThis)
    {
        prop = CreatePropertyEmplace<wxStringProperty>("Value", afterThis);
        prop->Enable(IsEditable());
        auto underlyingProp = new StringButtonProperty();
        for (auto &loop : TraitsT::Sequence().value)
            underlyingProp->AddString(TraitsT::StringGetter(loop));
        PropertyGrid()->SetPropertyEditor(prop, underlyingProp);
        PropertyGrid()->Bind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
        underlyingProp->onChanged.Subscribe(&DataBreakdown::OnStringPropertyChanged, *this);
    }

    template<class T>
    void DataBreakdown<Build::Package<::Atmos::AssetReference<T>>>::UpdateEditorPropertiesImpl(DataViewSelection::Group &selected)
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
    void DataBreakdown<Build::Package<::Atmos::AssetReference<T>>>::DestroyEditorPropertiesImpl(bool destroyTreeItem)
    {
        DestroyProperty(prop);
        PropertyGrid()->Unbind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
    }

    template<class T>
    void DataBreakdown<Build::Package<::Atmos::AssetReference<T>>>::SetEditableImpl(bool set)
    {
        if (prop)
            prop->Enable(set);
    }

    template<class T>
    DataBreakdown<Build::Package<::Atmos::AssetReference<T>>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent), prop(nullptr)
    {
        SetAddCategory(false);
    }

    template<class T>
    DataBreakdown<Build::Package<::Atmos::AssetReference<T>>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent), prop(std::move(arg.prop))
    {
        SetAddCategory(false);
    }

    template<class T>
    DataBreakdown<Build::Package<::Atmos::AssetReference<T>>>& DataBreakdown<Build::Package<::Atmos::AssetReference<T>>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        prop = std::move(arg.prop);
        return *this;
    }
}