//
// Created by edson on 15/05/18.
//

#ifndef TREES_NODE_H
#define TREES_NODE_H

#include <iostream>

using namespace std;

template <class T> class Node {
private:
    T data;
    Node* right;
    Node* left;
    unsigned int height;
public:
    void test ()
    {
        cout << data;
    }

    Node<T>(T data)
    {
        this->data = data;
        this->right = nullptr;
        this->left = nullptr;
        this->height = 0;
    }
};
#endif //TREES_NODE_H
