#pragma once

#include "String.h"
#include <wx/propgrid/propgrid.h>

namespace Creation::Editing
{
    String PropertyName(const String& base, wxPGProperty* parentProperty);
}