#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <queue>

struct Account
{
    std::string email;
    std::string password;

    std::queue<std::string> passwordHist;

    Account(std::string Email, std::string Password) : email(Email), password(Password){}
};

#endif