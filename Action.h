#ifndef ACTION_H
#define ACTION_H

class Action
{
public:

	enum Type
	{
		RemoveItem = 0,
		AddItem
	};
	Type type;

	union value
	{
		float price;

	};
};

#endif //ACTION_H