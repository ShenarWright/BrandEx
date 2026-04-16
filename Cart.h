#ifndef CART_H
#define CART_H

#include <iostream>
#include <vector>

#include "Product.h"

class Cart
{
public:
    void addProduct(int productId, int quantity);
    void addProduct(Product p);
    Product getProduct(int productId);
    void removeProduct(int productId);

    bool isEmpty();

    std::vector<Product> getAllProducts();
    void emptyCart();

    Cart(){}
    
private:
    std::vector<Product> products;
};

inline std::ostream& operator<<(std::ostream& os, std::vector<Product> vec)
{
    if (!vec.empty())
    {
        os << "[" << vec[0];
        for (int i = 1; i < vec.size(); i++)
        {
            os << " , " << vec[i];
        }
        os << "]";

    }
        return os;
}

inline std::ostream& operator<<(std::ostream& os, Cart& cart)
{
    os << cart.getAllProducts();
    return os;
}

#endif //CART_H