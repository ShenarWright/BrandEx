#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <queue>

#include "DataStructures/Queue.h"

struct Account
{
    std::string email;
    std::string password;

    Queue<std::string> passwordHist;

    Account(std::string Email, std::string Password) : email(Email), password(Password){}
};

#endif