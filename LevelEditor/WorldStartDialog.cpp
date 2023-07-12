
#include "WorldStartDialog.h"
#include <Atmos/StringUtility.h>
#include <wx/textctrl.h>
#include <wx/valnum.h>

#include "DataBreakdownAssets.h"
#include "DataBreakdownEntities.h"
#include "DataBreakdownGameData.h"
#include "DataBreakdownRegistries.h"
#include "DataBreakdownTiles.h"

namespace Creation
{
    WorldStartDialog::WorldStartDialog(::Atmos::FieldID fieldID, wxWindow *parent, wxWindowID windowID) : wxDialog(parent, windowID, "World Start")
    {
        wxIntegerValidator<::Atmos::FieldID> val;
        fieldText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, val);
    }

    ::Atmos::FieldID WorldStartDialog::GetFieldID() const
    {
        return ::Atmos::FromString<::Atmos::FieldID>(fieldText->GetValue().ToStdString());
    }
}