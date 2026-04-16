#include "ActionManager.h"

void ActionManager::pushAction(Action action)
{
	undoActions.push(action);
}

void ActionManager::redoAction(User& currentUser)
{
	Action currentAction = redoActions.getTop();
	redoActions.pop();
	switch (currentAction.type)
	{
		case Action::REMOVEITEM: break;
		case Action::CHANGEQUANTITY: break;

	}
}

void ActionManager::undoAction(User& currentUser)
{
	Action currentAction = undoActions.getTop();
	redoActions.push(currentAction);
	

	switch (currentAction.type)
	{
	//If the customer removed an item we add it back
	case Action::REMOVEITEM: 
		currentUser.cart.addProduct(currentAction.product);
		break;
	case Action::CHANGEQUANTITY: 
		currentUser.cart.addProduct(currentAction.product);
		break;
	}
}

//Reiniializeds the stacks so that it cleans up old information
void ActionManager::reset()
{
	undoActions = Stack<Action>();
	redoActions = Stack<Action>();
}

ActionManager& ActionManager::GetInstance()
{
	static ActionManager manager;
	return manager;
}