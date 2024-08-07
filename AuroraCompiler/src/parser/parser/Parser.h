#pragma once
#include <memory>
#include <vector>

#include "../../lexer/ScannedData.h"
#include "../nodes/Ast.h"

namespace Aurora
{
    struct AUR_API ParsedData
    {
        std::vector<std::shared_ptr<AurSyntaxTreeNode>> Nodes;
    };

    class AUR_API Parser
    {
    public:
        ParsedData ParseScannedData(const ScannedData& scannedData);

        
    private:
        std::vector<Token> m_Tokens;
    };
}
