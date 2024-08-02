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

    Scanner::~Scanner() = default;

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
        }

        ScannedData data = ScannedData(m_Tokens);
        return data;
    }

    template <typename... Args>
    void Scanner::PushError(const std::string& message, Args&&... args)
    {
        m_ErrorStack.emplace_back(std::vformat(message, std::make_format_args(std::forward<Args>(args)...)));
    }

    void Scanner::ScanToken()
    {
        SkipWhitespace();

        SCAN_LOG_INFO("Before: '{}'", Peek());
        switch (Peek())
        {
        case '+':
            if (Match('+')) MakeToken(TokenType::PlusPlus);
            else if (Match('=')) MakeToken(TokenType::PlusEqual);
            else MakeToken(TokenType::Plus);
            break;
        case '-':
            if (Match('-')) MakeToken(TokenType::MinusMinus);
            else if (Match('=')) MakeToken(TokenType::MinusEqual);
            else MakeToken(TokenType::Minus);
            break;
        case '*':
            if (Match('*')) MakeToken(TokenType::StarStar);
            else if (Match('=')) MakeToken(TokenType::StarEqual);
            else MakeToken(TokenType::Star);
            break;
        case '/':
            if (Match('/')) MakeToken(TokenType::SlashSlash);
            else if (Match('=')) MakeToken(TokenType::SlashEqual);
            else MakeToken(TokenType::Slash);
            break;
        case '=':
            if (Match('=')) MakeToken(TokenType::EqualEqual);
            else MakeToken(TokenType::Equal);
            break;
        case '@':
            MakeToken(TokenType::AtSign);
            break;
        case '!':
            if (Match('=')) MakeToken(TokenType::MarkEqual);
            else MakeToken(TokenType::Mark);
            break;
        case '&':
            if (Match('=')) MakeToken(TokenType::BitwiseAndEqual);
            else if (Match('&')) MakeToken(TokenType::And);
            else MakeToken(TokenType::BitwiseAnd);
            break;
        case '|':
            if (Match('=')) MakeToken(TokenType::BitwiseOrEqual);
            else if (Match('|')) MakeToken(TokenType::Or);
            else MakeToken(TokenType::BitwiseOr);
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
        case '~':
            if (Match('=')) MakeToken(TokenType::BitwiseNotEqual);
            else MakeToken(TokenType::BitwiseNot);
            break;
        case '^':
            if (Match('=')) MakeToken(TokenType::BitwiseXorEqual);
            else MakeToken(TokenType::BitwiseXor);
            break;
        case '.':
            if (Match('.')) MakeToken(TokenType::DoubleDot);
            else MakeToken(TokenType::Dot);
            break;
        case ',':
            MakeToken(TokenType::Comma);
            break;
        case ';':
            MakeToken(TokenType::Semicolon);
            break;
        case ':':
            MakeToken(TokenType::Colon);
            break;
        case '>':
            if (Match('=')) MakeToken(TokenType::GreaterEqual);
            else if (Match('>')) MakeToken(TokenType::RightShift);
            else MakeToken(TokenType::Greater);
            break;
        case '<':
            if (Match('=')) MakeToken(TokenType::LessEqual);
            else if (Match('<')) MakeToken(TokenType::LeftShift);
            else MakeToken(TokenType::Less);
            break;
        case '%':
            if (Match('=')) MakeToken(TokenType::ModEqual);
            else MakeToken(TokenType::Mod);
            break;
        case '$':
            MakeToken(TokenType::Dollar);
            break;
        case '#':
            MakeToken(TokenType::Hash);
            break;
        case '\n':
            SCAN_LOG_INFO("NewLine");
            Advance();
            m_Line++;
            m_Column = 1;
            m_Start = m_Current;
            return;
        case ' ':
        case '\t':
            SkipWhitespace();
            return;
        case '"':
            String();
            break;

        default:
            if (IsDigit(Peek()))
            {
                Number();
                break;
            }
            if (IsAlpha(Peek()))
            {
                Identifier();
                break;
            }

            PushError("Unexpected character at line {} in column {}.", m_Line, m_Column);
            m_HasError = true;
        }
        Advance();
        SCAN_LOG_INFO("After: '{}'", Peek());
    }

    void Scanner::SkipWhitespace()
    {
        while (true)
        {
            switch (Peek())
            {
                case ' ':
                case '\t':
                    Advance();
                    m_Column++;
                    break;
                case '\n':
                    Advance();
                    m_Line++;
                    m_Column = 1;
                    break;
                default:
                    SyncCursors();
                    return;
            }
        }
    }

    void Scanner::SyncCursors()
    {
        m_Start = m_Current;
    }

    void Scanner::MakeToken(TokenType type, const std::string& lexeme, const std::string& literal)
    {
        Token token = Token(m_Line, m_Column, type, lexeme, literal);
        m_Tokens.emplace_back(token);
        Index delta = m_Current - m_Start;
        m_Start = m_Current;
        m_Column += delta;
    }

    void Scanner::Identifier()
    {
        while (IsAlphaNumeric(Peek()))
        {
            Advance();
        }

        std::string lexeme = m_Source.substr(m_Start, m_Current - m_Start);
        MakeToken(keywords.contains(lexeme) ? keywords[lexeme] : TokenType::Identifier, lexeme);
    }

    void Scanner::String()
    {
        Advance();
        while (!Check('"'))
        {
            Advance();
        }

        std::string string = m_Source.substr(m_Start + 1, m_Current - m_Start - 1);
        MakeToken(TokenType::String, "", string);
    }

    void Scanner::Number()
    {
        if (Peek() == '0')
        {
            Advance();
            if (Peek() == 'x' || Peek() == 'X')
            {
                HexadecimalNumber();
            }
            else if (Peek() == 'b' || Peek() == 'B')
            {
                BinaryNumber();
            }
            else
            {
                DecimalNumber();
            }
        }
        else
        {
            DecimalNumber();
        }
    }

    bool Scanner::IsAtEnd() const
    {
        return Peek() == '\0' || m_Current >= m_Source.length();
    }

    void Scanner::Advance()
    {
        m_Current++;
    }

    char Scanner::Previous() const
    {
        return m_Source[m_Current - 1];
    }

    void Scanner::HexadecimalNumber()
    {
        Advance();
        Advance();

        while (IsHexDigit(Peek()))
        {
            Advance();
        }

        std::string lexeme = m_Source.substr(m_Start, m_Current - m_Start);
        MakeToken(TokenType::Int, lexeme);
    }

    void Scanner::BinaryNumber()
    {
        Advance();
        Advance();

        while (Peek() == '0' || Peek() == '1')
        {
            Advance();
        }

        std::string lexeme = m_Source.substr(m_Start, m_Current - m_Start);
        MakeToken(TokenType::Int, lexeme);
    }

    void Scanner::DecimalNumber()
    {
        bool isFloat = false;
        while (IsDigit(Peek()))
        {
            Advance();
        }

        if (Peek() == '.')
        {
            isFloat = true;
            Advance();

            while (IsDigit(Peek()))
            {
                Advance();
            }
        }

        if (Peek() == 'e' || Peek() == 'E')
        {
            Advance();
            if (Peek() == '+' || Peek() == '-')
            {
                Advance();
            }
            while (IsDigit(Peek()))
            {
                Advance();
            }
        }

        std::string lexeme = m_Source.substr(m_Start, m_Current - m_Start);
        MakeToken(isFloat ? TokenType::Float : TokenType::Int, lexeme);
    }

    void Scanner::IEEEScientificNotationNumber()
    {
    }

    bool Scanner::IsHexDigit(char c) const
    {
        return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
    }

    bool Scanner::IsDigit(const char c)
    {
        return c >= '0' && c <= '9';
    }

    bool Scanner::IsAlpha(const char c)
    {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    }

    bool Scanner::IsAlphaNumeric(const char c)
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

    bool Scanner::Match(const char c)
    {
        if (m_Current == m_Source.length()) return false;
        if (c != m_Source[m_Current + 1]) return false;

        Advance();
        return true;
    }
}
