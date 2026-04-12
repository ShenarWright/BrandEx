#include "ActionManager.h"

void ActionManager::pushAction(Action action)
{
	undoActions.push(action);
}

void ActionManager::redoAction()
{
	Action currentAction = redoActions.getTop();
	switch (currentAction.type)
	{
		case Action::AddItem: break;
		case Action::RemoveItem: break;

	}
}

void ActionManager::undoAction()
{
	Action currentAction = undoActions.getTop();
	switch (currentAction.type)
	{
	case Action::AddItem: break;
	case Action::RemoveItem: break;

	}
}
