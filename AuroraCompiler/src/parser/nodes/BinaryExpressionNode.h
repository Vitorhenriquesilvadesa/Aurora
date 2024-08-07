#pragma once
#include <memory>

#include "Ast.h"
#include "Token.h"

namespace Aurora
{
    class AUR_API BinaryExpressionNode : public AurSyntaxTreeNode
    {
    public:
        BinaryExpressionNode(const std::shared_ptr<AurSyntaxTreeNode>& left,
                             const std::shared_ptr<AurSyntaxTreeNode>& right, Token operator_)
        : left(left),
          right(right),
          Operator(std::move(operator_))
        {
        }

        void AcceptProcessor(AurSyntaxTreeProcessor& processor) override;

        std::shared_ptr<AurSyntaxTreeNode> left;
        std::shared_ptr<AurSyntaxTreeNode> right;
        Token Operator;
    };
}
