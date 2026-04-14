#include <iostream>

#include "Database.h"
#include <thread> // used for sleep
#include <chrono> // to use duration

#include "Utils/Console.h"

#include "DataStructures/Stack.h"
#include "DataStructures/LinkedList.h"


// Used for liters such as 1s for 1 second and 3min for 3 minutes
using namespace std::chrono_literals;

int getMainMenuItem();

// Login options
void handleLogin();

bool validateUser();
void forcePasswordSet(std::string email);

int handleBrowseProducts();

int getClientMenuItem();
int getAdminMenuItem();

//Signup options
void handleSignUp();

User currentUser;

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
    validateUser();

    int option = 0;
    std::system("cls");
    if (currentUser.userType == User::customer)
        switch (getClientMenuItem())
        {
        case 1:

            break;
        }
    else
        switch (getAdminMenuItem())
        {

        }

}

void handleSignUp()
{
    std::string name, lastName, email;

    std::cout << "Please enter your First name: ";
    std::cin >> name;
    
    std::cout << "Please enter you Last name: ";
    std::cin >> lastName;

    std::cout << "Please enter your email: \n";
    std::cin >> email;

    User user;
    user.firstName = name;
    user.lastName = lastName;
    user.email = email;

    std::cout << "Save Your OTP (One Time Password): " << Database::GetInstance().generateOneTimePassword();

    Database::GetInstance().addAccountToDatabase(Account{email,""});
    Database::GetInstance().AddUser(user);

    std::this_thread::sleep_for(5s);
}

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
        system("cls");
        Logger::error("Invalid Input Please try again");

        std::this_thread::sleep_for(2s);
    } while (true);

    system("cls");
    return option;
}

bool validateUser()
{
    std::string email, password;
    bool authorized = false;
    do
    {
        std::system("cls");
        std::cout << "BrandEx Login!!\n";
        std::cout << "Please Enter email: ";
        std::cin >> email;
        std::cout << "Please Enter password or generate OTP: ";
        password = getPassword();

  

        //Get password from the database - password in database is already encrypted
        std::string storedPassword = Crypto::decryptPassword(Database::GetInstance().getPassword(email));
        bool isOneTimePassword = Database::GetInstance().validateOneTimePassword(password);

        
        if (password == storedPassword || isOneTimePassword)
        {
            authorized = true;
            Logger::success("Login Successful!");
            std::this_thread::sleep_for(3s);
            currentUser = Database::GetInstance().getUser(email);

            if(isOneTimePassword)
                forcePasswordSet(email);
        }
        else if(email == "root" && password == "admin")
        {
            authorized = true;
            Logger::success("Successfully Logged in as Admin!");

            User user;
            user.userType = User::admin;
            std::this_thread::sleep_for(3s);
        }
        else
        {
            Logger::error("Password or email incorrect!");
            std::this_thread::sleep_for(3s);
        }

    } while (!authorized);

    
    return authorized;
}

void forcePasswordSet(std::string email)
{
    std::string password;
    std::cout << "BrandEx!! - Set Password\n";
    std::cout << "Please enter a password: ";
    
    password = getPassword();
   
    Database::GetInstance().updateAccountPassword(email, password);
}

int handleBrowseProducts()
{   
    std::this_thread::sleep_for(3s);
    return 0;
}

int getClientMenuItem()
{
    int option = 0;
    do
    {
        std::system("cls");

        std::cout << "BrandEx!!\n";
        std::cout << "1. Browse Products\n";
        std::cout << "2. Modify Cart\n";
        std::cout << "3. Checkout \n";
        std::cout << "4. Modify Account\n";
        std::cout << "5. Exit\n";
        std::cout << ">";

        std::cin >> option;

        if (option < 0 || option > 5)
            break;

        Logger::error("Invalid Input please try again!");
        std::this_thread::sleep_for(3s);

    } while (true);

    return option;
}

int getAdminMenuItem()
{
    return 0;
}
