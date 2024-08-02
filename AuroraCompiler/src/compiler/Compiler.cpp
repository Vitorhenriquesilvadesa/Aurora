#include "Compiler.h"
#include <iostream>
#include <fstream>

#include "Logging.h"

namespace Aurora
{
    AurCompiler::AurCompiler()
    {
        m_Scanner = std::make_unique<Scanner>(ScanSpecification{.LogLexingPass = Enabled});
    }

    bool AurCompiler::Compile(const std::string& absoluteMainFilepath)
    {
        COMPILE_LOG_INFO("Compiling file: {}", absoluteMainFilepath);
        std::string source = ReadSourceFile(absoluteMainFilepath);
        ScannedData data = m_Scanner->Scan(source);

        if(m_Scanner->HasError())
        {
            for(const auto& error : m_Scanner->GetErrorStack())
            {
                AUR_INFO("Error in file '{}': {}", absoluteMainFilepath, error);
            }
        }

        for(const auto& token : data.Data)
        {
            AUR_INFO("{} | '{}'", TokenTypeToString(token.type), token.lexeme);
        }
        
        return true;
    }

    std::string AurCompiler::ReadSourceFile(const std::string& absolutePath)
    {
        std::ifstream file(absolutePath);
        AUR_ASSERT(file.is_open(), "Cannot open '{}'.", absolutePath);

        std::string source;
        std::string line;

        while (std::getline(file, line))
        {
            source.append(line).append("\n");
        }

        file.close();
        return source;
    }
}
