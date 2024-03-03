
#include "Application.h"
#include "MainFrame.h"
#include "FieldCommand.h"
#include "CurrentWorld.h"

namespace LevelEditor
{
    namespace Command
    {
        AddField::AddField(atmos::FieldID id) : id(id)
        {}

        void AddField::Do()
        {
            CurrentWorld::Add(id);
            CurrentWorld::Select(id, false);
            static_cast<Application*>(wxApp::GetInstance())->GetMainFrame()->OnNewField(id);
        }

        void AddField::Undo()
        {
            CurrentWorld::Remove(id);
            static_cast<Application*>(wxApp::GetInstance())->GetMainFrame()->OnRemoveField(id);
        }

        ChangeField::ChangeField(atmos::FieldID toID) : toID(toID), fromID(CurrentWorld::GetCurrentField()->GetID())
        {}

        void ChangeField::Do()
        {
            CurrentWorld::Select(toID, false);
        }

        void ChangeField::Undo()
        {
            CurrentWorld::Select(fromID, false);
        }
    }
}