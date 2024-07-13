#include "Repl.h"
#include <string>

namespace Aurora
{
	Repl::Repl()
	{
		std::cout << "<<< Aurora Console >>>\n" << std::endl;
	}

	void Repl::RunConsole()
	{
		std::string input;
		
		do {
			std::cout << ">> ";
			std::getline(std::cin, input);

			if (input == "exit")
			{
				return;
			}
		} while (true);
	}
}
