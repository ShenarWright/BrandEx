#ifndef PRODUCTINFO_H
#define PRODUCTINFO_H

#include <string>
#include <iostream>

struct ProductInfo
{
    int productId;
    std::string itemName;
    float price;

    ProductInfo(int ProductId, std::string ItemName, float Price) : productId(ProductId), itemName(ItemName), price(Price){}
    ProductInfo():productId(-1), itemName(), price(-1.f){}

    bool operator<(const ProductInfo& other)
    {
        return productId < other.productId;
    }

    bool operator>(const ProductInfo& other)
    {
        return productId > other.productId;
    }

    bool operator==(int id)
    {
        return id == productId;
    }

    bool operator!=(int id)
    {
        return !(*this == id);
    }
};

inline std::ostream& operator<<(std::ostream& os, ProductInfo p)
{
    os << p.productId << " : " << p.itemName;
    return os;
}

#endif //PRODUCTINFO_H