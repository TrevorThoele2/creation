#pragma once

#include <wx/propgrid/propgrid.h>

#include <vector>
#include "NexusCommon.h"
#include "EditableNexusBase.h"

#include "NexusBatch.h"
#include "NexusBatchBase.h"

#include <Atmos/AnyEventConnection.h>

namespace Creation::Editing
{
    template<class Data>
    class EditableNexusCommon : public NexusCommon<Data, true>, public EditableNexusBase
    {
    private:
        using BaseT = NexusCommon<Data, true>;
    public:
        using DataT = typename BaseT::DataT;

        using BatchT = NexusBatch<DataT>;

        using LabelRetriever = typename BaseT::LabelRetriever;
    public:
        EditableNexusCommon(
            DataT& data,
            NexusNode* parent,
            NexusHistory nexusHistory,
            UI& ui,
            Arca::Reliquary& reliquary,
            const String& label);
        EditableNexusCommon(EditableNexusCommon&& arg, NexusNode* parent) noexcept;
        virtual ~EditableNexusCommon() = 0;

        std::unique_ptr<NexusBatchBase> StartEditingBatch(wxPropertyGrid& grid) override;
    protected:
        std::vector<AnyEventConnection> eventConnections;

        using BaseT::OwningUI;
        using BaseT::RetrieveNexusHistory;
    };

    template <class Data>
    EditableNexusCommon<Data>::EditableNexusCommon(
        DataT& data,
        NexusNode* parent,
        NexusHistory nexusHistory,
        UI& ui,
        Arca::Reliquary& reliquary,
        const String& label)
        :
        NexusCommon<Data, true>(data, parent, nexusHistory, ui, reliquary, label)
    {}

    template <class Data>
    EditableNexusCommon<Data>::EditableNexusCommon(EditableNexusCommon&& arg, NexusNode* parent) noexcept :
        NexusCommon<Data, true>(std::move(arg), parent)
    {}

    template <class Data>
    EditableNexusCommon<Data>::~EditableNexusCommon() = default;

    template<class Data>
    std::unique_ptr<NexusBatchBase> EditableNexusCommon<Data>::StartEditingBatch(wxPropertyGrid& grid)
    {
        auto batch = std::make_unique<BatchT>(grid, RetrieveNexusHistory(), OwningUI());
        batch->Add(static_cast<Nexus<Data>&>(*this));
        grid.Refresh();
        return batch;
    }
}