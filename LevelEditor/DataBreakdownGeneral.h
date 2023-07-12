#pragma once

#include "DataBreakdownBase.h"

#include "BuildPackageGeneral.h"

#include "Command.h"
#include "MainFrame.h"
#include "DataView.h"

#include "StringGroup.h"

#include <wx/sizer.h>
#include "FixedPointValidator.h"

namespace Creation
{
    template<>
    class DataBreakdown<Build::Package<bool>> : public DataBreakdownBase<Build::Package<bool>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        wxBoolProperty *checkbox;

        void OnPropertyGridChanged(wxPropertyGridEvent &e);

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
    class DataBreakdownInteger : public DataBreakdownBase<T>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
        static constexpr bool test = std::is_signed<T>::value;
    private:
        template<bool b>
        struct PropertyImpl;

        template<> struct PropertyImpl<true> { typedef wxIntProperty PropT; typedef long long ValueT; static constexpr wxLongLong(wxVariant::*getter)() const = &wxVariant::GetLongLong; };
        template<> struct PropertyImpl<false> { typedef wxUIntProperty PropT; typedef unsigned long long ValueT; static constexpr wxULongLong(wxVariant::*getter)() const = &wxVariant::GetULongLong;};
    private:
        typedef std::numeric_limits<BuildT> NumericLimitsT;

        typedef PropertyImpl<std::is_signed<BuildT>::value> ImplT;

        typedef typename ImplT::PropT PropT;
        typedef typename ImplT::ValueT ValueT;

        PropT *prop;
        BuildT min, max;

        void OnPropertyGridChanged(wxPropertyGridEvent &e);

        void CreateEditorPropertiesImpl(const ChildReference &afterThis) override final;
        void UpdateEditorPropertiesImpl(DataViewSelection::Group &selected) override final;
        void DestroyEditorPropertiesImpl(bool destroyTreeItem) override final;
        void SetEditableImpl(bool set) override final;
    public:
        DataBreakdownInteger(const String &name, DataBreakdownCommon *parent);
        DataBreakdownInteger(DataBreakdownInteger &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdownInteger& operator=(DataBreakdownInteger &&arg);

        void SetMin(BuildT set);
        void SetMax(BuildT set);
    };

    template<class T>
    void DataBreakdownInteger<T>::OnPropertyGridChanged(wxPropertyGridEvent &e)
    {
        if (e.GetProperty() != prop)
        {
            e.Skip();
            return;
        }

        PackageT nPackage;
        nPackage.value = ::Atmos::FromString<BuildT>(prop->GetValue().GetString().ToStdString());
        ChangePackage<DataBreakdownInteger>(nPackage);

        e.Skip();
    }

    template<class T>
    void DataBreakdownInteger<T>::CreateEditorPropertiesImpl(const ChildReference &afterThis)
    {
        prop = CreatePropertyEmplace<PropT>("Value", afterThis);
        prop->Enable(IsEditable());
        prop->SetAttribute("Min", wxAny(min));
        prop->SetAttribute("Max", wxAny(max));
        PropertyGrid()->Bind(wxEVT_PG_CHANGED, &DataBreakdownInteger::OnPropertyGridChanged, this);
    }

    template<class T>
    void DataBreakdownInteger<T>::UpdateEditorPropertiesImpl(DataViewSelection::Group &selected)
    {
        prop->Enable(IsEditable());

        prop->SetValue(wxAny(static_cast<DataBreakdownInteger*>(*selected.begin())->Get()->value));
        for (auto loop = ++selected.begin(); loop != selected.end(); ++loop)
        {
            if (static_cast<DataBreakdownInteger*>(*loop)->Get()->value != (prop->GetValue().*ImplT::getter)())
            {
                prop->SetValueToUnspecified();
                return;
            }
        }
    }

    template<class T>
    void DataBreakdownInteger<T>::DestroyEditorPropertiesImpl(bool destroyTreeItem)
    {
        DestroyProperty(prop);
        PropertyGrid()->Unbind(wxEVT_PG_CHANGED, &DataBreakdownInteger::OnPropertyGridChanged, this);
    }

    template<class T>
    void DataBreakdownInteger<T>::SetEditableImpl(bool set)
    {
        if (prop)
            prop->Enable(set);
    }

    template<class T>
    DataBreakdownInteger<T>::DataBreakdownInteger(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent), min(NumericLimitsT::min()), max(NumericLimitsT::max()), prop(nullptr)
    {
        SetAddCategory(false);
    }

    template<class T>
    DataBreakdownInteger<T>::DataBreakdownInteger(DataBreakdownInteger &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent), prop(std::move(arg.prop)), min(std::move(arg.min)), max(std::move(arg.max))
    {
        SetAddCategory(false);
    }

    template<class T>
    DataBreakdownInteger<T>& DataBreakdownInteger<T>::operator=(DataBreakdownInteger &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        min = std::move(arg.min);
        max = std::move(arg.max);
        prop = std::move(arg.prop);
        return *this;
    }

    template<class T>
    void DataBreakdownInteger<T>::SetMin(BuildT set)
    {
        min = set;
        static_cast<wxIntegerValidator<BuildT>*>(prop->GetValidator())->SetMin(min);
        // If the current value is < the one to set, then change to set
        if (::Atmos::FromString<BuildT>(prop->GetValue().ToStdString()) < set)
            prop->SetValue(::Atmos::ToString(set));
    }

    template<class T>
    void DataBreakdownInteger<T>::SetMax(BuildT set)
    {
        max = set;
        static_cast<wxIntegerValidator<BuildT>*>(prop->GetValidator())->SetMax(max);
    }

    template<class T>
    class DataBreakdownFloatingPoint : public DataBreakdownBase<T>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        typedef std::numeric_limits<BuildT> NumericLimitsT;

        wxFloatProperty *prop;
        BuildT min, max;

        void OnPropertyGridChanged(wxPropertyGridEvent &e);

        void CreateEditorPropertiesImpl(const ChildReference &afterThis) override final;
        void UpdateEditorPropertiesImpl(DataViewSelection::Group &selected) override final;
        void DestroyEditorPropertiesImpl(bool destroyTreeItem) override final;
        void SetEditableImpl(bool set) override final;
    public:
        DataBreakdownFloatingPoint(const String &name, DataBreakdownCommon *parent);
        DataBreakdownFloatingPoint(DataBreakdownFloatingPoint &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdownFloatingPoint& operator=(DataBreakdownFloatingPoint &&arg);

        void SetMin(BuildT set);
        void SetMax(BuildT set);
    };

    template<class T>
    void DataBreakdownFloatingPoint<T>::OnPropertyGridChanged(wxPropertyGridEvent &e)
    {
        if (e.GetProperty() != prop)
        {
            e.Skip();
            return;
        }

        PackageT nPackage;
        nPackage.value = ::Atmos::FromString<BuildT>(prop->GetValue().GetString().ToStdString());
        ChangePackage<DataBreakdownFloatingPoint>(nPackage);

        e.Skip();
    }

    template<class T>
    void DataBreakdownFloatingPoint<T>::CreateEditorPropertiesImpl(const ChildReference &afterThis)
    {
        prop = CreatePropertyEmplace<wxFloatProperty>("Value", afterThis);
        prop->Enable(IsEditable());
        prop->SetAttribute("Min", wxAny(min));
        prop->SetAttribute("Max", wxAny(max));
        PropertyGrid()->Bind(wxEVT_PG_CHANGED, &DataBreakdownFloatingPoint::OnPropertyGridChanged, this);
    }

    template<class T>
    void DataBreakdownFloatingPoint<T>::UpdateEditorPropertiesImpl(DataViewSelection::Group &selected)
    {
        prop->Enable(IsEditable());

        prop->SetValue(static_cast<DataBreakdownFloatingPoint*>(*selected.begin())->Get()->value);
        for (auto loop = ++selected.begin(); loop != selected.end(); ++loop)
        {
            if (static_cast<DataBreakdownFloatingPoint*>(*loop)->Get()->value != prop->GetValue().GetDouble())
            {
                prop->SetValueToUnspecified();
                return;
            }
        }
    }

    template<class T>
    void DataBreakdownFloatingPoint<T>::DestroyEditorPropertiesImpl(bool destroyTreeItem)
    {
        DestroyProperty(prop);
        PropertyGrid()->Unbind(wxEVT_PG_CHANGED, &DataBreakdownFloatingPoint::OnPropertyGridChanged, this);
    }

    template<class T>
    void DataBreakdownFloatingPoint<T>::SetEditableImpl(bool set)
    {
        if (prop)
            prop->Enable(set);
    }

    template<class T>
    DataBreakdownFloatingPoint<T>::DataBreakdownFloatingPoint(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent), min(NumericLimitsT::lowest()), max(NumericLimitsT::max()), prop(nullptr)
    {
        SetAddCategory(false);
    }

    template<class T>
    DataBreakdownFloatingPoint<T>::DataBreakdownFloatingPoint(DataBreakdownFloatingPoint &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent), min(std::move(arg.min)), max(std::move(arg.max)), prop(std::move(arg.prop))
    {
        SetAddCategory(false);
    }

    template<class T>
    DataBreakdownFloatingPoint<T>& DataBreakdownFloatingPoint<T>::operator=(DataBreakdownFloatingPoint &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        min = std::move(arg.min);
        max = std::move(arg.max);
        prop = std::move(arg.prop);
        return *this;
    }

    template<class T>
    void DataBreakdownFloatingPoint<T>::SetMin(BuildT set)
    {
        min = set;
        static_cast<wxFloatingPointValidator<BuildT>*>(prop->GetValidator())->SetMin(min);
        // If the current value is < the one to set, then change to set
        if (::Atmos::FromString<BuildT>(prop->GetValue().ToStdString()) < set)
            prop->SetValue(::Atmos::ToString(set));
    }

    template<class T>
    void DataBreakdownFloatingPoint<T>::SetMax(BuildT set)
    {
        max = set;
        static_cast<wxFloatingPointValidator<BuildT>*>(prop->GetValidator())->SetMax(max);
    }

    template<>
    class DataBreakdown<Build::Package<std::uint8_t>> : public DataBreakdownInteger<Build::Package<std::uint8_t>>
    {
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<std::uint16_t>> : public DataBreakdownInteger<Build::Package<std::uint16_t>>
    {
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<std::uint32_t>> : public DataBreakdownInteger<Build::Package<std::uint32_t>>
    {
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<std::uint64_t>> : public DataBreakdownInteger<Build::Package<std::uint64_t>>
    {
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<std::int8_t>> : public DataBreakdownInteger<Build::Package<std::int8_t>>
    {
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<std::int16_t>> : public DataBreakdownInteger<Build::Package<std::int16_t>>
    {
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<std::int32_t>> : public DataBreakdownInteger<Build::Package<std::int32_t>>
    {
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<std::int64_t>> : public DataBreakdownInteger<Build::Package<std::int64_t>>
    {
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<float>> : public DataBreakdownFloatingPoint<Build::Package<float>>
    {
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<double>> : public DataBreakdownFloatingPoint<Build::Package<double>>
    {
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<class T, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type lowerBound, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type upperBound>
    class DataBreakdown<Build::Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>> : public DataBreakdownBase<Build::Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        template<bool>
        struct Impl;

        template<>
        struct Impl<true>
        {
            typedef wxFloatProperty PropT;
            typedef wxFloatingPointValidator<T> ValidatorT;
        };

        template<>
        struct Impl<false>
        {
        private:
            template<bool>
            struct Impl2;

            template<>
            struct Impl2<true>
            {
                typedef wxIntProperty PropT;
            };

            template<>
            struct Impl2<false>
            {
                typedef wxUIntProperty PropT;
            };
        public:
            typedef typename Impl2<std::is_signed<T>::value>::PropT PropT;
            typedef wxIntegerValidator<T> ValidatorT;
        };
    private:
        typedef typename Impl<std::is_floating_point<T>::value>::PropT PropT;
        typedef typename Impl<std::is_floating_point<T>::value>::ValidatorT ValidatorT;

        PropT *prop;

        void OnPropertyGridChanged(wxPropertyGridEvent &e);

        void CreateEditorPropertiesImpl(const ChildReference &afterThis) override final;
        void UpdateEditorPropertiesImpl(DataViewSelection::Group &selected) override final;
        void DestroyEditorPropertiesImpl(bool destroyTreeItem) override final;
        void SetEditableImpl(bool set) override final;
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<class T, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type lowerBound, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type upperBound>
    void DataBreakdown<Build::Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>>::OnPropertyGridChanged(wxPropertyGridEvent &e)
    {
        if (e.GetProperty() != prop)
        {
            e.Skip();
            return;
        }

        PackageT nPackage;
        nPackage.value = ::Atmos::FromString<typename BuildT::ValueT>(prop->GetValue().GetString().ToStdString());
        Edit(nPackage);

        e.Skip();
    }

    template<class T, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type lowerBound, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type upperBound>
    void DataBreakdown<Build::Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>>::CreateEditorPropertiesImpl(const ChildReference &afterThis)
    {
        prop = CreatePropertyEmplace<PropT>("Value", afterThis);
        prop->Enable(IsEditable());
        ValidatorT validator;
        validator.SetMin(lowerBound);
        validator.SetMax(upperBound);
        prop->SetValidator(validator);
        PropertyGrid()->Bind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
    }

    template<class T, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type lowerBound, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type upperBound>
    void DataBreakdown<Build::Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>>::UpdateEditorPropertiesImpl(DataViewSelection::Group &selected)
    {
        prop->Enable(IsEditable());

        prop->SetValue(static_cast<DataBreakdown*>(*selected.begin())->Get()->value.Get());
        for (auto loop = ++selected.begin(); loop != selected.end(); ++loop)
        {
            if (static_cast<DataBreakdown*>(*loop)->Get()->value != prop->GetValue().GetBool())
            {
                prop->SetValueToUnspecified();
                return;
            }
        }
    }

    template<class T, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type lowerBound, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type upperBound>
    void DataBreakdown<Build::Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>>::DestroyEditorPropertiesImpl(bool destroyTreeItem)
    {
        DestroyProperty(prop);
        PropertyGrid()->Unbind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
    }

    template<class T, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type lowerBound, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type upperBound>
    void DataBreakdown<Build::Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>>::SetEditableImpl(bool set)
    {
        if (prop)
            prop->Enable(set);
    }

    template<class T, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type lowerBound, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type upperBound>
    DataBreakdown<Build::Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent), prop(nullptr)
    {}

    template<class T, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type lowerBound, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type upperBound>
    DataBreakdown<Build::Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        prop(std::move(arg.prop))
    {}

    template<class T, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type lowerBound, typename ::Atmos::Detail::BoundedNumberFloatTransform<T>::Type upperBound>
    DataBreakdown<Build::Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>>& DataBreakdown<Build::Package<::Atmos::StaticBoundedNumber<T, lowerBound, upperBound>>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        prop = std::move(arg.prop);
        return *this;
    }

    template<class T>
    class DataBreakdown<Build::Package<::Atmos::FixedPoint<T>>> : public DataBreakdownBase<Build::Package<::Atmos::FixedPoint<T>>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        wxStringProperty *prop;

        void OnPropertyGridChanged(wxPropertyGridEvent &e);

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
    void DataBreakdown<Build::Package<::Atmos::FixedPoint<T>>>::OnPropertyGridChanged(wxPropertyGridEvent &e)
    {
        if (e.GetProperty() != prop)
        {
            e.Skip();
            return;
        }

        auto value = ::Atmos::FromString<BuildT>(prop->GetValue().GetString().ToStdString());
        if (Get()->value == value)
            return;

        PackageT nPackage;
        nPackage.value = value;
        Command::Edit<DataBreakdown>::Create(this, nPackage, GetName())->Commit();

        e.Skip();
    }

    template<class T>
    void DataBreakdown<Build::Package<::Atmos::FixedPoint<T>>>::CreateEditorPropertiesImpl(const ChildReference &afterThis)
    {
        prop = CreatePropertyEmplace<wxStringProperty>("Value", afterThis);
        prop->Enable(IsEditable());
        FixedPointValidator<T> validator;
        prop->SetValidator(validator);
        PropertyGrid()->Bind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
    }

    template<class T>
    void DataBreakdown<Build::Package<::Atmos::FixedPoint<T>>>::UpdateEditorPropertiesImpl(DataViewSelection::Group &selected)
    {
        prop->Enable(IsEditable());

        prop->SetValue(wxAny(static_cast<DataBreakdown*>(*selected.begin())->Get()->value.GetRawValue()));
        for (auto loop = ++selected.begin(); loop != selected.end(); ++loop)
        {
            if (static_cast<DataBreakdown*>(*loop)->Get()->value.GetRawValue() != prop->GetValue().GetLongLong())
            {
                prop->SetValue("");
                return;
            }
        }
    }

    template<class T>
    void DataBreakdown<Build::Package<::Atmos::FixedPoint<T>>>::DestroyEditorPropertiesImpl(bool destroyTreeItem)
    {
        DestroyProperty(prop);
        PropertyGrid()->Unbind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
    }

    template<class T>
    void DataBreakdown<Build::Package<::Atmos::FixedPoint<T>>>::SetEditableImpl(bool set)
    {
        if (prop)
            prop->Enable(set);
    }

    template<class T>
    DataBreakdown<Build::Package<::Atmos::FixedPoint<T>>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent), prop(nullptr)
    {
        SetAddCategory(false);
    }

    template<class T>
    DataBreakdown<Build::Package<::Atmos::FixedPoint<T>>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        prop(std::move(arg.prop))
    {
        SetAddCategory(false);
    }

    template<class T>
    DataBreakdown<Build::Package<::Atmos::FixedPoint<T>>>& DataBreakdown<Build::Package<::Atmos::FixedPoint<T>>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        prop = std::move(arg.prop);
        return *this;
    }

    template<>
    class DataBreakdown<Build::Package<String>> : public DataBreakdownBase<Build::Package<String>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
        typedef StringGroup::size_type GroupID;
    private:
        wxStringProperty *textProp;
        wxEnumProperty *choiceProp;
        StringGroup group;

        void OnPropertyGridChanged(wxPropertyGridEvent &e);

        void SetGroupImpl(bool previouslyUsingTextbox);
        // Find out if this property uses a textbox
        bool UsesTextbox() const;

        void CreateEditorPropertiesImpl(const ChildReference &afterThis) override final;
        void UpdateEditorPropertiesImpl(DataViewSelection::Group &selected) override final;
        void DestroyEditorPropertiesImpl(bool destroyTreeItem) override final;
        void SetEditableImpl(bool set) override final;
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);

        void SetGroup(const StringGroup &set);
        void SetGroup(StringGroup &&set);
        const StringGroup& GetGroup() const;
        GroupID AddToGroup(const BuildT &add);
        GroupID AddToGroup(BuildT &&add);
        void RemoveFromGroup(const BuildT &add);
        void RemoveFromGroup(GroupID id);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::FilePath>> : public DataBreakdownBase<Build::Package<::Atmos::FilePath>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        wxFileProperty *prop;
        ::Atmos::FilePath defaultFilePath;
        String wildcard;

        void OnPropertyGridChanged(wxPropertyGridEvent &e);

        void CreateEditorPropertiesImpl(const ChildReference &afterThis) override final;
        void UpdateEditorPropertiesImpl(DataViewSelection::Group &selected) override final;
        void DestroyEditorPropertiesImpl(bool destroyTreeItem) override final;
        void SetEditableImpl(bool set) override final;
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);

        void SetDefaultFilePath(const ::Atmos::FilePath &set);
        const ::Atmos::FilePath& GetDefaultFilePath() const;
        void SetWildcard(const String &set);
        const String& GetWildcard() const;
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::FileName>> : public DataBreakdownBase<Build::Package<::Atmos::FileName>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        wxStringProperty *prop;

        void OnPropertyGridChanged(wxPropertyGridEvent &e);

        void CreateEditorPropertiesImpl(const ChildReference &afterThis) override final;
        void UpdateEditorPropertiesImpl(DataViewSelection::Group &selected) override final;
        void DestroyEditorPropertiesImpl(bool destroyTreeItem) override final;
        void SetEditableImpl(bool set) override final;
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Percentage>> : public DataBreakdownBase<Build::Package<::Atmos::Percentage>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<BuildT::WrappedT>> value;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Angle>> : public DataBreakdownBase<Build::Package<::Atmos::Angle>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<BuildT::ValueT>> value;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Position3D>> : public DataBreakdownBase<Build::Package<::Atmos::Position3D>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<BuildT::ValueT>> x;
        DataBreakdown<Build::Package<BuildT::ValueT>> y;
        DataBreakdown<Build::Package<BuildT::ValueT>> z;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::GridPosition>> : public DataBreakdownBase<Build::Package<::Atmos::GridPosition>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<BuildT::ValueT>> x;
        DataBreakdown<Build::Package<BuildT::ValueT>> y;
        DataBreakdown<Build::Package<BuildT::ValueT>> z;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::RelativeGridPosition>> : public DataBreakdownBase<Build::Package<::Atmos::RelativeGridPosition>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<BuildT::ValueT>> x;
        DataBreakdown<Build::Package<BuildT::ValueT>> y;
        DataBreakdown<Build::Package<BuildT::ValueT>> z;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<class FlagPass>
    class DataBreakdown<Build::Package<::Atmos::Flags<FlagPass>>> : public DataBreakdownBase<Build::Package<::Atmos::Flags<FlagPass>>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
        typedef FlagPass FlagT;
    private:
        typedef DataManager<FlagT> DataManagerT;

        std::vector<wxBoolProperty*> checkboxProps;

        void OnPropertyGridChanged(wxPropertyGridEvent &e);
        bool IsInHere(wxPGProperty *find);

        void CreateEditorPropertiesImpl(const ChildReference &afterThis) override final;
        void UpdateEditorPropertiesImpl(DataViewSelection::Group &selected) override final;
        void DestroyEditorPropertiesImpl(bool destroyTreeItem) override final;
        void SetEditableImpl(bool set) override final;
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<class FlagsPass>
    void DataBreakdown<Build::Package<::Atmos::Flags<FlagsPass>>>::OnPropertyGridChanged(wxPropertyGridEvent &e)
    {
        if (!IsInHere(e.GetProperty()))
        {
            e.Skip();
            return;
        }

        auto focusProp = static_cast<wxBoolProperty*>(e.GetProperty());

        PackageT nPackage;
        nPackage = *Get();
        nPackage.value.Set(DataManagerT::FindFromString(focusProp->GetLabel().ToStdString())->GetValue(), focusProp->GetValue().GetBool());
        ChangePackage<DataBreakdown>(nPackage);

        e.Skip();
    }

    template<class FlagsPass>
    bool DataBreakdown<Build::Package<::Atmos::Flags<FlagsPass>>>::IsInHere(wxPGProperty *find)
    {
        for (auto &loop : checkboxProps)
        {
            if (loop == find)
                return true;
        }

        return false;
    }

    template<class FlagsPass>
    void DataBreakdown<Build::Package<::Atmos::Flags<FlagsPass>>>::CreateEditorPropertiesImpl(const ChildReference &afterThis)
    {
        for (auto &loop : DataManagerT::Get())
        {
            checkboxProps.push_back(CreatePropertyLabelEmplace<wxBoolProperty>(loop.GetString(), loop.GetString(), afterThis));
            checkboxProps.back()->Enable(IsEditable());
            checkboxProps.back()->SetAttribute("UseCheckbox", 1);
        }

        PropertyGrid()->Bind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
    }

    template<class FlagsPass>
    void DataBreakdown<Build::Package<::Atmos::Flags<FlagsPass>>>::UpdateEditorPropertiesImpl(DataViewSelection::Group &selected)
    {
        auto &got = *Get();
        auto checkboxLoop = checkboxProps.begin();
        for (auto &loop : DataManagerT::Get())
        {
            (*checkboxLoop)->SetValue(got.value.Get(loop.GetValue()));
            ++checkboxLoop;
        }
    }

    template<class FlagsPass>
    void DataBreakdown<Build::Package<::Atmos::Flags<FlagsPass>>>::DestroyEditorPropertiesImpl(bool destroyTreeItem)
    {
        for (auto loop = checkboxProps.begin(); loop != checkboxProps.end();)
        {
            DestroyProperty(*loop);
            loop = checkboxProps.erase(loop);
        }

        PropertyGrid()->Unbind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
    }

    template<class FlagsPass>
    void DataBreakdown<Build::Package<::Atmos::Flags<FlagsPass>>>::SetEditableImpl(bool set)
    {
        for(auto &loop : checkboxProps)
            loop->Enable(set);
    }

    template<class FlagsPass>
    DataBreakdown<Build::Package<::Atmos::Flags<FlagsPass>>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent)
    {}

    template<class FlagsPass>
    DataBreakdown<Build::Package<::Atmos::Flags<FlagsPass>>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        checkboxProps(std::move(arg.checkboxProps))
    {}

    template<class FlagsPass>
    DataBreakdown<Build::Package<::Atmos::Flags<FlagsPass>>>& DataBreakdown<Build::Package<::Atmos::Flags<FlagsPass>>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        checkboxProps = std::move(arg.checkboxProps);
        return *this;
    }

    template<class WrappedPackage>
    class DataBreakdown<Build::Package<::Atmos::Optional<WrappedPackage>>> : public DataBreakdownBase<Build::Package<::Atmos::Optional<WrappedPackage>>>
    {
    public:
        typedef WrappedPackage WrappedPackageT;
        typedef typename PackageT::BuildT BuildT;
    private:
        ::Atmos::EventAnyConnection validChangedConnection;

        void OnValidChanged(const DataBreakdownEditArgs &args);
        void AddAllChildren();
        void SubscribeEvents();

        void SetupImpl() override final;
        void OnEdited() override final;

        void CreateEditorPropertiesImpl(const ChildReference &afterThis) override final {}
    public:
        DataBreakdown<Build::Package<bool>> valid;
        DataBreakdown<WrappedPackageT> wrapped;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<class WrappedPackage>
    void DataBreakdown<Build::Package<::Atmos::Optional<WrappedPackage>>>::OnValidChanged(const DataBreakdownEditArgs &args)
    {
        wrapped.SetEditable(valid.Get()->Build());
    }

    template<class WrappedPackage>
    void DataBreakdown<Build::Package<::Atmos::Optional<WrappedPackage>>>::AddAllChildren()
    {
        AddChild(valid);
        AddChild(wrapped);
    }

    template<class WrappedPackage>
    void DataBreakdown<Build::Package<::Atmos::Optional<WrappedPackage>>>::SubscribeEvents()
    {
        validChangedConnection = valid.edited.Subscribe(&DataBreakdown::OnValidChanged, *this);
    }

    template<class WrappedPackage>
    void DataBreakdown<Build::Package<::Atmos::Optional<WrappedPackage>>>::SetupImpl()
    {
        valid.Setup(Get()->valid);
        wrapped.Setup(Get()->value);

        wrapped.SetEditable(valid.Get()->Build());
    }

    template<class WrappedPackage>
    void DataBreakdown<Build::Package<::Atmos::Optional<WrappedPackage>>>::OnEdited()
    {
        wrapped.SetEditable(valid.Get()->Build());
    }

    template<class WrappedPackage>
    DataBreakdown<Build::Package<::Atmos::Optional<WrappedPackage>>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        valid("Valid", this),
        wrapped("Wrapped", this)
    {
        AddAllChildren();
        wrapped.SetAddCategory(false);
        wrapped.SetAddTreePiece(false);
        SubscribeEvents();
    }

    template<class WrappedPackage>
    DataBreakdown<Build::Package<::Atmos::Optional<WrappedPackage>>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        valid(std::move(arg.valid), this),
        wrapped(std::move(arg.wrapped), this)
    {
        AddAllChildren();
        SubscribeEvents();
    }

        template<class WrappedPackage>
    DataBreakdown<Build::Package<::Atmos::Optional<WrappedPackage>>>& DataBreakdown<Build::Package<::Atmos::Optional<WrappedPackage>>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        valid = std::move(arg.valid);
        wrapped = std::move(arg.wrapped);
        return *this;
    }

    template<class T>
    class DataBreakdown<Build::Package<::Atmos::Range<T>>> : public DataBreakdownBase<Build::Package<::Atmos::Range<T>>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<T>> first;
        DataBreakdown<Build::Package<T>> second;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<class T>
    void DataBreakdown<Build::Package<::Atmos::Range<T>>>::AddAllChildren()
    {
        AddChild(first);
        AddChild(second);
    }

    template<class T>
    void DataBreakdown<Build::Package<::Atmos::Range<T>>>::SetupImpl()
    {
        first.Setup(Get()->first);
        second.Setup(Get()->second);
    }

    template<class T>
    DataBreakdown<Build::Package<::Atmos::Range<T>>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        first("First", this),
        second("Second", this)
    {
        AddAllChildren();
    }

    template<class T>
    DataBreakdown<Build::Package<::Atmos::Range<T>>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        first(std::move(arg.first), this),
        second(std::move(arg.second), this)
    {
        AddAllChildren();
    }

    template<class T>
    DataBreakdown<Build::Package<::Atmos::Range<T>>>& DataBreakdown<Build::Package<::Atmos::Range<T>>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        first = std::move(arg.first);
        second = std::move(arg.second);
        return *this;
    }
}