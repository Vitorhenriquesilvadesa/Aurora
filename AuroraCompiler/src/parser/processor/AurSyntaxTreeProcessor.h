#ifndef AUR_SYNTAX_TREE_PROCESSOR_H
#define AUR_SYNTAX_TREE_PROCESSOR_H

#include "../nodes/BinaryExpressionNode.h"
#include "../nodes/LiteralExpressionNode.h"
#include "../nodes/UnaryExpressionNode.h"

namespace Aurora
{
    class AUR_API AurSyntaxTreeProcessor
    {
    public:
        AurSyntaxTreeProcessor() = default;
        virtual void ProcessNode(AurSyntaxTreeNode* node) = 0;
        virtual void ProcessBinaryExpressionNode(BinaryExpressionNode* node) = 0;
        virtual void ProcessUnaryExpressionNode(UnaryExpressionNode* node) = 0;
        virtual void ProcessLiteralExpressionNode(LiteralExpressionNode* node) = 0;
        virtual ~AurSyntaxTreeProcessor();
    };
}

#endif