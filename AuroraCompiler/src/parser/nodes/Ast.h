#pragma once
#include <Core.h>

namespace Aurora
{
    class AUR_API AurSyntaxTreeProcessor;
    
    class AUR_API AurSyntaxTreeNode
    {
    public:
        AurSyntaxTreeNode() = default;
        virtual void AcceptNodeProcessor(AurSyntaxTreeProcessor* processor) = 0;
        virtual ~AurSyntaxTreeNode() = default;
    };
}
