#pragma once

#include "SequenceNexusBase.h"
#include "NexusHistory.h"

namespace Creation::Editing
{
    class PropertiesTree;
}

namespace Creation::Editing::Data
{
    class Root
    {
    public:
        explicit Root(bool visible, const NexusHistory& nexusHistory);
        Root(const Root& arg) = delete;
        Root(Root&& arg) noexcept = default;

        virtual ~Root() = 0;

        void CreateTreeElements(PropertiesTree& tree);
        void DestroyTreeElements();

        void Show();
        void Hide();
        [[nodiscard]] bool IsVisible() const;
    protected:
        [[nodiscard]] virtual std::vector<SequenceNexusBase*> TopNexi() { return {}; }
    protected:
        [[nodiscard]] const NexusHistory& RetrieveNexusHistory() const;
    private:
        bool visible;

        Editing::NexusHistory nexusHistory;
    };
}