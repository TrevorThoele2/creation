
#include "DataBreakdownColor.h"

#include <Atmos/StringUtility.h>

#include <wx/statline.h>
#include <wx/stattext.h>

namespace Creation
{
    void DataBreakdown<Build::Package<::Atmos::Color>>::OnPropertyGridChanged(wxPropertyGridEvent &e)
    {
        if (e.GetProperty() != colorProperty)
        {
            e.Skip();
            return;
        }

        wxColour col;
        col << colorProperty->GetValue();
        PackageT nPackage;
        nPackage.a.value = col.Alpha();
        nPackage.r.value = col.Red();
        nPackage.g.value = col.Green();
        nPackage.b.value = col.Blue();
        ChangePackage<DataBreakdown>(nPackage);

        e.Skip();
    }

    void DataBreakdown<Build::Package<::Atmos::Color>>::CreateEditorPropertiesImpl(const ChildReference &afterThis)
    {
        colorProperty = CreatePropertyEmplace<wxColourProperty>("Value", afterThis);
        colorProperty->Enable(IsEditable());
        colorProperty->SetAttribute("HasAlpha", true);
        PropertyGrid()->Bind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
    }

    void DataBreakdown<Build::Package<::Atmos::Color>>::UpdateEditorPropertiesImpl(DataViewSelection::Group &selected)
    {
        colorProperty->Enable(IsEditable());

        // Set initial value
        {
            auto builtColor(static_cast<DataBreakdown*>(*selected.begin())->Get()->Build());
            wxVariant var;
            var << wxColour(builtColor.red, builtColor.green, builtColor.blue, builtColor.alpha);
            colorProperty->SetValue(var);
        }

        for (auto loop = ++selected.begin(); loop != selected.end(); ++loop)
        {
            auto builtColor(static_cast<DataBreakdown*>(*loop)->Get()->Build());
            wxVariant var;
            var << wxColour(builtColor.red, builtColor.green, builtColor.blue, builtColor.alpha);
            if (var != colorProperty->GetValue())
            {
                colorProperty->SetValueToUnspecified();
                return;
            }
        }
    }

    void DataBreakdown<Build::Package<::Atmos::Color>>::DestroyEditorPropertiesImpl(bool destroyTreeItem)
    {
        DestroyProperty(colorProperty);
        PropertyGrid()->Unbind(wxEVT_PG_CHANGED, &DataBreakdown::OnPropertyGridChanged, this);
    }

    void DataBreakdown<Build::Package<::Atmos::Color>>::SetEditableImpl(bool set)
    {
        if (colorProperty)
            colorProperty->Enable(set);
    }

    DataBreakdown<Build::Package<::Atmos::Color>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent), colorProperty(nullptr)
    {
        SetAddCategory(false);
    }

    DataBreakdown<Build::Package<::Atmos::Color>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        colorProperty(std::move(arg.colorProperty))
    {
        SetAddCategory(false);
    }

    DataBreakdown<Build::Package<::Atmos::Color>>& DataBreakdown<Build::Package<::Atmos::Color>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        colorProperty = std::move(arg.colorProperty);
        return *this;
    }
}