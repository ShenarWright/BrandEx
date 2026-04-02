#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

#include "Cart.h"

struct User
{
    std::string firstName;
    std::string lastName;
    std::string email;

    enum UserType{
        admin = 0,
        customer
    };

    UserType userType;
    Cart cart;
};

#endif // USER_H