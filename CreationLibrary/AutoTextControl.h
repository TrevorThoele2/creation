#pragma once

#include <wx/textctrl.h>
#include <wx/valnum.h>
#include <functional>

#include "wxWidgetsHelper.h"
#include "ValidatorTraits.h"

#include <Atmos/String.h>
#include <Atmos/StringUtility.h>

namespace Creation
{
    template<
        class ValT,
        ValT minVal = std::numeric_limits<ValT>::min(),
        ValT maxVal = std::numeric_limits<ValT>::max(),
        ValT defaultVal = minVal>
    class AutoTextControl
    {
    public:
        using WrappedT = wxTextCtrl;
        using ValueT = ValT;

        // If false, then the default value will be reinstated and the first value is ignored
        using RetrieveValueFunction = std::function<std::pair<ValueT, bool>()>;
        using OnSetFunction = std::function<void(ValueT)>;
        using OnEnterFunction = std::function<void()>;
    public:
        AutoTextControl() = default;
        AutoTextControl(const AutoTextControl& arg) = default;
        AutoTextControl(AutoTextControl&& arg);
        AutoTextControl& operator=(const AutoTextControl& arg) = default;
        AutoTextControl& operator=(AutoTextControl&& arg);

        WrappedT* InitWrapped(
            wxWindow* parent,
            wxWindowID id = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            const wxString& name = wxTextCtrlNameStr);
        void SetupFunctionsSet(RetrieveValueFunction&& retrieveValue, OnSetFunction&& onSet);
        void SetupFunctionsEnter(RetrieveValueFunction&& retrieveValue, OnEnterFunction&& onEnter);
        void SetRetrieveValueFunction(RetrieveValueFunction&& set);
        void SetOnSetFunction(OnSetFunction&& set);
        void SetOnEnterFunction(OnEnterFunction&& set);
        void DestroyWrapped();

        void ResetValue();
        // WILL send the changed event
        void SetValue(ValueT set);
        // Will NOT send the changed event
        void ChangeValue(ValueT set);
        ValueT GetValue() const;
        constexpr static ValueT GetMinimumValue();
        constexpr static ValueT GetMaximumValue();
        constexpr static ValueT GetDefaultValue();

        wxString GetString() const;

        void Enable(bool enable = true);
        void Disable();

        void SetValidator(const wxValidator& set);
    private:
        WrappedT* wrapped = nullptr;
        RetrieveValueFunction retrieveValue;
        OnSetFunction onSet;
        OnEnterFunction onEnter;

        void OnLostFocus(wxFocusEvent& e);
        void OnSet(wxCommandEvent& e);
        void OnEnter(wxCommandEvent& e);
    private:
        using Validator = typename ValidatorTraits<ValT>::Validator;
    };

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    AutoTextControl<ValT, minVal, maxVal, defaultVal>::AutoTextControl(
        AutoTextControl&& arg) :
        wrapped(std::move(arg.wrapped)),
        retrieveValue(std::move(arg.retrieveValue)),
        onSet(std::move(arg.onSet)),
        onEnter(std::move(arg.onEnter))
    {}

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    AutoTextControl<ValT, minVal, maxVal, defaultVal>& AutoTextControl<ValT, minVal, maxVal, defaultVal>::operator=(
        AutoTextControl&& arg)
    {
        wrapped = std::move(arg.wrapped);
        retrieveValue = std::move(arg.retrieveValue);
        onSet = std::move(arg.onSet);
        onEnter = std::move(arg.onEnter);
        return *this;
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    typename AutoTextControl<ValT, minVal, maxVal, defaultVal>::WrappedT* AutoTextControl<ValT, minVal, maxVal, defaultVal>::InitWrapped(
        wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, const wxString& name)
    {
        Validator validator;
        validator.SetMin(GetMinimumValue());
        validator.SetMax(GetMaximumValue());
        wrapped = new wxTextCtrl(parent, id, "", pos, size, wxTE_PROCESS_ENTER, validator, name);
        wrapped->Bind(wxEVT_KILL_FOCUS, &AutoTextControl::OnLostFocus, this);
        wrapped->Bind(wxEVT_TEXT, &AutoTextControl::OnSet, this);
        wrapped->Bind(wxEVT_TEXT_ENTER, &AutoTextControl::OnEnter, this);
        ResetValue();
        return wrapped;
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::SetupFunctionsSet(
        RetrieveValueFunction&& retrieveValue, OnSetFunction&& onSet)
    {
        this->retrieveValue = std::move(retrieveValue);
        this->onSet = std::move(onSet);
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::SetupFunctionsEnter(
        RetrieveValueFunction&& retrieveValue, OnEnterFunction&& onEnter)
    {
        this->retrieveValue = std::move(retrieveValue);
        this->onEnter = std::move(onEnter);
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::SetRetrieveValueFunction(
        RetrieveValueFunction&& set)
    {
        retrieveValue = std::move(set);
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::SetOnSetFunction(
        OnSetFunction&& set)
    {
        onSet = std::move(set);
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::SetOnEnterFunction(
        OnEnterFunction&& set)
    {
        onEnter = std::move(set);
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
    auto AutoTextControl<ValT, minVal, maxVal, defaultVal>::GetValue() const -> ValueT
    {
        return Atmos::FromString<ValT>(wrapped->GetValue().ToStdString());
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    constexpr auto AutoTextControl<ValT, minVal, maxVal, defaultVal>::GetMinimumValue() -> ValueT
    {
        return minVal;
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    constexpr auto AutoTextControl<ValT, minVal, maxVal, defaultVal>::GetMaximumValue() -> ValueT
    {
        return maxVal;
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    constexpr auto AutoTextControl<ValT, minVal, maxVal, defaultVal>::GetDefaultValue() -> ValueT
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
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::SetValidator(const wxValidator& set)
    {
        wrapped->SetValidator(set);
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::OnLostFocus(wxFocusEvent& e)
    {
        if (wrapped->GetValue() == "")
        {
            if (retrieveValue)
            {
                auto retrieved = retrieveValue();
                (!retrieved.second) ? ResetValue() : SetValue(retrieved.first);
            }
            else
                ResetValue();
        }

        e.Skip();
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::OnSet(wxCommandEvent& e)
    {
        if (wrapped->GetValue() != "" && onSet)
            onSet(GetValue());
    }

    template<class ValT, ValT minVal, ValT maxVal, ValT defaultVal>
    void AutoTextControl<ValT, minVal, maxVal, defaultVal>::OnEnter(wxCommandEvent& e)
    {
        if (wrapped->GetValue() != "" && onEnter)
            onEnter();
    }
}