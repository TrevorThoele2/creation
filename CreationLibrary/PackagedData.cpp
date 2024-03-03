#include "PackagedData.h"

namespace Creation::Editing
{
    PackagedData::PackagedData() : type(typeid(nullptr))
    {}

    std::type_index PackagedData::Type() const
    {
        return type;
    }

    PackagedData::Base::~Base() = default;
}