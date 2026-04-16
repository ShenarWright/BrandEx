#ifndef EMAIL_H
#define EMAIL_H

#include <string>

struct Email
{
	std::string recipient;
	std::string subject;
	std::string message;
};

#endif // !EMAIL_H
