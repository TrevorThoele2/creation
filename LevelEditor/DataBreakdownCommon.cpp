
#include "DataBreakdownCommon.h"

#include "DataBreakdownWXItemData.h"
#include "BuildPackage.h"

#include "MainFrame.h"
#include "Assert.h"

#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/treectrl.h>
#include <wx/propgrid/propgrid.h>

namespace Creation
{
    DataBreakdownCommon::ChildReference::ChildReference() : child(nullptr)
    {}

    DataBreakdownCommon::ChildReference::ChildReference(const Child *child) : child(child)
    {}

    DataBreakdownCommon::ChildReference::ChildReference(const Child &child) : child(&child)
    {}

    bool DataBreakdownCommon::ChildReference::operator==(const ChildReference &arg) const
    {
        return child == arg.child;
    }

    bool DataBreakdownCommon::ChildReference::operator!=(const ChildReference &arg) const
    {
        return !(*this == arg);
    }

    const DataBreakdownCommon::Child& DataBreakdownCommon::ChildReference::operator*() const
    {
        return *Get();
    }

    const DataBreakdownCommon::Child* DataBreakdownCommon::ChildReference::operator->() const
    {
        return Get();
    }

    DataBreakdownCommon::ChildReference::operator bool() const
    {
        return IsValid();
    }

    bool DataBreakdownCommon::ChildReference::IsValid() const
    {
        return static_cast<bool>(child);
    }

    const DataBreakdownCommon::Child* DataBreakdownCommon::ChildReference::Get() const
    {
        return child;
    }

    DataBreakdownCommon::ChildReference DataBreakdownCommon::ChildReference::Next() const
    {
        if (!IsValid() || !child->Is<DataBreakdownCommon*>())
            return nullptr;

        return child->Get<DataBreakdownCommon*>()->GetParent()->GetNextChild(*child);
    }

    DataBreakdownCommon::ChildReference DataBreakdownCommon::ChildReference::NextChange()
    {
        *this = Next();
        return *this;
    }

    DataBreakdownCommon::ChildReference DataBreakdownCommon::ChildReference::Previous() const
    {
        if (!IsValid() || !child->Is<DataBreakdownCommon*>())
            return nullptr;

        return child->Get<DataBreakdownCommon*>()->GetParent()->GetPreviousChild(*child);
    }

    DataBreakdownCommon::ChildReference DataBreakdownCommon::ChildReference::PreviousChange()
    {
        *this = Previous();
        return *this;
    }

    void DataBreakdownCommon::DestroyTreeItem()
    {
        if (!treeItemID.IsOk())
            return;

        auto oldTreeItemID = treeItemID;
        treeItemID.Unset();
        GetMainFrame()->GetDataView()->Tree()->Delete(oldTreeItemID);
    }

    wxString DataBreakdownCommon::GetCategoryNameSequence() const
    {
        String useName((propName) ? *propName : GetName());

        if (parent)
            return parent->GetCategoryNameSequence() + "." + useName;
        else
            return useName;
    }

    bool DataBreakdownCommon::FindIfActuallyEditable() const
    {
        if (!editableBase)
            return false;

        // If a parent is not editable, then this is uneditable
        auto tempParent = parent;
        while (tempParent)
        {
            if (!tempParent->IsEditable())
                return false;

            tempParent = tempParent->parent;
        }

        return editableBase;
    }

    void DataBreakdownCommon::NotifyParentEditableChanged(bool above)
    {
        bool prevActuallyEditable = actuallyEditable;
        if (!editableBase)
            actuallyEditable = false;
        else
            actuallyEditable = above;

        if (prevActuallyEditable != actuallyEditable)
            SetEditableInner(actuallyEditable);

        for (auto &loop : children)
            DoIfBreakdown(loop, &DataBreakdownCommon::NotifyParentEditableChanged, actuallyEditable);
    }

    std::vector<Build::PackageBase*> DataBreakdownCommon::MakeEditPackageStack()
    {
        std::vector<Build::PackageBase*> ret;
        DataBreakdownCommon *focusParent = parent;
        while (focusParent)
        {
            ret.push_back(focusParent->GetCurrentValue()->Clone());
            focusParent = focusParent->GetParent();
        }

        return ret;
    }

    void DataBreakdownCommon::ConsumeEditPackageStack(std::vector<Build::PackageBase*> &&consume)
    {
        DataBreakdownCommon *focusParent = parent;
        auto loop = consume.begin();
        while (focusParent)
        {
            focusParent->EmitEditEvent(*loop);
            focusParent = focusParent->GetParent();
            delete *loop;
            loop = consume.erase(loop);
        }
    }

    bool DataBreakdownCommon::ConsumePreEditPackageStack(std::vector<Build::PackageBase*> &&consume)
    {
        bool ret = false;
        DataBreakdownCommon *focusParent = parent;
        auto loop = consume.begin();
        while (focusParent)
        {
            if (focusParent->EmitPreEditEvent(*loop))
                ret = true;
            focusParent = focusParent->GetParent();
            delete *loop;
            loop = consume.erase(loop);
        }
        
        return ret;
    }

    bool DataBreakdownCommon::HasChild(const ChildReference &afterThis) const
    {
        if (!afterThis)
            return false;

        for (auto &loop : children)
        {
            if (loop == *afterThis)
                return true;
        }

        return false;
    }

    void DataBreakdownCommon::AddChild(DataBreakdownCommon &add)
    {
        Child child;
        child.Set(&add);
        AddChild(std::move(child));
    }

    void DataBreakdownCommon::AddChild(wxPGProperty &add)
    {
        Child child;
        child.Set(&add);
        AddChild(std::move(child));
    }

    void DataBreakdownCommon::AddChild(const Child &add)
    {
        children.push_back(add);
    }

    void DataBreakdownCommon::AddChild(Child &&add)
    {
        children.push_back(std::move(add));
    }

    void DataBreakdownCommon::InsertChild(DataBreakdownCommon &add, const ChildReference &afterThis)
    {
        Child child;
        child.Set(&add);
        InsertChild(std::move(child), afterThis);
    }

    void DataBreakdownCommon::InsertChild(wxPGProperty &add, const ChildReference &afterThis)
    {
        Child child;
        child.Set(&add);
        InsertChild(std::move(child), afterThis);
    }

    void DataBreakdownCommon::InsertChild(const Child &add, const ChildReference &afterThis)
    {
        auto prev = children.begin();
        for (auto loop = ++children.begin(); loop != children.end(); ++loop)
        {
            if (*loop == *afterThis.Get())
            {
                children.insert(prev, add);
                return;
            }

            prev = loop;
        }

        AddChild(add);
    }

    void DataBreakdownCommon::InsertChild(Child &&add, const ChildReference &afterThis)
    {
        auto prev = children.begin();
        for (auto loop = ++children.begin(); loop != children.end(); ++loop)
        {
            if (*prev == *afterThis.Get())
            {
                children.insert(loop, add);
                return;
            }

            prev = loop;
        }

        AddChild(add);
    }

    void DataBreakdownCommon::RemoveChild(DataBreakdownCommon &remove)
    {
        Child child;
        child.Set(&remove);
        RemoveChild(std::move(child));
    }

    void DataBreakdownCommon::RemoveChild(wxPGProperty &remove)
    {
        Child child;
        child.Set(&remove);
        RemoveChild(std::move(child));
    }

    void DataBreakdownCommon::RemoveChild(const Child &remove)
    {
        for (auto loop = children.begin(); loop != children.end(); ++loop)
        {
            if (*loop == remove)
            {
                children.erase(loop);
                return;
            }
        }
    }

    void DataBreakdownCommon::RemoveChild(Child &&remove)
    {
        for (auto loop = children.begin(); loop != children.end(); ++loop)
        {
            if (*loop == remove)
            {
                children.erase(loop);
                return;
            }
        }
    }

    DataViewSelection::Group* DataBreakdownCommon::GetSelected()
    {
        return DataViewSelection::GetGroup(*this);
    }

    wxString DataBreakdownCommon::GetPropertyNameSequence(const wxString &append) const
    {
        if (!IsSelected())
            return append;

        String useName((propName) ? *propName : GetName());

        if (propCategory)
        {
            if (parent)
                return parent->GetPropertyNameSequence(useName + "." + append);
            else
                return useName + "." + append;
        }
        else
        {
            if (parent)
                return parent->GetPropertyNameSequence(append);
            else
                return append;
        }
    }

    void DataBreakdownCommon::AppendProperty(wxPGProperty *append)
    {
        if(propCategory)
            PropertyGrid()->AppendIn(propCategory, append);
        else
        {
            // If no property category, find a parent with one or go until no more parents and then just append
            if (parent)
                parent->AppendProperty(append);
            else
                PropertyGrid()->Append(append);
        }
    }

    void DataBreakdownCommon::InsertProperty(wxPGProperty *insert, const ChildReference &afterThis)
    {
        if (!afterThis)
        {
            AppendProperty(insert);
            return;
        }

        struct Visitor
        {
            static const wxPGProperty* DoReturn(const DataBreakdownCommon *breakdown) { return breakdown->GetTopProperty(); }
            static const wxPGProperty* DoReturn(const wxPGProperty *prop) { return prop; }
        };

        // Check for property category
        if (propCategory)
        {
            // If we have a property category, find the index to place this into and leave
            auto next = afterThis.Next();

            int index = wxNOT_FOUND;
            if (next.IsValid())
            {
                const wxPGProperty *topProp = ::function::VisitReturn<Visitor, const wxPGProperty*>(*afterThis.Next());
                index = topProp->GetParent()->Index(topProp);
            }
            
            PropertyGrid()->Insert(propCategory, index, insert);
            return;
        }

        // No property category here
        if (parent)
        {
            // If no property category and a parent, then we need to look for one that does or until we hit no parent
            parent->InsertProperty(insert, afterThis);
            return;
        }

        // Find the next child property
        if (afterThis->Is<wxPGProperty*>())
        {
            auto got = afterThis->Get<wxPGProperty*>();
            auto next = ++PropertyGrid()->GetIterator(wxPG_ITERATE_DEFAULT, got);
            if (next.AtEnd())
            {
                AppendProperty(insert);
                return;
            }

            PropertyGrid()->Insert(*next, insert);
        }
        else if (afterThis->Is<DataBreakdownCommon*>())
        {
            // Make sure we have a next child after the afterThis
            auto next = afterThis.Next();
            if (!next)
            {
                AppendProperty(insert);
                return;
            }

            // Get the next child as the top property
            auto found = ::function::VisitReturn<Visitor, const wxPGProperty*>(*next);
            if (!found)
            {
                AppendProperty(insert);
                return;
            }

            PropertyGrid()->Insert(found, insert);
        }
    }

    wxTreeCtrl* DataBreakdownCommon::Tree()
    {
        return GetMainFrame()->GetDataView()->Tree();
    }

    const wxTreeCtrl* DataBreakdownCommon::Tree() const
    {
        return GetMainFrame()->GetDataView()->Tree();
    }

    wxPanel* DataBreakdownCommon::EditorPanel()
    {
        return GetMainFrame()->GetDataView()->EditorPanel();
    }

    const wxPanel* DataBreakdownCommon::EditorPanel() const
    {
        return GetMainFrame()->GetDataView()->EditorPanel();
    }

    wxPropertyGrid* DataBreakdownCommon::PropertyGrid()
    {
        return GetMainFrame()->GetDataView()->PropertyGrid();
    }

    const wxPropertyGrid* DataBreakdownCommon::PropertyGrid() const
    {
        return GetMainFrame()->GetDataView()->PropertyGrid();
    }

    DataBreakdownCommon::DataBreakdownCommon(const String &name, DataBreakdownCommon *parent) : name(name), niceName(name), parent(parent), sortTreeItem(false),
        propCategory(nullptr), editableBase(true), actuallyEditable(FindIfActuallyEditable()), attached(false), selected(SelectedState::NONE), invisible(false), addCategory(true),
        addChildrenToProperties(true), updateChildren(true), destroyChildProperties(true), addChildrenToTree(true), addTreePiece(true), selectChildren(true), setEditableChildren(true)
    {}

    DataBreakdownCommon::DataBreakdownCommon(DataBreakdownCommon &&arg, DataBreakdownCommon *parent) : name(std::move(arg.name)), niceName(std::move(arg.niceName)),
        parent((parent) ? parent : arg.parent), sortTreeItem(std::move(arg.sortTreeItem)), treeItemID(std::move(arg.treeItemID)), propCategory(std::move(arg.propCategory)),
        propName(std::move(arg.propName)), editableBase(std::move(arg.editableBase)), actuallyEditable(std::move(arg.actuallyEditable)), attached(std::move(arg.attached)),
        selected(std::move(arg.selected)), invisible(std::move(arg.invisible)), addCategory(std::move(arg.addCategory)), addChildrenToProperties(std::move(arg.addChildrenToProperties)), updateChildren(std::move(arg.updateChildren)),
        destroyChildProperties(std::move(arg.destroyChildProperties)), addChildrenToTree(std::move(arg.addChildrenToTree)), addTreePiece(std::move(arg.addTreePiece)), selectChildren(std::move(arg.selectChildren)),
        setEditableChildren(std::move(arg.setEditableChildren))
    {}

    DataBreakdownCommon& DataBreakdownCommon::operator=(DataBreakdownCommon &&arg)
    {
        name = std::move(arg.name);
        niceName = std::move(arg.niceName);
        parent = std::move(arg.parent);
        sortTreeItem = std::move(arg.sortTreeItem);
        treeItemID = std::move(arg.treeItemID);
        propCategory = std::move(arg.propCategory);
        propName = std::move(arg.propName);
        editableBase = std::move(arg.editableBase);
        actuallyEditable = std::move(arg.actuallyEditable);
        attached = std::move(arg.attached);
        selected = std::move(arg.selected);
        invisible = std::move(arg.invisible);
        addCategory = std::move(arg.addCategory);
        addChildrenToProperties = std::move(arg.addChildrenToProperties);
        updateChildren = std::move(arg.updateChildren);
        destroyChildProperties = std::move(arg.destroyChildProperties);
        addTreePiece = std::move(arg.addTreePiece);
        selectChildren = std::move(arg.selectChildren);
        setEditableChildren = std::move(arg.setEditableChildren);
        return *this;
    }

    void DataBreakdownCommon::Reparent(DataBreakdownCommon *parent)
    {
        this->parent = parent;
    }

    void DataBreakdownCommon::Reset()
    {
        for (auto &loop : children)
            DoIfBreakdown(loop, &DataBreakdownCommon::Reset);
        ResetInner();
    }

    void DataBreakdownCommon::CreateEditorProperties(const ChildReference &afterThis)
    {
        if (!IsValid() || IsInvisible())
            return;

        if (IsAttached())
        {
            UpdateEditorProperties();
            return;
        }

        attached = true;

        if (addCategory)
        {
            wxString categoryNameSequence(GetCategoryNameSequence());
            auto tempPropCategory = new wxPropertyCategory(GetNiceName(), categoryNameSequence);
            InsertProperty(tempPropCategory, afterThis);
            propCategory = tempPropCategory;
            propCategory->SetClientObject(new DataBreakdownWXItemData(this));
        }

        CreateEditorPropertiesInner(afterThis);

        if (addChildrenToProperties)
            for (auto &loop : children)
                DoIfBreakdown(loop, &DataBreakdownCommon::CreateEditorProperties, afterThis);

        UpdateEditorProperties();

        if (propCategory)
        {
            if (treeItemID.IsOk() && Tree()->IsExpanded(treeItemID))
                PropertyGrid()->Expand(propCategory);
            else
                PropertyGrid()->Collapse(propCategory);
        }

        GetMainFrame()->GetDataView()->RefreshOnIdle();
    }

    void DataBreakdownCommon::ReinsertEditorProperties(DataBreakdownCommon &breakdown)
    {
        Child child;
        child.Set(&breakdown);
        breakdown.CreateEditorProperties(&child);
    }

    void DataBreakdownCommon::UpdateEditorProperties()
    {
        if (!IsValid() || !IsAttached() || !IsSelected() || IsInvisible())
            return;

        if (updateChildren)
            for (auto &loop : children)
                DoIfBreakdown(loop, &DataBreakdownCommon::UpdateEditorProperties);

        UpdateEditorPropertiesInner(*DataViewSelection::GetGroup(*this));
    }

    void DataBreakdownCommon::DestroyEditorProperties(bool destroyTreeItem)
    {
        if (destroyTreeItem)
            DestroyTreeItem();

        if (!attached)
            return;

        if (destroyChildProperties)
            for (auto &loop : children)
                DoIfBreakdown(loop, &DataBreakdownCommon::DestroyEditorProperties, destroyTreeItem);

        DestroyEditorPropertiesInner(destroyTreeItem);

        attached = false;
        if (propCategory)
        {
            PropertyGrid()->DeleteProperty(propCategory);
            propCategory = nullptr;
        }

        GetMainFrame()->GetDataView()->RefreshOnIdle();
    }

    void DataBreakdownCommon::CreateTreePiece(wxTreeItemId parentItemID, const ChildReference &afterThis)
    {
        if (IsInvisible())
            return;

        if (addTreePiece)
        {
            if(!afterThis || !afterThis->Is<DataBreakdownCommon*>())
                treeItemID = Tree()->AppendItem(parentItemID, GetNiceName(), -1, -1, new DataBreakdownWXItemData(this));
            else
                treeItemID = Tree()->InsertItem(parentItemID, afterThis.Previous()->Get<DataBreakdownCommon*>()->GetTreeItemID(), GetNiceName(), -1, -1, new DataBreakdownWXItemData(this));

            if (sortTreeItem)
                Tree()->SortChildren(treeItemID);

            if (addChildrenToTree)
                for (auto &loop : children)
                    DoIfBreakdown(loop, &DataBreakdownCommon::CreateTreePiece, GetTreeItemID(), afterThis);

            CreateTreePieceInner(parentItemID, afterThis);
        }
        else
        {
            // Find a parent who has the tree ID to use
            wxTreeItemId passParentID;
            DataBreakdownCommon *checkParent(parent);
            while ((passParentID == wxTreeItemId()) && checkParent)
            {
                passParentID = checkParent->treeItemID;
                checkParent = parent->parent;
            }

            if (addChildrenToTree)
                for (auto &loop : children)
                    DoIfBreakdown(loop, &DataBreakdownCommon::CreateTreePiece, passParentID, afterThis);
        }

        Tree()->FitInside();
    }

    void DataBreakdownCommon::ReinsertTreePiece(DataBreakdownCommon &breakdown)
    {
        Child child;
        child.Set(&breakdown);
        breakdown.CreateTreePiece(GetTreeItemID(), &child);
    }

    const DataBreakdownCommon::Child* DataBreakdownCommon::GetPreviousChild(const Child &post) const
    {
        if (children.empty())
            return nullptr;

        auto prev = children.begin();
        for (auto loop = ++children.begin(); loop != children.end(); ++loop)
        {
            if (*loop == post)
                return &*prev;

            prev = loop;
        }

        return nullptr;
    }

    const DataBreakdownCommon::Child* DataBreakdownCommon::GetNextChild(const Child &post) const
    {
        if (children.empty())
            return nullptr;

        auto prev = children.begin();
        for (auto loop = ++children.begin(); loop != children.end(); ++loop)
        {
            if (*prev == post)
                return &*loop;

            prev = loop;
        }

        return nullptr;
    }

    const wxPGProperty* DataBreakdownCommon::GetTopProperty() const
    {
        if (children.empty())
            return nullptr;

        struct Visitor
        {
            static const wxPGProperty* DoReturn(DataBreakdownCommon *breakdown) { return breakdown->GetTopProperty(); }
            static const wxPGProperty* DoReturn(wxPGProperty *prop) { return prop; }
        };

        for (auto &loop : children)
        {
            auto found = ::function::VisitReturn<Visitor, const wxPGProperty*>(loop);
            if (found)
                return found;
        }

        return nullptr;
    }

    const wxPGProperty* DataBreakdownCommon::GetBottomProperty() const
    {
        if (children.empty())
            return nullptr;

        struct Visitor
        {
            static const wxPGProperty* DoReturn(DataBreakdownCommon *breakdown) { return breakdown->GetTopProperty(); }
            static const wxPGProperty* DoReturn(wxPGProperty *prop) { return prop; }
        };

        for (auto loop = children.rbegin(); loop != children.rend(); ++loop)
        {
            auto found = ::function::VisitReturn<Visitor, const wxPGProperty*>(*loop);
            if (found)
                return found;
        }

        return nullptr;
    }

    DataBreakdownCommon::Child DataBreakdownCommon::AsChild() const
    {
        Child child;
        child.Set(const_cast<DataBreakdownCommon*>(this));
        return child;
    }

    void DataBreakdownCommon::CreateBreakdowns()
    {
        for (auto &loop : children)
            DoIfBreakdown(loop, &DataBreakdownCommon::CreateBreakdowns);
        CreateBreakdownsInner();
    }

    void DataBreakdownCommon::DestroyBreakdowns()
    {
        DestroyBreakdownsInner();
    }

    Command::ICommand* DataBreakdownCommon::CreateAddToCommand()
    {
        if (!IsAddingEnabled())
            return nullptr;

        return CreateAddToCommandImpl();
    }

    Command::ICommand* DataBreakdownCommon::CreateAddToGroupCommand()
    {
        if (!IsAddingEnabled())
            return nullptr;

        return CreateAddToGroupCommandImpl();
    }

    void DataBreakdownCommon::AddAddCommandToGroup(Command::ICommand *group)
    {
        if (!IsAddingEnabled())
            return;

        AddAddCommandToGroupImpl(group);
    }

    Command::ICommand* DataBreakdownCommon::CreateRemoveThisCommand()
    {
        if (!CanRemoveThis())
            return nullptr;

        return parent->CreateRemoveThisCommandImpl(this);
    }

    Command::ICommand* DataBreakdownCommon::CreateRemoveThisGroupCommand()
    {
        if (!CanRemoveThis())
            return nullptr;

        return parent->CreateRemoveThisGroupCommandImpl();
    }

    void DataBreakdownCommon::AddRemoveCommandToGroup(Command::ICommand *group)
    {
        if (!CanRemoveThis())
            return;

        parent->AddRemoveCommandToGroupImpl(this, group);
    }

    bool DataBreakdownCommon::IsAddingEnabled() const
    {
        return IsEditable() && IsAddingEnabledImpl();
    }

    bool DataBreakdownCommon::CanRemoveThis() const
    {
        return parent && parent->IsEditable() && parent->IsAddingEnabled();
    }

    bool DataBreakdownCommon::IsValid() const
    {
        return IsValidImpl();
    }

    void DataBreakdownCommon::SetEditable(bool set)
    {
        editableBase = set;
        actuallyEditable = FindIfActuallyEditable();
        SetEditableInner(set);
        if (setEditableChildren)
        {
            for (auto &loop : children)
                DoIfBreakdown(loop, &DataBreakdownCommon::NotifyParentEditableChanged, actuallyEditable);
        }
    }

    bool DataBreakdownCommon::IsEditable() const
    {
        return actuallyEditable;
    }

    void DataBreakdownCommon::SetInvisible(bool set)
    {
        invisible = set;
        if (invisible)
            DestroyEditorProperties();
        else
        {
            // If we're setting to visible, make sure we should be creating the editor properties
            if (!GetParent() || GetParent()->IsAttached())
                CreateEditorProperties();
        }
    }

    bool DataBreakdownCommon::IsInvisible() const
    {
        return invisible;
    }

    void DataBreakdownCommon::SelectThisPrimary()
    {
        if (!IsValid() || selected == SelectedState::PRIMARY)
            return;

        selected = SelectedState::PRIMARY;
        DataViewSelection::SelectPrimary(*this);
        if (selectChildren)
        {
            for (auto &loop : children)
                DoIfBreakdown(loop, &DataBreakdownCommon::SelectThisSecondary);
        }
        ChangeSelectInner(selected);
    }

    void DataBreakdownCommon::SelectThisSecondary()
    {
        if (!IsValid() || IsSelected())
            return;

        selected = SelectedState::SECONDARY;
        DataViewSelection::SelectSecondary(*this);
        if (selectChildren)
        {
            for (auto &loop : children)
                DoIfBreakdown(loop, &DataBreakdownCommon::SelectThisSecondary);
        }
        ChangeSelectInner(selected);
    }

    void DataBreakdownCommon::DeselectThis()
    {
        if (!IsSelected())
            return;

        DestroyEditorProperties();
        selected = SelectedState::NONE;
        DataViewSelection::Deselect(*this);
        if (selectChildren)
        {
            for (auto &loop : children)
                DoIfBreakdown(loop, &DataBreakdownCommon::DeselectThis);
        }

        ChangeSelectInner(selected);
    }

    void DataBreakdownCommon::ClearSelectedGroups()
    {
        DataViewSelection::Clear();
    }

    bool DataBreakdownCommon::IsSelectedPrimary() const
    {
        return selected == SelectedState::PRIMARY;
    }

    bool DataBreakdownCommon::IsSelectedSecondary() const
    {
        return selected == SelectedState::SECONDARY;
    }

    bool DataBreakdownCommon::IsSelected() const
    {
        return selected != SelectedState::NONE;
    }

    bool DataBreakdownCommon::IsAttached() const
    {
        return attached;
    }

    bool DataBreakdownCommon::IsTreePieceAttached() const
    {
        return treeItemID != wxTreeItemId();
    }

    void DataBreakdownCommon::SetNiceName(const String &set)
    {
        niceName = set;
        if (propCategory)
            propCategory->SetLabel(niceName);
    }

    void DataBreakdownCommon::ResetPropName()
    {
        propName.reset();
    }

    void DataBreakdownCommon::SetPropName(const String &set)
    {
        propName.reset(new String(set));
    }

    const String& DataBreakdownCommon::GetName() const
    {
        return name;
    }

    const String& DataBreakdownCommon::GetNiceName() const
    {
        return niceName;
    }

    DataBreakdownCommon* DataBreakdownCommon::GetParent()
    {
        return parent;
    }

    const DataBreakdownCommon* DataBreakdownCommon::GetParent() const
    {
        return parent;
    }

    void DataBreakdownCommon::SortTreeItem(bool set)
    {
        sortTreeItem = set;
    }

    bool DataBreakdownCommon::SortTreeItem() const
    {
        return sortTreeItem;
    }

    wxTreeItemId DataBreakdownCommon::GetTreeItemID() const
    {
        return treeItemID;
    }

    void DataBreakdownCommon::SetAddCategory(bool set)
    {
        addCategory = set;
    }

    bool DataBreakdownCommon::WillAddCategory() const
    {
        return addCategory;
    }

    void DataBreakdownCommon::SetAddTreePiece(bool set)
    {
        addTreePiece = set;
    }

    bool DataBreakdownCommon::WillAddTreePiece() const
    {
        return addTreePiece;
    }

    void DataBreakdownCommon::SetAddChildrenToProperties(bool set)
    {
        addChildrenToProperties = set;
    }

    bool DataBreakdownCommon::WillAddChildrenToProperties() const
    {
        return addChildrenToProperties;
    }

    void DataBreakdownCommon::SetUpdateChildrenProperties(bool set)
    {
        updateChildren = set;
    }

    bool DataBreakdownCommon::WillUpdateChildrenProperties() const
    {
        return updateChildren;
    }

    void DataBreakdownCommon::SetDestroyChildrenProperties(bool set)
    {
        destroyChildProperties = set;
    }

    bool DataBreakdownCommon::WillDestroyChildrenProperties() const
    {
        return destroyChildProperties;
    }

    void DataBreakdownCommon::SetAddChildrenToTree(bool set)
    {
        addChildrenToTree = set;
    }

    bool DataBreakdownCommon::WillAddChildrenToTree() const
    {
        return addChildrenToTree;
    }

    void DataBreakdownCommon::SetSelectChildren(bool set)
    {
        selectChildren = set;
    }

    bool DataBreakdownCommon::WillSelectChildren() const
    {
        return selectChildren;
    }

    void DataBreakdownCommon::SetEditableChildren(bool set)
    {
        setEditableChildren = set;
    }

    bool DataBreakdownCommon::WillEditChildren() const
    {
        return setEditableChildren;
    }

    void DataBreakdownCommon::SetHandleChildren(bool set)
    {
        SetAddChildrenToProperties(set);
        SetUpdateChildrenProperties(set);
        SetDestroyChildrenProperties(set);
        SetAddChildrenToTree(set);
        SetSelectChildren(set);
        SetEditableChildren(set);
    }

    bool DataBreakdownCommon::WillHandleChildren() const
    {
        return WillAddChildrenToProperties() && WillUpdateChildrenProperties() && WillDestroyChildrenProperties() && WillAddChildrenToTree() && WillSelectChildren() && WillEditChildren();
    }

    wxPropertyCategory* DataBreakdownCommon::GetPropertyCategory()
    {
        return propCategory;
    }

    const wxPropertyCategory* DataBreakdownCommon::GetPropertyCategory() const
    {
        return propCategory;
    }

    bool DataBreakdownCommon::IgnoreNameForKey() const
    {
        return IgnoreNameForKeyImpl();
    }
}

#include "UndefAssert.h"