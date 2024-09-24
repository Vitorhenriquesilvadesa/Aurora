#include "Scanner.h"
#include <format>
#include <Token.h>
#include <unordered_map>
#include "Logging.h"
#include "ScannedData.h"

namespace Aurora
{
    static std::unordered_map<std::string, TokenType> keywords =
    {
        {"for", TokenType::For},
        {"foreach", TokenType::Foreach},
        {"if", TokenType::If},
        {"else", TokenType::Else},
        {"while", TokenType::While},
        {"do", TokenType::Do},
        {"true", TokenType::True},
        {"false", TokenType::False},
        {"null", TokenType::NullValue},
        {"class", TokenType::Class},
        {"actor", TokenType::Actor},
        {"async", TokenType::Async},
        {"parallel", TokenType::Parallel},
        {"struct", TokenType::Struct},
        {"function", TokenType::Function},
        {"method", TokenType::Method},
        {"public", TokenType::Public},
        {"locked", TokenType::Locked},
        {"const", TokenType::Const},
        {"mutable", TokenType::Mutable},
        {"import", TokenType::Import},
        {"macro", TokenType::Macro},
        {"summary", TokenType::Summary},
        {"lock", TokenType::Lock},
        {"define", TokenType::Define},
        {"float", TokenType::Float},
    };

    Scanner::Scanner()
    : m_Start(0), m_Current(0), m_Line(0), m_Column(0), m_HasError(false)
    {
        m_Spec = {.LogLexingPass = Disabled};
    }

    Scanner::Scanner(const ScanSpecification& specification)
    : m_Start(0), m_Current(0), m_Line(0), m_Column(0), m_HasError(false)
    {
        m_Spec = specification;
    }

    ScannedData Scanner::Scan(const std::string& source)
    {
        m_Start = 0;
        m_Current = 0;
        m_Line = 1;
        m_Column = 1;
        m_Source = source;
        m_Tokens = std::vector<Token>();
        m_ErrorStack = std::vector<std::string>();
        m_HasError = false;

        SCAN_LOG_INFO("Scanning now.");

        while (!IsAtEnd())
        {
            ScanToken();
            m_Start = m_Current;
        }

        MakeToken(TokenType::EndOfFile);

        ScannedData data = ScannedData(m_Tokens);

        for (const auto& token : data.Data)
        {
            SCAN_LOG_INFO("Token[type: {}, lexeme: {}, literal: {}]", TokenTypeToString(token.type), token.lexeme,
                          token.literal);
        }

        return data;
    }

    void Scanner::ScanToken()
    {
        char c = Advance();

        switch (c)
        {
        case ',':
            MakeToken(TokenType::Comma);
            break;

        case '!':
            MakeToken(TokenType::Mark);
            break;

        case ';':
            MakeToken(TokenType::Semicolon);
            break;

        case '(':
            MakeToken(TokenType::LeftParen);
            break;
        case ')':
            MakeToken(TokenType::RightParen);
            break;

        case '[':
            MakeToken(TokenType::LeftBracket);
            break;

        case ']':
            MakeToken(TokenType::RightBracket);
            break;

        case '{':
            MakeToken(TokenType::LeftBrace);
            break;

        case '}':
            MakeToken(TokenType::RightBrace);
            break;

        case '>':
            MakeToken(Match('=') ? TokenType::GreaterEqual : TokenType::Greater);
            break;

        case '<':
            MakeToken(Match('=') ? TokenType::LessEqual : TokenType::Less);
            break;

        case '=':
            if (Match('>'))
            {
                MakeToken(TokenType::Lambda);
                break;
            }
            else if (Match('='))
            {
                MakeToken(TokenType::EqualEqual);
                break;
            }
            else
            {
                MakeToken(TokenType::Equal);
                break;
            }

        case '+':
            MakeToken(Match('+') ? TokenType::PlusPlus : TokenType::Plus);
            break;

        case '-':
            MakeToken(Match('-') ? TokenType::MinusMinus : TokenType::Minus);
            break;

        case '*':
            MakeToken(TokenType::Star);
            break;

        case '/':
            MakeToken(TokenType::Slash);
            break;

        case '.':
            MakeToken(TokenType::Dot);
            break;

        case '@':
            MakeToken(TokenType::AtSign);
            break;

        case '|':
            MakeToken(Match('|') ? TokenType::Or : TokenType::Pipe);
            break;

        case '&':
            MakeToken(Match('&') ? TokenType::And : TokenType::BitwiseAnd);
            break;

        case ':':
            MakeToken(TokenType::Colon);
            break;

        case ' ':
        case '\r':
        case '\t':
            break;

        case '\n':
            m_Line++;
            break;

        case '#':
            Comment();
            break;

        default:
            if (c == '"')
            {
                String();
                break;
            }

            if (IsDigit(c))
            {
                Number();
                break;
            }

            if (IsAlpha(c))
            {
                Identifier();
                break;
            }

            MakeToken(TokenType::ErrorToken, std::format("{}", Peek()));
            m_HasError = true;
        }
    }

    void Scanner::Comment()
    {
        while(!Check('\n'))
        {
            Advance();
        }
    }

    void Scanner::SyncCursors()
    {
        m_Start = m_Current;
    }

    void Scanner::MakeToken(TokenType type, const std::string& lexeme, const std::string& literal)
    {
        m_Tokens.emplace_back(m_Line, m_Column, type, lexeme, literal);
        Index delta = m_Current - m_Start;
        m_Column += delta;
    }

    void Scanner::Identifier()
    {
        while (IsAlphaNumeric(Peek()) || Check('_'))
        {
            Advance();
        }

        std::string word = m_Source.substr(m_Start, m_Current - m_Start);

        MakeToken(keywords.contains(word) ? keywords[word] : TokenType::Identifier, word);
    }

    void Scanner::String()
    {
        while (Peek() != '"' && !IsAtEnd())
        {
            if(Peek() == '\n') m_Line++;
            Advance();
        }

        if(IsAtEnd())
        {
            PushError("Unterminated string.");
        }

        Advance();

        std::string value = m_Source.substr(m_Start + 1, m_Current - m_Start - 2);
        MakeToken(TokenType::String, "", value);
    }

    void Scanner::Char()
    {
        char c = Advance();
        Advance();

        MakeToken(TokenType::Char, "", std::format("{}", c));
    }

    void Scanner::Number()
    {
        while(IsDigit(Peek())) Advance();

        if(Check('.') && IsDigit(PeekNext()))
        {
            do
            {
                Advance();
            } while(IsDigit(Peek()));
        }

        std::string number = m_Source.substr(m_Start, m_Current - m_Start);
        MakeToken(TokenType::Decimal, number, number);
    }

    bool Scanner::IsAtEnd() const
    {
        return m_Current >= m_Source.length();
    }

    char Scanner::Advance()
    {
        return m_Source[m_Current++];
    }

    char Scanner::Previous() const
    {
        return m_Source[m_Current - 1];
    }

    void Scanner::HexadecimalNumber()
    {
        while (IsHexDigit(Peek()))
        {
            Advance();
        }

        MakeToken(TokenType::Hexadecimal, "", m_Source.substr(m_Start, m_Current - m_Start));

        if (IsAlphaNumeric(Peek()))
        {
            Advance();
            PushError("Invalid hexadecimal notation, only permits hexadecimal digits. At line {} in column {}.",
                      m_Line,
                      m_Column);
        }
    }

    void Scanner::BinaryNumber()
    {
        while (Peek() == '0' || Peek() == '1')
        {
            Advance();
        }

        MakeToken(TokenType::Binary, "", m_Source.substr(m_Start, m_Current - m_Start));

        if (IsDigit(Peek()))
        {
            Advance();
            PushError("Invalid binary notation, only permits '0' and '1'. At line {} in column {}.", m_Line,
                      m_Column);
        }
    }

    void Scanner::DecimalNumber()
    {
        while (IsDigit(Peek()))
        {
            Advance();
        }

        if (Peek() == '.')
        {
            Advance();
            while (IsDigit(Peek()))
            {
                Advance();
            }
            if (Peek() == '.')
            {
                Advance();
                PushError("Invalid float notation, only one dot in floating point number in line {} in column {}.",
                          m_Line, m_Column);
            }
            MakeToken(TokenType::Float, "", m_Source.substr(m_Start, m_Current - m_Start));
        }
        else
        {
            MakeToken(TokenType::Decimal, "", m_Source.substr(m_Start, m_Current - m_Start));
        }
    }

    bool Scanner::IsHexDigit(char c) const
    {
        return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
    }

    bool Scanner::IsDigit(char c)
    {
        return c >= '0' && c <= '9';
    }

    bool Scanner::IsAlpha(char c)
    {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    bool Scanner::IsAlphaNumeric(char c)
    {
        return IsDigit(c) || IsAlpha(c);
    }

    bool Scanner::Check(char c)
    {
        return Peek() == c;
    }

    char Scanner::Peek() const
    {
        return m_Source[m_Current];
    }

    char Scanner::PeekNext() const
    {
        if (IsAtEnd()) return '\0';
        return m_Source[m_Current + 1];
    }

    bool Scanner::Match(char c)
    {
        if (IsAtEnd()) return false;
        if (m_Source[m_Current] != c) return false;

        m_Current++;
        SyncCursors();
        return true;
    }

    template
    <
        typename
        ...
        Args>

    void Scanner::PushError(const std::string& message, Args&&... args)
    {
        if (m_Spec.PushErrors)
        {
            m_ErrorStack.emplace_back(std::vformat(message, std::make_format_args(std::forward<Args>(args)...)));
            m_HasError = true;
        }
    }
}
