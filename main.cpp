#include <iostream>

#include "Database.h"
#include <thread> // used for sleep
#include <chrono> // to use duration

#include "Utils/Console.h"

#include "DataStructures/Stack.h"
#include "DataStructures/LinkedList.h"
#include "DataStructures/Queue.h"


// Used for liters such as 1s for 1 second and 3min for 3 minutes
using namespace std::chrono_literals;

int getMainMenuItem();

// Login options
void handleLogin();

bool validateUser();
void forcePasswordSet(std::string email);

int handleBrowseProducts();
void handleModifyAccount();

int getClientMenuItem();
int getAdminMenuItem();

//Signup options
void handleSignUp();

User currentUser;

int main()
{
    //Setting the random seed
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
    bool run = true;
    std::system("cls");
    if (currentUser.userType == User::customer)
    {
        do
        {
            switch (getClientMenuItem())
            {
            case 1:
                handleModifyAccount();
                break;
            case 2:
                handleBrowseProducts();
                break;
            case 3:
                break;
            case 4:
                
                break;
            case 5:
                run = false;
                break;
            }
        } while (run);
    }
    else
    {
        do
        {
            switch (getAdminMenuItem())
            {
            default:
                break;
            }
        } while (run);
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
    user.userType = User::customer;

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
        std::cout << Crypto::decryptPassword(Database::GetInstance().getPassword("johndoe@gmail.com")) << '\n';
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
            currentUser.userType = User::customer;

            if(isOneTimePassword)
                forcePasswordSet(email);
        }
        else if(email == "root" && password == "admin")
        {
            authorized = true;
            Logger::success("Successfully Logged in as Admin!");

            User user;
            currentUser.userType = User::admin;
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
    auto products = Database::GetInstance().getProducts();
    
    std::cout << std::format("{:->47}","") << '\n';
    std::cout << std::format("|{:<4}|{:<30}|{:<9}|", "ID", "Name", "Price") << '\n';
    std::cout << std::format("{:->47}", "") << '\n';
    for (int i = 0; i < products.size(); i++)
    {
        std::cout << std::format("|{:<4}|{:<30}|{:<9}|", products[i].productId, products[i].itemName, products[i].price) << '\n';
        std::cout << std::format("{:->47}", "") << '\n';
    }
    std::this_thread::sleep_for(10s);
    return 0;
}


// Client section
int getClientMenuItem()
{
    int option = 0;
    do
    {
        std::system("cls");

        std::cout << "BrandEx!!\n";
        std::cout << "1. Modify Account\n";
        std::cout << "2. Browse Products\n";
        std::cout << "3. Modify Cart\n";
        std::cout << "4. Checkout \n";
        std::cout << "5. View Order History\n";
        std::cout << "6. Exit\n";
        std::cout << ">";

        std::cin >> option;

        if (option > 0 || option < 6)
            break;

        Logger::error("Invalid Input please try again!");
        std::this_thread::sleep_for(3s);

    } while (true);

    return option;
}

void handleModifyAccount()
{
    std::system("cls");

    std::string firstName, lastName, password;

    std::cout << "Enter new first name (leave blank if you want to keep): ";
    //To combat the bug where input is skipped
    std::cin.get();
    std::getline(std::cin, firstName);

    std::cout << "Enter new last name (leave blank if you want to keep): ";
    std::getline(std::cin, lastName);

    std::cout << "Enter new password (leave blank if you want to keep current): ";
    password = getPassword();

    if (!firstName.empty())
    {
        currentUser.firstName = firstName;
        std::cout << "Firstname changed\n";
    }
    if (!lastName.empty())
    {
        currentUser.lastName = lastName;
        std::cout << "Lastname changed\n";
    }

    if (!password.empty())
    {
        Database::GetInstance().updateAccountPassword(currentUser.email, password);
    }

    Database::GetInstance().updateUser(currentUser);
    Logger::success("Sucessfully Updated Account");

    std::this_thread::sleep_for(3s);
}

int getAdminMenuItem()
{
    return 0;
}
