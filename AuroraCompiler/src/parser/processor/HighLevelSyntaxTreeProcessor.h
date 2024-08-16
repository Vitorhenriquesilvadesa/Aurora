#pragma once
#include "AurSyntaxTreeProcessor.h"

namespace Aurora
{
    class HighLevelSyntaxTreeProcessor : public AurSyntaxTreeProcessor
    {
    public:
        void ProcessNode(AurSyntaxTreeNode* node) override;
        void ProcessLiteralExpressionNode(LiteralExpressionNode* node) override;
    };

}
