#pragma once

#include "StackNode.h"

template <typename T>
class Stack
{
public:
	~Stack()
	{
		while (top != nullptr)
			pop();
	}

	void push(T data)
	{
		if (top == nullptr)
		{
			top = new StackNode<T>(data, nullptr);
			return;
		}

		StackNode<T>* newTop = new StackNode<T>(data, top);
		top = newTop;
	}

	T getTop()
	{
		if (top == nullptr)
			return T();

		return top->data;
	}

	void pop()
	{
		if (top == nullptr)
			return;
		
		StackNode<T>* temp = top;
		top = top->next;
		delete temp;
	}


	void print()
	{
		auto current = top;
		while (current != nullptr)
		{
			std::cout << current->data << '\n';
			std::cout << "|\n";
			std::cout << "V\n";

			current = current->next;
		}

		std::cout << "Null\n";
	}

private:
	StackNode<T>* top = nullptr;
};