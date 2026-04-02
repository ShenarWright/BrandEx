#ifndef CARTRECORD_H
#define CARTRECORD_H

#include <string>

#include "Cart.h"

struct CartRecord
{
	CartRecord(std::string Email, Cart cart):email(Email), cartInfo(cart){}

	std::string email;
	Cart cartInfo;
};

inline std::ostream& operator<<(std::ostream& os, CartRecord record)
{
	os << record.email << " : " << record.cartInfo;
	return os;
}

#endif //CARTRECORD_H