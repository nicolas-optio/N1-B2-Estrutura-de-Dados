// NodoAVL.h
#ifndef NODOAVL_H
#define NODOAVL_H

#include "Contato.h"

class NodoAVL {
public:
    Contato contato;
    NodoAVL* esquerda;
    NodoAVL* direita;
    int altura;

    // Construtor
    NodoAVL(const Contato& contato);
};

#endif // NODOAVL_H
