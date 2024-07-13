#include "EntryPoint.h"
#include "CommandReceptor.h"
#include <iostream>


void Aurora::Main()
{
	CommandReceptor::CallRepl();
}

void Aurora::Main(int argc, char** argv)
{
	std::vector<std::string> args = std::vector<std::string>();

	for (int i = 0; i < argc; i++)
	{
		args.push_back(argv[i]);
	}

	ArgumentDelegation(args);
}

void Aurora::ArgumentDelegation(const std::vector<std::string>& args)
{
	std::vector<std::string> filteredArgs(args.begin() + 1, args.end());

	CommandReceptor::Execute(filteredArgs);
}
