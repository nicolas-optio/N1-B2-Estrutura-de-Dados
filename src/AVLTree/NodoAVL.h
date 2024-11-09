// NodoAVL.h
#ifndef NODOAVL_H
#define NODOAVL_H

#include "Contact.h" // Alterado de "Contato.h" para "Contact.h"

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
