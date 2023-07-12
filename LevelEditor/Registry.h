#pragma once

#include <wx/listbox.h>
#include <wx/button.h>
#include <unordered_map>

#include "wxWidgetsHelper.h"

namespace Creation
{
    template<class T>
    class Registry
    {
    public:
        typedef T ObjectT;
        typedef std::unordered_map<std::string, ObjectT> SelectedMap;
    protected:
        typedef std::pair<ObjectT, std::string> AddRet;
        AddRet MakeInvalidAddRet() const;
    private:
        bool multipleSelection;
        SelectedMap selectedObjects;

        wxButton *addButton;
        wxButton *removeButton;
        wxListBox *list;

        virtual AddRet AddImplementation() = 0;
        virtual bool RemoveImplementation(const std::string &remove) = 0;
        virtual ObjectT RetrieveImplementation(const std::string &retrieve) = 0;
        virtual bool CanEnableAdd() const = 0;
        virtual void OnSelectedChanged(ObjectT selected) {}
        virtual ObjectT GetInvalidValue() const = 0;

        void OnAddButton(wxCommandEvent &e);
        void OnRemoveButton(wxCommandEvent &e);
        void OnSelectList(wxCommandEvent &e);

        void SelectObject(ObjectT select, int n);
        void EnableAddButton(bool enable = true);
    public:
        Registry();
        virtual ~Registry() = 0 {}
        wxButton* InitAddButton(bool valid, wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, const wxString &name = wxButtonNameStr);
        wxButton* InitRemoveButton(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, const wxString &name = wxButtonNameStr);
        wxListBox* InitList(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, const wxString &name = wxListBoxNameStr);
        wxListBox* InitListMultipleSelect(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, const wxString &name = wxListBoxNameStr);
        void DestroyAddButton();
        void DestroyRemoveButton();
        void DestroyList();

        void Append(const std::string &append);
        void Remove(const std::string &remove);
        void Clear();

        void SetAddingValid(bool set);
        bool IsAddingValid() const;
        void DeselectAll();
        void CheckEnableAddButton();

        void SelectObject();
        void SelectObject(ObjectT select, const std::string &string);
        // Only recommended when single selection
        ObjectT GetSelectedObject();
        // Only recommended when single selection
        const ObjectT GetSelectedObject() const;
        // Only recommended when single selection
        std::string GetSelectedString() const;
        const SelectedMap& GetMultipleSelected() const;
        bool IsSelectedObjectValid() const;

        int FindPosition(const std::string &string) const;
        bool IsIn(const std::string &string) const;
        size_t GetCount() const;

        wxButton* GetAddButton();
        wxButton* GetRemoveButton();
        wxListBox* GetList();
        const wxButton* GetAddButton() const;
        const wxButton* GetRemoveButton() const;
        const wxListBox* GetList() const;
    };

    template<class T>
    typename Registry<T>::AddRet Registry<T>::MakeInvalidAddRet() const
    {
        return AddRet(GetInvalidValue(), "");
    }

    template<class T>
    void Registry<T>::OnAddButton(wxCommandEvent &e)
    {
        auto &added = AddImplementation();
        if (added.first != GetInvalidValue())
        {
            list->Append(added.second);
            SelectObject(added.first, added.second);
        }
    }

    template<class T>
    void Registry<T>::OnRemoveButton(wxCommandEvent &e)
    {
        wxArrayInt selections;
        list->GetSelections(selections);
        if (selections.empty())
            return;

        size_t count = 0;
        for (auto &loop : selections)
        {
            auto &string = list->GetString(loop).ToStdString();
            if (RemoveImplementation(string))
            {
                selectedObjects.erase(string);
                list->Delete(loop - count);
                ++count;
            }
        }

        CheckEnableAddButton();
        removeButton->Disable();
    }

    template<class T>
    void Registry<T>::OnSelectList(wxCommandEvent &e)
    {
        wxArrayInt selections;
        list->GetSelections(selections);
        if (selections.empty())
        {
            selectedObjects.clear();
            return;
        }

        for (auto &loop : selections)
        {
            auto &string = list->GetString(loop).ToStdString();
            if (selectedObjects.find(string) == selectedObjects.end())
            {
                SelectObject(RetrieveImplementation(string), loop);
                return;
            }
        }
    }

    template<class T>
    void Registry<T>::SelectObject(ObjectT select, int n)
    {
        bool sendEvent = false;
        if (multipleSelection)
        {
            // Multiple selection
            // You should not send a nullptr through in multiple selection mode
            if (select == GetInvalidValue())
                return;

            list->Select(n);
            auto &string = list->GetString(n);

            sendEvent = selectedObjects.find(string.ToStdString()) == selectedObjects.end();
            selectedObjects.emplace(string, select);

            EnableAddButton(false);
            removeButton->Enable();
        }
        else
        {
            // Single selection
            if (select == GetInvalidValue())
            {
                // Deselect object
                list->DeselectAll();

                sendEvent = !selectedObjects.empty();
                selectedObjects.clear();

                removeButton->Disable();
                CheckEnableAddButton();
            }
            else
            {
                // Select object
                list->Select(n);
                auto &string = list->GetString(n);

                sendEvent = selectedObjects.find(string.ToStdString()) == selectedObjects.end();
                selectedObjects.clear();
                selectedObjects.emplace(string, select);

                EnableAddButton(false);
                removeButton->Enable();
            }
        }

        if (sendEvent)
             OnSelectedChanged(std::forward<decltype(select)>(select));
    }

    template<class T>
    void Registry<T>::EnableAddButton(bool enable)
    {
        if (enable)
        {
            addButton->Enable();
            removeButton->Disable();
            selectedObjects.clear();
            list->DeselectAll();
        }
        else
            addButton->Disable();
    }

    template<class T>
    Registry<T>::Registry() : multipleSelection(false), addButton(nullptr), removeButton(nullptr)
    {}

    template<class T>
    wxButton* Registry<T>::InitAddButton(bool valid, wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, const wxString& name)
    {
        addButton = new wxButton(parent, id, "Add", pos, size, wxBU_EXACTFIT, wxDefaultValidator, name);
        addButton->Bind(wxEVT_BUTTON, &Registry::OnAddButton, this);
        addButton->Enable(valid);

        return addButton;
    }

    template<class T>
    wxButton* Registry<T>::InitRemoveButton(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, const wxString& name)
    {
        removeButton = new wxButton(parent, id, "Remove", pos, size, wxBU_EXACTFIT, wxDefaultValidator, name);
        removeButton->Bind(wxEVT_BUTTON, &Registry::OnRemoveButton, this);
        removeButton->Disable();
        return removeButton;
    }

    template<class T>
    wxListBox* Registry<T>::InitList(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, const wxString& name)
    {
        list = new wxListBox(parent, id, pos, size, 0, nullptr, wxLB_SORT | wxLB_ALWAYS_SB | wxLB_HSCROLL, wxDefaultValidator, name);
        list->Bind(wxEVT_LISTBOX, &Registry::OnSelectList, this);
        multipleSelection = false;
        return list;
    }

    template<class T>
    wxListBox* Registry<T>::InitListMultipleSelect(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, const wxString& name)
    {
        list = new wxListBox(parent, id, pos, size, 0, nullptr, wxLB_EXTENDED | wxLB_SORT | wxLB_ALWAYS_SB | wxLB_HSCROLL, wxDefaultValidator, name);
        list->Bind(wxEVT_LISTBOX, &Registry::OnSelectList, this);
        multipleSelection = true;
        return list;
    }

    template<class T>
    void Registry<T>::DestroyAddButton()
    {
        addButton->Destroy();
    }

    template<class T>
    void Registry<T>::DestroyRemoveButton()
    {
        removeButton->Destroy();
    }

    template<class T>
    void Registry<T>::DestroyList()
    {
        list->Destroy();
    }

    template<class T>
    void Registry<T>::Append(const std::string &append)
    {
        list->Append(std::move(append));
    }

    template<class T>
    void Registry<T>::Remove(const std::string &remove)
    {
        list->Delete(list->FindString(remove));

        auto found = selectedObjects.find(remove);
        if (found != selectedObjects.end())
            OnSelectedChanged(GetInvalidValue());
    }

    template<class T>
    void Registry<T>::Clear()
    {
        selectedObjects.clear();
        list->Clear();
        CheckEnableAddButton();
    }

    template<class T>
    void Registry<T>::SetAddingValid(bool set)
    {
        if (set)
        {
            EnableAddButton();
            DeselectAll();
        }
        else
        {
            EnableAddButton(false);
            (GetSelectedObject()) ? removeButton->Enable() : removeButton->Disable();
        }
    }

    template<class T>
    bool Registry<T>::IsAddingValid() const
    {
        return addButton->IsEnabled();
    }

    template<class T>
    void Registry<T>::DeselectAll()
    {
        list->DeselectAll();
        selectedObjects.clear();
        removeButton->Disable();
        OnSelectedChanged(GetInvalidValue());
    }

    template<class T>
    void Registry<T>::CheckEnableAddButton()
    {
        if (multipleSelection || !IsSelectedObjectValid())
            EnableAddButton(CanEnableAdd());
        else
            EnableAddButton(false);
    }

    template<class T>
    void Registry<T>::SelectObject()
    {
        SelectObject(GetInvalidValue(), 0);
    }

    template<class T>
    void Registry<T>::SelectObject(ObjectT select, const std::string &string)
    {
        SelectObject(select, list->FindString(string));
    }

    template<class T>
    typename Registry<T>::ObjectT Registry<T>::GetSelectedObject()
    {
        if (selectedObjects.empty())
            return GetInvalidValue();
        else
            return selectedObjects.begin()->second;
    }

    template<class T>
    typename const Registry<T>::ObjectT Registry<T>::GetSelectedObject() const
    {
        if (selectedObjects.empty())
            return GetInvalidValue();
        else
            return selectedObjects.begin()->second;
    }

    template<class T>
    std::string Registry<T>::GetSelectedString() const
    {
        if (selectedObjects.empty())
            return "";
        else
            return selectedObjects.begin()->first;
    }

    template<class T>
    typename const Registry<T>::SelectedMap& Registry<T>::GetMultipleSelected() const
    {
        return selectedObjects;
    }

    template<class T>
    bool Registry<T>::IsSelectedObjectValid() const
    {
        return GetSelectedObject() != GetInvalidValue();
    }

    template<class T>
    int Registry<T>::FindPosition(const std::string &string) const
    {
        return list->FindString(string);
    }

    template<class T>
    bool Registry<T>::IsIn(const std::string &string) const
    {
        return FindPosition(string) != wxNOT_FOUND;
    }

    template<class T>
    size_t Registry<T>::GetCount() const
    {
        return list->GetCount();
    }

    template<class T>
    wxButton* Registry<T>::GetAddButton()
    {
        return addButton;
    }

    template<class T>
    wxButton* Registry<T>::GetRemoveButton()
    {
        return removeButton;
    }

    template<class T>
    wxListBox* Registry<T>::GetList()
    {
        return list;
    }

    template<class T>
    const wxButton* Registry<T>::GetAddButton() const
    {
        return addButton;
    }

    template<class T>
    const wxButton* Registry<T>::GetRemoveButton() const
    {
        return removeButton;
    }

    template<class T>
    const wxListBox* Registry<T>::GetList() const
    {
        return list;
    }
}