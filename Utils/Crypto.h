#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>

class Crypto
{
public:
	static std::string encryptPassword(std::string password);
	static std::string decryptPassword(std::string password);
};

#endif // CRYPTO_H
