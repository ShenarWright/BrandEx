#ifndef STACKNODE_H
#define STACKNODE_H

#include <iostream>

template <typename T>
struct StackNode
{
	StackNode(T value, StackNode* nextNode): data(value), next(nextNode)
	{}

	T data;
	StackNode* next = nullptr;
};

#endif