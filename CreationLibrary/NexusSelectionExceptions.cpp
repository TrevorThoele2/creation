#include "NexusSelectionExceptions.h"

namespace Creation::Editing
{
    ModifyHasNodeInSelectAndDeselect::ModifyHasNodeInSelectAndDeselect() :
        Exception("Called Modify with the same node in select and deselect. This is not allowed.")
    {}
}