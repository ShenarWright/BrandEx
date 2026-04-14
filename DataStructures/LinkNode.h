#ifndef  LINKNODE_H
#define LINKNODE_H


template <typename T>
struct LinkNode
{
	LinkNode(T value, LinkNode* nextNode) : data(value), next(nextNode) {}

	T data;
	LinkNode* next;
};

#endif // ! LINKNODE_H

