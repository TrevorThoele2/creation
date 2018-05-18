#include "PropertyName.h"

namespace Creation::Editing
{
    String PropertyName(const String& base, wxPGProperty* parentProperty)
    {
        auto returnValue = base;

        auto focusedParent = parentProperty;
        while (focusedParent)
        {
            returnValue = focusedParent->GetBaseName() + "." + returnValue;
            focusedParent = focusedParent->GetParent();
        }

        return returnValue;
    }
}