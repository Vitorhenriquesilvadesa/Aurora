#ifndef AUR_SYNTAX_TREE_PROCESSOR_H
#define AUR_SYNTAX_TREE_PROCESSOR_H

#pragma once

#include "../nodes/expression/ExpressionNode.h"
#include "../nodes/Ast.h"

namespace Aurora
{
    class AUR_API AurSyntaxTreeProcessor
    {
    public:
        virtual void ProcessNode(AurSyntaxTreeNode* node) = 0;
        virtual void ProcessLiteralExpressionNode(LiteralExpressionNode* node) = 0;
        virtual ~AurSyntaxTreeProcessor() = default;
    };
}

#endif