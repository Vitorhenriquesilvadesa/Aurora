#include "BinaryExpressionNode.h"
#include "../processor/AurSyntaxTreeProcessor.h"

namespace Aurora
{
    void BinaryExpressionNode::AcceptProcessor(AurSyntaxTreeProcessor& processor)
    {
        processor.ProcessBinaryExpressionNode(this);
    }
}
