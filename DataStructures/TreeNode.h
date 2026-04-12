#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <queue>

template <typename T>
struct Node
{
    Node(T nodeData, Node* leftNode, Node* rightNode) : data(nodeData), left(leftNode), right(rightNode) {};

    T data;
    Node* left;
    Node* right;
};

#endif