#pragma once

#include "Command.h"
#include <Atmos/Point2D.h>
#include "Point.h"
#include <Arca/Reliquary.h>

namespace Creation
{
    class ViewportState
    {
    public:
        bool isActive = false;

        std::optional<wxPoint> currentMousePosition;
        std::optional<wxPoint> previousMousePosition;
        
        Arca::Reliquary* reliquary = nullptr;
    };

    class ViewportCommands
    {
    public:
        using State = ViewportState;

        Command<Atmos::Spatial::Point2D> mouseLeftDown;
        Command<Atmos::Spatial::Point2D> mouseLeftUp;
        Command<Atmos::Spatial::Point2D> mouseRightDown;
        Command<Atmos::Spatial::Point2D> mouseRightUp;
        Command<Atmos::Spatial::Point2D> mouseMoved;

        Command<> activate;
        Command<> deactivate;
    public:
        ViewportCommands(State& state);
    private:
        State* state;
    private:
        void Activate();
        void Deactivate();
    };

    struct ViewportStack
    {
        using State = ViewportState;
        State state;

        using Commands = ViewportCommands;
        Commands commands;

        ViewportStack();
    };

    struct ViewportStackReference
    {
        using State = ViewportState;
        State& state;

        using Commands = ViewportCommands;
        Commands& commands;

        ViewportStackReference(State& state, Commands& commands);
    };
}
