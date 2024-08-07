#pragma once
#include "AurSyntaxTreeProcessor.h"

namespace Aurora
{
    class HighLevelSyntaxTreeProcessor : public AurSyntaxTreeProcessor
    {
    public:
        void ProcessNode(AurSyntaxTreeNode* node) override;
        void ProcessBinaryExpressionNode(BinaryExpressionNode* node) override;
        void ProcessUnaryExpressionNode(UnaryExpressionNode* node) override;
        void ProcessLiteralExpressionNode(LiteralExpressionNode* node) override;
    };

}
