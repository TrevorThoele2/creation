#pragma once

#include <memory>
#include <vector>

#include "UnifiedAccess.h"
#include "String.h"
#include "Assert.h"

#include <Atmos/Tile.h>
#include <Atmos/Entity.h>

namespace Creation
{
    namespace Command
    {
        class ICommand
        {
        private:
            virtual void DoImpl() = 0;
            virtual void UndoImpl() = 0;
            virtual String GetOutputMessageImpl() const = 0;
        public:
            virtual ~ICommand() = 0 {}
            void Do();
            void Undo();

            // Pushes this into the stack
            void Commit();
            // Returns a message that describes the action being done
            String GetOutputMessage() const { return GetOutputMessageImpl(); }
        };

        template<class Breakdown>
        class Edit : public ICommand
        {
        public:
            typedef Breakdown BreakdownT;
            typedef typename BreakdownT::PackageT PackageT;
        private:
            BreakdownT *breakdown;
            PackageT previous;
            PackageT editTo;
            String name;

            Edit(BreakdownT *breakdown, const PackageT &editTo, const String &name);
            Edit(const Edit &arg) = default;

            void DoImpl() override final;
            void UndoImpl() override final;
            String GetOutputMessageImpl() const override final;
        public:
            // Returns heap-memory. Make sure to commit this
            static Edit* Create(BreakdownT *breakdown, const PackageT &editTo, const String &name);
            // Returns heap-memory. Make sure to commit this
            static Edit* Create(const Edit &arg);
            Edit& operator=(const Edit &arg) = default;
        };

        template<class Breakdown>
        Edit<Breakdown>::Edit(BreakdownT *breakdown, const PackageT &editTo, const String &name) : breakdown(breakdown), editTo(editTo), name(name), previous(*breakdown->Get())
        {}

        template<class Breakdown>
        void Edit<Breakdown>::DoImpl()
        {
            bool prevEditable = breakdown->IsEditable();
            breakdown->SetEditable(true);
            breakdown->Edit(editTo);
            breakdown->SetEditable(prevEditable);
        }

        template<class Breakdown>
        void Edit<Breakdown>::UndoImpl()
        {
            bool prevEditable = breakdown->IsEditable();
            breakdown->SetEditable(true);
            breakdown->Edit(previous);
            breakdown->SetEditable(prevEditable);
        }

        template<class Breakdown>
        String Edit<Breakdown>::GetOutputMessageImpl() const
        {
            return "Edited " + name;
        }

        template<class Breakdown>
        Edit<Breakdown>* Edit<Breakdown>::Create(BreakdownT *breakdown, const PackageT &editTo, const String &name)
        {
            return new Edit(breakdown, editTo, name);
        }

        template<class Breakdown>
        Edit<Breakdown>* Edit<Breakdown>::Create(const Edit &arg)
        {
            return new Edit(arg);
        }

        template<class BreakdownList>
        class Add : public ICommand
        {
        public:
            typedef BreakdownList BreakdownListT;
            typedef typename BreakdownListT::PackageT PackageT;
        private:
            typedef typename BreakdownListT::iterator RemoveIterator;

            BreakdownListT *breakdownList;
            RemoveIterator removeIterator;
            PackageT set;
            String name;

            Add(BreakdownListT *breakdownList, PackageT &&set);
            Add(BreakdownListT *breakdownList, const PackageT &set);
            Add(const Add &arg) = default;

            void DoImpl() override final;
            void UndoImpl() override final;
            String GetOutputMessageImpl() const override final;
        public:
            // Returns heap-memory. Make sure to commit this
            static Add* Create(BreakdownListT *breakdownList, PackageT &&set);
            // Returns heap-memory. Make sure to commit this
            static Add* Create(BreakdownListT *breakdownList, const PackageT &set);
            // Returns heap-memory. Make sure to commit this
            static Add* Create(const Add &arg);
            Add& operator=(const Add &arg) = default;
        };

        template<class BreakdownList>
        Add<BreakdownList>::Add(BreakdownListT *breakdownList, PackageT &&set) : breakdownList(breakdownList), set(std::move(set))
        {}

        template<class BreakdownList>
        Add<BreakdownList>::Add(BreakdownListT *breakdownList, const PackageT &set) : breakdownList(breakdownList), set(set)
        {}

        template<class BreakdownList>
        void Add<BreakdownList>::DoImpl()
        {
            removeIterator = breakdownList->Add(set);
            name = removeIterator->GetNiceName();
        }

        template<class BreakdownList>
        void Add<BreakdownList>::UndoImpl()
        {
            breakdownList->Remove(removeIterator);
        }

        template<class BreakdownList>
        String Add<BreakdownList>::GetOutputMessageImpl() const
        {
            return "Added " + name;
        }

        template<class BreakdownList>
        Add<BreakdownList>* Add<BreakdownList>::Create(BreakdownListT *breakdownList, PackageT &&set)
        {
            return new Add(breakdownList, std::move(set));
        }

        template<class BreakdownList>
        Add<BreakdownList>* Add<BreakdownList>::Create(BreakdownListT *breakdownList, const PackageT &set)
        {
            return new Add(breakdownList, set);
        }

        template<class BreakdownList>
        Add<BreakdownList>* Add<BreakdownList>::Create(const Add &arg)
        {
            return new Add(arg);
        }

        template<class BreakdownList>
        class Remove : public ICommand
        {
        public:
            typedef BreakdownList BreakdownListT;
            typedef typename BreakdownListT::PackageT PackageT;
            typedef typename BreakdownListT::iterator RemoveIterator;
        private:
            BreakdownListT *breakdownList;
            RemoveIterator removeIterator;
            PackageT set;
            String name;

            Remove(BreakdownListT *breakdownList, RemoveIterator removeIterator);
            Remove(const Remove &arg) = default;

            void DoImpl() override final;
            void UndoImpl() override final;
            String GetOutputMessageImpl() const override final;
        public:
            // Returns heap-memory. Make sure to commit this
            static Remove* Create(BreakdownListT *breakdownList, RemoveIterator removeIterator);
            // Returns heap-memory. Make sure to commit this
            static Remove* Create(const Remove &arg);
            Remove& operator=(const Remove &arg) = default;
        };

        template<class BreakdownList>
        Remove<BreakdownList>::Remove(BreakdownListT *breakdownList, RemoveIterator removeIterator) : breakdownList(breakdownList), removeIterator(removeIterator)
        {
            set = *removeIterator->Get();
        }

        template<class BreakdownList>
        void Remove<BreakdownList>::DoImpl()
        {
            name = removeIterator->GetNiceName();
            breakdownList->Remove(removeIterator);
        }

        template<class BreakdownList>
        void Remove<BreakdownList>::UndoImpl()
        {
            removeIterator = breakdownList->Add(set);
        }

        template<class BreakdownList>
        String Remove<BreakdownList>::GetOutputMessageImpl() const
        {
            return "Removed " + name;
        }

        template<class BreakdownList>
        Remove<BreakdownList>* Remove<BreakdownList>::Create(BreakdownListT *breakdownList, RemoveIterator removeIterator)
        {
            return new Remove(breakdownList, removeIterator);
        }

        template<class BreakdownList>
        Remove<BreakdownList>* Remove<BreakdownList>::Create(const Remove &arg)
        {
            return new Remove(arg);
        }

        template<class Action>
        class Group : public ICommand
        {
        public:
            typedef Action ActionT;
            typedef std::vector<ActionT*> ActionVector;
        private:
            typedef std::unique_ptr<ActionT> ActionPtr;
            typedef std::vector<ActionPtr> StoredActionVector;
            StoredActionVector actions;

            Group();
            Group(StoredActionVector &&actions);
            Group(const Group &arg) = delete;

            void DoImpl() override final;
            void UndoImpl() override final;
            String GetOutputMessageImpl() const override final;

            static StoredActionVector MakeStore(ActionVector &&pass);
        public:
            // Returns heap-memory. Make sure to commit this
            static Group* Create();
            // Returns heap-memory. Make sure to commit this
            static Group* Create(ActionVector &&actions);
            Group& operator=(const Group &arg) = delete;

            void Add(ActionT &add);
            void Add(ActionT *add);
        };

        template<class Action>
        Group<Action>::Group()
        {}

        template<class Action>
        Group<Action>::Group(StoredActionVector &&actions) : actions(std::move(actions))
        {}

        template<class Action>
        void Group<Action>::DoImpl()
        {
            for (auto &loop : actions)
                loop->Do();
        }

        template<class Action>
        void Group<Action>::UndoImpl()
        {
            for (auto &loop : actions)
                loop->Undo();
        }

        template<class Action>
        String Group<Action>::GetOutputMessageImpl() const
        {
            return "Group (" + actions.back()->GetOutputMessage() + ")";
        }

        template<class Action>
        typename Group<Action>::StoredActionVector Group<Action>::MakeStore(ActionVector &&pass)
        {
            StoredActionVector ret;
            for (auto &loop : pass)
                ret.push_back(ActionPtr(loop));

            pass.clear();
            return ret;
        }

        template<class Action>
        Group<Action>* Group<Action>::Create()
        {
            return new Group();
        }

        template<class Action>
        Group<Action>* Group<Action>::Create(ActionVector &&actions)
        {
            return new Group(MakeStore(std::move(actions)));
        }

        template<class Action>
        void Group<Action>::Add(ActionT &add)
        {
            actions.push_back(ActionPtr(&add));
        }

        template<class Action>
        void Group<Action>::Add(ActionT *add)
        {
            actions.push_back(ActionPtr(add));
        }

        class AnyGroup : public ICommand
        {
        public:
            typedef std::vector<ICommand*> ActionVector;
        private:
            typedef std::unique_ptr<ICommand> ActionPtr;
            typedef std::vector<ActionPtr> StoredActionVector;
            StoredActionVector actions;

            AnyGroup();
            AnyGroup(StoredActionVector &&actions);
            AnyGroup(const AnyGroup &arg) = delete;

            void DoImpl() override final;
            void UndoImpl() override final;
            String GetOutputMessageImpl() const override final;

            static StoredActionVector MakeStore(ActionVector &&pass);
        public:
            // Returns heap-memory. Make sure to commit this
            static AnyGroup* Create();
            // Returns heap-memory. Make sure to commit this
            static AnyGroup* Create(ActionVector &&actions);
            AnyGroup& operator=(const AnyGroup &arg) = delete;

            void Add(ICommand &add);
            void Add(ICommand *add);
        };
    }
}