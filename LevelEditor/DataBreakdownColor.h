#pragma once

#include "DataBreakdownGeneral.h"
#include <wx/propgrid/advprops.h>

namespace Creation
{
    template<>
    class DataBreakdown<Build::Package<::Atmos::Color>> : public DataBreakdownBase<Build::Package<::Atmos::Color>>
    {
    public:
        typedef typename PackageT::BuildT BuildT;
    private:
        wxColourProperty *colorProperty;

        void OnPropertyGridChanged(wxPropertyGridEvent &e);

        void CreateEditorPropertiesImpl(const ChildReference &afterThis) override final;
        void UpdateEditorPropertiesImpl(DataViewSelection::Group &selected) override final;
        void DestroyEditorPropertiesImpl(bool destroyTreeItem) override final;
        void SetEditableImpl(bool set) override final;
    public:
        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };
}