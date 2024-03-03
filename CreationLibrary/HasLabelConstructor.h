#pragma once

#include <type_traits>
#include "Nexus.h"
#include "NexusNode.h"
#include "NexusHistory.h"
#include <Arca/Reliquary.h>

namespace Creation::Editing
{
    class UI;

    template<class T, class Enable = void>
    struct has_label_constructor : std::false_type
    {};

    template<class DataT>
    struct has_label_constructor<
        DataT,
        std::void_t<decltype(void(Nexus<DataT>
        {
            std::declval<DataT&>(),
            std::declval<NexusNode*>(),
            std::declval<NexusHistory>(),
            std::declval<UI&>(),
            std::declval<Arca::Reliquary&>(),
            std::declval<const String&>()
        })) >>
        : std::true_type
    {};

    template<class T>
    static constexpr bool has_label_constructor_v = has_label_constructor<T>::value;
}