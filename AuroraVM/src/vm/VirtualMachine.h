#include <Core.h>
#include <string>
#include <iostream>

namespace Aurora
{
	class AUR_API AurVirtualMachine
	{
	public:
		bool ExecuteBytecode(const std::string& bytecodeEntryPointFilePath);
	};
}