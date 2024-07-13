#include "VirtualMachine.h"


namespace Aurora
{
	bool AurVirtualMachine::ExecuteBytecode(const std::string& bytecodeEntryPointFilePath)
	{
		std::cout << "Executing bytecode from: " << bytecodeEntryPointFilePath << std::endl;
		return true;
	}
}
