#pragma once

#include <list>
#include "DataViewSelection.h"
#include "String.h"
#include "Event.h"
#include <Function/Variant.h>
#include <wx/treebase.h>
#include <wx/propgrid/propgrid.h>
class wxWindow;
class wxTreeCtrl;
class wxPanel;

namespace Creation
{
    namespace Build { class PackageBase; }
    namespace Command { class ICommand; }

    class DataBreakdownCommon
    {
    public:
        typedef unsigned int Level;
    public:
        typedef ::function::Variant<DataBreakdownCommon*, wxPGProperty*> Child;

        class ChildReference
        {
        private:
            const Child *child;
        public:
            ChildReference();
            ChildReference(const Child *child);
            ChildReference(const Child &child);
            ChildReference(const ChildReference &arg) = default;
            ChildReference& operator=(const ChildReference &arg) = default;
            bool operator==(const ChildReference &arg) const;
            bool operator!=(const ChildReference &arg) const;

            const Child& operator*() const;
            const Child* operator->() const;

            explicit operator bool() const;
            bool IsValid() const;

            const Child* Get() const;
            ChildReference Next() const;
            // Changes the object that this is called on
            ChildReference NextChange();
            ChildReference Previous() const;
            // Changes the object that this is called on
            ChildReference PreviousChange();
        };
    protected:
        enum class SelectedState
        {
            PRIMARY,
            SECONDARY,
            NONE
        };
    private:
        DataBreakdownCommon *parent;
        std::list<Child> children;

        String name;
        String niceName;

        bool sortTreeItem;
        wxTreeItemId treeItemID;

        wxPropertyCategory *propCategory;
        // If this is nullptr, then will use the regular name
        std::unique_ptr<String> propName;

        bool editableBase;
        bool actuallyEditable;

        bool attached;
        SelectedState selected;
        bool invisible;

        bool addCategory;
        bool addChildrenToProperties;
        bool updateChildren;
        bool destroyChildProperties;
        bool addChildrenToTree;
        bool addTreePiece;
        bool selectChildren;
        bool setEditableChildren;

        void DestroyTreeItem();
        // Creates a name sequence through all parents until a null parent
        // Used for setting a name on a new category
        wxString GetCategoryNameSequence() const;
        bool FindIfActuallyEditable() const;
        void NotifyParentEditableChanged(bool above);

        virtual void ResetInner() = 0;
        virtual bool IsValidImpl() const = 0;
        virtual bool IsAddingEnabledImpl() const = 0;
        virtual Command::ICommand* CreateAddToCommandImpl() { return nullptr; }
        virtual Command::ICommand* CreateAddToGroupCommandImpl() { return nullptr; }
        virtual void AddAddCommandToGroupImpl(Command::ICommand *group) {}
        virtual Command::ICommand* CreateRemoveThisCommandImpl(DataBreakdownCommon *remove) { return nullptr; }
        virtual Command::ICommand* CreateRemoveThisGroupCommandImpl() { return nullptr; }
        virtual void AddRemoveCommandToGroupImpl(DataBreakdownCommon *remove, Command::ICommand *group) {}

        virtual void CreateEditorPropertiesInner(const ChildReference &afterThis) {}
        virtual void UpdateEditorPropertiesInner(DataViewSelection::Group &selected) {}
        virtual void DestroyEditorPropertiesInner(bool destroyTreeItem) {}
        virtual void CreateTreePieceInner(wxTreeItemId parentItemID, const ChildReference &afterThis) {}
        virtual void ChangeSelectInner(SelectedState state) {}

        virtual void CreateBreakdownsInner() {}
        virtual void DestroyBreakdownsInner() {}

        virtual void SetEditableInner(bool set) {}

        virtual bool IgnoreNameForKeyImpl() const { return false; }

        virtual Build::PackageBase* GetCurrentValue() { return nullptr; };
        virtual void EmitEditEvent(Build::PackageBase *prev) {}
        // Returns true if the event should be rejected
        virtual bool EmitPreEditEvent(Build::PackageBase *proposed) { return false; }

        std::vector<Build::PackageBase*> MakeEditPackageStack();
        void ConsumeEditPackageStack(std::vector<Build::PackageBase*> &&consume);
        // Returns true if the event should be rejected
        bool ConsumePreEditPackageStack(std::vector<Build::PackageBase*> &&consume);

        // Does something if the child is a breakdown
        template<class... FuncArgs, class... Args>
        void DoIfBreakdown(Child &child, void(DataBreakdownCommon::*func)(FuncArgs...), Args && ... args);
        bool HasChild(const ChildReference &afterThis) const;

        template<class Package>
        friend class DataBreakdownBase;
        template<class Package>
        friend class DataBreakdownList;
    protected:
        void AddChild(DataBreakdownCommon &add);
        void AddChild(wxPGProperty &add);
        void AddChild(const Child &add);
        void AddChild(Child &&add);
        void InsertChild(DataBreakdownCommon &add, const ChildReference &afterThis);
        void InsertChild(wxPGProperty &add, const ChildReference &afterThis);
        void InsertChild(const Child &add, const ChildReference &afterThis);
        void InsertChild(Child &&add, const ChildReference &afterThis);
        void RemoveChild(DataBreakdownCommon &remove);
        void RemoveChild(wxPGProperty &remove);
        void RemoveChild(const Child &remove);
        void RemoveChild(Child &&remove);

        DataViewSelection::Group* GetSelected();

        // Creates a name sequence through all parents until a null parent
        // Used for setting a name on a new property
        wxString GetPropertyNameSequence(const wxString &append) const;

        // If the priorTo is valid, then it will insert - otherwise will append
        // Uses the nice name of this
        template<class T, class... Args>
        T* CreatePropertyEmplace(const wxString &propName, const ChildReference &afterThis, Args && ... args);
        // If the priorTo is valid, then it will insert - otherwise will append
        // Also appends the property
        template<class T, class... Args>
        T* CreatePropertyLabelEmplace(const wxString &propName, const wxString &label, const ChildReference &afterThis, Args && ... args);
        // Also appends the property
        // Uses the nice name of this
        template<class T, class... Args>
        T* CreatePropertyAppend(const wxString &propName, Args && ... args);
        // Also appends the property
        template<class T, class... Args>
        T* CreatePropertyLabelAppend(const wxString &propName, const wxString &label, Args && ... args);
        void AppendProperty(wxPGProperty *append);
        void InsertProperty(wxPGProperty *insert, const ChildReference &afterThis);
        template<class PropT>
        void DestroyProperty(PropT *&destroy);

        wxTreeCtrl* Tree();
        const wxTreeCtrl* Tree() const;

        wxPanel* EditorPanel();
        const wxPanel* EditorPanel() const;

        wxPropertyGrid* PropertyGrid();
        const wxPropertyGrid* PropertyGrid() const;
    public:
        DataBreakdownCommon(const String &name, DataBreakdownCommon *parent);
        DataBreakdownCommon(DataBreakdownCommon &&arg, DataBreakdownCommon *parent);
        DataBreakdownCommon& operator=(DataBreakdownCommon &&arg);
        DataBreakdownCommon(const DataBreakdownCommon &arg) = delete;
        DataBreakdownCommon& operator=(const DataBreakdownCommon &arg) = delete;

        void Reparent(DataBreakdownCommon *parent = nullptr);
        // Resets the setup call
        void Reset();

        void CreateEditorProperties(const ChildReference &afterThis = ChildReference());
        // Will insert the breakdown's properties right above its next sibling (or append if none)
        void ReinsertEditorProperties(DataBreakdownCommon &breakdown);
        void UpdateEditorProperties();
        void DestroyEditorProperties(bool destroyTreeItem = false);
        void CreateTreePiece(wxTreeItemId parentItemID, const ChildReference &afterThis = ChildReference());
        // Will insert the breakdown's properties right above its next sibling (or append if none)
        void ReinsertTreePiece(DataBreakdownCommon &breakdown);
        const Child* GetPreviousChild(const Child &post) const;
        const Child* GetNextChild(const Child &post) const;
        const wxPGProperty* GetTopProperty() const;
        const wxPGProperty* GetBottomProperty() const;
        Child AsChild() const;

        void CreateBreakdowns();
        void DestroyBreakdowns();

        Command::ICommand* CreateAddToCommand();
        Command::ICommand* CreateAddToGroupCommand();
        void AddAddCommandToGroup(Command::ICommand *group);
        Command::ICommand* CreateRemoveThisCommand();
        Command::ICommand* CreateRemoveThisGroupCommand();
        void AddRemoveCommandToGroup(Command::ICommand *group);
        bool IsAddingEnabled() const;
        bool CanRemoveThis() const;

        bool IsValid() const;
        void SetEditable(bool set);
        bool IsEditable() const;
        void SetInvisible(bool set);
        bool IsInvisible() const;

        void SelectThisPrimary();
        void SelectThisSecondary();
        void DeselectThis();
        void ClearSelectedGroups();
        bool IsSelectedPrimary() const;
        bool IsSelectedSecondary() const;
        bool IsSelected() const;

        bool IsAttached() const;
        bool IsTreePieceAttached() const;

        void SetNiceName(const String &set);
        void ResetPropName();
        void SetPropName(const String &set);
        const String& GetName() const;
        const String& GetNiceName() const;
        DataBreakdownCommon* GetParent();
        const DataBreakdownCommon* GetParent() const;

        void SortTreeItem(bool set);
        bool SortTreeItem() const;
        wxTreeItemId GetTreeItemID() const;

        void SetAddCategory(bool set = true);
        bool WillAddCategory() const;
        void SetAddTreePiece(bool set = true);
        bool WillAddTreePiece() const;
        void SetAddChildrenToProperties(bool set = true);
        bool WillAddChildrenToProperties() const;
        void SetUpdateChildrenProperties(bool set = true);
        bool WillUpdateChildrenProperties() const;
        void SetDestroyChildrenProperties(bool set = true);
        bool WillDestroyChildrenProperties() const;
        void SetAddChildrenToTree(bool set = true);
        bool WillAddChildrenToTree() const;
        void SetSelectChildren(bool set = true);
        bool WillSelectChildren() const;
        void SetEditableChildren(bool set = true);
        bool WillEditChildren() const;
        void SetHandleChildren(bool set = true);
        bool WillHandleChildren() const;

        wxPropertyCategory* GetPropertyCategory();
        const wxPropertyCategory* GetPropertyCategory() const;

        bool IgnoreNameForKey() const;
    };

    template<class... FuncArgs, class... Args>
    void DataBreakdownCommon::DoIfBreakdown(Child &child, void(DataBreakdownCommon::*func)(FuncArgs...), Args && ... args)
    {
        if (!child.Is<DataBreakdownCommon*>())
            return;

        (child.Get<DataBreakdownCommon*>()->*func)(std::forward<Args>(args)...);
    }

    template<class T, class... Args>
    T* DataBreakdownCommon::CreatePropertyEmplace(const wxString &propName, const ChildReference &afterThis, Args && ... args)
    {
        return CreatePropertyLabelEmplace<T>(propName, GetNiceName(), afterThis, std::forward<Args>(args)...);
    }

    template<class T, class... Args>
    T* DataBreakdownCommon::CreatePropertyLabelEmplace(const wxString &propName, const wxString &label, const ChildReference &afterThis, Args && ... args)
    {
        if(!afterThis)
            return CreatePropertyLabelAppend<T>(propName, GetNiceName(), std::forward<Args>(args)...);
        else
        {
            auto str = (parent) ? parent->GetPropertyNameSequence(GetName() + "." + propName) : GetName() + "." + propName;
            auto made = new T(label, str, std::forward<Args>(args)...);
            InsertProperty(made, afterThis);
            AddChild(*made);
            return made;
        }
    }

    template<class T, class... Args>
    T* DataBreakdownCommon::CreatePropertyAppend(const wxString &propName, Args && ... args)
    {
        return CreatePropertyLabelAppend<T>(propName, GetNiceName(), std::forward<Args>(args)...);
    }

    template<class T, class... Args>
    T* DataBreakdownCommon::CreatePropertyLabelAppend(const wxString &propName, const wxString &label, Args && ... args)
    {
        auto str = (parent) ? parent->GetPropertyNameSequence(GetName() + "." + propName) : GetName() + "." + propName;
        auto made = new T(label, str, std::forward<Args>(args)...);
        AppendProperty(made);
        AddChild(*made);
        return made;
    }

    template<class PropT>
    void DataBreakdownCommon::DestroyProperty(PropT *&destroy)
    {
        if (!destroy)
            return;

        RemoveChild(*destroy);
        PropertyGrid()->DeleteProperty(destroy);
        destroy = nullptr;
    }
}