#include "Database.h"

void Database::loadDatabase()
{
    loadPasswords();
    loadPasswordHist();
    loadUsers();
    loadProducts();
    loadCarts();
    loadOrders();
    loadPastOrders();
    loadEmails();
}

void Database::saveDatabase()
{
    savePasswords();
    savePasswordHist();
    saveUsers();
    saveProducts();
    saveCarts();
    saveOrders();
    savePastOrders();
    saveEmails();
}

void Database::loadPasswords()
{
    std::fstream fs("data/passwords.txt",std::ios::in | std::ios::out | std::ios::app | std::ios::out | std::ios::app);

    if (!fs.is_open())
        Logger::error("Failed to open file");

    std::string buffer;
    while(std::getline(fs,buffer))
    {
        accounts.push_back(parseAccount(buffer));
    }
    fs.close();
}

void Database::loadPasswordHist()
{
    std::fstream fs("data/passwordhist.txt",std::ios::in | std::ios::out | std::ios::app);

    if (!fs.is_open())
        return;

    std::string buffer;
    while(std::getline(fs,buffer))
    {
        Account temp = parseAccount(buffer);
        for(int i = 0; i < accounts.size();i++)
        {
            if(accounts[i].email == temp.email)
                accounts[i].passwordHist.push(temp.password);
        }
    }
    fs.close();
}

void Database::savePasswords()
{
    std::fstream fs("data/passwords.txt",std::ios::out | std::ios::trunc);

    if (!fs.is_open())
        return;

    
    for(int i = 0; i < accounts.size();i++)
    {
        fs << std::format("{} : {}",accounts[i].email, accounts[i].password) << std::endl;
    } 

    fs.close();
}

void Database::savePasswordHist()
{
    std::fstream fs("data/passwordhist.txt",std::ios::out | std::ios::trunc);

    if (!fs.is_open())
        return;

    for(int i = 0; i < accounts.size();i++)
    {
        for(int j = 0; j < accounts[i].passwordHist.size();j++)
            fs << std::format("{} : {}",accounts[i].email, accounts[i].passwordHist[j]) << std::endl;
    } 

    fs.close();
}

void Database::loadUsers()
{
    std::fstream fs("data/users.txt",std::ios::in | std::ios::out | std::ios::app);
    
    if (!fs.is_open())
        return;

    std::string buffer;
    while(std::getline(fs,buffer))
    {
        users.push_back(parseUser(buffer));
    }
}

void Database::saveUsers()
{
    std::fstream fs("data/users.txt",std::ios::out | std::ios::trunc);

    if (!fs.is_open())
        return;

    
    for(int i = 0; i < users.size();i++)
    {
        fs << std::format("{};{};{}",users[i].firstName, users[i].lastName,users[i].email) << std::endl;
    } 

    fs.close();
}

void Database::loadProducts()
{
    std::fstream fs("data/products.txt");

    if (!fs.is_open())
        return;

    std::string buffer;
    while(std::getline(fs,buffer))
    {
        ProductInfo productInfo = parseProductInfo(buffer);
        products.insert(productInfo);
    }

    //products.display();
    fs.close();
}

void Database::loadCarts()
{
    std::fstream fs("data/carts.txt");

    if (!fs.is_open())
        return;

    std::string buffer;
    while (std::getline(fs, buffer))
    {
        CartRecord cartRecord = parseCartRecord(buffer);
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].email == cartRecord.email)
            {
                users[i].cart = cartRecord.cartInfo;
                break;
                std::cout << cartRecord << '\n';
            }
        }
    }

    //products.display();
    fs.close();
}

void Database::loadOrders()
{
    std::fstream fs("data/orders.txt");

    if (!fs.is_open())
        return;

    std::string buffer;
    while (std::getline(fs, buffer))
    {
        CartRecord record = parseCartRecord(buffer);
        orders.push_back(record);
    }
}

void Database::loadPastOrders()
{
    std::fstream fs("data/past-orders.txt");

    if (!fs.is_open())
        return;

    std::string buffer;
    while (std::getline(fs, buffer))
    {
        CartRecord record = parseCartRecord(buffer);
        pastOrders.push_back(record);
    }
}

void Database::loadEmails()
{
    std::fstream fs("data/emails.txt");

    if (!fs.is_open())
        return;

    std::string buffer;
    while (std::getline(fs, buffer))
    {
        auto email = parseEmail(buffer);
        emails.push_back(email);
    }
}

void Database::saveProducts()
{
    std::fstream fs("data/products.txt", std::ios::out | std::ios::trunc);

    if (!fs.is_open())
        return;

    auto productInfoList = products.getElements();
    for (int i = 0; i < productInfoList.size(); i++)
    {
        fs << std::format("{};{};{}",
            productInfoList[i].productId,
            productInfoList[i].itemName,
            productInfoList[i].price
            ) << std::endl;
    }
}

void Database::saveCarts()
{
    std::fstream fs("data/carts.txt", std::ios::out | std::ios::trunc);
    if (!fs.is_open())
        return;

    for (int i = 0; i < users.size(); i++)
    {
        auto cartProducts = users[i].cart.getAllProducts();

        if (!cartProducts.empty())
        {
            std::string buffer = users[i].email + ':' + std::format("[{},{}]",cartProducts[0].id,cartProducts[0].quantity);

            for (int i = 1; i < cartProducts.size(); i++)
            {
                buffer += std::format(";[{},{}]", cartProducts[i].id, cartProducts[i].quantity);
            }

            fs << buffer << std::endl;
        }
    }
}

void Database::saveOrders()
{
    std::fstream fs("data/orders.txt", std::ios::out | std::ios::trunc);

    if (!fs.is_open())
        return;

    for(int i = 0; i < orders.size();i++)
    {
        auto cartProducts = orders[i].cartInfo.getAllProducts();
        std::string buffer = orders[i].email + ':' + std::format("[{},{}]", cartProducts[0].id, cartProducts[0].quantity);

        for (int i = 1; i < cartProducts.size(); i++)
        {
            buffer += std::format(";[{},{}]", cartProducts[i].id, cartProducts[i].quantity);
        }

        fs << buffer << std::endl;
    }
}

void Database::savePastOrders()
{
    std::fstream fs("data/past-orders.txt", std::ios::out | std::ios::trunc);

    if (!fs.is_open())
        return;

    for (int i = 0; i < pastOrders.size(); i++)
    {
        auto cartProducts = pastOrders[i].cartInfo.getAllProducts();
        std::string buffer = pastOrders[i].email + ':' + std::format("[{},{}]", cartProducts[0].id, cartProducts[0].quantity);

        for (int i = 1; i < cartProducts.size(); i++)
        {
            buffer += std::format(";[{},{}]", cartProducts[i].id, cartProducts[i].quantity);
        }

        fs << buffer << std::endl;
    }
}

void Database::saveEmails()
{
    std::fstream fs("data/emails.txt",std::ios::out | std::ios::trunc);

    if (!fs.is_open())
        return;

    for (int i = 0; i < emails.size(); i++)
    {
        fs << std::format("{};{};{}", emails[i].recipient, emails[i].subject, emails[i].message) << '\n';
    }
}


void Database::addAccountToDatabase(Account acc)
{
    accounts.push_back(acc);
}

//TODO: IMPLEMENT OWN STACK AND QUEUE
bool Database::updateAccountPassword(std::string email, std::string password)
{
    //Encrypt password
    password = Crypto::encryptPassword(password);

    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].email == email) 
        {

            //Todo : add a find feature when implementing the list            
            if (accounts[i].passwordHist.hasElement(password) || accounts[i].password == password)
            {
                Logger::error("Error: Password cannot be any of your previous passwords\n");
                return false;
            }
            
            if (!accounts[i].password.empty())
            {
                //If this is a password change , i will insert the previous into the password history
                std::string currentPassword = accounts[i].password;
                accounts[i].passwordHist.push(currentPassword);
                
                //IF more than 2 passwords are in the history, remove the one at the front of the list
                if (accounts[i].passwordHist.size() > 2)
                    accounts[i].passwordHist.pop();
                
            }
            accounts[i].password = password;

            //Send email to customer
            Email emailInfo;
            emailInfo.recipient = email;
            emailInfo.subject = "Password Successfully Updated";
            emailInfo.message = std::format("Your Password has been updated successfully. Your new password is {}", Crypto::decryptPassword(password));

            addEmail(email,emailInfo);

            Logger::success("Successfully Updated Password!");
            return true;
        }
    }
    return false;
}

std::string Database::getPassword(std::string email)
{
    for (auto& e : accounts)
    {
        if (e.email == email)
            return e.password;
    }
    return {};
}

std::queue<std::string> Database::getRecentPasswords(std::string email)
{
    std::queue<std::string> passwords;

    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].email == email)
            return passwords;
    }
    return std::queue<std::string>();
}

bool Database::validateOneTimePassword(std::string password)
{
    for (int i = 0; i < oneTimePasswords.size(); i++)
    {
        if (oneTimePasswords[i] == password)
        {
            oneTimePasswords.erase(oneTimePasswords.begin() + i);
            
            return true;
        }
    }
    return false;
}

bool Database::accountExists(std::string email)
{
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].email == email)
            return true;
    }
    return false;
}

std::string Database::generateOneTimePassword()
{
    int length = 6;
    std::string password;
    for (int i = 0; i < length; i++)
    {
        //characters between 48 and 56
        password += (char)(48 + rand() % 9);
    }

    oneTimePasswords.push_back(password );
    return password;
}

void Database::changeUserPassword(std::string email, std::string newPassword)
{
    int index = -1;
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].email == email)
        {
            index = i;
            break;
        }
    }

    if (index <= -1)
    {
        Logger::error("Error could not find userName specified");
    }

    if (accounts[index].password == newPassword)
    {
        Logger::error("Cannot use old password");
    }
}

int Database::searchProducts(std::string productName)
{
    return 0;// products.search();
}

Database& Database::GetInstance()
{
    static Database db;
    return db;
}

User Database::getUser(std::string email)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].email == email)
            return users[i];
    }
    return User();
}

void Database::AddUser(User user)
{
    users.push_back(user);
}

void Database::updateUser(User user)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].email == user.email)
        {
            users[i] = user;
            return;
        }
    }

    //if user doesn't exist create it
    AddUser(user);
}

std::vector<ProductInfo> Database::getProducts()
{
    return products.getElements();
}

ProductInfo Database::getProductInfo(int id)
{
    return products.search(id);
}

//Finish implementing
std::vector<CartRecord> Database::filterCustomerOrder(std::string email)
{
    std::vector<CartRecord> userOrders;
    for (int i = 0; i < pastOrders.size(); i++)
    {
        if (pastOrders[i].email == email)
            userOrders.push_back(pastOrders[i]);
    }

    return userOrders;
}

std::vector<User> Database::getAllUsers()
{
    return users;
}

std::vector<Email> Database::filterCustomerEmail(std::string email)
{
    std::vector<Email> userEmails;

    for (int i = 0; i < emails.size(); i++)
    {
        if (emails[i].recipient == email)
            userEmails.push_back(emails[i]);
    }

    return userEmails;
}

void Database::addEmail(std::string recipient, Email email)
{
    emails.push_back(email);
}

std::queue<CartRecord> Database::getUnprocessedOrders()
{

    std::queue<CartRecord> records;
    for (int i = 0; i < orders.size(); i++)
    {
        records.push(orders[i]);
    }
    orders.clear();
    return records;
}

void Database::setProcessedOrders(CartRecord order)
{
    pastOrders.push_back(order);
}

void Database::addCustomerOrder(CartRecord order)
{
    orders.push_back(order);
}

Account Database::parseAccount(std::string data)
{
    std::string email, password;

    //Get the index of the separator
    size_t seperator = data.find(':');
    email = data.substr(0, seperator - 1);
    password = data.substr(seperator + 2, data.size());

    return Account(email,password);
}

User Database::parseUser(std::string data)
{
    std::string firstName, lastName, email;

    size_t openingSeperator = 0, closingSeperator = 0;

    closingSeperator = data.find(';');
    firstName = data.substr(openingSeperator,closingSeperator);
   
    openingSeperator = closingSeperator;
    closingSeperator = data.find(';',closingSeperator + 1);
    lastName = data.substr(openingSeperator + 1,closingSeperator - openingSeperator - 1);

    openingSeperator = closingSeperator;
    closingSeperator = data.find(';',closingSeperator + 1);
    email = data.substr(openingSeperator + 1, data.size());

    return User(firstName, lastName, email);
}

ProductInfo Database::parseProductInfo(std::string data)
{
    int productId;
    std::string productName;
    float price;

    size_t openingSeperator = 0, closingSeperator = 0;
    closingSeperator = data.find(';');
    productId = std::stoi(data.substr(openingSeperator,closingSeperator));
    //std::cout << data.substr(openingSeperator, closingSeperator) << " : ";

    openingSeperator = closingSeperator;
    closingSeperator = data.find(';', closingSeperator + 1);
    productName = data.substr(openingSeperator + 1, closingSeperator - openingSeperator - 1);
    //std::cout << data.substr(openingSeperator + 1, closingSeperator - openingSeperator - 1) << " : ";

    openingSeperator = closingSeperator;
    price = std::stof(data.substr(openingSeperator + 1, data.size()));
    //std::cout << std::stof(data.substr(openingSeperator + 1, data.size())) << '\n';

    return ProductInfo(productId,productName,price);
}

//This function assumes that there will be an opening and closing sqare brackets - eg. [ 1, 20 ]
Product Database::parseProduct(std::string data)
{
    int id = 0, quantity = 0;
    
    size_t openingSeperator = data.find('[') + 1, closingSeperator = data.find(',');

    id = std::stoi(data.substr(openingSeperator, closingSeperator - 1));

    openingSeperator = closingSeperator;
    closingSeperator = data.find(']');


    quantity = std::stoi(data.substr(openingSeperator + 1, closingSeperator - openingSeperator - 1));
    //std::cout << Product(id, quantity) << '\n';

    return Product(id, quantity);
}

Cart Database::parseCart(std::string data)
{
    //Function expects that there is a : at the front of the incoming string
    size_t openingSeperator = 0, closingSeperator = data.find(';');
    Cart cart;

    while (openingSeperator != std::string::npos)
    {
        //std::cout << data.substr(openingSeperator + 1 , closingSeperator - openingSeperator - 1) << '\n';

        auto product = parseProduct(data.substr(openingSeperator + 1, closingSeperator - openingSeperator - 1));
        cart.addProduct(product);

        openingSeperator = data.find(';', openingSeperator + 1);
        closingSeperator = data.find(';', closingSeperator + 1);
    }
    return cart;
}

CartRecord Database::parseCartRecord(std::string data)
{
    size_t seperator = data.find(":");
    std::string email;
    Cart cart;

    if (seperator != std::string::npos)
    {
        email = data.substr(0, seperator);
        cart = parseCart(data.substr(seperator, data.size()));
    }
    //std::cout << CartRecord(email,cart) << '\n';
    //std::cout << data.substr(0, seperator) << '\n';
    //std::cout << data.substr(seperator, data.size()) << '\n';

    return CartRecord(email,cart);
}

Email Database::parseEmail(std::string data)
{
    std::string recipient, subject, message;

    size_t openingSeperator = 0, closingSeperator = 0;

    closingSeperator = data.find(';');
    recipient = data.substr(openingSeperator, closingSeperator);

    openingSeperator = closingSeperator;
    closingSeperator = data.find(';', closingSeperator + 1);
    subject = data.substr(openingSeperator + 1, closingSeperator - openingSeperator - 1);

    openingSeperator = closingSeperator;
    closingSeperator = data.find(';', closingSeperator + 1);
    message = data.substr(openingSeperator + 1, data.size());

    return Email(recipient, subject, message);
}
