
#include "DataBreakdownGeneral.h"

#include "Optional.h"
#include <wx/propgrid/propgrid.h>

namespace Creation
{
    void DataBreakdown<Build::Package<bool>>::OnPropertyGridChanged(wxPropertyGridEvent &e)
    {
        if (e.GetProperty() != checkbox)
        {
            e.Skip();
            return;
        }

        PackageT nPackage;
        nPackage.value = checkbox->GetValue();
        ChangePackage<DataBreakdown>(nPackage);

        e.Skip();
    }

    void DataBreakdown<Build::Package<bool>>::CreateEditorPropertiesImpl(const ChildReference &afterThis)
    {
        checkbox = CreatePropertyEmplace<wxBoolProperty>("Checkbox", afterThis);
        checkbox->Enable(IsEditable());
        checkbox->SetAttribute("UseCheckbox", 1);
        PropertyGrid()->Bind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
    }

    void DataBreakdown<Build::Package<bool>>::UpdateEditorPropertiesImpl(DataViewSelection::Group &selected)
    {
        checkbox->Enable(IsEditable());

        checkbox->SetValue(static_cast<DataBreakdown*>(*selected.begin())->Get()->value);
        for (auto loop = ++selected.begin(); loop != selected.end(); ++loop)
        {
            if (static_cast<DataBreakdown*>(*loop)->Get()->value != checkbox->GetValue().GetBool())
            {
                checkbox->SetValueToUnspecified();
                return;
            }
        }
    }

    void DataBreakdown<Build::Package<bool>>::DestroyEditorPropertiesImpl(bool destroyTreeItem)
    {
        DestroyProperty(checkbox);
        PropertyGrid()->Unbind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
    }

    void DataBreakdown<Build::Package<bool>>::SetEditableImpl(bool set)
    {
        if (checkbox)
            checkbox->Enable(set);
    }

    DataBreakdown<Build::Package<bool>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent), checkbox(nullptr)
    {
        SetAddCategory(false);
    }

    DataBreakdown<Build::Package<bool>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent), checkbox(std::move(arg.checkbox))
    {
        SetAddCategory(false);
    }

    DataBreakdown<Build::Package<bool>>& DataBreakdown<Build::Package<bool>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        checkbox = std::move(arg.checkbox);
        return *this;
    }

    DataBreakdown<Build::Package<std::uint8_t>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownInteger(name, parent)
    {}

    DataBreakdown<Build::Package<std::uint8_t>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownInteger(std::move(arg), parent)
    {}

    DataBreakdown<Build::Package<std::uint8_t>>& DataBreakdown<Build::Package<std::uint8_t>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownInteger::operator=(std::move(arg));
        return *this;
    }

    DataBreakdown<Build::Package<std::uint16_t>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownInteger(name, parent)
    {}

    DataBreakdown<Build::Package<std::uint16_t>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownInteger(std::move(arg), parent)
    {}

    DataBreakdown<Build::Package<std::uint16_t>>& DataBreakdown<Build::Package<std::uint16_t>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownInteger::operator=(std::move(arg));
        return *this;
    }

    DataBreakdown<Build::Package<std::uint32_t>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownInteger(name, parent)
    {}

    DataBreakdown<Build::Package<std::uint32_t>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownInteger(std::move(arg), parent)
    {}

    DataBreakdown<Build::Package<std::uint32_t>>& DataBreakdown<Build::Package<std::uint32_t>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownInteger::operator=(std::move(arg));
        return *this;
    }

    DataBreakdown<Build::Package<std::uint64_t>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownInteger(name, parent)
    {}

    DataBreakdown<Build::Package<std::uint64_t>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownInteger(std::move(arg), parent)
    {}

    DataBreakdown<Build::Package<std::uint64_t>>& DataBreakdown<Build::Package<std::uint64_t>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownInteger::operator=(std::move(arg));
        return *this;
    }

    DataBreakdown<Build::Package<std::int8_t>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownInteger(name, parent)
    {}

    DataBreakdown<Build::Package<std::int8_t>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownInteger(std::move(arg), parent)
    {}

    DataBreakdown<Build::Package<std::int8_t>>& DataBreakdown<Build::Package<std::int8_t>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownInteger::operator=(std::move(arg));
        return *this;
    }

    DataBreakdown<Build::Package<std::int16_t>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownInteger(name, parent)
    {}

    DataBreakdown<Build::Package<std::int16_t>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownInteger(std::move(arg), parent)
    {}

    DataBreakdown<Build::Package<std::int16_t>>& DataBreakdown<Build::Package<std::int16_t>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownInteger::operator=(std::move(arg));
        return *this;
    }

    DataBreakdown<Build::Package<std::int32_t>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownInteger(name, parent)
    {}

    DataBreakdown<Build::Package<std::int32_t>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownInteger(std::move(arg), parent)
    {}

    DataBreakdown<Build::Package<std::int32_t>>& DataBreakdown<Build::Package<std::int32_t>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownInteger::operator=(std::move(arg));
        return *this;
    }

    DataBreakdown<Build::Package<std::int64_t>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownInteger(name, parent)
    {}

    DataBreakdown<Build::Package<std::int64_t>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownInteger(std::move(arg), parent)
    {}

    DataBreakdown<Build::Package<std::int64_t>>& DataBreakdown<Build::Package<std::int64_t>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownInteger::operator=(std::move(arg));
        return *this;
    }

    DataBreakdown<Build::Package<float>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownFloatingPoint(name, parent)
    {}

    DataBreakdown<Build::Package<float>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownFloatingPoint(std::move(arg), parent)
    {}

    DataBreakdown<Build::Package<float>>& DataBreakdown<Build::Package<float>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownFloatingPoint::operator=(std::move(arg));
        return *this;
    }

    DataBreakdown<Build::Package<double>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownFloatingPoint(name, parent)
    {}

    DataBreakdown<Build::Package<double>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownFloatingPoint(std::move(arg), parent)
    {}

    DataBreakdown<Build::Package<double>>& DataBreakdown<Build::Package<double>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownFloatingPoint::operator=(std::move(arg));
        return *this;
    }

    void DataBreakdown<Build::Package<String>>::OnPropertyGridChanged(wxPropertyGridEvent &e)
    {
        if (e.GetProperty() != textProp && e.GetProperty() != choiceProp)
        {
            e.Skip();
            return;
        }

        PackageT nPackage;
        if (UsesTextbox())
            nPackage.value = textProp->GetValue().GetString();
        else // CHOICE
            nPackage.value = choiceProp->GetValueAsString();

        ChangePackage<DataBreakdown>(nPackage);

        e.Skip();
    }

    void DataBreakdown<Build::Package<String>>::SetGroupImpl(bool previouslyUsingTextbox)
    {
        // If previously using textbox, just update the properties and leave
        if (previouslyUsingTextbox == UsesTextbox())
        {
            UpdateEditorProperties();
            return;
        }

        // Otherwise reinsert the editor properties if we're attached
        if (IsAttached())
        {
            DestroyEditorProperties();
            GetParent()->ReinsertEditorProperties(*this);
        }
    }

    bool DataBreakdown<Build::Package<String>>::UsesTextbox() const
    {
        return group.empty();
    }

    void DataBreakdown<Build::Package<String>>::CreateEditorPropertiesImpl(const ChildReference &afterThis)
    {
        if (UsesTextbox())
        {
            textProp = CreatePropertyEmplace<wxStringProperty>("Value", afterThis);
            textProp->Enable(IsEditable());
        }
        else // CHOICE
        {
            wxPGChoices choices;
            for (auto &loop : group)
                choices.Add(loop);
            choiceProp = CreatePropertyEmplace<wxEnumProperty>("Value", afterThis, choices);
            choiceProp->Enable(IsEditable());
        }

        PropertyGrid()->Bind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
    }

    void DataBreakdown<Build::Package<String>>::UpdateEditorPropertiesImpl(DataViewSelection::Group &selected)
    {
        if (UsesTextbox())
        {
            textProp->Enable(IsEditable());

            textProp->SetValue(static_cast<DataBreakdown*>(*selected.begin())->Get()->value);
            for (auto loop = ++selected.begin(); loop != selected.end(); ++loop)
            {
                if (static_cast<DataBreakdown*>(*loop)->Get()->value != textProp->GetValue().GetString())
                {
                    textProp->SetValue("");
                    return;
                }
            }
        }
        else // CHOICE
        {
            // Reset the choices
            wxPGChoices choices;
            for (auto &loop : group)
                choices.Add(loop);
            choiceProp->SetChoices(choices);

            choiceProp->Enable(IsEditable());

            choiceProp->SetValue(static_cast<DataBreakdown*>(*selected.begin())->Get()->value);
            for (auto loop = ++selected.begin(); loop != selected.end(); ++loop)
            {
                if (static_cast<DataBreakdown*>(*loop)->Get()->value != choiceProp->GetValue().GetString())
                {
                    choiceProp->SetValue("");
                    return;
                }
            }
        }
    }

    void DataBreakdown<Build::Package<String>>::DestroyEditorPropertiesImpl(bool destroyTreeItem)
    {
        DestroyProperty(textProp);
        DestroyProperty(choiceProp);
        PropertyGrid()->Unbind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
    }

    void DataBreakdown<Build::Package<String>>::SetEditableImpl(bool set)
    {
        if (textProp)
            textProp->Enable(set);
        else if (choiceProp)
            choiceProp->Enable(set);
    }

    DataBreakdown<Build::Package<String>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent), textProp(nullptr), choiceProp(nullptr)
    {
        SetAddCategory(false);
    }

    DataBreakdown<Build::Package<String>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent), textProp(std::move(arg.textProp)), choiceProp(std::move(arg.choiceProp)), group(std::move(arg.group))
    {}

    DataBreakdown<Build::Package<String>>& DataBreakdown<Build::Package<String>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        textProp = std::move(arg.textProp);
        choiceProp = std::move(arg.choiceProp);
        group = std::move(arg.group);
        return *this;
    }

    void DataBreakdown<Build::Package<String>>::SetGroup(const StringGroup &set)
    {
        bool prev = UsesTextbox();
        group = set;
        SetGroupImpl(prev);
    }

    void DataBreakdown<Build::Package<String>>::SetGroup(StringGroup &&set)
    {
        bool prev = UsesTextbox();
        group = std::move(set);
        SetGroupImpl(prev);
    }

    const StringGroup& DataBreakdown<Build::Package<String>>::GetGroup() const
    {
        return group;
    }

    DataBreakdown<Build::Package<String>>::GroupID DataBreakdown<Build::Package<String>>::AddToGroup(const BuildT &add)
    {
        bool prev = UsesTextbox();
        group.push_back(add);
        if (prev != UsesTextbox() && IsAttached())
        {
            DestroyEditorProperties();
            GetParent()->ReinsertEditorProperties(*this);
        }

        return group.size() - 1;
    }

    DataBreakdown<Build::Package<String>>::GroupID DataBreakdown<Build::Package<String>>::AddToGroup(BuildT &&add)
    {
        bool prev = UsesTextbox();
        group.push_back(std::move(add));
        if (prev != UsesTextbox() && IsAttached())
        {
            DestroyEditorProperties();
            GetParent()->ReinsertEditorProperties(*this);
        }

        return group.size() - 1;
    }

    void DataBreakdown<Build::Package<String>>::RemoveFromGroup(const BuildT &add)
    {
        bool prev = UsesTextbox();

        for (auto loop = group.begin(); loop != group.end(); ++loop)
        {
            if (*loop == add)
                loop = group.erase(loop);
        }

        if (prev != UsesTextbox() && IsAttached())
        {
            DestroyEditorProperties();
            GetParent()->ReinsertEditorProperties(*this);
        }
    }

    void DataBreakdown<Build::Package<String>>::RemoveFromGroup(GroupID id)
    {
        bool prev = UsesTextbox();
        group.erase(group.begin() + id);
        if (prev != UsesTextbox() && IsAttached())
        {
            DestroyEditorProperties();
            GetParent()->ReinsertEditorProperties(*this);
        }
    }

    void DataBreakdown<Build::Package<::Atmos::FilePath>>::OnPropertyGridChanged(wxPropertyGridEvent &e)
    {
        if (e.GetProperty() != prop)
        {
            e.Skip();
            return;
        }

        PackageT nPackage;
        nPackage.value = prop->GetValue().GetString().ToStdString();
        ChangePackage<DataBreakdown>(nPackage);

        e.Skip();
    }

    void DataBreakdown<Build::Package<::Atmos::FilePath>>::CreateEditorPropertiesImpl(const ChildReference &afterThis)
    {
        prop = CreatePropertyEmplace<wxFileProperty>("Value", afterThis);
        prop->Enable(IsEditable());
        prop->SetAttribute("InitialPath", defaultFilePath.GetValue());
        prop->SetAttribute("Wildcard", wildcard);
        PropertyGrid()->Bind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
    }

    void DataBreakdown<Build::Package<::Atmos::FilePath>>::UpdateEditorPropertiesImpl(DataViewSelection::Group &selected)
    {
        prop->Enable(IsEditable());

        prop->SetValue(static_cast<DataBreakdown*>(*selected.begin())->Get()->value.GetValue());
        for (auto loop = ++selected.begin(); loop != selected.end(); ++loop)
        {
            if (static_cast<DataBreakdown*>(*loop)->Get()->value != prop->GetValue().GetString())
            {
                prop->SetValueToUnspecified();
                return;
            }
        }
    }

    void DataBreakdown<Build::Package<::Atmos::FilePath>>::DestroyEditorPropertiesImpl(bool destroyTreeItem)
    {
        DestroyProperty(prop);
        PropertyGrid()->Unbind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
    }

    void DataBreakdown<Build::Package<::Atmos::FilePath>>::SetEditableImpl(bool set)
    {
        if (prop)
            prop->Enable(set);
    }

    DataBreakdown<Build::Package<::Atmos::FilePath>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent), prop(nullptr)
    {
        SetAddCategory(false);
    }

    DataBreakdown<Build::Package<::Atmos::FilePath>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent), prop(std::move(arg.prop)), defaultFilePath(std::move(arg.defaultFilePath)), wildcard(std::move(arg.wildcard))
    {}

    DataBreakdown<Build::Package<::Atmos::FilePath>>& DataBreakdown<Build::Package<::Atmos::FilePath>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        prop = std::move(arg.prop);
        defaultFilePath = std::move(arg.defaultFilePath);
        wildcard = std::move(arg.wildcard);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::FilePath>>::SetDefaultFilePath(const ::Atmos::FilePath &set)
    {
        defaultFilePath = set;
    }

    const ::Atmos::FilePath& DataBreakdown<Build::Package<::Atmos::FilePath>>::GetDefaultFilePath() const
    {
        return defaultFilePath;
    }

    void DataBreakdown<Build::Package<::Atmos::FilePath>>::SetWildcard(const String &set)
    {
        wildcard = set;
    }

    const String& DataBreakdown<Build::Package<::Atmos::FilePath>>::GetWildcard() const
    {
        return wildcard;
    }

    void DataBreakdown<Build::Package<::Atmos::FileName>>::OnPropertyGridChanged(wxPropertyGridEvent &e)
    {
        if (e.GetProperty() != prop)
        {
            e.Skip();
            return;
        }

        PackageT nPackage;
        nPackage.value = prop->GetValue().GetString().ToStdString();
        ChangePackage<DataBreakdown>(nPackage);

        e.Skip();
    }

    void DataBreakdown<Build::Package<::Atmos::FileName>>::CreateEditorPropertiesImpl(const ChildReference &afterThis)
    {
        prop = CreatePropertyEmplace<wxStringProperty>("Value", afterThis);
        prop->Enable(IsEditable());
        PropertyGrid()->Bind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
    }

    void DataBreakdown<Build::Package<::Atmos::FileName>>::UpdateEditorPropertiesImpl(DataViewSelection::Group &selected)
    {
        prop->Enable(IsEditable());

        prop->SetValue(static_cast<DataBreakdown*>(*selected.begin())->Get()->value.GetValue());
        for (auto loop = ++selected.begin(); loop != selected.end(); ++loop)
        {
            if (static_cast<DataBreakdown*>(*loop)->Get()->value != prop->GetValue().GetString())
            {
                prop->SetValue("");
                return;
            }
        }
    }

    void DataBreakdown<Build::Package<::Atmos::FileName>>::DestroyEditorPropertiesImpl(bool destroyTreeItem)
    {
        DestroyProperty(prop);
        PropertyGrid()->Unbind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
    }

    void DataBreakdown<Build::Package<::Atmos::FileName>>::SetEditableImpl(bool set)
    {
        if (prop)
            prop->Enable(set);
    }

    DataBreakdown<Build::Package<::Atmos::FileName>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent), prop(nullptr)
    {
        SetAddCategory(false);
    }

    DataBreakdown<Build::Package<::Atmos::FileName>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent), prop(std::move(arg.prop))
    {}

    DataBreakdown<Build::Package<::Atmos::FileName>>& DataBreakdown<Build::Package<::Atmos::FileName>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        prop = std::move(arg.prop);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Percentage>>::AddAllChildren()
    {
        AddChild(value);
    }

    void DataBreakdown<Build::Package<::Atmos::Percentage>>::SetupImpl()
    {
        value.Setup(Get()->value);
    }

    DataBreakdown<Build::Package<::Atmos::Percentage>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        value(name, this)
    {
        SetAddCategory(false);
        SetAddTreePiece(false);
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Percentage>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        value(std::move(arg.value))
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Percentage>>& DataBreakdown<Build::Package<::Atmos::Percentage>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        value = std::move(arg.value);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Angle>>::AddAllChildren()
    {
        AddChild(value);
    }

    void DataBreakdown<Build::Package<::Atmos::Angle>>::SetupImpl()
    {
        value.Setup(Get()->value);
    }

    DataBreakdown<Build::Package<::Atmos::Angle>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        value(name, this)
    {
        SetAddCategory(false);
        SetAddTreePiece(false);
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Angle>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        value(std::move(arg.value), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Angle>>& DataBreakdown<Build::Package<::Atmos::Angle>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        value = std::move(arg.value);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Position3D>>::AddAllChildren()
    {
        AddChild(x);
        AddChild(y);
        AddChild(z);
    }

    void DataBreakdown<Build::Package<::Atmos::Position3D>>::SetupImpl()
    {
        x.Setup(Get()->x);
        y.Setup(Get()->y);
        z.Setup(Get()->z);
    }

    DataBreakdown<Build::Package<::Atmos::Position3D>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        x("X", this),
        y("Y", this),
        z("Z", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Position3D>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        x(std::move(arg.x)),
        y(std::move(arg.y)),
        z(std::move(arg.z))
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Position3D>>& DataBreakdown<Build::Package<::Atmos::Position3D>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        x = std::move(arg.x);
        y = std::move(arg.y);
        z = std::move(arg.z);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::GridPosition>>::AddAllChildren()
    {
        AddChild(x);
        AddChild(y);
        AddChild(z);
    }

    void DataBreakdown<Build::Package<::Atmos::GridPosition>>::SetupImpl()
    {
        x.Setup(Get()->x);
        y.Setup(Get()->y);
        z.Setup(Get()->z);
    }

    DataBreakdown<Build::Package<::Atmos::GridPosition>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        x("X", this),
        y("Y", this),
        z("Z", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::GridPosition>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        x(std::move(arg.x), this),
        y(std::move(arg.y), this),
        z(std::move(arg.z), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::GridPosition>>& DataBreakdown<Build::Package<::Atmos::GridPosition>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        x = std::move(arg.x);
        y = std::move(arg.y);
        z = std::move(arg.z);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::RelativeGridPosition>>::AddAllChildren()
    {
        AddChild(x);
        AddChild(y);
        AddChild(z);
    }

    void DataBreakdown<Build::Package<::Atmos::RelativeGridPosition>>::SetupImpl()
    {
        x.Setup(Get()->x);
        y.Setup(Get()->y);
        z.Setup(Get()->z);
    }

    DataBreakdown<Build::Package<::Atmos::RelativeGridPosition>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        x("X", this),
        y("Y", this),
        z("Z", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::RelativeGridPosition>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        x(std::move(arg.x), this),
        y(std::move(arg.y), this),
        z(std::move(arg.z), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::RelativeGridPosition>>& DataBreakdown<Build::Package<::Atmos::RelativeGridPosition>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        x = std::move(arg.x);
        y = std::move(arg.y);
        z = std::move(arg.z);
        return *this;
    }
}