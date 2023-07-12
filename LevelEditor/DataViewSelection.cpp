
#include "DataViewSelection.h"
#include "DataBreakdownCommon.h"

namespace Creation
{
    DataViewSelection::GroupMap DataViewSelection::groups;
    DataViewSelection::PrimaryGroupMap DataViewSelection::primaryGroups;

    DataViewSelection::PrimaryGroup::PrimaryGroup(GroupMap::iterator focused) : focused(focused)
    {}

    DataViewSelection& DataViewSelection::Instance()
    {
        static DataViewSelection instance;
        return instance;
    }

    void DataViewSelection::SelectPrimary(DataBreakdownCommon &select)
    {
        Deselect(select);

        Key key(select);
        auto emplaced = Instance().primaryGroups.emplace(key, PrimaryGroup(groups.emplace(key, Group()).first)).first;
        emplaced->second.anchors.emplace(&select);
        emplaced->second.focused->second.emplace(&select);
    }

    void DataViewSelection::SelectSecondary(DataBreakdownCommon &select)
    {
        Deselect(select);

        groups.emplace(Key(select), Group()).first->second.emplace(&select);
    }

    void DataViewSelection::Deselect(DataBreakdownCommon &deselect)
    {
        Key key(deselect);
        auto groupFound = groups.find(key);
        if (groupFound == groups.end())
            return;

        groupFound->second.erase(&deselect);

        // Eliminate from the primary group
        {
            auto primaryGroupFound = primaryGroups.find(key);
            if (primaryGroupFound != primaryGroups.end())
            {
                primaryGroupFound->second.anchors.erase(&deselect);
                if (primaryGroupFound->second.anchors.empty())
                    primaryGroups.erase(primaryGroupFound);
            }
        }

        if (groupFound->second.empty())
            groups.erase(groupFound);
    }

    void DataViewSelection::Clear()
    {
        groups.clear();
        primaryGroups.clear();
    }

    DataViewSelection::Group* DataViewSelection::GetGroup(DataBreakdownCommon &get)
    {
        auto found = groups.find(Key(get));
        if (found == groups.end())
            return nullptr;

        return &found->second;
    }

    DataViewSelection::Group* DataViewSelection::GetPrimaryGroup(DataBreakdownCommon &get)
    {
        auto group = primaryGroups.find(Key(get));
        if (group == primaryGroups.end())
            return nullptr;

        return &group->second.focused->second;
    }

    DataViewSelection::Group* DataViewSelection::GetOnlyPrimaryGroup()
    {
        if (primaryGroups.empty() || primaryGroups.size() != 1)
            return nullptr;

        return &primaryGroups.begin()->second.focused->second;
    }

    size_t DataViewSelection::PrimaryGroupCount()
    {
        return primaryGroups.size();
    }

    std::vector<DataViewSelection::Group*> DataViewSelection::GetGroups(const std::type_info &ti)
    {
        typedef std::vector<DataViewSelection::Group*> RetT;
        RetT ret;
        for (auto &loop : groups)
            if (loop.first.ti == ti)
                ret.push_back(&loop.second);
        int myInt = 1 + 1;
        return ret;
    }

    bool DataViewSelection::AnySelected()
    {
        return !groups.empty();
    }

    bool DataViewSelection::IsSelectedPrimary(const DataBreakdownCommon &check)
    {
        DataBreakdownCommon &casted = const_cast<DataBreakdownCommon&>(check);
        auto group = GetPrimaryGroup(casted);
        if (!group)
            return false;

        return group->find(&casted) != group->end();
    }

    bool DataViewSelection::IsSelectedSecondary(const DataBreakdownCommon &check)
    {
        DataBreakdownCommon &casted = const_cast<DataBreakdownCommon&>(check);
        auto group = GetGroup(casted);
        if (!group)
            return false;

        return group->find(&casted) != group->end();
    }
}