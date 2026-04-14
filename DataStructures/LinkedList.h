#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "LinkNode.h"

#include <iostream>
#include <string>

template <typename T>
class LinkedList
{
public:
	LinkedList() :
		head(nullptr)
	{
		std::cout << "Constructor";
	}

	~LinkedList()
	{
		auto current = head;

		while (current != nullptr)
		{
			auto prev = current;
			current = current->next;

			delete prev;
		}
	}

	void insert(T data)
	{
		//Check if the head is null
		if (head == nullptr)
		{
			head = new LinkNode<T>(data,nullptr);
			return;
		}

		auto current = head->next;
		LinkNode<T>* prev = head;



		while (current != nullptr)
		{
			if (data.age >= current->data.age)
			{
				auto newNode = new LinkNode<T>(data,nullptr);
				prev->next = newNode;
				newNode->next = current;
				return;
			}

			current = current->next;
			prev = current;
		}

		current = new LinkNode<T>(data, nullptr);
		prev->next = current;
	}
	void remove(const std::string name)
	{
		if (head == nullptr)
			return;

		auto current = head->next;
		LinkNode<T>* prev = head;

		//If head is the one being deleted
		if (head->data.firstName == name)
		{
			prev = head;
			head = head->next;

			delete prev;
			return;
		}

		while (current != nullptr)
		{
			if (current->data.firstName == name)
			{
				auto temp = current;
				current = current->next;
				prev->next = current;

				delete temp;
			}

			prev = current;
			current = current->next;
		}
	}
	/*void display()
	{
		auto current = head;

		while (current != nullptr)
		{
			current->data.display();
			std::cout << "------------------>";
			current = current->next;
		}
	}*/

private:
	LinkNode<T>* head;
};


#endif // !LINKEDLIST_H
