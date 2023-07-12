#pragma once

#include <Atmos/Event.h>

namespace Creation
{
    template<class... Args>
    using Event = ::Atmos::Event<Args...>;
    typedef ::Atmos::NullEvent NullEvent;
}