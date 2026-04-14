#ifndef ACTION_H
#define ACTION_H

class Action
{
public:

	enum ActionType
	{
		RemoveItem = 0,
		AddItem
	};
	ActionType type;

	union value
	{
		float price;

	};
};

#endif //ACTION_H