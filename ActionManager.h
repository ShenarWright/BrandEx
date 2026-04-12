#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include "Action.h"
#include "DataStructures/Stack.h"


class ActionManager
{
public:
	void pushAction(Action action);
	void redoAction();
	void undoAction();
private:
	Stack<Action> undoActions;
	Stack<Action> redoActions;
};

#endif