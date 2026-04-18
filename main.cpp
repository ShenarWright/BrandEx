#include <iostream>

#include "Database.h"
#include <thread> // used for sleep
#include <chrono> // to use duration

#include "Utils/Console.h"

#include "DataStructures/Stack.h"
#include "DataStructures/LinkedList.h"
#include "DataStructures/Queue.h"

#include "Warehouse.h"
#include "ActionManager.h"


// Used for liters such as 1s for 1 second and 3min for 3 minutes
using namespace std::chrono_literals;

int getMainMenuItem();

// Login options
void handleLogin();

bool validateUser();
void handleForgotPassword(std::string email);
void forcePasswordSet(std::string email);

int getUserInput(std::string title,std::vector<std::string> options);

void printProducts();
void handleBrowseProducts();
void handleModifyCart();
void handleModifyAccount();
void handleCheckOut();
void handleViewOrderHistory();
void handleCheckEmail();
void showEmail(Email email);

//Prints the cart from the cart and returns the total
float printCart(Cart cart);

int getClientMenuItem();
int getAdminMenuItem();

void handleProcessOrders();
void handleGetClientPasswords();
void printClientPasswords();
void handleChangeCustomerPassword();

//Signup options
void handleSignUp();

User currentUser = User("John","Doe","johndoe@gmail.com");


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
            Database::GetInstance().saveDatabase();
            return 0;
        }

        Database::GetInstance().saveDatabase();
    }
   
    return 0;
}

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
        std::cout << "6. View Email\n";
        std::cout << "7. Exit\n";
        std::cout << ">";

        std::cin >> option;

        if (option > 0 && option < 8)
            break;

        Logger::error("Invalid Input please try again!");
        std::this_thread::sleep_for(1s);

    } while (true);

    return option;
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
                handleModifyCart();
                break;
            case 4:
                handleCheckOut();
                break;
            case 5:
                handleViewOrderHistory();
                break;
            case 6:
                handleCheckEmail();
                break;
            case 7:
                return;
            }
            Database::GetInstance().saveDatabase();
        } while (run);
    }
    else
    {
        do
        {
            switch (getAdminMenuItem())
            {
            case 1:
                handleProcessOrders();
                break;
            case 2:
                handleGetClientPasswords();
                break;
            case 3:
                handleChangeCustomerPassword();
                break;
            case 4:
                return;
                break;
            default:
                break;
            }
            Database::GetInstance().saveDatabase();
        } while (run);
    }

    ActionManager::GetInstance().reset();
}

void handleSignUp()
{
    std::string name, lastName, email;

    do
    {
        std::cout << "Please enter your First name: ";
        std::cin >> name;

        std::cout << "Please enter you Last name: ";
        std::cin >> lastName;

        std::cout << "Please enter your email: ";
        std::cin >> email;

        if (!validateEmailAddress(email))
        {
            Logger::error("Invalid Email try again");
            std::this_thread::sleep_for(3s);
        }

        if (!Database::GetInstance().accountExists(email))
            break;
        else
        {
            Logger::error("An account already Exists");
            std::this_thread::sleep_for(3s);
        }

    } while (true);
    
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
        std::cout << "BrandEx Login!!\n";
        std::cout << "Please Enter email: ";
        std::cin >> email;
        std::cout << "Forgot password? just enter -1\n";
        std::cout << "Please Enter password or generate OTP: ";
        password = getPassword();

        if (password == "-1")
        {
            handleForgotPassword(email);
            continue;
        }

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

void handleForgotPassword(std::string email)
{
    std::string firstName, lastName,password;
    bool loop = true;
    do
    {
        std::system("cls");

        std::cout << "BrandEx! Forgot Password?\n";
        std::cout << "Please enter your First name: ";
        std::cin >> firstName;

        std::cout << "Please enter your First name:";
        std::cin >> lastName;

        std::cout << "Please Enter new Password: ";
        password = getPassword();

        auto user = Database::GetInstance().getUser(email);
        if (user.firstName == firstName && user.lastName == lastName)
        {
            loop = !Database::GetInstance().updateAccountPassword(email,password);
        }
        else
        {
            Logger::error("Names don't match");
        }

         std::this_thread::sleep_for(3s);
    } while (loop);

}

void forcePasswordSet(std::string email)
{
    std::system("cls");
    std::string password;
    std::cout << "BrandEx!! - Set Password\n";
    std::cout << "Please enter a password: ";
    
    password = getPassword();
   
    Database::GetInstance().updateAccountPassword(email, password);
    std::this_thread::sleep_for(3s);
}

int getUserInput(std::string title, std::vector<std::string> options)
{
    int option = 0;
    do
    {
        std::system("cls");
        std::cout << title << '\n';

        for (int i = 0; i < options.size(); i++)
        {
            std::cout << i + 1 << " " << options[i] << '\n';
        }

        std::cin >> option;

        if (option > 0 && option <= options.size())
            break;

        Logger::error("Invalid input please try again");
        std::this_thread::sleep_for(2s);
    } while (true);

    return option;
}

void printProducts()
{
    auto products = Database::GetInstance().getProducts();

    std::cout << std::format("{:->47}", "") << "     " << std::format("{:->47}", "") << '\n';
    std::cout << std::format("|{:<4}|{:<30}|${:>9}|", "ID", "Name", "Price") << "     " << std::format("|{:<4}|{:<30}|${:>9}|", "ID", "Name", "Price") << '\n';
    std::cout << std::format("{:->47}", "") << "     " << std::format("{:->47}", "") << '\n';
    for (int i = 0; i < products.size(); i+= 2)
    {
        std::cout << std::format("|{:<4}|{:<30}|${:>9}|", products[i].productId, products[i].itemName, products[i].price) << "    ";

        if (i + 1 < products.size())
        {
            std::cout << std::format("|{:<4}|{:<30}|${:>9}|", products[i+ 1].productId, products[i + 1].itemName, products[i + 1].price) << '\n';
            std::cout << std::format("{:->47}", "") << "     ";
        }
        else
            std::cout << '\n';
        std::cout << std::format("{:->47}", "") << '\n';
    }
}

void handleBrowseProducts()
{   

    int option;
    do
    {
        std::system("cls");
        printProducts();
        auto products = Database::GetInstance().getProducts();
        std::cout << "Enter the ID of the item you want to add (-1 to exit): ";
        std::cin >> option;

        if (option == -1)
            break;

        if (option < 0 || option > products.size())
        {
            Logger::error("Invalid input please try again");
        }
        else
        {
            currentUser.cart.addProduct(option, 1);
            Database::GetInstance().updateUser(currentUser);
        }

    } while (true);

}

void handleModifyCart()
{

    int option = 0;
    do
    {
        option = getUserInput("BrandEx!!\n",
            {
                "View Cart",
                "Change Quantity of Item",
                "Remove Item From Cart",
                "Undo Action",
                "Redo Action",
                "Exit"
            });

        switch (option)
        {
        case 1:
        {
            std::system("cls");

            printCart(currentUser.cart);

            system("pause");
        }
         break;
        case 2:
        {
            int id = 0, quantity = 0;
            std::system("cls");
            printCart(currentUser.cart);

            std::cout << "\nEnter the ID of the Item you want to modify: ";
            std::cin >> id;

            std::cout << "Enter the quantity of the Item: ";
            std::cin >> quantity;

            //Validate Info

            //Save current product information
            ActionManager::GetInstance().pushAction({ Action::CHANGEQUANTITY,currentUser.cart.getProduct(id)});

            //Update info
            currentUser.cart.addProduct(id, quantity);

            Logger::success("Successfully Changed Item");
        }
        break;
        case 3:
        {
            int id = 0;
            do
            {
                std::system("cls");
                printCart(currentUser.cart);
                std::cout << "Enter the Id of the Item you want to remove: ";
                std::cin >> id;

                if (currentUser.cart.getProduct(id).id > 0)
                    break;

                Logger::error("Item does not exist is cart");
                std::this_thread::sleep_for(3s);
                
            } while (true);

            //Get current product iformation
            ActionManager::GetInstance().pushAction({Action::REMOVEITEM, {currentUser.cart.getProduct(id)}});

            //Remove Products
            currentUser.cart.removeProduct(id);
            Logger::success("Successfully Removed Item");
        }
        break;
        case 4: 
            ActionManager::GetInstance().undoAction(currentUser);
            Logger::success("Successfully Undid Action");
            
            break;
        case 5: 
            ActionManager::GetInstance().redoAction(currentUser); 
            Logger::success("Successfully Redid Action");
            break;
        case 6: Database::GetInstance().updateUser(currentUser); return;
        }
        std::this_thread::sleep_for(2s);
    } while (true);

}


// Client section

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
        Logger::success("First Name changed");
    }
    if (!lastName.empty())
    {
        currentUser.lastName = lastName;
        Logger::success("Last Name changed");
    }

    if (!password.empty())
    {
        Database::GetInstance().updateAccountPassword(currentUser.email, password);
    }

    Database::GetInstance().updateUser(currentUser);
    Logger::success("Sucessfully Updated Account");

    std::this_thread::sleep_for(1s);
}

void handleCheckOut()
{
    std::system("cls");

    if (!currentUser.cart.isEmpty())
    {
        CartRecord order(currentUser.email, currentUser.cart);
        Database::GetInstance().addCustomerOrder(order);
        currentUser.cart.emptyCart();
        Logger::success("Successfully placed order, Order will be processed in a timely manner");
    }
    else
    {
        Logger::error("Cart is empty");
    }

    std::this_thread::sleep_for(2s);
}

void handleViewOrderHistory()
{
    std::system("cls");

    float grandTotal = 0.0f;
    auto orders = Database::GetInstance().filterCustomerOrder(currentUser.email);

    for (int i = 0; i < orders.size(); i++)
    {

        grandTotal += printCart(orders[i].cartInfo);
        std::cout << "\n\n";
    }

    std::cout << std::format("|{:->40}|", "") << '\n';
    std::cout << std::format("|GrandTotal: {:>28.2f}|", grandTotal * 1.15f) << '\n';
    std::cout << std::format("|{:->40}|", "") << '\n';

    std::system("pause");
}

void handleCheckEmail()
{
    auto emails = Database::GetInstance().filterCustomerEmail(currentUser.email);

    if (emails.size() <= 0)
    {
        std::system("cls");
        std::cout << "There are no emails in the inbox\n";
        std::system("pause");
        return;
    }

    int option = 0;
    do
    {
        std::system("cls");
        std::cout << std::format("|{:-<58}|","") << '\n';
        std::cout << std::format("|{:<7}|{:<50}|", "Number", "Subject") << '\n';
        std::cout << std::format("|{:-<58}|","") << '\n';

        for (int i = 0; i < emails.size(); i++)
        {
            std::cout << std::format("|{:<7}|{:<50}|",i + 1,emails[i].subject) << '\n';
            std::cout << std::format("|{:-<58}|", "") << '\n';
        }

    
        
        std::cout << "\nSelect email to view";
        std::cin >> option;

        if (option > 0 && option <= emails.size())
            break;

        Logger::error("Invalid input please try again");
    } while (true);

    showEmail(emails[option - 1]);
}

void showEmail(Email email)
{
    std::system("cls");

    std::cout << "From: System\n";
    std::cout << "To: " << email.recipient << '\n';
    std::cout << "Subject: " << email.subject << '\n';
    std::cout << std::format("{:->60}", "") << '\n';
    std::cout << email.message << '\n';

    std::this_thread::sleep_for(1s);


    std::system("pause");
}

float printCart(Cart cart)
{
    auto products = cart.getAllProducts();
    float total = 0.f;

    std::cout << std::format("|{:->48}|", "") << '\n';
    std::cout << std::format("|{:<4}|{:<20}|{:<8}|${:>12}|","ID", "Name", "Quantity", "Total") << '\n';
    std::cout << std::format("|{:->48}|", "") << '\n';

    for (int i = 0; i < products.size(); i++)
    {
        std::string productName = Database::GetInstance().getProductInfo(products[i].id).itemName;
        int quantity = products[i].quantity;
        float price = Database::GetInstance().getProductInfo(products[i].id).price;

        std::cout << std::format("|{:<4}|{:<20}|{:<8}|${:>12.2f}|",products[i].id,productName,quantity,price * (float)quantity) << '\n';
        std::cout << std::format("|{:->48}|", "") << '\n';
        total += price * quantity;
    }
    std::cout << std::format("|Tax: ${:>42.2f}|", total * 0.15f) << '\n';
    std::cout << std::format("|Total: ${:>40.2f}|", total * 1.15) << '\n';
    std::cout << std::format("|{:->48}|", "") << '\n';

    return total;
}

int getAdminMenuItem()
{
    int option = 0;
    do
    {
        std::system("cls");
        std::cout << "BrandEx!!\n";
        std::cout << "1. Process Orders\n";
        std::cout << "2. View Customer Passwords\n";
        std::cout << "3. Modify a password\n";
        std::cout << "4. Exit\n";

        std::cin >> option;

        if (option > 0 && option < 5)
            break;

        Logger::error("Invalid Input please try again");

        std::this_thread::sleep_for(1s);

    } while (true);
    return option;
}

void handleProcessOrders()
{
    Warehouse::processOrders();
    Logger::success("Orders have been queued to process");

    system("pause");
}

void handleGetClientPasswords()
{
    
    std::system("cls");
    printClientPasswords();
    
    system("pause");
}

void printClientPasswords()
{
    auto users = Database::GetInstance().getAllUsers();
    std::cout << std::format("|{:->56}|", "") << '\n';
    std::cout << std::format("|{:<40}|{:<15}|", "email", "password") << '\n';
    std::cout << std::format("|{:->56}|", "") << '\n';
    for (int i = 0; i < users.size(); i++)
    {
        std::string email = users[i].email;
        std::string password = Crypto::decryptPassword(Database::GetInstance().getPassword(email));
        std::cout << std::format("|{:<40}|{:<15}|", email, password) << '\n';
        std::cout << std::format("|{:->56}|", "") << '\n';
    }
}

void handleChangeCustomerPassword()
{
    std::string email, password;

    do
    {
        std::system("cls"); 
        printClientPasswords();
        std::cout << "Enter Customer email: ";
        std::cin >> email;

        if (Database::GetInstance().accountExists(email))
        {
            break;
        }

        if (!validateEmailAddress(email))
            Logger::error("Invalid Email, try again");

        std::this_thread::sleep_for(2s);
    } while (true);

    std::cout << "Enter new Password: ";
    password = getPassword();

    Database::GetInstance().updateAccountPassword(email, password);
    std::this_thread::sleep_for(3s);
    
}