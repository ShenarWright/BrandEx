#ifndef EMAIL_H
#define EMAIL_H

#include <string>

struct Email
{
	std::string recipient;
	std::string subject;
	std::string message;
};

inline bool validateEmailAddress(std::string email)
{
	return email.find('@') != std::string::npos;
}

#endif // !EMAIL_H
