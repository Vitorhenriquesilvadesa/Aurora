#pragma once
#include <memory>
#include <string>

#include "../CompileSpecification.h"
#include "../lexer/Scanner.h"

#define COMPILE_LOG_INFO(message, ...) \
    do { \
        if(m_Spec.LogCompilation) { \
            std::cout << std::vformat((message), std::make_format_args(__VA_ARGS__)) << '\n'; \
        } \
    } while(false)

namespace Aurora
{
    class AUR_API AurCompiler
    {
    public:
        AurCompiler();

        bool Compile(const std::string& absoluteMainFilepath);
        
    private:
        std::string ReadSourceFile(const std::string& absolutePath);
        
    private:
        std::unique_ptr<Scanner> m_Scanner;
        AurCompileSpecification m_Spec;
    };
}
