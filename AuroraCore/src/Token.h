#pragma once
#include <cstdint>
#include <string>
#include "Core.h"

namespace Aurora
{
#define TOKEN_TYPE_LIST \
X(Bool) X(Byte) X(Decimal) X(Hexadecimal) X(Binary) X(Float) X(String) \
X(Char) X(Nullable) X(NullValue) \
\
X(Class) X(Actor) X(Async) X(Parallel) X(Struct) \
X(Function) X(Method) X(Public) X(Locked) \
X(Const) X(Mutable) X(Import) X(Macro) \
X(Summary) X(Lock) X(If) X(Else) X(For) X(While) \
X(Do) X(Foreach) X(True) X(False) \
\
X(Plus) X(Minus) X(Star) X(Slash) X(Mod) X(PlusPlus) \
X(MinusMinus) X(StarStar) X(SlashSlash) X(Mark) X(MarkEqual) \
X(Less) X(Greater) X(Equal) X(LessEqual) X(GreaterEqual) \
X(EqualEqual) X(QuestionQuestion) X(QuestionEqual) \
X(PlusEqual) X(MinusEqual) X(StarEqual) X(SlashEqual) \
X(ModEqual) X(And) X(Pipe) X(BitwiseAnd) X(BitwiseOr) \
X(BitwiseNot) X(Message) \
\
X(LeftParen) X(RightParen) X(LeftBracket) X(RightBracket) \
X(LeftBrace) X(RightBrace) X(Semicolon) X(Dot) X(Comma) \
X(Colon) X(AtSign) X(Dollar) X(Hash) X(ShiftL) X(ShiftR) \
\
X(Identifier) X(Lambda) X(Comment) X(Newline) X(Whitespace) \
X(BitwiseAndEqual) X(BitwiseOrEqual) X(BitwiseNotEqual) \
X(BitwiseXorEqual) X(BitwiseXor) X(DoubleDot) X(RightShift) \
X(LeftShift) X(ErrorToken) X(Define) X(RightShiftEqual) X(LeftShiftEqual) \
X(Or) X(DubleQuestionEqual) X(Question) X(TripleDot) X(EndOfFile)

    enum class TokenType
    {
#define X(name) name,
        TOKEN_TYPE_LIST
        #undef X
    };

    inline std::string TokenTypeToString(TokenType type)
    {
        switch (type)
        {
#define X(name) case TokenType::name: return #name;
            TOKEN_TYPE_LIST
            #undef X
            default: return "Unknown TokenType";
        }
    }

    class AUR_API Token
    {
    public:
        uint32_t line;
        uint32_t column;
        TokenType type;
        std::string lexeme;
        std::string literal;

        Token(uint32_t line, uint32_t column, TokenType type, std::string lexeme, std::string value);
    };

    inline Token::Token(const uint32_t line, const uint32_t column, const TokenType type, std::string lexeme,
                        std::string value): line(line),
                                            column(column),
                                            type(type),
                                            lexeme(std::move(lexeme)),
                                            literal(std::move(value))
    {
    }
}
