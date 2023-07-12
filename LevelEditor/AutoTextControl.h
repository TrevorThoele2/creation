#pragma once

#include <wx/textctrl.h>
#include <wx/valnum.h>
#include <memory>

#include <Function/Function.h>
#include "wxWidgetsHelper.h"

#include <Atmos/String.h>

namespace Creation
{
    template<class ValT, ValT minVal = std::numeric_limits<ValT>::min(), ValT maxVal = std::numeric_limits<ValT>::max(), ValT defaultVal = minVal>
    class AutoTextControl
    {
    public:
        typedef wxTextCtrl WrappedT;
        typedef ValT ValueT;

        // If false, then the default value will be reinstated and the first value is ignored
        typedef function::Function<std::pair<ValueT, bool>> RetrieveValueFunction;
        typedef function::Function<void, ValueT> OnSetFunction;
    private:
        template<class T>
        struct Traits;
        template<> struct Traits<char> { typedef wxIntegerValidator<char> Validator; };
        template<> struct Traits<unsigned char> { typedef wxIntegerValidator<unsigned char> Validator; };
        template<> struct Traits<signed char> { typedef wxIntegerValidator<signed char> Validator; };
        template<> struct Traits<short> { typedef wxIntegerValidator<short> Validator; };
        template<> struct Traits<unsigned short> { typedef wxIntegerValidator<unsigned short> Validator; };
        template<> struct Traits<int> { typedef wxIntegerValidator<int> Validator; };
        template<> struct Traits<unsigned int> { typedef wxIntegerValidator<unsigned int> Validator; };
        template<> struct Traits<long> { typedef wxIntegerValidator<long> Validator; };
        template<> struct Traits<unsigned long> { typedef wxIntegerValidator<unsigned long> Validator; };
        template<> struct Traits<long long> { typedef wxIntegerValidator<long long> Validator; };
        template<> struct Traits<unsigned long long> { typedef wxIntegerValidator<unsigned long long> Validator; };
        template<> struct Traits<float> { typedef wxFloatingPointValidator<float> Validator; };
        template<> struct Traits<double> { typedef wxFloatingPointValidator<double> Validator; };

        typedef Traits<ValT> TraitsT;
    private:
        WrappedT *wrapped;
        RetrieveValueFunction retrieveValue;
        OnSetFunction onSet;

        void OnLostFocus(wxFocusEvent &e);
        void OnSet(wxCommandEvent &e);
    public:
        AutoTextControl();
        AutoTextControl(const AutoTextControl &arg) = default;
        AutoTextControl(AutoTextControl &&arg);
        AutoTextControl& operator=(const AutoTextControl &arg) = default;
        AutoTextControl& operator=(AutoTextControl &&arg);

        WrappedT* InitWrapped(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, const wxString &name = wxTextCtrlNameStr);
        void SetupFunctions(RetrieveValueFunction &&retrieveValue, OnSetFunction &&onSet);
        void SetRetrieveValueFunction(RetrieveValueFunction &&set);
        void SetOnSetFunction(OnSetFunction &&set);
        void DestroyWrapped();

        void ResetValue();
        // WILL send the changed event
        void SetValue(ValueT set);
        // Will NOT send the changed event
        void ChangeValue(ValueT set);
        ValueT GetValue() const;
        constexpr ValueT GetMinimumValue() const;
        constexpr ValueT GetMaximumValue() const;
        constexpr ValueT GetDefaultValue() const;

        wxString GetString() const;

        void Enable(bool enable = true);
        void Disable();

        void SetValidator(const wxValidator &set);
    };

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::OnLostFocus(wxFocusEvent &e)
    {
        if (wrapped->GetValue() == "")
        {
            if (retrieveValue.IsValid())
            {
                auto &retrieved = retrieveValue.Execute();
                (!retrieved.second) ? ResetValue() : SetValue(retrieved.first);
            }
            else
                ResetValue();
        }

        e.Skip();
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::OnSet(wxCommandEvent &e)
    {
        if (wrapped->GetValue() != "" && onSet.IsValid())
            onSet.Execute(GetValue());
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    AutoTextControl<ValT, minVal, maxVal, defaultVal>::AutoTextControl() : wrapped(nullptr)
    {}

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    AutoTextControl<ValT, minVal, maxVal, defaultVal>::AutoTextControl(AutoTextControl &&arg) : wrapped(std::move(arg.wrapped)), retrieveValue(std::move(arg.retrieveValue)), onSet(std::move(arg.onSet))
    {}

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    AutoTextControl<ValT, minVal, maxVal, defaultVal>& AutoTextControl<ValT, minVal, maxVal, defaultVal>::operator=(AutoTextControl &&arg)
    {
        wrapped = std::move(arg.wrapped);
        retrieveValue = std::move(arg.retrieveValue);
        onSet = std::move(arg.onSet);
        return *this;
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    typename AutoTextControl<ValT, minVal, maxVal, defaultVal>::WrappedT* AutoTextControl<ValT, minVal, maxVal, defaultVal>::InitWrapped(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, const wxString &name)
    {
        typename TraitsT::Validator validator;
        validator.SetMin(GetMinimumValue());
        validator.SetMax(GetMaximumValue());
        wrapped = new wxTextCtrl(parent, id, "", pos, size, 0, validator, name);
        wrapped->Bind(wxEVT_KILL_FOCUS, &AutoTextControl::OnLostFocus, this);
        wrapped->Bind(wxEVT_TEXT, &AutoTextControl::OnSet, this);
        ResetValue();
        return wrapped;
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::SetupFunctions(RetrieveValueFunction &&retrieveValue, OnSetFunction &&onSet)
    {
        this->retrieveValue = std::move(retrieveValue);
        this->onSet = std::move(onSet);
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::SetRetrieveValueFunction(RetrieveValueFunction &&set)
    {
        retrieveValue = std::move(set);
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::SetOnSetFunction(OnSetFunction &&set)
    {
        onSet = std::move(set);
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::DestroyWrapped()
    {
        wrapped->Destroy();
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::ResetValue()
    {
        ChangeValue(GetDefaultValue());
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::SetValue(ValueT set)
    {
        wrapped->SetValue(std::to_string(set));
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::ChangeValue(ValueT set)
    {
        wrapped->ChangeValue(std::to_string(set));
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    typename AutoTextControl<ValT, minVal, maxVal, defaultVal>::ValueT AutoTextControl<ValT, minVal, maxVal, defaultVal>::GetValue() const
    {
        return Atmos::FromString<ValT>(wrapped->GetValue().ToStdString());
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    typename constexpr AutoTextControl<ValT, minVal, maxVal, defaultVal>::ValueT AutoTextControl<ValT, minVal, maxVal, defaultVal>::GetMinimumValue() const
    {
        return minVal;
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    typename constexpr AutoTextControl<ValT, minVal, maxVal, defaultVal>::ValueT AutoTextControl<ValT, minVal, maxVal, defaultVal>::GetMaximumValue() const
    {
        return maxVal;
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    typename constexpr AutoTextControl<ValT, minVal, maxVal, defaultVal>::ValueT AutoTextControl<ValT, minVal, maxVal, defaultVal>::GetDefaultValue() const
    {
        return defaultVal;
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    wxString AutoTextControl<ValT, minVal, maxVal, defaultVal>::GetString() const
    {
        return wrapped->GetValue();
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::Enable(bool enable)
    {
        wrapped->Enable(enable);
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::Disable()
    {
        wrapped->Disable();
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::SetValidator(const wxValidator &set)
    {
        wrapped->SetValidator(set);
    }
}