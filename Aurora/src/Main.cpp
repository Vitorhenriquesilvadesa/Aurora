#include "EntryPoint.h"

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		Aurora::Main();
		return EXIT_OK;
	}
	else if (argc > 1)
	{
		Aurora::Main(argc, argv);
		return EXIT_OK;
	}
}