#include "Parser.h"

#include <format>
#include <stdexcept>
#include <iostream>
#include <Token.h>

#include <Object.h>
#include "../nodes/expression/ExpressionNode.h"


#define PARSE_ERROR(token, message) \
    std::cerr << std::format("{} ", TokenTypeToString((token).type)) << message << std::endl; \
    throw std::runtime_error(message)

namespace Aurora
{
    Parser::~Parser() = default;

    ParsedData Parser::ParseScannedData(const ScannedData& scannedData)
    {
        m_Tokens = scannedData.Data;
        m_Current = 0;

        ParsedData parsedData;

        while (!IsAtEnd())
        {
            ExpressionNode* node = Primary();
            parsedData.Nodes.emplace_back(node);
        }

        return parsedData;
    }

    ExpressionNode* Parser::Expression()
    {
        return nullptr;
    }

    ExpressionNode* Parser::Grouping()
    {
        return nullptr;
    }

    ExpressionNode* Parser::Factor()
    {
        return nullptr;
    }

    ExpressionNode* Parser::Term()
    {
        return nullptr;
    }

    ExpressionNode* Parser::Primary()
    {
        if (Match({TokenType::Float, TokenType::Decimal, TokenType::Hexadecimal, TokenType::Binary}))
        {
            AurValue* object = GetObjectFromLiteral(Peek());
            LiteralExpressionNode* expressionNode = new LiteralExpressionNode(object);
            return expressionNode;
        }
    }

    bool Parser::Match(std::vector<TokenType>&& types)
    {
        for (const auto& type : types)
        {
            if (Check(type))
            {
                Advance();
                return true;
            }
        }

        return false;
    }

    bool Parser::Check(TokenType type)
    {
        if (IsAtEnd()) return false;
        return Peek().type == type;
    }

    Token Parser::Advance()
    {
        if (!IsAtEnd()) m_Current++;
        return Previous();
    }

    Token Parser::Previous()
    {
        return m_Tokens[m_Current - 1];
    }

    Token Parser::Consume(TokenType type, const std::string& message)
    {
        if (!Check(type))
        {
            return Advance();
        }

        PARSE_ERROR(Peek(), message);
    }

    bool Parser::IsAtEnd()
    {
        return Peek().type == TokenType::EndOfFile;
    }

    void Parser::Synchronize()
    {
    }

    Token Parser::Peek()
    {
        return m_Tokens[m_Current];
    }

    AurValue* Parser::GetObjectFromLiteral(const Token& literal)
    {
        AurValue* value;

        switch (literal.type)
        {
        case TokenType::Decimal: value = new AurValue{
                .Type = ValueType::Int, .mInt = std::stoi(literal.literal, nullptr, 10)
            };
            break;
        case TokenType::Hexadecimal: value = new AurValue{
                .Type = ValueType::Int, .mInt = std::stoi(literal.literal.substr(2), nullptr, 16)
            };
            break;
        case TokenType::Binary: value = new AurValue{
                .Type = ValueType::Int, .mInt = std::stoi(literal.literal.substr(2), nullptr, 2)
            };
            break;
        case TokenType::Bool: value = new AurValue{
                .Type = ValueType::Bool, .mBool = std::stoi(literal.literal) == 1
            };
            break;
        default:
            PARSE_ERROR(literal, "Cannot make AurValue from this type.");
        }

        return value;
    }
}
