
#include "OutputView.h"

#include <Atmos/Error.h>
#include <Atmos/StringUtility.h>

namespace Creation
{
    OutputView::Entry::Entry(SizeT size) : size(size)
    {}

    void OutputView::OnAtmosError(const ::Atmos::String &message)
    {
        OutputMessage(message);
    }

    void OutputView::OnListBox(wxCommandEvent &e)
    {
        listbox->DeselectAll();
    }

    void OutputView::CullEntries()
    {
        auto loop = entries.begin();
        while (entries.size() > maxEntryCount)
        {
            for (Entry::SizeT entryLoop = 0; entryLoop != loop->size; ++entryLoop)
                listbox->Delete(0);
            loop = entries.erase(loop);
        }
    }

    OutputView::OutputView(wxWindow *parent, EntryCountT maxEntryCount) : listbox(new wxListBox(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxLB_ALWAYS_SB | wxLB_HSCROLL)), maxEntryCount(maxEntryCount)
    {
        onAtmosErrorConnection.Set(::Atmos::ErrorHandler::Instance().onLogged.Subscribe(&OutputView::OnAtmosError, *this));
        listbox->Bind(wxEVT_LISTBOX, &OutputView::OnListBox, this);
    }

    void OutputView::OutputMessage(const ::Atmos::String &message, bool generateTimeStamp)
    {
        size_t startIndex(0);
        size_t substrLength(1);
        size_t currentIndex(0);
        Entry::SizeT entrySize(0);

        if (generateTimeStamp)
        {
            listbox->Append(::Atmos::ToString(listbox->GetCount()) + ":>  " + ::Atmos::ErrorHandler::GetTimeValue());
            ++entrySize;
        }

        bool moveToBottom = (listbox->GetCount() >= static_cast<unsigned int>(listbox->GetCountPerPage()))
            ? (listbox->GetCount() - static_cast<unsigned int>(listbox->GetCountPerPage())) >= static_cast<unsigned int>(listbox->GetTopItem())
            : true;
        for (auto loop = message.begin(); loop != message.end(); ++loop, ++currentIndex)
        {
            if (*loop == '\n')
            {
                ::Atmos::String substr(message.substr(startIndex, substrLength - 1));
                if (substr == "")
                {
                    substrLength = 1;
                    continue;
                }

                listbox->Append(::Atmos::ToString(listbox->GetCount()) + ":>  " + substr);
                ++entrySize;
                startIndex = currentIndex + 1;
                substrLength = 1;
            }
            else
                ++substrLength;
        }

        if (substrLength > 1)
        {
            listbox->Append(::Atmos::ToString(listbox->GetCount()) + ":>  " + message.substr(startIndex, substrLength - 1));
            ++entrySize;
        }

        if (entrySize > 0)
        {
            listbox->Append(::Atmos::ToString(listbox->GetCount()) + ":>");
            entries.push_back(Entry(entrySize + 1));
        }

        if (moveToBottom)
            listbox->EnsureVisible(listbox->GetCount() - 1);

        CullEntries();
    }

    void OutputView::SetMaxEntryCount(EntryCountT set)
    {
        maxEntryCount = set;
        CullEntries();
    }

    wxListBox* OutputView::GetListbox()
    {
        return listbox;
    }

    const wxListBox* OutputView::GetListbox() const
    {
        return listbox;
    }
}