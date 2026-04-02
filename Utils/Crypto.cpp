#include "Crypto.h"

//Simple Ceasor cypher
std::string Crypto::encryptPassword(std::string data)
{
    for (int i = 0; i < data.size(); i++)
    {
        data[i] += 2;
    }
    return data;
}

//Simple Ceasor cypher
std::string Crypto::decryptPassword(std::string data)
{
    for (int i = 0; i < data.size(); i++)
    {
        data[i] -= 2;
    }
    return data;
}