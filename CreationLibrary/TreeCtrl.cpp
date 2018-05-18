#include "TreeCtrl.h"

namespace Creation
{
    Store::Store() : root(std::make_unique<Node>(nullptr, "", std::unique_ptr<wxClientData>{}))
    {}

    wxDataViewItem Store::Append(
        const wxDataViewItem& parent,
        const wxString& text,
        std::unique_ptr<wxClientData>&& data)
    {
        auto parentNode = NodeFor(parent);
        if (!parentNode)
            parentNode = root.get();
        parentNode->children.push_back(std::make_unique<Node>(parentNode, text, std::move(data)));
        return wxDataViewItem{ parentNode->children.back().get() };
    }

    wxDataViewItem Store::Prepend(
        const wxDataViewItem& parent,
        const wxString& text,
        std::unique_ptr<wxClientData>&& data)
    {
        auto parentNode = NodeFor(parent);
        if (!parentNode)
            parentNode = root.get();
        parentNode->children.insert(parentNode->children.begin(), std::make_unique<Node>(parentNode, text, std::move(data)));
        return wxDataViewItem{ parentNode->children.front().get() };
    }

    wxDataViewItem Store::Insert(
        const wxDataViewItem& parent,
        const wxDataViewItem& previous,
        const wxString& text,
        std::unique_ptr<wxClientData>&& data)
    {
        auto parentNode = NodeFor(parent);
        if (!parentNode)
            parentNode = root.get();
        const auto iterator = IteratorFor(*parentNode, *NodeFor(previous));
        const auto inserted = parentNode->children.insert(
            iterator, std::make_unique<Node>(parentNode, text, std::move(data)));
        return wxDataViewItem{ inserted->get() };
    }

    void Store::Delete(const wxDataViewItem& item)
    {
        const auto node = NodeFor(item);
        if (!node)
            return;

        const auto parentNode = node->parent;
        if (!parentNode)
            return;

        const auto iterator = IteratorFor(*parentNode, *node);
        parentNode->children.erase(iterator);
    }
    
    void Store::SetText(const wxDataViewItem& item, const wxString& text)
    {
        const auto node = NodeFor(item);
        if (node)
            node->text = text;
    }
    
    void Store::SetData(const wxDataViewItem& item, std::unique_ptr<wxClientData>&& data)
    {
        const auto found = NodeFor(item);
        if (found)
            found->data = std::move(data);
    }

    wxDataViewItem Store::ChildAt(const wxDataViewItem& parent, unsigned int pos) const
    {
        auto found = NodeFor(parent);
        if (!found)
            found = root.get();

        const auto iterator = std::next(found->children.begin(), pos);
        return iterator != found->children.end() ? wxDataViewItem{ iterator->get() } : wxDataViewItem{};
    }

    size_t Store::ChildrenCount(const wxDataViewItem& parent) const
    {
        const auto found = NodeFor(parent);
        return found ? found->children.size() : root->children.size();
    }

    wxString Store::TextOf(const wxDataViewItem& item) const
    {
        const auto found = NodeFor(item);
        return found ? found->text : wxString(wxEmptyString);
    }

    wxClientData* Store::DataOf(const wxDataViewItem& item) const
    {
        const auto found = NodeFor(item);
        return found ? found->data.get() : nullptr;
    }

    bool Store::IsContainer(const wxDataViewItem& item) const
    {
        const bool result = item ? !NodeFor(item)->children.empty() : true;
        return result;
    }

    wxDataViewItem Store::GetParent(const wxDataViewItem& item) const
    {
        const auto node = NodeFor(item);
        return node
            ? node->parent != root.get() ? wxDataViewItem{ node->parent } : wxDataViewItem{}
            : wxDataViewItem{};
    }

    unsigned int Store::GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const
    {
        auto node = NodeFor(item);
        if (!node)
            node = root.get();

        for (auto& child : node->children)
            children.Add(wxDataViewItem{ child.get() });

        return node->children.size();
    }

    unsigned int Store::GetColumnCount() const
    {
        return 1;
    }

    wxString Store::GetColumnType(unsigned int col) const
    {
        const auto columnType = wxDataViewTextRenderer::GetDefaultType();
        return columnType;
    }

    bool Store::SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned int col)
    {
        auto node = NodeFor(item);
        if (!node)
            node = root.get();
        
        node->text = variant.GetString();

        return true;
    }

    void Store::GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned int col) const
    {
        auto node = NodeFor(item);
        if (!node)
            node = root.get();

        variant = node->text;
    }

    int Store::Compare(const wxDataViewItem& item1, const wxDataViewItem& item2, unsigned column, bool ascending) const
    {
        const auto text1 = TextOf(item1);
        const auto text2 = TextOf(item2);
        return text1 == text2
            ? 0
            : std::lexicographical_compare(text1.begin(), text1.end(), text2.begin(), text2.end())
            ? -1
            : 1;
    }

    Store::Node::Node(Node* parent, const wxString& text, std::unique_ptr<wxClientData>&& data) :
        parent(parent), text(text), data(std::move(data))
    {}

    Store::Node::Node(Node&& arg) noexcept :
        parent(arg.parent), text(arg.text), data(std::move(arg.data)), children(std::move(arg.children))
    {}

    auto Store::Node::operator=(Node&& arg) noexcept -> Node&
    {
        parent = arg.parent;
        text = arg.text;
        data = std::move(arg.data);
        children = std::move(arg.children);
        return *this;
    }

    auto Store::NodeFor(const wxDataViewItem& item) -> Node*
    {
        return item ? static_cast<Node*>(item.GetID()) : nullptr;
    }

    auto Store::IteratorFor(Node& parent, Node& item) -> Node::Nodes::iterator
    {
        auto& children = parent.children;
        return std::find_if(
            children.begin(),
            children.end(),
            [&item](const std::unique_ptr<Node>& check)
            {
                return check.get() == &item;
            });
    }

    TreeCtrl::TreeCtrl() = default;

    TreeCtrl::TreeCtrl(
        wxWindow* parent,
        wxWindowID id,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxValidator& validator)
        :
        store(new Store())
    {
        Create(parent, id, pos, size, style, validator);
    }

    bool TreeCtrl::Create(
        wxWindow* parent,
        wxWindowID id,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxValidator& validator)
    {
        if (!wxDataViewCtrl::Create(parent, id, pos, size, style, validator))
            return false;
        
        AssociateModel(store.get());

        AppendTextColumn(wxString(), 0, wxDATAVIEW_CELL_INERT, -1, wxALIGN_NOT, 0);

        SetRowHeight(17);

        return true;
    }

    wxDataViewItem TreeCtrl::Append(
        const wxDataViewItem& parent,
        const wxString& text,
        std::unique_ptr<wxClientData>&& data)
    {
        const auto store = ModelAsStore();
        const auto added = store->Append(parent, text, std::move(data));
        store->ItemChanged(parent);
        store->ItemAdded(parent, added);
        return added;
    }

    wxDataViewItem TreeCtrl::Prepend(
        const wxDataViewItem& parent,
        const wxString& text,
        std::unique_ptr<wxClientData>&& data)
    {
        const auto store = ModelAsStore();
        const auto added = store->Prepend(parent, text, std::move(data));
        store->ItemChanged(parent);
        store->ItemAdded(parent, added);
        return added;
    }

    wxDataViewItem TreeCtrl::Insert(
        const wxDataViewItem& parent,
        const wxDataViewItem& previous,
        const wxString& text,
        std::unique_ptr<wxClientData>&& data)
    {
        const auto store = ModelAsStore();
        const auto added = store->Insert(parent, previous, text, std::move(data));
        store->ItemChanged(parent);
        store->ItemAdded(parent, added);
        return added;
    }

    void TreeCtrl::Delete(const wxDataViewItem& item)
    {
        const auto store = ModelAsStore();
        const auto parent = store->GetParent(item);
        store->Delete(item);
        store->ItemDeleted(parent, item);
    }

    void TreeCtrl::SetText(const wxDataViewItem& item, const wxString& text)
    {
        const auto store = ModelAsStore();
        store->SetText(item, text);
        store->ValueChanged(item, 0);
    }

    void TreeCtrl::SetData(const wxDataViewItem& item, std::unique_ptr<wxClientData>&& data)
    {
        ModelAsStore()->SetData(item, std::move(data));
    }

    wxString TreeCtrl::TextOf(const wxDataViewItem& item) const
    {
        return ModelAsStore()->TextOf(item);
    }

    wxClientData* TreeCtrl::DataOf(const wxDataViewItem& item) const
    {
        return ModelAsStore()->DataOf(item);
    }

    wxDataViewItem TreeCtrl::ChildAt(const wxDataViewItem& parent, size_t position) const
    {
        return ModelAsStore()->ChildAt(parent, position);
    }

    int TreeCtrl::ChildrenCount(const wxDataViewItem& parent) const
    {
        return ModelAsStore()->ChildrenCount(parent);
    }

    wxDataViewColumn* TreeCtrl::GetSortingColumn() const
    {
        return GetColumn(0);
    }

    Store* TreeCtrl::ModelAsStore()
    {
        return dynamic_cast<Store*>(GetModel());
    }

    const Store* TreeCtrl::ModelAsStore() const
    {
        return dynamic_cast<const Store*>(GetModel());
    }

    void TreeCtrl::OnSize(wxSizeEvent& event)
    {
        if (GetColumnCount())
        {
            const auto size = GetClientSize();
            GetColumn(0)->SetWidth(size.x);
        }

        event.Skip(true);
    }

    wxIMPLEMENT_DYNAMIC_CLASS(TreeCtrl, wxDataViewCtrl);

    wxBEGIN_EVENT_TABLE(TreeCtrl, wxDataViewCtrl)
        EVT_SIZE(TreeCtrl::OnSize)
    wxEND_EVENT_TABLE()
}