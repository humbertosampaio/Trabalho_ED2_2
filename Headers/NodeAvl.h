//
// Created by viniman on 5/19/18.
//

#ifndef TRABALHO_ED2_2_NODEAVL_H
#define TRABALHO_ED2_2_NODEAVL_H

#include "../Source/Node.cpp"

template <class T> class NodeAvl : public Node<T>
{
public:
    explicit NodeAvl(T &val):Node<T>(val)
    {
    }
    virtual ~NodeAvl() = default;
    int getAltura()
    {
        if(this == nullptr)
            return 0;
        else
            return height;
    }
    void setHeight(int height)
    {
        this->height = height;
    }
    int getHeight()
    {
        return this->height;
    }
    NodeAvl<T> *getRight()
    {
        return (NodeAvl<T>*)this->right;
    }
    NodeAvl<T> *getLeft()
    {
        return (NodeAvl<T>*)this->left;
    }

public:
    int height;
};

#endif //TRABALHO_ED2_2_NODEAVL_H
