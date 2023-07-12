#pragma once

#include <wx/validate.h>
#include <wx/textentry.h>
#include <wx/window.h>
#include <wx/valnum.h>

#include <Atmos/FixedPoint.h>
#include <Atmos/StringUtility.h>

namespace Creation
{
    template<class T>
    class FixedPointValidator : public wxValidator
    {
    public:
        typedef ::Atmos::FixedPoint<T> ValueT;
        typedef typename ValueT::ValueT RawValueT;
        typedef typename ValueT::Radix Radix;
    private:
        ValueT *value;
        ValueT min;
        ValueT max;
        Radix radixPoint;
    public:
        FixedPointValidator(ValueT *value = nullptr, Radix radixPoint = ValueT::GetDefaultRadixPoint());
        FixedPointValidator(const FixedPointValidator &arg) = default;
        FixedPointValidator& operator=(const FixedPointValidator &arg) = default;

        FixedPointValidator* Clone() const override final;
        bool TransferFromWindow() override final;
        bool TransferToWindow() override final;
        bool Validate(wxWindow *parent) override final;

        void SetMin(RawValueT set);
        void SetMax(RawValueT set);
        RawValueT GetMin() const;
        RawValueT GetMax() const;
        void SetRadixPoint(Radix set);
        Radix GetRadixPoint() const;
    };

    template<class T>
    FixedPointValidator<T>::FixedPointValidator(ValueT *value, Radix radixPoint) : value(value), radixPoint(radixPoint)
    {
        min.SetRadixPoint(radixPoint);
        max.SetRadixPoint(radixPoint);
        SetMin(ValueT::GetLowest());
        SetMax(ValueT::GetMax());
    }

    template<class T>
    FixedPointValidator<T>* FixedPointValidator<T>::Clone() const
    {
        return new FixedPointValidator(*this);
    }

    template<class T>
    bool FixedPointValidator<T>::TransferFromWindow()
    {
        auto textEntry = reinterpret_cast<wxTextEntry*>(GetWindow());
        if (!textEntry)
            return false;

        if (!value)
            return true;

        *value = ::Atmos::FromString<ValueT>(textEntry->GetValue().ToStdString());
        return true;
    }

    template<class T>
    bool FixedPointValidator<T>::TransferToWindow()
    {
        auto textEntry = reinterpret_cast<wxTextEntry*>(GetWindow());
        if (!textEntry)
            return false;

        if (!value)
            return true;

        textEntry->SetValue(value->ToString());
        return true;
    }

    template<class T>
    bool FixedPointValidator<T>::Validate(wxWindow *parent)
    {
        auto textEntry = reinterpret_cast<wxTextEntry*>(GetWindow());
        if (!textEntry)
            return false;

        if (textEntry->GetValue().size() > ValueT::maxDigits)
            return false;

        size_t radixCount = 0;
        for (auto &loop : textEntry->GetValue())
        {
            if (loop.GetValue() == '.')
                return radixCount == radixPoint.Get();

            ++radixCount;
        }

        return false;
    }

    template<class T>
    void FixedPointValidator<T>::SetMin(RawValueT set)
    {
        min.SetRawValue(set);
    }

    template<class T>
    void FixedPointValidator<T>::SetMax(RawValueT set)
    {
        max.SetRawValue(set);
    }

    template<class T>
    typename FixedPointValidator<T>::RawValueT FixedPointValidator<T>::GetMin() const
    {
        return min.GetRawValue();
    }

    template<class T>
    typename FixedPointValidator<T>::RawValueT FixedPointValidator<T>::GetMax() const
    {
        return max.GetRawValue();
    }

    template<class T>
    void FixedPointValidator<T>::SetRadixPoint(Radix set)
    {
        radixPoint = set;
        min.SetRadixPoint(set);
        max.SetRadixPoint(set);
    }

    template<class T>
    typename FixedPointValidator<T>::Radix FixedPointValidator<T>::GetRadixPoint() const
    {
        return radixPoint;
    }
}