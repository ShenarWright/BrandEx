#include <iostream>

#include "Database.h"
#include <thread> // used for sleep
#include <chrono> // to use duration

#include "Utils/Console.h"

#include "DataStructures/Stack.h"


// Used for liters such as 1s for 1 second and 3min for 3 minutes
using namespace std::chrono_literals;

int getMainMenuItem()
{
    int option = 0;
    do
    {
        //Clears the console
        std::system("cls");

        std::cout << "BrandEx welcome!\n"
                  << "Select an Option\n"
                  << "1. Signup\n"
                  << "2. Login\n"
                  << "3. Exit" << std::endl;

        std::cin >> option;



        //If input is valid
        if (option >= 1 && option <= 3)
            break;

        //If input is invalid
        std::cerr << "Error! Invalid input" << std::endl;

        std::this_thread::sleep_for(2s);
    } while (true);

    return option;
}

void handleLogin();
void handleSignUp();

int main()
{
    srand((unsigned int)time(0));
    Database::GetInstance().loadDatabase();


    while (true)
    {
        switch (getMainMenuItem())
        {
        case 1:
            handleSignUp();
            break;
        case 2:
            handleLogin();
            break;
        default:
            return 0;
        }

        Database::GetInstance().saveDatabase();
    }

    Database::GetInstance().saveDatabase();

   
    return 0;
}

void handleLogin()
{

}

void handleSignUp()
{

}