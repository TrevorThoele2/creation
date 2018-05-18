#include <catch.hpp>
#include "GeneralFixture.h"

#include <CreationLibrary/ListData.h>
#include <CreationLibrary/EditableNexusCommon.h>
#include <CreationLibrary/IntegerData.h>

#include <Arca/ReliquaryOrigin.h>

class NexusHistoryTestsFixture : public GeneralFixture
{
public:
    class ChildData
    {
    public:
        int integer = 0;
    public:
        ChildData() = default;
        ChildData(const ChildData& arg) = default;
        ChildData& operator=(const ChildData& arg) = default;
    };
};

namespace Creation::Editing
{
    template<>
    class Nexus<NexusHistoryTestsFixture::ChildData> final :
        public EditableNexusCommon<NexusHistoryTestsFixture::ChildData>
    {
    public:
        Nexus<int> integer;
    public:
        Nexus(
            DataT& data,
            NexusNode* parent,
            NexusHistory nexusHistory,
            UI& ui,
            Arca::Reliquary& reliquary)
            :
            EditableNexusCommon(data, parent, nexusHistory, ui, reliquary, "childData"),
            integer(data.integer, this, nexusHistory, ui, reliquary, "integer")
        {}

        Nexus(Nexus&& arg, NexusNode* parent) noexcept :
            EditableNexusCommon(std::move(arg), parent),
            integer(std::move(arg.integer), this)
        {}

        Nexus(Nexus&& arg) noexcept = default;
    };

    template<>
    class NexusBatch<NexusHistoryTestsFixture::ChildData> final :
        public NexusBatchCommon<NexusHistoryTestsFixture::ChildData>
    {
    public:
        NexusBatch(wxPropertyGrid& grid, NexusHistory nexusHistory, UI& ui) :
            NexusBatchCommon(grid)
        {}

        NexusBatch(NexusBatch&& arg) noexcept :
            NexusBatchCommon(std::move(arg))
        {}
    };
}

SCENARIO_METHOD(NexusHistoryTestsFixture, "nexus history")
{
    auto history = Creation::Editing::History();
    auto selection = Creation::Editing::NexusSelection();

    const auto reliquary = Arca::ReliquaryOrigin().Actualize();
    Creation::Editing::UI* ui = nullptr;

    GIVEN("nexus history")
    {
        std::list<ChildData> listData;

        auto nexusHistory = Creation::Editing::NexusHistory(history, selection);

        auto sequence = Creation::Editing::Nexus<std::list<ChildData>>(
            listData,
            nullptr,
            Creation::Editing::NexusHistory(history, selection),
            *ui,
            *reliquary,
            "label");

        WHEN("adding")
        {
            auto added = sequence.Add();
            nexusHistory.Add({ added });

            WHEN("reversing")
            {
                history.Reverse();

                THEN("sequence is empty")
                {
                    REQUIRE(sequence.Children().empty());
                }

                WHEN("going forward")
                {
                    history.Forward();

                    THEN("sequence has one child")
                    {
                        REQUIRE(sequence.Children().size() == 1);
                    }
                }
            }
        }
    }
}