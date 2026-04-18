#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

class Logger
{
public:
	static void error(std::string message)
	{
		std::cerr << "\033[31m" << message << "\033[0m" << std::endl;
	}

	static void success(std::string message)
	{
		std::cout << "\033[32m" << message << "\033[0m" << std::endl;
	}
};

#endif // LOGGER_H