#pragma once
#include <iostream>
#include <cstdlib>
#include <format>

#define AUR_ASSERT(condition, message, ...) \
	static_assert((message) != NULL); \
	do \
	{  \
		if(!(condition)) { \
			std::cerr << std::vformat((message), std::make_format_args(__VA_ARGS__)) << std::endl; \
			exit(EXIT_FAILURE); \
		} \
	} while(false)

#define AUR_INFO(message, ...) \
	std::cout << std::vformat((message), std::make_format_args(__VA_ARGS__)) << '\n'