#pragma once
#include <string>
#include <vector>
#include <Token.h>

#include "ScannedData.h"
#include "ScanSpecification.h"

#define SCAN_LOG_INFO(message, ...) \
    do { \
        if(m_Spec.LogLexingPass) { \
        std::cout << std::vformat((message), std::make_format_args(__VA_ARGS__)) << '\n'; \
    } \
} while(false)

namespace Aurora
{
    enum class NumberNotation
    {
        Decimal, Hexadecimal, Binary, IEEE
    };
    
    class AUR_API Scanner
    {
    public:
        Scanner();
        explicit Scanner(const ScanSpecification& specification);
        ~Scanner();
        ScannedData Scan(const std::string& source);

        template<typename... Args>
        void PushError(const std::string& message, Args&&... args);
        void ScanToken();
        void SkipWhitespace();
        void SyncCursors();
        void MakeToken(TokenType type, const std::string& lexeme = "", const std::string& literal = "");
        void Identifier();
        void String();
        void Number();
        bool IsAtEnd() const;
        void Advance();
        char Previous() const;
        void HexadecimalNumber();
        void BinaryNumber();
        void DecimalNumber();
        void IEEEScientificNotationNumber();
        bool IsHexDigit(char c) const;
        bool IsDigit(char c);
        bool IsAlpha(char c);
        bool IsAlphaNumeric(char c);
        bool Check(char c);
        char Peek() const;
        bool Match(char c);

        bool HasError() const { return m_HasError; }
        std::vector<std::string> GetErrorStack() const { return m_ErrorStack; }

    private:
        ScanSpecification m_Spec;
        Index m_Start;
        Index m_Current;
        Index m_Line;
        Index m_Column;
        std::string m_Source;
        std::vector<Token> m_Tokens;
        std::vector<std::string> m_ErrorStack;
        bool m_HasError;
    };
}
