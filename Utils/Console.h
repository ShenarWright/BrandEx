#pragma once

#include <iostream>
#include <conio.h>

#include <chrono> // to use duration
#include <thread> // used for sleep

using namespace std::chrono_literals;

void clearLastLine()
{
    std::cout << "\033[1A";
    std::cout << "\033[2K";
}

void printAseterisks(int num)
{
    for(int i = 0; i < num;i++)
        std::cout << '*';
}

std::string getPassword()
{
    char character;
    std::string password;

    while (character = _getch())
    {
        if (character == 13) // Enter key
        {
            std::cout << '\n';
            break;
        }
        if (character == 8) // Backspace Key
        {
            if (password.size() > 0)
            {
                password.resize(password.size() - 1);
                std::cout << "\b \b";
            }
        }
        else
        {
            password += character;
            printAseterisks(1);
        }
    }

    return password;
}