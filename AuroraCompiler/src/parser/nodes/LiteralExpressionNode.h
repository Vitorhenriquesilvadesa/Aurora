#pragma once
#include "Ast.h"

namespace Aurora
{
    class AurSyntaxTreeProcessor;
    
    class AUR_API LiteralExpressionNode : public AurSyntaxTreeNode
    {
    public:
        
        void AcceptProcessor(AurSyntaxTreeProcessor& processor) override;
    };

}
