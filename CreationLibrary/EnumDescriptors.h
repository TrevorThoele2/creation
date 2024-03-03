#pragma once

#include <vector>
#include <optional>
#include "String.h"

namespace Creation::Editing
{
    template<class T>
    class EnumDescriptors
    {
    public:
        struct Entry
        {
            T value;
            String name;
            Entry(T value, const String& name);
        };
    public:
        EnumDescriptors(const std::vector<Entry>& entries);

        [[nodiscard]] std::optional<T> Value(const String& name) const;
        [[nodiscard]] const wxArrayInt& Values() const;
        [[nodiscard]] std::optional<String> Name(T value) const;
        [[nodiscard]] const wxArrayString& Names() const;
    private:
        std::vector<Entry> entries;

        wxArrayInt wxValues;
        wxArrayString wxNames;
    };

    template<class T>
    EnumDescriptors<T>::Entry::Entry(T value, const String& name) : value(value), name(name)
    {}

    template<class T>
    EnumDescriptors<T>::EnumDescriptors(const std::vector<Entry>& entries) : entries(entries)
    {
        wxNames.Alloc(entries.size());
        for (auto& entry : entries)
            wxNames.Add(entry.name);

        wxValues.Alloc(entries.size());
        for (auto& entry : entries)
            wxValues.Add(static_cast<std::underlying_type_t<T>>(entry.value));
    }

    template<class T>
    std::optional<T> EnumDescriptors<T>::Value(const String& name) const
    {
        for (auto& entry : entries)
            if (entry.name == name)
                return entry.value;

        return {};
    }

    template<class T>
    const wxArrayInt& EnumDescriptors<T>::Values() const
    {
        return wxValues;
    }

    template<class T>
    std::optional<String> EnumDescriptors<T>::Name(T value) const
    {
        for (auto& entry : entries)
            if (entry.value == value)
                return entry.name;

        return {};
    }

    template<class T>
    const wxArrayString& EnumDescriptors<T>::Names() const
    {
        return wxNames;
    }
}