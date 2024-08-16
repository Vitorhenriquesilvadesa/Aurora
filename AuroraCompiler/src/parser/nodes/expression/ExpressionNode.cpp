#include "ExpressionNode.h"

#include "Object.h"
#include "../../processor/AurSyntaxTreeProcessor.h"

namespace Aurora
{
    LiteralExpressionNode::LiteralExpressionNode(AurValue* object)
    {
        m_Literal = object;
    }

    void LiteralExpressionNode::AcceptNodeProcessor(AurSyntaxTreeProcessor* processor)
    {
        processor->ProcessLiteralExpressionNode(this);
    }
}
