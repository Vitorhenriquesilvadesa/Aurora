#include "Parser.h"

namespace Aurora
{
    ParsedData Parser::ParseScannedData(const ScannedData& scannedData)
    {
        m_Tokens = scannedData.Data;

        return {};
    }
}
