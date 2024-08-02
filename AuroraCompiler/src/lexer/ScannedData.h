#pragma once
#include <vector>
#include <Token.h>

namespace Aurora
{
    class ScannedData
    {
    public:
        explicit ScannedData(const std::vector<Token>& data)
        : Data(data)
        {
        }

        std::vector<Token> Data;
    };
}
