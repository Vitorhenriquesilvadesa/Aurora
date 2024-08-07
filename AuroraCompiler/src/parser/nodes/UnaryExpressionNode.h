#pragma once
#include "Ast.h"

namespace Aurora
{
    class AUR_API UnaryExpressionNode : public AurSyntaxTreeNode
    {
    public:
        void AcceptProcessor(AurSyntaxTreeProcessor& processor) override;
    };
}
