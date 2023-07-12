#pragma once

#include <list>
#include <memory>

#include "DataBreakdownCommon.h"
#include "DataBreakdownWXItemData.h"
#include "BuildPackageList.h"

#include "DataBase.h"

#include "Event.h"
#include <Function/Any.h>
#include "Assert.h"

#include <wx/listbox.h>
#include <wx/treectrl.h>
#include <wx/panel.h>

namespace Creation
{
    class DataBreakdownPreEditArgs
    {
    private:
        DataBreakdownCommon *handler;
        std::unique_ptr<Build::PackageBase> current;
        std::unique_ptr<Build::PackageBase> proposed;
        bool reject;

        DataBreakdownPreEditArgs() = delete;
    public:
        template<class PackageT>
        DataBreakdownPreEditArgs(DataBreakdownCommon &handler, const PackageT &current, const PackageT &proposed);
        DataBreakdownCommon* Handler() const;
        Build::PackageBase* Current() const;
        Build::PackageBase* Proposed() const;
        void Reject(bool set);
        bool Reject() const;
    };

    template<class PackageT>
    DataBreakdownPreEditArgs::DataBreakdownPreEditArgs(DataBreakdownCommon &handler, const PackageT &current, const PackageT &proposed) : handler(&handler), current(new PackageT(current)), proposed(new PackageT(proposed)), reject(false)
    {}

    class DataBreakdownEditArgs
    {
    private:
        DataBreakdownCommon *handler;
        std::unique_ptr<Build::PackageBase> prev;
        std::unique_ptr<Build::PackageBase> current;

        DataBreakdownEditArgs() = delete;
    public:
        template<class PackageT>
        DataBreakdownEditArgs(DataBreakdownCommon &handler, const PackageT &prev, const PackageT &current);
        DataBreakdownCommon* Handler() const;
        Build::PackageBase* Prev() const;
        Build::PackageBase* Current() const;
    };

    template<class PackageT>
    DataBreakdownEditArgs::DataBreakdownEditArgs(DataBreakdownCommon &handler, const PackageT &prev, const PackageT &current) : handler(&handler), prev(new PackageT(prev)), current(new PackageT(current))
    {}

    class DataBreakdownAddArgs
    {
    private:
        DataBreakdownCommon *handler;
        DataBreakdownCommon *added;

        DataBreakdownAddArgs() = delete;
    public:
        DataBreakdownAddArgs(DataBreakdownCommon &handler, DataBreakdownCommon *added);
        DataBreakdownCommon* Handler() const;
        DataBreakdownCommon* Added() const;
    };

    class DataBreakdownPreRemoveArgs
    {
    private:
        DataBreakdownCommon *handler;
        DataBreakdownCommon *toBeRemoved;

        DataBreakdownPreRemoveArgs() = delete;
    public:
        DataBreakdownPreRemoveArgs(DataBreakdownCommon &handler, DataBreakdownCommon *toBeRemoved);
        DataBreakdownCommon* Handler() const;
        DataBreakdownCommon* ToBeRemoved() const;
    };

    class DataBreakdownPostRemoveArgs
    {
    private:
        DataBreakdownCommon *handler;
        std::unique_ptr<Build::PackageBase> package;

        DataBreakdownPostRemoveArgs() = delete;
    public:
        template<class PackageT>
        DataBreakdownPostRemoveArgs(DataBreakdownCommon &handler, const PackageT &package);
        DataBreakdownCommon* Handler() const;
        Build::PackageBase* Package() const;
    };

    template<class PackageT>
    DataBreakdownPostRemoveArgs::DataBreakdownPostRemoveArgs(DataBreakdownCommon &handler, const PackageT &package) : handler(&handler), package(new PackageT(package))
    {}

    template<class T>
    class DataBreakdown;

    template<class Package>
    class DataBreakdownBase : public DataBreakdownCommon
    {
    public:
        typedef Package PackageT;
        typedef DataBreakdownBase EventT;
    private:
        // DataBreakdownCommon overrides
        void ResetInner() override final;
        bool IsValidImpl() const override final;
        bool IsAddingEnabledImpl() const override final;
        void CreateEditorPropertiesInner(const ChildReference &afterThis) override final;
        void UpdateEditorPropertiesInner(DataViewSelection::Group &selected) override final;
        void DestroyEditorPropertiesInner(bool destroyTreeItem) override final;
        void CreateTreePieceInner(wxTreeItemId parentItemID, const ChildReference &afterThis) override final;
        void ChangeSelectInner(SelectedState state) override final;
        void CreateBreakdownsInner() override final;
        void DestroyBreakdownsInner() override final;
        void SetEditableInner(bool set) override final;

        Build::PackageBase* GetCurrentValue() override final;
        void EmitEditEvent(Build::PackageBase *prev) override final;
        // Returns true if the event should be rejected
        bool EmitPreEditEvent(Build::PackageBase *proposed) override final;

        virtual void ResetImpl() {}
        virtual void CreateEditorPropertiesImpl(const ChildReference &afterThis) {}
        virtual void UpdateEditorPropertiesImpl(DataViewSelection::Group &selected) {}
        virtual void DestroyEditorPropertiesImpl(bool destroyTreeItem) {}
        virtual void CreateTreePieceImpl(wxTreeItemId parentItemID, const ChildReference &afterThis) {}
        virtual void ChangeSelectImpl(SelectedState state) {}
        virtual void CreateBreakdownsImpl() {}
        virtual void DestroyBreakdownsImpl() {}
        virtual void SetEditableImpl(bool set) {}

        virtual void OnPreEdited() {}
        virtual void OnEdited() {}
    private:
        PackageT *package;

        virtual void SetupImpl() {}
    protected:
        template<class DerivedT>
        void ChangePackage(const PackageT &change);
    public:
        Event<DataBreakdownPreEditArgs&> preEdit;
        Event<const DataBreakdownEditArgs&> edited;

        DataBreakdownBase(const String &name, DataBreakdownCommon *parent);
        DataBreakdownBase(DataBreakdownBase &&arg, DataBreakdownCommon *parent);
        DataBreakdownBase& operator=(DataBreakdownBase &&arg);
        virtual ~DataBreakdownBase() = 0 {}

        void Setup(PackageT &set);

        void Edit(const PackageT &edit);
        void Edit(PackageT &&edit);
        void ForceEdit(const PackageT &edit);
        void ForceEdit(PackageT &&edit);
        PackageT* Get();
        const PackageT* Get() const;
    };

    template<class Package>
    void DataBreakdownBase<Package>::ResetInner()
    {
        package = nullptr;
        ResetImpl();
    }

    template<class Package>
    bool DataBreakdownBase<Package>::IsValidImpl() const
    {
        return static_cast<bool>(package);
    }

    template<class Package>
    bool DataBreakdownBase<Package>::IsAddingEnabledImpl() const
    {
        return false;
    }

    template<class Package>
    void DataBreakdownBase<Package>::CreateEditorPropertiesInner(const ChildReference &afterThis)
    {
        CreateEditorPropertiesImpl(afterThis);
    }

    template<class Package>
    void DataBreakdownBase<Package>::UpdateEditorPropertiesInner(DataViewSelection::Group &selected)
    {
        UpdateEditorPropertiesImpl(selected);
    }

    template<class Package>
    void DataBreakdownBase<Package>::DestroyEditorPropertiesInner(bool destroyTreeItem)
    {
        DestroyEditorPropertiesImpl(destroyTreeItem);
    }

    template<class Package>
    void DataBreakdownBase<Package>::CreateTreePieceInner(wxTreeItemId parentItemID, const ChildReference &afterThis)
    {
        CreateTreePieceImpl(parentItemID, afterThis);
    }

    template<class Package>
    void DataBreakdownBase<Package>::ChangeSelectInner(SelectedState state)
    {
        ChangeSelectImpl(state);
    }

    template<class Package>
    void DataBreakdownBase<Package>::CreateBreakdownsInner()
    {
        CreateBreakdownsImpl();
    }

    template<class Package>
    void DataBreakdownBase<Package>::DestroyBreakdownsInner()
    {
        DestroyBreakdownsImpl();
    }

    template<class Package>
    void DataBreakdownBase<Package>::SetEditableInner(bool set)
    {
        SetEditableImpl(set);
    }

    template<class Package>
    Build::PackageBase* DataBreakdownBase<Package>::GetCurrentValue()
    {
        return Get();
    }

    template<class Package>
    void DataBreakdownBase<Package>::EmitEditEvent(Build::PackageBase *prev)
    {
        OnEdited();
        edited(DataBreakdownEditArgs(*this, *static_cast<PackageT*>(prev), *Get()));
    }

    template<class Package>
    bool DataBreakdownBase<Package>::EmitPreEditEvent(Build::PackageBase *proposed)
    {
        OnPreEdited();
        DataBreakdownPreEditArgs args(*this, *Get(), *static_cast<PackageT*>(proposed));
        preEdit(args);
        return args.Reject();
    }

    template<class Package>
    template<class DerivedT>
    void DataBreakdownBase<Package>::ChangePackage(const PackageT &change)
    {
        auto selected = GetSelected();
        if (!selected || selected->empty())
            return;

        typedef Command::Edit<DerivedT> EditCommand;

        if (selected->size() == 1)
        {
            EditCommand::Create(static_cast<DerivedT*>(*selected->begin()), change, GetName())->Commit();
            return;
        }

        auto commandGroup = Command::Group<EditCommand>::Create();
        for (auto loop : *selected)
            commandGroup->Add(EditCommand::Create(static_cast<DerivedT*>(loop), change, GetName()));
        commandGroup->Commit();
    }

    template<class Package>
    DataBreakdownBase<Package>::DataBreakdownBase(const String &name, DataBreakdownCommon *parent) : DataBreakdownCommon(name, parent), package(nullptr)
    {}

    template<class Package>
    DataBreakdownBase<Package>::DataBreakdownBase(DataBreakdownBase &&arg, DataBreakdownCommon *parent) : DataBreakdownCommon(std::move(arg), parent), package(std::move(arg.package))
    {}

    template<class Package>
    DataBreakdownBase<Package>& DataBreakdownBase<Package>::operator=(DataBreakdownBase &&arg)
    {
        DataBreakdownCommon::operator=(std::move(arg));
        package = std::move(arg.package);
        return *this;
    }

    template<class Package>
    void DataBreakdownBase<Package>::Setup(PackageT &set)
    {
        package = &set;
        SetupImpl();
    }

    template<class Package>
    void DataBreakdownBase<Package>::Edit(const PackageT &edit)
    {
        if (edit == *package)
            return;

        // Pre edit
        {
            auto prevPackage = *package;
            *package = edit;
            std::vector<Build::PackageBase*> curPackages(MakeEditPackageStack());
            *package = prevPackage;

            bool reject = false;

            DataBreakdownPreEditArgs preEditArgs(*this, *package, edit);
            preEdit(preEditArgs);
            if (preEditArgs.Reject())
                reject = true;

            if (ConsumePreEditPackageStack(std::move(curPackages)))
                reject = true;

            if (reject)
            {
                UpdateEditorProperties();
                return;
            }
        }

        std::vector<Build::PackageBase*> prevPackages(MakeEditPackageStack());

        PackageT prev = *package;
        *package = edit;
        UpdateEditorProperties();
        OnEdited();
        edited(DataBreakdownEditArgs(*this, prev, *Get()));

        ConsumeEditPackageStack(std::move(prevPackages));
    }

    template<class Package>
    void DataBreakdownBase<Package>::Edit(PackageT &&edit)
    {
        if (edit == *package)
            return;

        // Pre edit
        {
            auto prevPackage = *package;
            *package = edit;
            std::vector<Build::PackageBase*> curPackages(MakeEditPackageStack());
            *package = prevPackage;

            bool reject = false;

            DataBreakdownPreEditArgs preEditArgs(*this, *package, edit);
            preEdit(preEditArgs);
            if (preEditArgs.Reject())
                reject = true;

            if (ConsumePreEditPackageStack(std::move(curPackages)))
                reject = true;

            if (reject)
            {
                UpdateEditorProperties();
                return;
            }
        }

        std::vector<Build::PackageBase*> prevPackages(MakeEditPackageStack());

        PackageT prev = *package;
        *package = std::move(edit);
        UpdateEditorProperties();
        OnEdited();
        edited(DataBreakdownEditArgs(*this, prev, *Get()));

        ConsumeEditPackageStack(std::move(prevPackages));
    }

    template<class Package>
    void DataBreakdownBase<Package>::ForceEdit(const PackageT &edit)
    {
        bool resetAs = IsEditable();
        SetEditable(true);
        Edit(edit);
        SetEditable(resetAs);
    }

    template<class Package>
    void DataBreakdownBase<Package>::ForceEdit(PackageT &&edit)
    {
        bool resetAs = IsEditable();
        SetEditable(true);
        Edit(std::move(edit));
        SetEditable(resetAs);
    }

    template<class Package>
    typename DataBreakdownBase<Package>::PackageT* DataBreakdownBase<Package>::Get()
    {
        return package;
    }

    template<class Package>
    typename const DataBreakdownBase<Package>::PackageT* DataBreakdownBase<Package>::Get() const
    {
        return package;
    }

    template<class Package>
    class DataBreakdownList : public DataBreakdownCommon
    {
    public:
        typedef Package PackageT;
        typedef Build::Package<::Atmos::RandomAccessSequence<PackageT>> ListT;
        typedef typename ListT::BuildT::ValueT BasePackageT;
        typedef typename ListT::BuildT::ID ListPositionT;
        typedef typename ListT::BuildT::ID EntryCountT;
        typedef DataBreakdown<Package> BreakdownT;
        typedef DataBreakdownList EventT;

        typedef ::function::Function<String, BreakdownT&> NiceNameExtractorFunction;
        typedef ::function::Function<Event<const DataBreakdownEditArgs&>*, BreakdownT&> NiceNameGetEventFunction;
        typedef ::function::Function<void, BreakdownT&, const String&> NameSetFunction;
    private:
        typedef ::Atmos::RandomAccessSequence<BreakdownT> BreakdownListT;
    public:
        typedef typename BreakdownListT::iterator iterator;
    private:
        // DataBreakdownCommon overrides
        void ResetInner() override final;
        bool IsValidImpl() const override final;
        bool IsAddingEnabledImpl() const override final;
        Command::ICommand* CreateAddToCommandImpl() override final;
        Command::ICommand* CreateAddToGroupCommandImpl() override final;
        virtual void AddAddCommandToGroupImpl(Command::ICommand *group) override final;
        Command::ICommand* CreateRemoveThisCommandImpl(DataBreakdownCommon *remove) override final;
        Command::ICommand* CreateRemoveThisGroupCommandImpl() override final;
        void AddRemoveCommandToGroupImpl(DataBreakdownCommon *remove, Command::ICommand *group) override final;

        void CreateBreakdownsInner() override final;
        void DestroyBreakdownsInner() override final;

        Build::PackageBase* GetCurrentValue() override final;
        void EmitEditEvent(Build::PackageBase *prev) override final;
        // Returns true if the event should be rejected
        bool EmitPreEditEvent(Build::PackageBase *proposed) override final;
    private:
        iterator CreateBreakdown(PackageT &package);

        void SetBreakdownEmptyNiceName(BreakdownT &breakdown);
        void OnNiceNameEdited(const DataBreakdownEditArgs &args);
    private:
        ListT *list;
        BreakdownListT breakdownList;

        EntryCountT minEntryCount;
        EntryCountT maxEntryCount;

        bool makeChildrenCategory;

        String prependEntryName;

        NiceNameExtractorFunction niceNameExtractorFunc;
        NiceNameGetEventFunction getNiceNameEventFunc;
        NameSetFunction nameSetFunc;
        std::unordered_map<BreakdownT*, ::Atmos::EventScopedConnection> eventConnections;
    public:
        // Can reject the event here, which means that the edit will not finalize
        Event<DataBreakdownPreEditArgs&> preEdit;
        // Edited parameter in the received argument object will be ListT
        Event<const DataBreakdownEditArgs&> edited;
        // Added parameter in the received argument object will be BreakdownT
        Event<const DataBreakdownAddArgs&> added;
        // Removed parameter in the received argument object will be BreakdownT
        Event<const DataBreakdownPreRemoveArgs&> preRemove;
        // Removed parameter in the received argument object will be BasePackageT
        Event<const DataBreakdownPostRemoveArgs&> postRemove;

        DataBreakdownList(const String &name, DataBreakdownCommon *parent);
        DataBreakdownList(DataBreakdownList &&arg, DataBreakdownCommon *parent);
        DataBreakdownList& operator=(DataBreakdownList &&arg);

        void Setup(ListT &set);

        iterator Add(PackageT &&add);
        iterator Add(const PackageT &add);
        iterator AddOnlyBreakdown(PackageT &add);
        void Remove(ListPositionT position);
        void Remove(iterator remove);
        iterator Find(ListPositionT position);

        void Edit(const ListT &edit);
        void Edit(ListT &&edit);
        void ForceEdit(const ListT &edit);
        void ForceEdit(ListT &&edit);
        ListT* Get();
        const ListT* Get() const;

        iterator begin();
        iterator end();

        void SetMakeChildrenCategory(bool set = true);
        bool GetMakeChildrenCategory() const;

        void SetPrependEntryName(const String &set);
        void SetNiceNameFunctions(NiceNameExtractorFunction &&extractor, NiceNameGetEventFunction &&getEvent, NameSetFunction &&nameSet);
    };

    template<class Package>
    void DataBreakdownList<Package>::ResetInner()
    {
        list = nullptr;
    }

    template<class Package>
    bool DataBreakdownList<Package>::IsValidImpl() const
    {
        return static_cast<bool>(list);
    }

    template<class Package>
    bool DataBreakdownList<Package>::IsAddingEnabledImpl() const
    {
        return true;
    }

    template<class Package>
    Command::ICommand* DataBreakdownList<Package>::CreateAddToCommandImpl()
    {
        return Command::Add<DataBreakdownList>::Create(this, PackageT());
    }

    template<class Package>
    Command::ICommand* DataBreakdownList<Package>::CreateAddToGroupCommandImpl()
    {
        return Command::Group<Command::Add<DataBreakdownList>>::Create();
    }

    template<class Package>
    void DataBreakdownList<Package>::AddAddCommandToGroupImpl(Command::ICommand *group)
    {
        Command::Group<Command::Add<DataBreakdownList>> *castedGroup = static_cast<Command::Group<Command::Add<DataBreakdownList>>*>(group);
        castedGroup->Add(Command::Add<DataBreakdownList>::Create(this, PackageT()));
    }

    template<class Package>
    Command::ICommand* DataBreakdownList<Package>::CreateRemoveThisCommandImpl(DataBreakdownCommon *remove)
    {
        ListPositionT position = 0;
        for (auto loop = breakdownList.begin(); loop != breakdownList.end(); ++loop, ++position)
        {
            if (&*loop == remove)
                return Command::Remove<DataBreakdownList>::Create(this, loop);
        }

        return nullptr;
    }

    template<class Package>
    Command::ICommand* DataBreakdownList<Package>::CreateRemoveThisGroupCommandImpl()
    {
        return Command::Group<Command::Remove<DataBreakdownList>>::Create();
    }

    template<class Package>
    void DataBreakdownList<Package>::AddRemoveCommandToGroupImpl(DataBreakdownCommon *remove, Command::ICommand *group)
    {
        Command::Group<Command::Remove<DataBreakdownList>> *castedGroup = static_cast<Command::Group<Command::Remove<DataBreakdownList>>*>(group);

        ListPositionT position = 0;
        for (auto loop = breakdownList.begin(); loop != breakdownList.end(); ++loop, ++position)
        {
            if (&*loop == remove)
            {
                castedGroup->Add(Command::Remove<DataBreakdownList>::Create(this, loop));
                return;
            }
        }
    }

    template<class Package>
    void DataBreakdownList<Package>::CreateBreakdownsInner()
    {
        for (auto &loop : list->value)
            CreateBreakdown(loop);
    }

    template<class Package>
    void DataBreakdownList<Package>::DestroyBreakdownsInner()
    {
        eventConnections.clear();

        for (auto loop = breakdownList.begin(); loop != breakdownList.end();)
        {
            loop->DestroyEditorProperties(true);
            loop = breakdownList.erase(loop);
        }
    }

    template<class Package>
    Build::PackageBase* DataBreakdownList<Package>::GetCurrentValue()
    {
        return Get();
    }

    template<class Package>
    void DataBreakdownList<Package>::EmitEditEvent(Build::PackageBase *prev)
    {
        edited(DataBreakdownEditArgs(*this, *static_cast<ListT*>(prev), *Get()));
    }

    template<class Package>
    bool DataBreakdownList<Package>::EmitPreEditEvent(Build::PackageBase *proposed)
    {
        DataBreakdownPreEditArgs args(*this, *Get(), *static_cast<ListT*>(proposed));
        preEdit(args);
        return args.Reject();
    }

    template<class Package>
    typename DataBreakdownList<Package>::iterator DataBreakdownList<Package>::CreateBreakdown(PackageT &package)
    {
        iterator breakdownItr;

        {
            // Find the name to use
            String niceName(prependEntryName + ::Atmos::ToString(breakdownList.size() + 1));
            breakdownItr = breakdownList.AddBack(BreakdownT(prependEntryName, this));
            breakdownItr->SetNiceName(niceName);
            breakdownItr->SetPropName(niceName);
        }

        breakdownItr->Reparent(this);
        breakdownItr->Setup(package);
        breakdownItr->SetAddCategory(makeChildrenCategory);

        if (niceNameExtractorFunc.IsValid())
        {
            auto prevNiceName = breakdownItr->GetNiceName();
            CREATION_ASSERT_MESSAGE(getNiceNameEventFunc.IsValid(), "The getter event function needs to exist.");
            CREATION_ASSERT_MESSAGE(nameSetFunc.IsValid(), "The name setter event function needs to exist.");
            auto e = getNiceNameEventFunc(*breakdownItr);
            CREATION_ASSERT_MESSAGE(e, "The nice name event needs to exist.");
            breakdownItr->SetNiceName(niceNameExtractorFunc(*breakdownItr));
            eventConnections.emplace(&*breakdownItr, e->Subscribe(&DataBreakdownList::OnNiceNameEdited, *this));
            if(breakdownItr->GetNiceName() == "")
                (prevNiceName == "") ? SetBreakdownEmptyNiceName(*breakdownItr) : breakdownItr->SetNiceName(prevNiceName);

            nameSetFunc(*breakdownItr, breakdownItr->GetNiceName());
        }

        breakdownItr->CreateBreakdowns();
        if (IsTreePieceAttached())
            breakdownItr->CreateTreePiece(GetTreeItemID());
        AddChild(*breakdownItr);
        if (WillAddChildrenToProperties() && IsAttached())
        {
            breakdownItr->SelectThisSecondary();
            breakdownItr->CreateEditorProperties(nullptr);
        }

        added(DataBreakdownAddArgs(*this, &*breakdownItr));
        PropertyGrid()->SetSplitterLeft();
        return breakdownItr;
    }

    template<class Package>
    void DataBreakdownList<Package>::SetBreakdownEmptyNiceName(BreakdownT &breakdown)
    {
        breakdown.SetNiceName(breakdown.GetName());
    }

    template<class Package>
    void DataBreakdownList<Package>::OnNiceNameEdited(const DataBreakdownEditArgs &args)
    {
        // Retrieve the breakdown
        DataBreakdownCommon *common = args.Handler();
        while (common->GetParent() != this)
            common = common->GetParent();
        BreakdownT &casted = static_cast<BreakdownT&>(*common);

        // Set nice name
        if(niceNameExtractorFunc.IsValid())
            common->SetNiceName(niceNameExtractorFunc(casted));
        if (common->GetNiceName() == "")
            SetBreakdownEmptyNiceName(casted);

        if(common->GetTreeItemID().IsOk())
            Tree()->SetItemText(common->GetTreeItemID(), common->GetNiceName());
    }

    template<class Package>
    DataBreakdownList<Package>::DataBreakdownList(const String &name, DataBreakdownCommon *parent) : DataBreakdownCommon(name, parent), list(nullptr), minEntryCount(1), maxEntryCount(10), prependEntryName("Entry"), makeChildrenCategory(true)
    {
        SetAddChildrenToProperties(true);
    }

    template<class Package>
    DataBreakdownList<Package>::DataBreakdownList(DataBreakdownList &&arg, DataBreakdownCommon *parent) : DataBreakdownCommon(std::move(arg), parent), list(std::move(arg.list)), breakdownList(std::move(arg.breakdownList)), minEntryCount(std::move(arg.minEntryCount)), maxEntryCount(std::move(arg.maxEntryCount)), prependEntryName(std::move(arg.prependEntryName)), makeChildrenCategory(std::move(arg.makeChildrenCategory)), niceNameExtractorFunc(std::move(arg.niceNameExtractorFunc)), getNiceNameEventFunc(std::move(arg.getNiceNameEventFunc)), nameSetFunc(std::move(arg.nameSetFunc))
    {}

    template<class Package>
    DataBreakdownList<Package>& DataBreakdownList<Package>::operator=(DataBreakdownList &&arg)
    {
        DataBreakdownCommon::operator=(std::move(arg));
        list = std::move(arg.list);
        breakdownList = std::move(arg.breakdownList);
        minEntryCount = std::move(arg.minEntryCount);
        maxEntryCount = std::move(arg.maxEntryCount);
        prependEntryName = std::move(arg.prependEntryName);
        makeChildrenCategory = std::move(arg.makeChildrenCategory);
        niceNameExtractorFunc = std::move(arg.niceNameExtractorFunc);
        getNiceNameEventFunc = std::move(arg.getNiceNameEventFunc);
        nameSetFunc = std::move(arg.nameSetFunc);
        return *this;
    }

    template<class Package>
    void DataBreakdownList<Package>::Setup(ListT &set)
    {
        list = &set;
    }

    template<class Package>
    typename DataBreakdownList<Package>::iterator DataBreakdownList<Package>::Add(PackageT &&add)
    {
        return AddOnlyBreakdown(*list->value.AddBack(std::move(add)));
    }

    template<class Package>
    typename DataBreakdownList<Package>::iterator DataBreakdownList<Package>::Add(const PackageT &add)
    {
        return AddOnlyBreakdown(*list->value.AddBack(add));
    }

    template<class Package>
    typename DataBreakdownList<Package>::iterator DataBreakdownList<Package>::AddOnlyBreakdown(PackageT &add)
    {
        auto ret = CreateBreakdown(add);
        if (IsSelectedPrimary())
            Tree()->Expand(GetTreeItemID());
        return ret;
    }

    template<class Package>
    void DataBreakdownList<Package>::Remove(ListPositionT position)
    {
        auto found = &*breakdownList.Find(position);
        if (!found)
            return;

        BasePackageT prev(*found->Get());
        preRemove(DataBreakdownPreRemoveArgs(*this, found));

        found->DestroyEditorProperties(true);
        found->DeselectThis();

        eventConnections.erase(found);
        RemoveChild(*found);
        list->value.Remove(position);
        breakdownList.Remove(position);
        postRemove(DataBreakdownPostRemoveArgs(*this, prev));
    }

    template<class Package>
    void DataBreakdownList<Package>::Remove(iterator remove)
    {
        std::unique_ptr<BasePackageT> prev;
        for (auto loop = list->value.begin(); loop != list->value.end(); ++loop)
        {
            if (&*loop != remove->Get())
                continue;

            preRemove(DataBreakdownPreRemoveArgs(*this, &*remove));

            remove->DestroyEditorProperties(true);
            remove->DeselectThis();

            eventConnections.erase(&*remove);
            prev.reset(new BasePackageT(*loop));
            list->value.Remove(loop);
            break;
        }

        RemoveChild(*remove);
        breakdownList.Remove(remove);
        postRemove(DataBreakdownPostRemoveArgs(*this, *prev));
    }

    template<class Package>
    typename DataBreakdownList<Package>::iterator DataBreakdownList<Package>::Find(ListPositionT position)
    {
        return breakdownList[position];
    }

    template<class Package>
    void DataBreakdownList<Package>::Edit(const ListT &edit)
    {
        if (*list == edit)
            return;

        // Pre edit
        {
            auto prevPackage = *list;
            *list = edit;
            std::vector<Build::PackageBase*> curPackages(MakeEditPackageStack());
            *list = prevPackage;

            bool reject = false;

            DataBreakdownPreEditArgs preEditArgs(*this, *list, edit);
            preEdit(preEditArgs);
            if (preEditArgs.Reject())
                reject = true;

            if (ConsumePreEditPackageStack(std::move(curPackages)))
                reject = true;

            if (reject)
            {
                UpdateEditorProperties();
                return;
            }
        }

        std::vector<Build::PackageBase*> prevPackages(MakeEditPackageStack());

        ListT prev(std::move(*list));
        *list = edit;
        edited(DataBreakdownEditArgs(*this, prev, *list));

        ConsumeEditPackageStack(std::move(prevPackages));
    }

    template<class Package>
    void DataBreakdownList<Package>::Edit(ListT &&edit)
    {
        if (*list == edit)
            return;

        // Pre edit
        {
            auto prevPackage = *list;
            *list = edit;
            std::vector<Build::PackageBase*> curPackages(MakeEditPackageStack());
            *list = prevPackage;

            bool reject = false;

            DataBreakdownPreEditArgs preEditArgs(*this, *list, edit);
            preEdit(preEditArgs);
            if (preEditArgs.Reject())
                reject = true;

            if (ConsumePreEditPackageStack(std::move(curPackages)))
                reject = true;

            if (reject)
            {
                UpdateEditorProperties();
                return;
            }
        }

        std::vector<Build::PackageBase*> prevPackages(MakeEditPackageStack());

        ListT prev(std::move(*list));
        *list = std::move(edit);
        edited(DataBreakdownEditArgs(*this, prev, *list));

        ConsumeEditPackageStack(std::move(prevPackages));
    }

    template<class Package>
    void DataBreakdownList<Package>::ForceEdit(const ListT &edit)
    {
        bool resetAs = IsEditable();
        SetEditable(true);
        Edit(edit);
        SetEditable(resetAs);
    }

    template<class Package>
    void DataBreakdownList<Package>::ForceEdit(ListT &&edit)
    {
        bool resetAs = IsEditable();
        SetEditable(true);
        Edit(std::move(edit));
        SetEditable(resetAs);
    }

    template<class Package>
    typename DataBreakdownList<Package>::ListT* DataBreakdownList<Package>::Get()
    {
        return list;
    }

    template<class Package>
    typename const DataBreakdownList<Package>::ListT* DataBreakdownList<Package>::Get() const
    {
        return list;
    }

    template<class Package>
    typename DataBreakdownList<Package>::iterator DataBreakdownList<Package>::begin()
    {
        return breakdownList.begin();
    }

    template<class Package>
    typename DataBreakdownList<Package>::iterator DataBreakdownList<Package>::end()
    {
        return breakdownList.end();
    }

    template<class Package>
    void DataBreakdownList<Package>::SetMakeChildrenCategory(bool set)
    {
        makeChildrenCategory = set;
    }

    template<class Package>
    bool DataBreakdownList<Package>::GetMakeChildrenCategory() const
    {
        return makeChildrenCategory;
    }

    template<class Package>
    void DataBreakdownList<Package>::SetPrependEntryName(const String &set)
    {
        prependEntryName = set;
    }

    template<class Package>
    void DataBreakdownList<Package>::SetNiceNameFunctions(NiceNameExtractorFunction &&extractor, NiceNameGetEventFunction &&getEvent, NameSetFunction &&nameSet)
    {
        eventConnections.clear();
        niceNameExtractorFunc = std::move(extractor);
        getNiceNameEventFunc = std::move(getEvent);
        nameSetFunc = std::move(nameSet);
    }

    template<class Enum>
    class DataBreakdownEnum : public DataBreakdownBase<Build::Package<typename std::underlying_type<Enum>::type>>
    {
    private:
        typedef DataManager<Enum> ManagerT;
    public:
        typedef Enum EnumT;
        typedef typename ManagerT::DataT::StringT DataStringT;
        typedef typename ManagerT::DataT::ValueT DataValueT;
    private:
        typedef typename ManagerT::Container DataContainer;
        typedef typename std::underlying_type<Enum>::type UnderlyingT;

        wxEnumProperty *prop;
        DataContainer dataContainer;

        void OnPropertyGridChanged(wxPropertyGridEvent &e);

        void CreateEditorPropertiesImpl(const ChildReference &afterThis) override final;
        void UpdateEditorPropertiesImpl(DataViewSelection::Group &selected) override final;
        void DestroyEditorPropertiesImpl(bool destroyTreeItem) override final;
        void SetEditableImpl(bool set) override final;
    public:
        DataBreakdownEnum(const String &name, DataBreakdownCommon *parent);
        DataBreakdownEnum(DataBreakdownEnum &&arg, DataBreakdownCommon *parent);
        DataBreakdownEnum& operator=(DataBreakdownEnum &&arg);

        void ResetData();
        void RemoveData(const DataStringT &string);
        void RemoveData(const DataValueT &value);

        EnumT GetAsEnum() const;
    };

    template<class Enum>
    void DataBreakdownEnum<Enum>::OnPropertyGridChanged(wxPropertyGridEvent &e)
    {
        if (e.GetProperty() != prop)
        {
            e.Skip();
            return;
        }

        PackageT nPackage;
        nPackage.value = prop->GetValue().GetInteger();
        ChangePackage<DataBreakdownEnum>(nPackage);

        e.Skip();
    }

    template<class Enum>
    void DataBreakdownEnum<Enum>::CreateEditorPropertiesImpl(const ChildReference &afterThis)
    {
        wxPGChoices choices;
        for (auto &loop : dataContainer)
            choices.Add(loop.GetString(), static_cast<UnderlyingT>(loop.GetValue()));

        prop = CreatePropertyEmplace<wxEnumProperty>("Value", afterThis, choices);
        PropertyGrid()->Bind(wxEVT_PG_CHANGED, &DataBreakdownEnum::OnPropertyGridChanged, this);
    }

    template<class Enum>
    void DataBreakdownEnum<Enum>::UpdateEditorPropertiesImpl(DataViewSelection::Group &selected)
    {
        // Reset the choices
        wxPGChoices choices;
        for (auto &loop : dataContainer)
            choices.Add(loop.GetString(), static_cast<UnderlyingT>(loop.GetValue()));
        prop->SetChoices(choices);

        prop->Enable(IsEditable());

        prop->SetValue(static_cast<DataBreakdownEnum*>(*selected.begin())->Get()->value);
        for (auto loop = ++selected.begin(); loop != selected.end(); ++loop)
        {
            if (static_cast<DataBreakdownEnum*>(*loop)->Get()->value != prop->GetValue().GetInteger())
            {
                prop->SetValue(wxPG_INVALID_VALUE);
                return;
            }
        }
    }

    template<class Enum>
    void DataBreakdownEnum<Enum>::DestroyEditorPropertiesImpl(bool destroyTreeItem)
    {
        DestroyProperty(prop);
        PropertyGrid()->Unbind(wxEVT_PG_CHANGED, &DataBreakdownEnum::OnPropertyGridChanged, this);
    }

    template<class Enum>
    void DataBreakdownEnum<Enum>::SetEditableImpl(bool set)
    {
        if (prop)
            prop->Enable(set);
    }

    template<class Enum>
    DataBreakdownEnum<Enum>::DataBreakdownEnum(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent), prop(nullptr)
    {
        SetAddCategory(false);
        ResetData();
    }

    template<class Enum>
    DataBreakdownEnum<Enum>::DataBreakdownEnum(DataBreakdownEnum &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent), prop(std::move(arg.prop))
    {
        SetAddCategory(false);
        ResetData();
    }

    template<class Enum>
    DataBreakdownEnum<Enum>& DataBreakdownEnum<Enum>::operator=(DataBreakdownEnum &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        prop = std::move(arg.prop);
        return *this;
    }

    template<class Enum>
    void DataBreakdownEnum<Enum>::ResetData()
    {
        dataContainer = ManagerT::Get();
    }

    template<class Enum>
    void DataBreakdownEnum<Enum>::RemoveData(const DataStringT &string)
    {
        for(auto loop = dataContainer.begin(); loop != dataContainer.end(); ++loop)
            if (loop->GetString() == string)
            {
                dataContainer.erase(loop);
                return;
            }
    }

    template<class Enum>
    void DataBreakdownEnum<Enum>::RemoveData(const DataValueT &value)
    {
        for (auto loop = dataContainer.begin(); loop != dataContainer.end(); ++loop)
            if (loop->GetValue() == value)
            {
                dataContainer.erase(loop);
                return;
            }
    }

    template<class Enum>
    typename DataBreakdownEnum<Enum>::EnumT DataBreakdownEnum<Enum>::GetAsEnum() const
    {
        return static_cast<EnumT>(Get()->value);
    }
}