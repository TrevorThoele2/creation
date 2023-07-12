#pragma once

#include <vector>
#include <wx/listbox.h>
#include <Atmos/String.h>
#include <Atmos/Event.h>

namespace Creation
{
    class OutputView
    {
    public:
        typedef size_t EntryCountT;
    private:
        struct Entry
        {
            typedef size_t SizeT;

            size_t size;
            Entry(SizeT size);
        };
    private:
        wxListBox *listbox;

        std::vector<Entry> entries;
        EntryCountT maxEntryCount;

        ::Atmos::EventScopedConnection onAtmosErrorConnection;

        void OnAtmosError(const ::Atmos::String &message);
        void OnListBox(wxCommandEvent &e);

        void CullEntries();
    public:
        OutputView(wxWindow *parent, EntryCountT maxEntryCount = 50);

        void OutputMessage(const ::Atmos::String &message, bool generateTimeStamp = false);
        void SetMaxEntryCount(EntryCountT set);

        wxListBox* GetListbox();
        const wxListBox* GetListbox() const;
    };
}