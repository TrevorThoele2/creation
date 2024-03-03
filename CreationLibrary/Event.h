#pragma once

#include <Chroma/Event.h>
#include <Atmos/AnyEventConnection.h>
#include <Chroma/ScopedEventConnection.h>

namespace Creation
{
    template<class... Args>
    using Event = Chroma::Event<Args...>;
    template<class... Args>
    using EventConnection = Chroma::EventConnection<Args...>;
    using Atmos::AnyEventConnection;
    using Chroma::ScopedEventConnection;
}