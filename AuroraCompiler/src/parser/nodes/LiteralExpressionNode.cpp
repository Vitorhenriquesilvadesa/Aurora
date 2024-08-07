#include "LiteralExpressionNode.h"
#include "../processor/AurSyntaxTreeProcessor.h"

namespace Aurora
{
    void LiteralExpressionNode::AcceptProcessor(AurSyntaxTreeProcessor& processor)
    {
        processor.ProcessLiteralExpressionNode(this);
    }

}