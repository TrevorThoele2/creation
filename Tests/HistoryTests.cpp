#include <catch.hpp>
#include "GeneralFixture.h"
#include <CreationLibrary/History.h>

#include "EventListener.h"

class HistoryTestsFixture : public GeneralFixture
{
public:

};

SCENARIO_METHOD(HistoryTestsFixture, "History")
{
    GIVEN("history")
    {
        auto history = Creation::Editing::History();

        auto onDo = EventListener(history.onDo);
        auto onUndo = EventListener(history.onUndo);
        auto onChanged = EventListener(history.onChanged);

        WHEN("querying initial state")
        {
            THEN("position is 0")
            {
                REQUIRE(history.Position() == 0);
            }

            THEN("cannot forward")
            {
                REQUIRE(!history.CanForward());
            }

            THEN("cannot reverse")
            {
                REQUIRE(!history.CanReverse());
            }
        }

        WHEN("reversing")
        {
            history.Reverse();

            THEN("position is 0")
            {
                REQUIRE(history.Position() == 0);
            }

            THEN("did not execute do event")
            {
                REQUIRE(onDo.Executions().empty());
            }

            THEN("did not execute reverse event")
            {
                REQUIRE(onUndo.Executions().empty());
            }

            THEN("did not execute changed event")
            {
                REQUIRE(onChanged.Executions().empty());
            }
        }

        WHEN("forwarding")
        {
            history.Forward();

            THEN("position is 0")
            {
                REQUIRE(history.Position() == 0);
            }

            THEN("did not execute do event")
            {
                REQUIRE(onDo.Executions().empty());
            }

            THEN("did not execute reverse event")
            {
                REQUIRE(onUndo.Executions().empty());
            }

            THEN("did not execute changed event")
            {
                REQUIRE(onChanged.Executions().empty());
            }
        }

        WHEN("clearing")
        {
            history.Clear();

            THEN("position is 0")
            {
                REQUIRE(history.Position() == 0);
            }

            THEN("did not execute do event")
            {
                REQUIRE(onDo.Executions().empty());
            }

            THEN("did not execute reverse event")
            {
                REQUIRE(onUndo.Executions().empty());
            }

            THEN("did not execute changed event")
            {
                REQUIRE(onChanged.Executions().empty());
            }
        }

        WHEN("pushing new command")
        {
            auto forwardCount = 0;
            auto reverseCount = 0;
            const auto function =
                [&forwardCount, &reverseCount](bool forward) { forward ? ++forwardCount : ++reverseCount; };

            const auto message = dataGeneration.Random<Creation::String>();

            history.Push(message, function);

            THEN("position is 1")
            {
                REQUIRE(history.Position() == 1);
            }

            THEN("moved forward once")
            {
                REQUIRE(forwardCount == 1);
            }

            THEN("did not move reverse")
            {
                REQUIRE(reverseCount == 0);
            }

            THEN("executed do event")
            {
                REQUIRE(onDo.Executions().size() == 1);
                REQUIRE(std::get<0>(onDo.Executions()[0]).message == message);
            }

            THEN("did not execute reverse event")
            {
                REQUIRE(onUndo.Executions().empty());
            }

            THEN("executed on changed")
            {
                REQUIRE(onChanged.Executions().size() == 1);
                REQUIRE(std::get<0>(onChanged.Executions()[0]) == &history);
            }

            WHEN("redoing")
            {
                history.Forward();

                THEN("position is 1")
                {
                    REQUIRE(history.Position() == 1);
                }

                THEN("moved forward once")
                {
                    REQUIRE(forwardCount == 1);
                }

                THEN("did not move reverse")
                {
                    REQUIRE(reverseCount == 0);
                }

                THEN("executed do event once")
                {
                    REQUIRE(onDo.Executions().size() == 1);
                    REQUIRE(std::get<0>(onDo.Executions()[0]).message == message);
                }

                THEN("did not execute reverse event")
                {
                    REQUIRE(onUndo.Executions().empty());
                }

                THEN("executed on changed once")
                {
                    REQUIRE(onChanged.Executions().size() == 1);
                    REQUIRE(std::get<0>(onChanged.Executions()[0]) == &history);
                }
            }

            WHEN("clearing")
            {
                history.Clear();

                THEN("position is 0")
                {
                    REQUIRE(history.Position() == 0);
                }

                THEN("moved forward once")
                {
                    REQUIRE(forwardCount == 1);
                }

                THEN("did not move reverse")
                {
                    REQUIRE(reverseCount == 0);
                }

                THEN("executed do event once")
                {
                    REQUIRE(onDo.Executions().size() == 1);
                    REQUIRE(std::get<0>(onDo.Executions()[0]).message == message);
                }

                THEN("did not execute reverse event")
                {
                    REQUIRE(onUndo.Executions().empty());
                }

                THEN("executed on changed twice")
                {
                    REQUIRE(onChanged.Executions().size() == 2);
                    REQUIRE(std::get<0>(onChanged.Executions()[0]) == &history);
                    REQUIRE(std::get<0>(onChanged.Executions()[1]) == &history);
                }
            }

            WHEN("undoing")
            {
                history.Reverse();

                THEN("position is 0")
                {
                    REQUIRE(history.Position() == 0);
                }

                THEN("moved forward once")
                {
                    REQUIRE(forwardCount == 1);
                }

                THEN("moved reverse once")
                {
                    REQUIRE(reverseCount == 1);
                }

                THEN("executed do event once")
                {
                    REQUIRE(onDo.Executions().size() == 1);
                    REQUIRE(std::get<0>(onDo.Executions()[0]).message == message);
                }

                THEN("executed reverse event once")
                {
                    REQUIRE(onUndo.Executions().size() == 1);
                    REQUIRE(std::get<0>(onUndo.Executions()[0]).message == message);
                }

                THEN("executed on changed twice")
                {
                    REQUIRE(onChanged.Executions().size() == 2);
                    REQUIRE(std::get<0>(onChanged.Executions()[0]) == &history);
                    REQUIRE(std::get<0>(onChanged.Executions()[1]) == &history);
                }

                WHEN("undoing")
                {
                    history.Reverse();

                    THEN("position is 0")
                    {
                        REQUIRE(history.Position() == 0);
                    }

                    THEN("moved forward once")
                    {
                        REQUIRE(forwardCount == 1);
                    }

                    THEN("moved reverse once")
                    {
                        REQUIRE(reverseCount == 1);
                    }

                    THEN("executed do event once")
                    {
                        REQUIRE(onDo.Executions().size() == 1);
                        REQUIRE(std::get<0>(onDo.Executions()[0]).message == message);
                    }

                    THEN("executed reverse event once")
                    {
                        REQUIRE(onUndo.Executions().size() == 1);
                        REQUIRE(std::get<0>(onUndo.Executions()[0]).message == message);
                    }

                    THEN("executed on changed twice")
                    {
                        REQUIRE(onChanged.Executions().size() == 2);
                        REQUIRE(std::get<0>(onChanged.Executions()[0]) == &history);
                        REQUIRE(std::get<0>(onChanged.Executions()[1]) == &history);
                    }
                }

                WHEN("clearing")
                {
                    history.Clear();

                    THEN("position is 0")
                    {
                        REQUIRE(history.Position() == 0);
                    }

                    THEN("moved forward once")
                    {
                        REQUIRE(forwardCount == 1);
                    }

                    THEN("moved reverse once")
                    {
                        REQUIRE(reverseCount == 1);
                    }

                    THEN("executed do event once")
                    {
                        REQUIRE(onDo.Executions().size() == 1);
                        REQUIRE(std::get<0>(onDo.Executions()[0]).message == message);
                    }

                    THEN("executed reverse event once")
                    {
                        REQUIRE(onUndo.Executions().size() == 1);
                        REQUIRE(std::get<0>(onUndo.Executions()[0]).message == message);
                    }

                    THEN("executed on changed three times")
                    {
                        REQUIRE(onChanged.Executions().size() == 3);
                        REQUIRE(std::get<0>(onChanged.Executions()[0]) == &history);
                        REQUIRE(std::get<0>(onChanged.Executions()[1]) == &history);
                        REQUIRE(std::get<0>(onChanged.Executions()[2]) == &history);
                    }
                }

                WHEN("redoing")
                {
                    history.Forward();

                    THEN("position is 1")
                    {
                        REQUIRE(history.Position() == 1);
                    }

                    THEN("moved forward twice")
                    {
                        REQUIRE(forwardCount == 2);
                    }

                    THEN("moved reverse once")
                    {
                        REQUIRE(reverseCount == 1);
                    }

                    THEN("executed do event twice")
                    {
                        REQUIRE(onDo.Executions().size() == 2);
                        REQUIRE(std::get<0>(onDo.Executions()[0]).message == message);
                        REQUIRE(std::get<0>(onDo.Executions()[1]).message == message);
                    }

                    THEN("executed reverse event once")
                    {
                        REQUIRE(onUndo.Executions().size() == 1);
                        REQUIRE(std::get<0>(onUndo.Executions()[0]).message == message);
                    }

                    THEN("executed on changed three times")
                    {
                        REQUIRE(onChanged.Executions().size() == 3);
                        REQUIRE(std::get<0>(onChanged.Executions()[0]) == &history);
                        REQUIRE(std::get<0>(onChanged.Executions()[1]) == &history);
                        REQUIRE(std::get<0>(onChanged.Executions()[2]) == &history);
                    }

                    WHEN("clearing")
                    {
                        history.Clear();

                        THEN("position is 0")
                        {
                            REQUIRE(history.Position() == 0);
                        }

                        THEN("moved forward once")
                        {
                            REQUIRE(forwardCount == 2);
                        }

                        THEN("moved reverse once")
                        {
                            REQUIRE(reverseCount == 1);
                        }

                        THEN("executed do event twice")
                        {
                            REQUIRE(onDo.Executions().size() == 2);
                            REQUIRE(std::get<0>(onDo.Executions()[0]).message == message);
                            REQUIRE(std::get<0>(onDo.Executions()[1]).message == message);
                        }

                        THEN("executed reverse event once")
                        {
                            REQUIRE(onUndo.Executions().size() == 1);
                            REQUIRE(std::get<0>(onUndo.Executions()[0]).message == message);
                        }

                        THEN("executed on changed four times")
                        {
                            REQUIRE(onChanged.Executions().size() == 4);
                            REQUIRE(std::get<0>(onChanged.Executions()[0]) == &history);
                            REQUIRE(std::get<0>(onChanged.Executions()[1]) == &history);
                            REQUIRE(std::get<0>(onChanged.Executions()[2]) == &history);
                            REQUIRE(std::get<0>(onChanged.Executions()[3]) == &history);
                        }
                    }
                }
            }
        }
    }
}