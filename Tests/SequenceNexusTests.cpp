#include <catch.hpp>
#include "GeneralFixture.h"

#include <CreationLibrary/ListData.h>
#include <CreationLibrary/EditableNexusCommon.h>
#include <CreationLibrary/IntegerData.h>

#include <Arca/ReliquaryOrigin.h>

class SequenceNexusTestsFixture : public GeneralFixture
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
    class Nexus<SequenceNexusTestsFixture::ChildData> final :
        public EditableNexusCommon<SequenceNexusTestsFixture::ChildData>
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
    class NexusBatch<SequenceNexusTestsFixture::ChildData> final :
        public NexusBatchCommon<SequenceNexusTestsFixture::ChildData>
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

SCENARIO_METHOD(SequenceNexusTestsFixture, "sequence nexi")
{
    auto history = Creation::Editing::History();
    auto selection = Creation::Editing::NexusSelection();

    const auto reliquary = Arca::ReliquaryOrigin().Actualize();
    Creation::Editing::UI* ui = nullptr;

    GIVEN("list nexus")
    {
        std::list<ChildData> listData;

        auto sequence = Creation::Editing::Nexus<std::list<ChildData>>(
            listData,
            nullptr,
            Creation::Editing::NexusHistory(history, selection),
            *ui,
            *reliquary,
            "label");

        WHEN("adding default data")
        {
            auto added = sequence.Add();

            THEN("sequence has one child")
            {
                REQUIRE(sequence.Children().size() == 1);
            }

            THEN("added is first child")
            {
                REQUIRE(sequence.Children()[0] == added);
            }

            WHEN("releasing node")
            {
                auto released = sequence.Release(*added);

                THEN("sequence is empty")
                {
                    REQUIRE(sequence.Children().empty());
                }

                WHEN("reinstating node")
                {
                    auto reinstated = sequence.Reinstate(std::move(released));

                    THEN("sequence has one child")
                    {
                        REQUIRE(sequence.Children().size() == 1);
                    }

                    THEN("reinstated is first child")
                    {
                        REQUIRE(sequence.Children()[0] == reinstated);
                    }
                }
            }
        }
    }
}