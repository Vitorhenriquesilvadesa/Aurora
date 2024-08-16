#pragma once
#include <memory>
#include <vector>

#include "../../lexer/ScannedData.h"
#include <Token.h>
#include "../nodes/expression/ExpressionNode.h"
#include "../../SpecTypes.h"

namespace Aurora
{
    struct AUR_API ParsedData
    {
        std::vector<std::shared_ptr<AurSyntaxTreeNode>> Nodes;
    };

    class AUR_API Parser
    {
    public:
        Parser() : m_Current(0) {}
        ~Parser();
        ParsedData ParseScannedData(const ScannedData& scannedData);

    private:
        ExpressionNode* Expression();
        ExpressionNode* Grouping();
        ExpressionNode* Factor();
        ExpressionNode* Term();
        ExpressionNode* Primary();
        bool Match(std::vector<TokenType>&& types);
        bool Check(TokenType type);
        Token Advance();
        Token Previous();
        Token Consume(TokenType type,const std::string& message);
        bool IsAtEnd();
        void Synchronize();
        Token Peek();
        static AurValue* GetObjectFromLiteral(const Token& literal);

        std::vector<Token> m_Tokens;
        Index m_Current;
    };
}
