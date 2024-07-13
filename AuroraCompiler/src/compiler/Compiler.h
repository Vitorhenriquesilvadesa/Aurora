#include <Core.h>
#include <string>

namespace Aurora
{
	class AUR_API AurCompiler
	{
	public:
		bool Compile(const std::string& absoluteMainFilepath);
	};
}