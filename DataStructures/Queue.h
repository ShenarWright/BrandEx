#ifndef QUEUE_H
#define QUEUE_H

#include "LinkNode.h"

template <typename T>
class Queue
{
public:
	~Queue()
	{
		while (last != nullptr)
			pop();
	}

	void push(T data)
	{
		if (last == nullptr)
		{
			last = new LinkNode<T>(data, nullptr);
			first = last;
			numElements++;
			return;
		}

		auto newNode = new LinkNode<T>(data, last);
		last = newNode;
		numElements++;
	}

	//Traverse from back to front
	void pop()
	{
		//Queue is empty
		if (last == nullptr)
			return;
		if (last->next == nullptr)
		{
			numElements--;
			delete last;
			last = nullptr;
			return;
		}

		auto current = last;
		LinkNode<T>* previous = nullptr;

		//Gets the element at the front
		while (current->next != nullptr)
		{
			previous = current;
			current = current->next;
		}

		delete current;
		previous->next = nullptr;

		first = previous;
		numElements--;
	}

	T front()
	{
		return first->data;
	}

	T back()
	{
		return last->data;
	}

	bool hasElement(T data)
	{
	
		auto current = last;

		while (current != nullptr)
		{
			if (current->data == data)
				return true;

			current = current->next;
		}
		return false;
	}

	int size()
	{
		return numElements;
	}

	//For convenience
	T operator[](int index)
	{
		if (index >= size())
			return T();

		int convertedIndex = 0;
		auto current = last;

		//We store this from back to front so we have to minus the index from the size to get the correct index
		while (convertedIndex != (size() - index - 1))
		{
			current = current->next;
			convertedIndex++;
		}

		return current->data;
	}

private:
	LinkNode<T>* last = nullptr;
	//Keep a copy of the first value at all time
	LinkNode<T>* first = nullptr;
	
	//keep track of the size
	int numElements = 0;
};

#endif // !QUEUE_H
