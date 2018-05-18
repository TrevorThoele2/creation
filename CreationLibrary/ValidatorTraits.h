#pragma once

#include <wx/valnum.h>

namespace Creation
{
    template<class T>
    struct ValidatorTraits;

    template<>
    struct ValidatorTraits<char>
    {
        using Validator = wxIntegerValidator<char>;
    };

    template<>
    struct ValidatorTraits<unsigned char>
    {
        using Validator = wxIntegerValidator<unsigned char>;
    };

    template<>
    struct ValidatorTraits<signed char>
    {
        using Validator = wxIntegerValidator<signed char>;
    };

    template<>
    struct ValidatorTraits<short>
    {
        using Validator = wxIntegerValidator<short>;
    };

    template<>
    struct ValidatorTraits<unsigned short>
    {
        using Validator = wxIntegerValidator<unsigned short>;
    };

    template<>
    struct ValidatorTraits<int>
    {
        using Validator = wxIntegerValidator<int>;
    };

    template<>
    struct ValidatorTraits<unsigned int>
    {
        using Validator = wxIntegerValidator<unsigned int>;
    };

    template<>
    struct ValidatorTraits<long>
    {
        using Validator = wxIntegerValidator<long>;
    };

    template<>
    struct ValidatorTraits<unsigned long>
    {
        using Validator = wxIntegerValidator<unsigned long>;
    };

    template<>
    struct ValidatorTraits<long long>
    {
        using Validator = wxIntegerValidator<long long>;
    };

    template<>
    struct ValidatorTraits<unsigned long long>
    {
        using Validator = wxIntegerValidator<unsigned long long>;
    };

    template<>
    struct ValidatorTraits<float>
    {
        using Validator = wxFloatingPointValidator<float>;
    };

    template<>
    struct ValidatorTraits<double>
    {
        using Validator = wxFloatingPointValidator<double>;
    };
}
