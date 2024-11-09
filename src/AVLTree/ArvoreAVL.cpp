// ArvoreAVL.cpp
#include "ArvoreAVL.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

// Construtor
ArvoreAVL::ArvoreAVL() : raiz(nullptr) {}

// Destrutor
ArvoreAVL::~ArvoreAVL() {
    destruirArvore(raiz);
}

void ArvoreAVL::destruirArvore(NodoAVL* nodo) {
    if (nodo != nullptr) {
        destruirArvore(nodo->esquerda);
        destruirArvore(nodo->direita);
        delete nodo;
    }
}

// Métodos auxiliares
int ArvoreAVL::altura(NodoAVL* nodo) {
    return nodo ? nodo->altura : 0;
}

int ArvoreAVL::fatorBalanceamento(NodoAVL* nodo) {
    return nodo ? altura(nodo->esquerda) - altura(nodo->direita) : 0;
}

void ArvoreAVL::atualizarAltura(NodoAVL* nodo) {
    nodo->altura = 1 + std::max(altura(nodo->esquerda), altura(nodo->direita));
}

NodoAVL* ArvoreAVL::rotacaoDireita(NodoAVL* y) {
    NodoAVL* x = y->esquerda;
    NodoAVL* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    atualizarAltura(y);
    atualizarAltura(x);

    return x;
}

NodoAVL* ArvoreAVL::rotacaoEsquerda(NodoAVL* x) {
    NodoAVL* y = x->direita;
    NodoAVL* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    atualizarAltura(x);
    atualizarAltura(y);

    return y;
}

NodoAVL* ArvoreAVL::balancear(NodoAVL* nodo) {
    atualizarAltura(nodo);

    int fb = fatorBalanceamento(nodo);

    // Esquerda Esquerda
    if (fb > 1 && fatorBalanceamento(nodo->esquerda) >= 0)
        return rotacaoDireita(nodo);

    // Esquerda Direita
    if (fb > 1 && fatorBalanceamento(nodo->esquerda) < 0) {
        nodo->esquerda = rotacaoEsquerda(nodo->esquerda);
        return rotacaoDireita(nodo);
    }

    // Direita Direita
    if (fb < -1 && fatorBalanceamento(nodo->direita) <= 0)
        return rotacaoEsquerda(nodo);

    // Direita Esquerda
    if (fb < -1 && fatorBalanceamento(nodo->direita) > 0) {
        nodo->direita = rotacaoDireita(nodo->direita);
        return rotacaoEsquerda(nodo);
    }

    return nodo;
}

// Inserção
void ArvoreAVL::inserir(const Contato& contato) {
    raiz = inserir(raiz, contato);
}

NodoAVL* ArvoreAVL::inserir(NodoAVL* nodo, const Contato& contato) {
    if (nodo == nullptr)
        return new NodoAVL(contato);

    if (contato < nodo->contato)
        nodo->esquerda = inserir(nodo->esquerda, contato);
    else if (contato > nodo->contato)
        nodo->direita = inserir(nodo->direita, contato);
    else
        return nodo; // Contato já existe

    return balancear(nodo);
}

// Remoção
void ArvoreAVL::remover(const std::string& nome) {
    raiz = remover(raiz, nome);
}

NodoAVL* ArvoreAVL::remover(NodoAVL* nodo, const std::string& nome) {
    if (nodo == nullptr)
        return nodo;

    if (nome < nodo->contato.getNome())
        nodo->esquerda = remover(nodo->esquerda, nome);
    else if (nome > nodo->contato.getNome())
        nodo->direita = remover(nodo->direita, nome);
    else {
        // Nodo com um ou nenhum filho
        if ((nodo->esquerda == nullptr) || (nodo->direita == nullptr)) {
            NodoAVL* temp = nodo->esquerda ? nodo->esquerda : nodo->direita;

            if (temp == nullptr) {
                temp = nodo;
                nodo = nullptr;
            } else
                *nodo = *temp;

            delete temp;
        } else {
            // Nodo com dois filhos
            NodoAVL* temp = minimoValorNodo(nodo->direita);
            nodo->contato = temp->contato;
            nodo->direita = remover(nodo->direita, temp->contato.getNome());
        }
    }

    if (nodo == nullptr)
        return nodo;

    return balancear(nodo);
}

NodoAVL* ArvoreAVL::minimoValorNodo(NodoAVL* nodo) {
    NodoAVL* atual = nodo;

    while (atual->esquerda != nullptr)
        atual = atual->esquerda;

    return atual;
}

// Busca
Contato* ArvoreAVL::buscar(const std::string& nome) {
    NodoAVL* resultado = buscar(raiz, nome);
    if (resultado)
        return &resultado->contato;
    else
        return nullptr;
}

NodoAVL* ArvoreAVL::buscar(NodoAVL* nodo, const std::string& nome) {
    if (nodo == nullptr || nodo->contato.getNome() == nome)
        return nodo;

    if (nome < nodo->contato.getNome())
        return buscar(nodo->esquerda, nome);
    else
        return buscar(nodo->direita, nome);
}

// Listar Contatos em ordem alfabética
std::vector<Contato> ArvoreAVL::listarContatos() {
    std::vector<Contato> contatos;
    inOrder(raiz, contatos);
    return contatos;
}

void ArvoreAVL::inOrder(NodoAVL* nodo, std::vector<Contato>& contatos) {
    if (nodo != nullptr) {
        inOrder(nodo->esquerda, contatos);
        contatos.push_back(nodo->contato);
        inOrder(nodo->direita, contatos);
    }
}

// Listar Favoritos
std::vector<Contato> ArvoreAVL::listarFavoritos() {
    std::vector<Contato> favoritos;
    listarFavoritos(raiz, favoritos);
    return favoritos;
}

void ArvoreAVL::listarFavoritos(NodoAVL* nodo, std::vector<Contato>& favoritos) {
    if (nodo != nullptr) {
        listarFavoritos(nodo->esquerda, favoritos);
        if (nodo->contato.isFavorito())
            favoritos.push_back(nodo->contato);
        listarFavoritos(nodo->direita, favoritos);
    }
}

// Importar contatos de um arquivo CSV
void ArvoreAVL::importarCSV(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    std::string linha;

    if (!arquivo.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo: " << nomeArquivo << std::endl;
        return;
    }

    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string nome, telefone, email, favoritoStr;
        bool favorito = false;

        std::getline(ss, nome, ',');
        std::getline(ss, telefone, ',');
        std::getline(ss, email, ',');
        std::getline(ss, favoritoStr, ',');

        if (favoritoStr == "1")
            favorito = true;

        if (!nome.empty()) {
            Contato contato(nome, telefone, email, favorito);
            inserir(contato);
        }
    }

    arquivo.close();
}

// Exportar contatos para um arquivo CSV
void ArvoreAVL::exportarCSV(const std::string& nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Não foi possível criar o arquivo: " << nomeArquivo << std::endl;
        return;
    }

    std::vector<Contato> contatos = listarContatos();

    for (const auto& contato : contatos) {
        arquivo << contato.getNome() << ","
                << contato.getTelefone() << ","
                << contato.getEmail() << ","
                << (contato.isFavorito() ? "1" : "0") << std::endl;
    }

    arquivo.close();
}
