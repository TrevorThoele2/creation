#pragma once

#include <wx/dataview.h>
#include "String.h"

namespace Creation::Editing
{
    class PropertiesTree;

    class TreeElementBase
    {
    public:
        TreeElementBase(wxDataViewItem id, PropertiesTree& tree);
        TreeElementBase(TreeElementBase&& arg) noexcept = default;
        virtual ~TreeElementBase() = 0;

        TreeElementBase& operator=(TreeElementBase&& arg) noexcept = delete;

        void ChangeLabel(const String& label);
        void ChangeID(wxDataViewItem id);
        
        [[nodiscard]] wxDataViewItem ID() const;
    private:
        PropertiesTree* tree;
        wxDataViewItem id;
    };
}