
#include "Command.h"
#include "CommandStack.h"
#include "CurrentWorld.h"
#include <Atmos/EntityPositionSystem.h>

namespace Creation
{
    namespace Command
    {
        void ICommand::Do()
        {
            DoImpl();
        }

        void ICommand::Undo()
        {
            UndoImpl();
        }

        void ICommand::Commit()
        {
            Stack::Push(*this);
        }

        AnyGroup::AnyGroup()
        {}

        AnyGroup::AnyGroup(StoredActionVector &&actions) : actions(std::move(actions))
        {}

        void AnyGroup::DoImpl()
        {
            for (auto &loop : actions)
                loop->Do();
        }

        void AnyGroup::UndoImpl()
        {
            for (auto &loop : actions)
                loop->Undo();
        }

        String AnyGroup::GetOutputMessageImpl() const
        {
            return "Group.";
        }

        AnyGroup::StoredActionVector AnyGroup::MakeStore(ActionVector &&pass)
        {
            StoredActionVector ret;
            for (auto &loop : pass)
                ret.push_back(ActionPtr(loop));

            pass.clear();
            return ret;
        }

        AnyGroup* AnyGroup::Create()
        {
            return new AnyGroup();
        }

        AnyGroup* AnyGroup::Create(ActionVector &&actions)
        {
            return new AnyGroup(MakeStore(std::move(actions)));
        }

        void AnyGroup::Add(ICommand &add)
        {
            actions.push_back(ActionPtr(&add));
        }

        void AnyGroup::Add(ICommand *add)
        {
            actions.push_back(ActionPtr(add));
        }
    }
}