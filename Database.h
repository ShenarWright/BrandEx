#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <fstream>
#include <filesystem>

//C++ 20
#include <format>

#include "Account.h"
#include "User.h"
#include "ProductInfo.h"
#include "CartRecord.h"
#include "Utils/BinaryTree.h"
#include "Utils/Crypto.h"

class Database
{
public:
    //This loads all files into memory
    void loadDatabase();
    
    //This saves all data to their appropriate files
    void saveDatabase();

    //Please encrypt before adding to database
    void addAccountToDatabase(Account acc);

    //Returns password tied to an account, if no password is found it returns an empty string
    //Note that passwords are encrypte
    std::string getPassword(std::string email);

    //Returns a queue with all recent passwords, returns an empty queue if none is found
    std::queue<std::string> getRecentPasswords(std::string email);

    //Test function deven worry about it
    friend void runTest(Database& db);

private:
    //Dynamic array that stores all the accounts
    std::vector<Account> accounts;

    //Dynamic array that stores all the userinfo
    std::vector<User> users;

    //Dynamic array that stores all the product info
    //std::map<int,ProductInfo> products;
    BinaryTree<ProductInfo> products;

private:

    //Parsing functions 
    Account parseAccount(std::string data);
    User parseUser(std::string data);
    ProductInfo parseProductInfo(std::string data);
    Product parseProduct(std::string data);
    Cart parseCart(std::string data);
    CartRecord parseCartRecord(std::string data);

    //Load passwords
    void loadPasswords();
    void loadPasswordHist();
    void loadUsers();
    void loadProducts();
    void loadCarts();

    //Save Passwords
    void savePasswords();
    void savePasswordHist();
    void saveUsers();
    void saveProducts();
    void saveCarts();
};

#endif // DATABASE_H