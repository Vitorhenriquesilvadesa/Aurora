#pragma once
#include <Core.h>
#include "SpecTypes.h"

namespace Aurora
{
    struct AUR_API AurCompileSpecification
    {
        Spec LogCompilation               : DefaultBit(Disabled);
        Spec LogLexingPass                : DefaultBit(Enabled);
        Spec LogParsingPass               : DefaultBit(Disabled);
        Spec LogPolimorficPass            : DefaultBit(Disabled);
        Spec LogMultiIDCheckingPass       : DefaultBit(Disabled);
        Spec LogDefaultCompilePass        : DefaultBit(Disabled);
        Spec LogKernelCompilation         : DefaultBit(Disabled);
        Spec LogInterpretation            : DefaultBit(Disabled);
        Spec PermitsPOOInKernels          : DefaultBit(Enabled);
        Spec SecurityMultithreadingTasks  : DefaultBit(Enabled);
        Spec MultithreadingCompilation    : DefaultBit(Disabled);
        Spec PermitsGPUWithCPUIntegration : DefaultBit(Disabled);
        Spec PermitsGPUWithComplexTypes   : DefaultBit(Disabled);
        Spec PermitsGPUWithClasses        : DefaultBit(Disabled);
        Spec CacheCUDAPrograms            : DefaultBit(Enabled);
        Spec CompactBytecodeFile          : DefaultBit(Disabled);
        Spec CompactCUDAPrograms          : DefaultBit(Disabled);
        Spec EnableTypeErasing            : DefaultBit(Enabled);
        Spec ForceOptimization            : DefaultBit(Disabled);
    };
}
