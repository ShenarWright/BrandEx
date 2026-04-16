#ifndef ACTION_H
#define ACTION_H

#include "Product.h"

class Action
{
public:

	enum ActionType
	{
		REMOVEITEM = 0,
		CHANGEQUANTITY
	};
	ActionType type;

	Product product;
};

#endif //ACTION_H