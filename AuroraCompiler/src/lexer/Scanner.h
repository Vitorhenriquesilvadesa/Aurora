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
    class AUR_API Scanner
    {
    public:
        Scanner();
        explicit Scanner(const ScanSpecification& specification);
        ~Scanner() = default;
        ScannedData Scan(const std::string& source);

        template <typename... Args>
        void PushError(const std::string& message, Args&&... args);
        void ScanToken();
        void SkipWhitespace();
        void SyncCursors();
        void MakeToken(TokenType type, const std::string& lexeme = "", const std::string& literal = "");
        void Identifier();
        void String();
        void Char();
        void Number();
        [[nodiscard]] bool IsAtEnd() const;
        char Advance();
        [[nodiscard]] char Previous() const;
        void HexadecimalNumber();
        void BinaryNumber();
        void DecimalNumber();
        [[nodiscard]] bool IsHexDigit(char c) const;
        bool IsDigit(char c);
        bool IsAlpha(char c);
        bool IsAlphaNumeric(char c);
        bool Check(char c);
        [[nodiscard]] char Peek() const;
        [[nodiscard]] char PeekNext() const;
        bool Match(char c);

        [[nodiscard]] bool HasError() const { return m_HasError; }
        [[nodiscard]] std::vector<std::string> GetErrorStack() const { return m_ErrorStack; }

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
