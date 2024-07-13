#pragma once

#include <vector>
#include <string>

#define EXIT_OK 0

namespace Aurora
{
	void Main();
	void Main(int argc, char** argv);
	void ArgumentDelegation(const std::vector<std::string> &args);
}