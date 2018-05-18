#include "OutputView.h"

#include <Atmos/StringUtility.h>

namespace Creation
{
    OutputView::OutputView(wxWindow* parent, EntryCount maxEntryCount) :
        listbox(new wxListBox(
            parent,
            wxID_ANY,
            wxDefaultPosition,
            wxDefaultSize,
            0,
            nullptr,
            wxLB_ALWAYS_SB | wxLB_HSCROLL)),
        maxEntryCount(maxEntryCount)
    {
        listbox->Bind(wxEVT_SIZE, &OutputView::OnListboxResize, this);
    }

    void OutputView::OutputMessage(const String& message)
    {
        listbox->Freeze();

        const auto messageTokens = MessageToTokens(message);

        for(auto& token : messageTokens)
            listbox->Append(token);

        messageCounts.emplace_back(messageTokens.size());

        CullEntries();
        MoveToBottom();

        listbox->Thaw();
    }

    void OutputView::SetMaxEntryCount(EntryCount set)
    {
        maxEntryCount = set;
        CullEntries();
    }

    wxListBox* OutputView::Listbox()
    {
        return listbox;
    }

    const wxListBox* OutputView::Listbox() const
    {
        return listbox;
    }

    std::vector<String> OutputView::MessageToTokens(const String& message)
    {
        auto messageTokens = Chroma::Split(message, String("\n"));
        for (auto& token : messageTokens)
            token = Chroma::Trim(token);

        for (auto token = messageTokens.begin() + 1; token != messageTokens.end(); ++token)
        {
            const auto whitespace = "        ";
            token->insert(0, whitespace);
        }
        return messageTokens;
    }

    void OutputView::CullEntries()
    {
        auto messageCount = messageCounts.begin();
        while (messageCounts.size() > maxEntryCount)
        {
            for (LineCount line = 0; line < *messageCount; ++line)
                listbox->Delete(0);
            messageCount = messageCounts.erase(messageCount);
        }
    }

    void OutputView::MoveToBottom()
    {
        if (listbox->IsEmpty())
            return;

        const auto ensureIDVisible = static_cast<int>(listbox->GetCount() - 1u);
        listbox->EnsureVisible(ensureIDVisible);
    }

    void OutputView::OnListboxResize(const wxSizeEvent&)
    {
        MoveToBottom();
    }
}