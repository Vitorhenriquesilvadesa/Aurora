#pragma once
#include <Core.h>
#include "../SpecTypes.h"

#define Index uint32_t

namespace Aurora
{
    struct AUR_API ScanSpecification
    {
        Spec LogLexingPass : DefaultBit(Disabled);
    };
}
