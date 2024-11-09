// NodoAVL.cpp
#include "NodoAVL.h"

NodoAVL::NodoAVL(const Contato& contato)
    : contato(contato), esquerda(nullptr), direita(nullptr), altura(1) {}
