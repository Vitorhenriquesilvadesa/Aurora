#include <iostream>
#include <cstdlib>

#define AUR_ASSERT(condition, message) \
	static_assert(message); \
	do \
	{  \
		if(!(condition)) { \
			std::cerr << (message) << std::endl; \
			exit(EXIT_FAILURE); \
		} \
	} while(false)