#pragma once

namespace Creation
{
    // General stack copy
    template<class T>
    T Copy(const T &t)
    {
        return T(t);
    }

    // General heap copy
    template<class T>
    T* CopyHeap(const T &t)
    {
        return new T(t);
    }

    // Returns nullptr in case of argument being null
    template<class T>
    T* CopyHeap(T *t)
    {
        if (t)
            return new T(*t);

        return nullptr;
    }

    // Move things up and down in a list
    /*
    void ScriptEditorDialog::OnMoveUp(wxCommandEvent &e)
    {
    auto &strings = coreScripts->GetStrings();
    if (strings.empty() || strings.size() == 1)
    return;

    // Setup new selection
    wxArrayInt newSelection;
    {
    wxArrayInt selection;
    coreScripts->GetSelections(selection);
    newSelection.reserve(selection.size());
    }

    // Setup new strings
    wxArrayString newStrings;
    newStrings.reserve(strings.size());
    std::list<std::string> newStringsToAtmos;

    int position = 0;
    auto loop = strings.begin();

    {
    bool isSelected = coreScripts->IsSelected(position);
    while (isSelected && loop != strings.end())
    {
    newStrings.Add(*loop);
    newSelection.Add(position);

    ++position;
    ++loop;

    isSelected = coreScripts->IsSelected(position);
    }
    }

    while(loop != strings.end())
    {
    if (coreScripts->IsSelected(position))
    {
    auto newPosition = position - 1;
    newStrings.Insert(*loop, newPosition);
    newSelection.Add(newPosition);
    }
    else
    newStrings.Add(*loop);

    ++position;
    ++loop;
    }

    coreScripts->Set(newStrings);
    for (auto &loop : newSelection)
    coreScripts->SetSelection(loop);

    Atmos::ScriptCompiler::ReorganizeCore(std::move(newStringsToAtmos));
    }

    void ScriptEditorDialog::OnMoveDown(wxCommandEvent &e)
    {
    auto &strings = coreScripts->GetStrings();
    if (strings.empty() || strings.size() == 1)
    return;

    // Setup new selection
    wxArrayInt newSelection;
    {
    wxArrayInt selection;
    coreScripts->GetSelections(selection);
    newSelection.reserve(selection.size());
    }

    // Setup new strings
    wxArrayString newStrings;
    newStrings.reserve(strings.size());
    std::list<std::string> newStringsToAtmos;

    int position = strings.size() - 1;
    auto loop = strings.rbegin();
    {
    bool isSelected = coreScripts->IsSelected(position);
    while (isSelected && loop != strings.rend())
    {
    newStrings.Insert(*loop, 0);
    newSelection.Add(position);

    --position;
    ++loop;

    isSelected = coreScripts->IsSelected(position);
    }
    }

    {
    while (loop != strings.rend())
    {
    if (coreScripts->IsSelected(position))
    {
    newStrings.Insert(*loop, 1);
    newSelection.Add(position + 1);
    }
    else
    {
    newStrings.Insert(*loop, 0);
    }

    --position;
    ++loop;
    }
    }

    coreScripts->Set(newStrings);
    for (auto &loop : newSelection)
    coreScripts->SetSelection(loop);

    Atmos::ScriptCompiler::ReorganizeCore(std::move(newStringsToAtmos));
    }
    */
}