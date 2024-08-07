#include "UnaryExpressionNode.h"
#include "../processor/AurSyntaxTreeProcessor.h"

namespace Aurora
{
    void UnaryExpressionNode::AcceptProcessor(AurSyntaxTreeProcessor& processor)
    {
        processor.ProcessUnaryExpressionNode(this);
    }
}