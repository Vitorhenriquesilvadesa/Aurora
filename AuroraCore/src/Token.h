#include <cstdint>
#include <string>

namespace Aurora
{
    enum class TokenType {
        // Primitive types.
        IDENTIFIER,    // Variables, function names, etc.
        INT,           // 'int' for integer type
        FLOAT,         // 'float' for floating-point type
        BYTE,          // 'byte' for char type
        STRING,        // 'string' for string type
        BOOL,          // 'bool' for boolean type

        // Keywords
        VAR,           // 'var' for mutable variables
        FUNCTION,      // 'function' for function declarations
        METHOD,        // 'method' for method declarations
        MESSAGE,       // 'message' for message declarations
        RETURN,        // 'return' for returning values from functions
        THROW,         // 'throw' for raise errors during runtime.
        IF,            // 'if' for conditional structures
        ELSE,          // 'else' for conditional structures
        THEN,          // 'then' for enhanced for loops
        FOR,           // 'for' for loops
        WHILE,         // 'while' for loops
        BREAK,         // 'break' for exiting loops
        CONTINUE,      // 'continue' for continuing to the next iteration of loops
        TRUE,          // 'true' boolean literal
        FALSE,         // 'false' boolean literal
        NULL_LITERAL,  // 'null' null literal
        PRINT,         // 'print' for outputting data
        CONST,         // 'const' for declaring constants
        CLASS,         // 'class' for class definitions
        ACTOR,         // 'actor' for actor definitions
        EXTENDS,       // ':' for class inheritance
        THIS,          // 'this' for referencing the current instance of a class
        SUPER,         // 'super' for referencing the superclass
        IMPORT,        // 'import' for importing modules
        EXPORT,        // 'export' for exporting modules
        ASYNC,         // 'async' for defining asynchronous functions
        AWAIT,         // 'await' for waiting for asynchronous functions to complete
        KERNEL,        // 'kernel' for defining functions that run on the GPU

        // Operators
        PLUS,          // '+'
        MINUS,         // '-'
        STAR,          // '*'
        SLASH,         // '/'
        PERCENT,       // '%'
        EQUAL,         // '='
        BANG,          // '!'
        EQUAL_EQUAL,   // '=='
        BANG_EQUAL,    // '!='
        LESS,          // '<'
        LESS_EQUAL,    // '<='
        GREATER,       // '>'
        GREATER_EQUAL, // '>='
        AND,           // '&&'
        OR,            // '||'
        PLUS_PLUS,     // '++'
        MINUS_MINUS,   // '--'
        PLUS_EQUAL,    // '+='
        MINUS_EQUAL,   // '-='
        STAR_EQUAL,    // '*='
        SLASH_EQUAL,   // '/='
        PERCENT_EQUAL, // '%='

        // Delimiters
        LEFT_PAREN,    // '('
        RIGHT_PAREN,   // ')'
        LEFT_BRACE,    // '{'
        RIGHT_BRACE,   // '}'
        LEFT_BRACKET,  // '['
        RIGHT_BRACKET, // ']'
        SEMICOLON,     // ';'
        COMMA,         // ','
        DOT,           // '.'

        // End of File
        END_OF_FILE    // Indicates end of file
    };

    struct Token {
        TokenType type;         
        std::string lexeme;     
        int line;               
        int column;             
        int startPosition;      
        int endPosition;        
        std::string filePath;   
        bool isPartOfMultiToken;

        Token(TokenType type, const std::string& lexeme, int line, int column,
            int startPosition, int endPosition, bool isPartOfMultiToken = false, const std::string& filePath = "")
            : type(type), lexeme(lexeme), line(line), column(column),
            startPosition(startPosition), endPosition(endPosition), isPartOfMultiToken(isPartOfMultiToken), filePath(filePath) {}
    };
}