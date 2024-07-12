#include "EntryPoint.h"
#include <iostream>
#include <CompileSpecification.h>

void Aurora::Main()
{
	Print();
}

void Aurora::Main(int argc, char** argv)
{
	std::vector<std::string> args = std::vector<std::string>();

	for (int i = 0; i < argc; i++)
	{
		args.push_back(argv[i]);
	}

	ArgumentDelegator(args);
}

void Aurora::ArgumentDelegator(const std::vector<std::string>& args)
{
	// Parse args implementation here.
}
