
#include "CCPOperation.h"

namespace Creation
{
    CCPOperationBase::CCPOperationBase(IsOverlappingOuterFunc &&isOverlappingOuter) : PreviewOperation(std::move(isOverlappingOuter))
    {}
}