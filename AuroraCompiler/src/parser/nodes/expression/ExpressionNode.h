#pragma once
#include "Object.h"
#include "../Ast.h"

namespace Aurora
{
    class AUR_API ExpressionNode : public AurSyntaxTreeNode
    {
    public:
        void AcceptNodeProcessor(AurSyntaxTreeProcessor* processor) override = 0;
    };

    class AUR_API LiteralExpressionNode : public ExpressionNode
    {
    public:
        ~LiteralExpressionNode() override = default;
        explicit LiteralExpressionNode(AurValue* object);
        void AcceptNodeProcessor(AurSyntaxTreeProcessor* processor) override;

        AurValue* m_Literal;
    };
}
