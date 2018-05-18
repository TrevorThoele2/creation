#pragma once

#include <vector>

#include <wx/listbox.h>

#include "String.h"

namespace Creation
{
    class OutputView
    {
    public:
        using EntryCount = size_t;
    public:
        OutputView(wxWindow* parent, EntryCount maxEntryCount);

        void OutputMessage(const String& message);
        void SetMaxEntryCount(EntryCount set);

        [[nodiscard]] wxListBox* Listbox();
        [[nodiscard]] const wxListBox* Listbox() const;
    private:
        wxListBox* listbox = nullptr;

        using LineCount = size_t;
        std::vector<LineCount> messageCounts;
        EntryCount maxEntryCount;

        [[nodiscard]] std::vector<String> MessageToTokens(const String& message);

        void CullEntries();
        void MoveToBottom();
    private:
        void OnListboxResize(const wxSizeEvent&);
    };
}