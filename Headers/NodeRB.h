//
// Created by edson on 24/05/18.
//

#ifndef ARVORES_ED2_RBNODE_H
#define ARVORES_ED2_RBNODE_H


template <class T> class NodeRB {
protected:
    T value;
    NodeRB<T>* right;
    NodeRB<T>* left;
    NodeRB<T>* parent;
    bool red; // true se o no eh vermelho, false preto
public:
    NodeRB<T>(){};
    NodeRB<T>(T value);
    T getValue();
    void setValue(T value);

    NodeRB<T> *getRight() const;
    NodeRB<T> *getLeft() const;
    void setRight(NodeRB<T>* right);
    void setLeft(NodeRB<T>* left);
    NodeRB<T> *getParent() const;
    void setParent(NodeRB<T> *parent);
    bool isRed() const;
    void setRed(bool red);
};


#endif //ARVORES_ED2_RBNODE_H
