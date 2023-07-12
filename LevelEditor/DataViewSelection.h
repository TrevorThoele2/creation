#pragma once

#include <unordered_map>
#include <unordered_set>

#include "DataBreakdownCommonKey.h"

#include "Optional.h"

namespace Creation
{
    class DataBreakdownCommon;

    class DataViewSelection
    {
    public:
        typedef std::unordered_set<DataBreakdownCommon*> Group;
        typedef DataBreakdownCommonKey Key;
        typedef DataBreakdownCommonKeyHasher KeyHasher;
        typedef std::unordered_map<Key, Group, KeyHasher> GroupMap;
    private:
        static GroupMap groups;
    private:
        struct PrimaryGroup
        {
            Group anchors;
            GroupMap::iterator focused;
            PrimaryGroup(GroupMap::iterator focused);
        };

        typedef std::unordered_map<Key, PrimaryGroup, KeyHasher> PrimaryGroupMap;
        static PrimaryGroupMap primaryGroups;
    private:
        DataViewSelection() = default;
        DataViewSelection(const DataViewSelection &arg) = delete;
        DataViewSelection& operator=(const DataViewSelection &arg) = delete;
    public:
        static DataViewSelection& Instance();

        static void SelectPrimary(DataBreakdownCommon &select);
        static void SelectSecondary(DataBreakdownCommon &select);
        static void Deselect(DataBreakdownCommon &deselect);
        static void Clear();

        static Group* GetGroup(DataBreakdownCommon &get);
        static Group* GetPrimaryGroup(DataBreakdownCommon &get);
        static Group* GetOnlyPrimaryGroup();
        static size_t PrimaryGroupCount();

        // Gets all groups with the type info
        static std::vector<Group*> GetGroups(const std::type_info &ti);

        static bool AnySelected();

        static bool IsSelectedPrimary(const DataBreakdownCommon &check);
        static bool IsSelectedSecondary(const DataBreakdownCommon &check);
    };
}