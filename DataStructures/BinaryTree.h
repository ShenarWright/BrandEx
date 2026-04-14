#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "TreeNode.h"


template <typename T>
class BinaryTree
{
public:
    BinaryTree() : root(nullptr) {}

    void insert(T data)
    {
        if (root == nullptr)
        {
            root = new Node<T>(data, nullptr, nullptr);
            depth++;
        }
        else
        {
            auto current = root;
            int currentDepth = 0;

            while (current != nullptr)
            {
                if (data < current->data)
                {
                    if (current->left != nullptr)
                    {
                        current = current->left;
                        continue;
                    }
                    else
                    {
                        current->left = new Node<T>(data, nullptr, nullptr);

                        currentDepth++;
                        if (currentDepth > depth)
                            depth = currentDepth;
                        break;
                    }
                }
                else
                {
                    if (current->right != nullptr)
                    {
                        current = current->right;
                        continue;
                    }
                    else
                    {
                        current->right = new Node<T>(data, nullptr, nullptr);
                        currentDepth++;
                        if (currentDepth > depth)
                            depth = currentDepth;
                        break;
                    }
                }
            }
        }
    }

    void display()
    {
        std::queue<Node<T>*> printQueue;
        printQueue.push(root);

        std::string indent = "";
        int currentDepth = 0;

        while (!printQueue.empty())
        {
            if (printQueue.front() != nullptr)
            {
                std::cout << indent << printQueue.front()->data << '\n';

                printQueue.push(printQueue.front()->left);
                printQueue.push(printQueue.front()->right);
            }
            else
                std::cout << indent << "null" << '\n';

            printQueue.pop();

            if (currentDepth % 2 == 0)
                indent += "  ";

            currentDepth++;
        }
    }

    std::vector<T> getElements()
    {
        std::vector<T> elements;

        std::queue<Node<T>*> elementQueue;
        elementQueue.push(root);

        while (!elementQueue.empty())
        {
            if (elementQueue.front() != nullptr)
            {
                elementQueue.push(elementQueue.front()->left);
                elementQueue.push(elementQueue.front()->right);
                elements.push_back(elementQueue.front()->data);
            }

            elementQueue.pop();
        }

        return elements;
    }

    int search(std::string productName)
    {

    }

private:
    Node<T>* root;


    //Just to make stuff easier
    int depth = 0;
};

#endif // BINARYTREE_H