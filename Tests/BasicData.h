#pragma once

#include <string>

#include <CreationLibrary/EditingPropertyIncludes.h>

class BasicData
{
public:
    int integer = 0;
    std::string string;

    BasicData() = default;
    BasicData(int integer, std::string string) : integer(integer), string(std::move(string))
    {}

    bool operator==(const BasicData& arg) const
    {
        return integer == arg.integer && string == arg.string;
    }
};

namespace Creation::Data
{
    template<>
    class EditingProperty<BasicData> final : public EditingPropertyTerminal<BasicData>
    {
    public:
        std::vector<DataSet> onDataSetChangedParameters;
    public:
        EditingProperty(const String& name, const String& label, EditingPropertyTerminal* parent) :
            EditingPropertyTerminal(name, label, parent)
        {}
    protected:
        void OnDataSetChanged(const DataSet& newDataSet) override
        {
            onDataSetChangedParameters.push_back(newDataSet);
        }
    };
}