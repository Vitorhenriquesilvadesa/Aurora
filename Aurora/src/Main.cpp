#include "EntryPoint.h"


int main(const int argc, char* argv[])
{
	if(argc == 1)
	{
		Aurora::Main();
	}
	else if(argc > 1)
	{
		Aurora::Main(argc, argv);
	}
}