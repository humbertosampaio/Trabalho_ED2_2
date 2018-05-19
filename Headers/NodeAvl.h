//
// Created by viniman on 5/19/18.
//

#ifndef TRABALHO_ED2_2_NODEAVL_H
#define TRABALHO_ED2_2_NODEAVL_H

class NodeAvl
{
public:
    explicit NodeAvl(int &val) 
    { 
        chave = val;
        altura = 1;
        esq = nullptr;
        dir  = nullptr;
    }
    virtual ~NodeAvl() = default;
    int getAltura()
    {
        if(this == nullptr)
            return 0;
        else
            return altura;
    }
    NodeAvl* getEsq() { return  esq; }
    NodeAvl* getDir() { return  dir; }
    int getChave() { return chave; }
    void setAltura(int altura) { this->altura = altura; }
    void setEsq(NodeAvl *no) { esq = no; }
    void setDir(NodeAvl *no) { dir = no; }
    void setChave(int val) { chave = val; }


private:
    NodeAvl *esq;
    NodeAvl *dir;
    int chave;
    int altura;

};

#endif //TRABALHO_ED2_2_NODEAVL_H
