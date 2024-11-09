// testes.cpp
#include "ArvoreAVL.h"
#include <cassert>

void testeInsercao() {
    ArvoreAVL arvore;
    Contato c1("Alice", "123", "alice@example.com");
    Contato c2("Bob", "456", "bob@example.com");
    Contato c3("Charlie", "789", "charlie@example.com");

    arvore.inserir(c1);
    arvore.inserir(c2);
    arvore.inserir(c3);

    assert(arvore.buscar("Alice") != nullptr);
    assert(arvore.buscar("Bob") != nullptr);
    assert(arvore.buscar("Charlie") != nullptr);
}

int main() {
    testeInsercao();
    std::cout << "Todos os testes passaram!\n";
    return 0;
}
