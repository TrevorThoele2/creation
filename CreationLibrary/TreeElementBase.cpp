#include "TreeElementBase.h"

#include "PropertiesTree.h"

namespace Creation::Editing
{
    TreeElementBase::TreeElementBase(wxDataViewItem id, PropertiesTree& tree) :
        tree(&tree), id(id)
    {}

    TreeElementBase::~TreeElementBase()
    {
        if (ID().IsOk())
            tree->Remove(ID());
        id = {};
    }

    void TreeElementBase::ChangeLabel(const String& label)
    {
        const auto id = ID();
        if (id.IsOk())
            tree->SetItemText(id, label);
    }

    void TreeElementBase::ChangeID(wxDataViewItem id)
    {
        this->id = id;
    }
    
    wxDataViewItem TreeElementBase::ID() const
    {
        return id;
    }
}