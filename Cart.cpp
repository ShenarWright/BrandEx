#include "Cart.h"

void Cart::addProduct(int productId, int quantity)
{
	bool found = false;
	//Finds the product being added and increments it
	for (int i = 0; i < products.size();i++)
	{
		if (products[i].id == productId)
		{
			found = true;
			products[i].quantity =  quantity;
		}
	}

	//if not found adds it to the list
	if (!found && productId > 0)
		products.push_back({ productId,quantity });
}

void Cart::addProduct(Product p)
{
	addProduct(p.id, p.quantity);
}

Product Cart::getProduct(int productId)
{
	for (int i = 0; i < products.size(); i++)
	{
		if (products[i].id == productId)
			return products[i];
	}
	return Product(-1,-1);
}

void Cart::removeProduct(int productId)
{
	for (int i = 0; i < products.size(); i++)
	{
		if (products[i].id == productId)
		{
			products.erase(products.begin() + i);
		}
	}
}

bool Cart::isEmpty()
{
	return products.empty();
}

std::vector<Product> Cart::getAllProducts()
{
	return products;
}

void Cart::emptyCart()
{
	products.clear();
}
