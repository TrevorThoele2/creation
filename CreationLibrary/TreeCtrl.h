#pragma once

#include <wx/dataview.h>

namespace Creation
{
    class Store final : public wxDataViewModel
    {
    public:
        Store();

        wxDataViewItem Append(
            const wxDataViewItem& parent,
            const wxString& text,
            std::unique_ptr<wxClientData>&& data);
        wxDataViewItem Prepend(
            const wxDataViewItem& parent,
            const wxString& text,
            std::unique_ptr<wxClientData>&& data);
        wxDataViewItem Insert(
            const wxDataViewItem& parent,
            const wxDataViewItem& previous,
            const wxString& text,
            std::unique_ptr<wxClientData>&& data);
        void Delete(const wxDataViewItem& item);
        
        void SetText(const wxDataViewItem& item, const wxString& text);
        void SetData(const wxDataViewItem& item, std::unique_ptr<wxClientData>&& data);

        [[nodiscard]] wxDataViewItem ChildAt(const wxDataViewItem& parent, unsigned int pos) const;
        [[nodiscard]] size_t ChildrenCount(const wxDataViewItem& parent) const;
        [[nodiscard]] wxString TextOf(const wxDataViewItem& item) const;
        [[nodiscard]] wxClientData* DataOf(const wxDataViewItem& item) const;
        
        [[nodiscard]] bool IsContainer(const wxDataViewItem& item) const override;
        [[nodiscard]] wxDataViewItem GetParent(const wxDataViewItem& item) const override;
        unsigned int GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const override;
        [[nodiscard]] unsigned int GetColumnCount() const override;
        [[nodiscard]] wxString GetColumnType(unsigned int col) const override;
        bool SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned int col) override;
        void GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned int col) const override;
        [[nodiscard]] int Compare(
            const wxDataViewItem& item1,
            const wxDataViewItem& item2,
            unsigned column,
            bool ascending) const override;
    private:
        class Node
        {
        public:
            Node* parent;
            wxString text;
            std::unique_ptr<wxClientData> data;

            using Nodes = std::vector<std::unique_ptr<Node>>;
            Nodes children;

            Node(Node* parent, const wxString& text, std::unique_ptr<wxClientData>&& data);
            Node(Node&& arg) noexcept;
            Node& operator=(Node&& arg) noexcept;
        };

        std::unique_ptr<Node> root;
    private:
        [[nodiscard]] static Node* NodeFor(const wxDataViewItem& item);
        [[nodiscard]] static Node::Nodes::iterator IteratorFor(Node& parent, Node& item);
    };

    class TreeCtrl final : public wxDataViewCtrl
    {
    public:
        TreeCtrl();
        TreeCtrl(wxWindow* parent,
            wxWindowID id,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxDV_NO_HEADER,
            const wxValidator& validator = wxDefaultValidator);

        bool Create(wxWindow* parent,
            wxWindowID id,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxDV_NO_HEADER,
            const wxValidator& validator = wxDefaultValidator);

        [[nodiscard]] wxDataViewItem Append(
            const wxDataViewItem& parent,
            const wxString& text,
            std::unique_ptr<wxClientData>&& data = {});
        [[nodiscard]] wxDataViewItem Prepend(
            const wxDataViewItem& parent,
            const wxString& text,
            std::unique_ptr<wxClientData>&& data = {});
        [[nodiscard]] wxDataViewItem Insert(
            const wxDataViewItem& parent,
            const wxDataViewItem& previous,
            const wxString& text,
            std::unique_ptr<wxClientData>&& data = {});
        void Delete(const wxDataViewItem& item);

        void SetText(const wxDataViewItem& item, const wxString& text);
        void SetData(const wxDataViewItem& item, std::unique_ptr<wxClientData>&& data);
        [[nodiscard]] wxString TextOf(const wxDataViewItem& item) const;
        [[nodiscard]] wxClientData* DataOf(const wxDataViewItem& item) const;

        [[nodiscard]] wxDataViewItem ChildAt(const wxDataViewItem& parent, size_t position) const;
        [[nodiscard]] int ChildrenCount(const wxDataViewItem& parent) const;

        [[nodiscard]] wxDataViewColumn* GetSortingColumn() const override;
    private:
        wxObjectDataPtr<Store> store;

        [[nodiscard]] Store* ModelAsStore();
        [[nodiscard]] const Store* ModelAsStore() const;
    private:
        void OnSize(wxSizeEvent& event);
    private:
        wxDECLARE_EVENT_TABLE();
        wxDECLARE_DYNAMIC_CLASS_NO_ASSIGN(TreeCtrl);
    };
}