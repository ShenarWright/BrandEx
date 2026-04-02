#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>


struct Product
{
    int id;
    int quantity;

    Product(int productId, int productQuantity) : id(productId), quantity(productQuantity){}
    Product() : id(-1), quantity(-1){}
};

inline std::ostream& operator <<(std::ostream& os, Product prod)
{
    os << "id: " << prod.id << " quantity: " << prod.quantity;
    return os;
}

#endif // PRODUCT_H