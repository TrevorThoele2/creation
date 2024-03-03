#include "ViewportStack.h"

namespace Creation
{
    ViewportCommands::ViewportCommands(State& state) :
        mouseLeftDown(),
        mouseLeftUp(),
        mouseRightDown(),
        mouseRightUp(),
        mouseMoved(),

        activate(std::bind(&ViewportCommands::Activate, this)),
        deactivate(std::bind(&ViewportCommands::Deactivate, this)),
        
        state(&state)
    {}

    void ViewportCommands::Activate()
    {
        state->isActive = true;
    }

    void ViewportCommands::Deactivate()
    {
        state->isActive = false;
        state->currentMousePosition.reset();
        state->previousMousePosition.reset();
    }

    ViewportStack::ViewportStack() : commands(state)
    {}

    ViewportStackReference::ViewportStackReference(State& state, Commands& commands) :
        state(state), commands(commands)
    {}
}