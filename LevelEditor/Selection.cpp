
#include "Viewport.h"
#include "Selection.h"

namespace Creation
{
    std::unordered_set<SelectionBase*> SelectionHandler::selections;

    void SelectionHandler::Add(SelectionBase &add)
    {
        selections.emplace(&add);
    }

    void SelectionHandler::Remove(SelectionBase &remove)
    {
        selections.erase(&remove);
    }

    void SelectionHandler::ClearAll()
    {
        for (auto &loop : selections)
            loop->Clear();
    }

    void SelectionHandler::TemporaryDeconstruct()
    {
        for (auto &loop : selections)
            loop->TemporaryDeconstruct();
    }

    void SelectionHandler::Reconstruct()
    {
        for (auto &loop : selections)
            loop->Reconstruct();
    }

    SelectionBase::SelectionBase()
    {
        SelectionHandler::Add(*this);
    }

    SelectionBase::~SelectionBase()
    {
        SelectionHandler::Remove(*this);
    }
}