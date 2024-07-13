#include "Compiler.h"
#include <iostream>

namespace Aurora
{
	bool AurCompiler::Compile(const std::string& absoluteMainFilepath)
	{
		std::cout << "Compiling file: " << absoluteMainFilepath << std::endl;
		return true;
	}
}
