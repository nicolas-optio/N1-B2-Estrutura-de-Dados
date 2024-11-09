// ArvoreAVL.h
#ifndef ARVOREAVL_H
#define ARVOREAVL_H

#include "NodoAVL.h"
#include <vector>
#include <string>

class ArvoreAVL {
private:
    NodoAVL* raiz;

    // Métodos auxiliares
    int altura(NodoAVL* nodo);
    int fatorBalanceamento(NodoAVL* nodo);
    void atualizarAltura(NodoAVL* nodo);

    NodoAVL* rotacaoEsquerda(NodoAVL* nodo);
    NodoAVL* rotacaoDireita(NodoAVL* nodo);
    NodoAVL* balancear(NodoAVL* nodo);

    NodoAVL* inserir(NodoAVL* nodo, const Contato& contato);
    NodoAVL* remover(NodoAVL* nodo, const std::string& nome);
    NodoAVL* minimoValorNodo(NodoAVL* nodo);
    NodoAVL* buscar(NodoAVL* nodo, const std::string& nome);

    void inOrder(NodoAVL* nodo, std::vector<Contato>& contatos);
    void listarFavoritos(NodoAVL* nodo, std::vector<Contato>& favoritos);

public:
    // Construtor
    ArvoreAVL();

    // Métodos públicos
    void inserir(const Contato& contato);
    void remover(const std::string& nome);
    Contato* buscar(const std::string& nome);
    std::vector<Contato> listarContatos();
    std::vector<Contato> listarFavoritos();

    // Importação e Exportação
    void importarCSV(const std::string& nomeArquivo);
    void exportarCSV(const std::string& nomeArquivo);

    // Destrutor
    ~ArvoreAVL();
    void destruirArvore(NodoAVL* nodo);
};

#endif // ARVOREAVL_H
