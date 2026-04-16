#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include "Action.h"
#include "DataStructures/Stack.h"

#include "User.h"


class ActionManager
{
public:
	void pushAction(Action action);

	//Takes the user by reference so that it can modify it directly
	void redoAction(User& currentUser);

	//Takes the user by reference so that it can modify it directly
	void undoAction(User& currentUser);

	void reset();

	static ActionManager& GetInstance();
private:
	Stack<Action> undoActions;
	Stack<Action> redoActions;
};

#endif