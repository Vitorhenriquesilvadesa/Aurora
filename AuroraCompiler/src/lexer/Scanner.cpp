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
            SyncCursors();
            ScanToken();
        }

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
        switch(Advance())
        {
        case '+':
        {
            if (Match('+'))
            {
                MakeToken(TokenType::PlusPlus);
                break;
            }
            else if (Match('='))
            {
                MakeToken(TokenType::PlusEqual);
                break;
            }
            else
            {
                MakeToken(TokenType::Plus);
                break;
            }
        }

        case '-':
        {
            if (Match('-'))
            {
                MakeToken(TokenType::MinusMinus);
                break;
            }
            else if (Match('='))
            {
                MakeToken(TokenType::MinusEqual);
                break;
            }
            else
            {
                MakeToken(TokenType::Minus);
                break;
            }
        }

        case '*':
        {
            if (Match('*'))
            {
                MakeToken(TokenType::StarStar);
                break;
            }
            else if (Match('='))
            {
                MakeToken(TokenType::StarEqual);
                break;
            }
            else
            {
                MakeToken(TokenType::Star);
                break;
            }
        }

        case '/':
        {
            if (Match('/'))
            {
                MakeToken(TokenType::SlashSlash);
                break;
            }
            else if (Match('='))
            {
                MakeToken(TokenType::SlashEqual);
                break;
            }
            else
            {
                MakeToken(TokenType::Slash);
                break;
            }
        }

        case '%':
        {
            if (Match('='))
            {
                MakeToken(TokenType::ModEqual);
                break;
            }
            else
            {
                MakeToken(TokenType::Mod);
                break;
            }
        }

        case '!':
        {
            if (Match('='))
            {
                MakeToken(TokenType::MarkEqual);
                break;
            }
            else
            {
                MakeToken(TokenType::Mark);
                break;
            }
        }

        case '=':
        {
            if (Match('='))
            {
                MakeToken(TokenType::EqualEqual);
                break;
            }
            else
            {
                MakeToken(TokenType::Equal);
                break;
            }
        }

        case '?':
        {
            if (Match('?'))
            {
                if (Match('='))
                {
                    MakeToken(TokenType::DubleQuestionEqual);
                    break;
                }
                else
                {
                    MakeToken(TokenType::QuestionQuestion);
                    break;
                }
            }
            else if (Match('='))
            {
                MakeToken(TokenType::QuestionEqual);
                break;
            }
            else
            {
                MakeToken(TokenType::Question);
                break;
            }
        }

        case '>':
        {
            if (Match('>'))
            {
                if (Match('='))
                {
                    MakeToken(TokenType::RightShiftEqual);
                    break;
                }
                else
                {
                    MakeToken(TokenType::RightShift);
                    break;
                }
            }
            else if (Match('='))
            {
                MakeToken(TokenType::GreaterEqual);
                break;
            }
            else
            {
                MakeToken(TokenType::Greater);
                break;
            }
        }

        case '<':
        {
            if (Match('<'))
            {
                if (Match('='))
                {
                    MakeToken(TokenType::LeftShiftEqual);
                    break;
                }
                else
                {
                    MakeToken(TokenType::LeftShift);
                    break;
                }
            }
            else if (Match('='))
            {
                MakeToken(TokenType::LessEqual);
                break;
            }
            else
            {
                MakeToken(TokenType::Less);
                break;
            }
        }
        
        case '|':
        {
            if (Match('|'))
            {
                MakeToken(TokenType::Or);
                break;
            }
            else if (Match('='))
            {
                MakeToken(TokenType::BitwiseOrEqual);
                break;
            }
            else
            {
                MakeToken(TokenType::Pipe);
                break;
            }
        }        

        case '&':
        {
            if (Match('&'))
            {
                MakeToken(TokenType::And);
                break;
            }
            else if (Match('='))
            {
                MakeToken(TokenType::BitwiseAndEqual);
                break;
            }
            else
            {
                MakeToken(TokenType::BitwiseAnd);
                break;
            }
        }

        case '#':
            MakeToken(TokenType::Hash); break;

        case '@':
            MakeToken(TokenType::AtSign); break;

        case '(':
            MakeToken(TokenType::LeftParen); break;

        case ')':
            MakeToken(TokenType::RightParen); break;

        case '[':
            MakeToken(TokenType::LeftBracket); break;

        case ']':
            MakeToken(TokenType::RightBracket); break;

        case '{':
            MakeToken(TokenType::LeftBrace); break;

        case '}':
            MakeToken(TokenType::RightBrace); break;

        case ';':
            MakeToken(TokenType::Semicolon); break;

        case '.':
            if (Match('.'))
            {
                if (Match('.'))
                {
                    MakeToken(TokenType::TripleDot); break;
                }
                else
                {
                    MakeToken(TokenType::DoubleDot); break;
                }
            }
            else
            {
                MakeToken(TokenType::Dot); break;
            }

        case ',':
            MakeToken(TokenType::Comma); break;

        case ':':
            MakeToken(TokenType::Colon); break;

        case '$':
            MakeToken(TokenType::Dollar); break;

        case '\n':
            m_Line++;
            m_Column = 1;
            break;

        case ' ':
        case '\r':
        case '\t':
            m_Column++;
            break;

        case '"':
            String();
            break;

        case '\'':
            Char();
            break;

        default:
            if (IsDigit(Previous()))
            {
                Number();
                break;
            }
            else if (IsAlpha(Peek()))
            {
                Identifier();
                break;
            }

            break;
        }
    }

    void Scanner::SkipWhitespace()
    {
    }

    void Scanner::SyncCursors()
    {
        m_Start = m_Current;
    }

    void Scanner::MakeToken(TokenType type, const std::string& lexeme, const std::string& literal)
    {
        m_Tokens.emplace_back(Token(m_Line, m_Column, type, lexeme, literal));
    }

    void Scanner::Identifier()
    {
        while (IsAlphaNumeric(Peek()) || Check('_'))
        {
            Advance();
        }

        MakeToken(TokenType::Identifier, m_Source.substr(m_Start, m_Current - m_Start));
    }

    void Scanner::String()
    {
        Advance();

        while (!IsAtEnd() && !Match('"'))
        {
            Advance();
        }
        
        MakeToken(TokenType::String, "", m_Source.substr(m_Start + 1, m_Current - m_Start - 2));
        
        Advance();
    }

    void Scanner::Char()
    {
        char c = Advance();
        Advance();
        Advance();

        MakeToken(TokenType::Char, "", std::format("{}", c));
    }

    void Scanner::Number()
    {
        if (Previous() == '0')
        {
            if (Peek() == 'x' || Peek() == 'X')
            {
                Advance();
                Advance();
                HexadecimalNumber();
            }
            else if (Peek() == 'b' || Peek() == 'B')
            {
                Advance();
                Advance();
                BinaryNumber();
            }
        }
        else
        {
            DecimalNumber();
        }
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
    }

    void Scanner::BinaryNumber()
    {
        while (Peek() == '0' || Peek() == '1')
        {
            Advance();
        }

        MakeToken(TokenType::Binary, "", m_Source.substr(m_Start, m_Current - m_Start));
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
            if(Peek() == '.')
            {
                PushError("Invalid float notation, only one dot in floating point number.");
                m_HasError = true;
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
        if(IsAtEnd()) return '\0';
        return m_Source[m_Current + 1];
    }

    bool Scanner::Match(char c)
    {
        if (IsAtEnd()) return false;
        if (m_Source[m_Current] != c) return false;

        m_Current++;
        return true;
    }

    template <typename... Args>
    void Scanner::PushError(const std::string& message, Args&&... args)
    {
        m_ErrorStack.emplace_back(std::vformat(message, std::make_format_args(std::forward<Args>(args)...)));
    }
}
