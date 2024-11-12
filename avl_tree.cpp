#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include "Contact.cpp"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

class NoAVL {
public:
    Contato contato;
    NoAVL* esquerda;
    NoAVL* direita;
    int altura;

    NoAVL(Contato contato) : contato(contato) {
        esquerda = direita = nullptr;
        altura = 1;
    }
};

class ArvoreAVL {
private:
    NoAVL* raiz;

    // Funções auxiliares existentes (getAltura, getFatorBalanceamento, rotacoes, inserir) permanecem iguais...

    int getAltura(NoAVL* no) {
        if (no == nullptr) return 0;
        return no->altura;
    }

    int getFatorBalanceamento(NoAVL* no) {
        if (no == nullptr) return 0;
        return getAltura(no->esquerda) - getAltura(no->direita);
    }

    NoAVL* rotacaoDireita(NoAVL* y) {
        NoAVL* x = y->esquerda;
        NoAVL* T2 = x->direita;

        x->direita = y;
        y->esquerda = T2;

        y->altura = std::max(getAltura(y->esquerda), getAltura(y->direita)) + 1;
        x->altura = std::max(getAltura(x->esquerda), getAltura(x->direita)) + 1;

        return x;
    }

    NoAVL* rotacaoEsquerda(NoAVL* x) {
        NoAVL* y = x->direita;
        NoAVL* T2 = y->esquerda;

        y->esquerda = x;
        x->direita = T2;

        x->altura = std::max(getAltura(x->esquerda), getAltura(x->direita)) + 1;
        y->altura = std::max(getAltura(y->esquerda), getAltura(y->direita)) + 1;

        return y;
    }

    NoAVL* inserir(NoAVL* no, Contato contato) {
        if (no == nullptr)
            return new NoAVL(contato);

        if (contato.getNome() < no->contato.getNome())
            no->esquerda = inserir(no->esquerda, contato);
        else if (contato.getNome() > no->contato.getNome())
            no->direita = inserir(no->direita, contato);
        else
            return no;

        no->altura = std::max(getAltura(no->esquerda), getAltura(no->direita)) + 1;

        int fb = getFatorBalanceamento(no);

        // Rotações
        if (fb > 1 && contato.getNome() < no->esquerda->contato.getNome())
            return rotacaoDireita(no);

        if (fb < -1 && contato.getNome() > no->direita->contato.getNome())
            return rotacaoEsquerda(no);

        if (fb > 1 && contato.getNome() > no->esquerda->contato.getNome()) {
            no->esquerda = rotacaoEsquerda(no->esquerda);
            return rotacaoDireita(no);
        }

        if (fb < -1 && contato.getNome() < no->direita->contato.getNome()) {
            no->direita = rotacaoDireita(no->direita);
            return rotacaoEsquerda(no);
        }

        return no;
    }

    NoAVL* menorValorNo(NoAVL* no) {
        NoAVL* atual = no;

        while (atual->esquerda != nullptr)
            atual = atual->esquerda;

        return atual;
    }

    NoAVL* remover(NoAVL* raiz, string nome) {
        if (raiz == nullptr)
            return raiz;

        if (nome < raiz->contato.getNome())
            raiz->esquerda = remover(raiz->esquerda, nome);
        else if (nome > raiz->contato.getNome())
            raiz->direita = remover(raiz->direita, nome);
        else {
            if ((raiz->esquerda == nullptr) || (raiz->direita == nullptr)) {
                NoAVL* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

                if (temp == nullptr) {
                    temp = raiz;
                    raiz = nullptr;
                } else
                    *raiz = *temp;

                delete temp;
            } else {
                NoAVL* temp = menorValorNo(raiz->direita);
                raiz->contato = temp->contato;
                raiz->direita = remover(raiz->direita, temp->contato.getNome());
            }
        }

        if (raiz == nullptr)
            return raiz;

        raiz->altura = 1 + std::max(getAltura(raiz->esquerda), getAltura(raiz->direita));

        int fb = getFatorBalanceamento(raiz);

        // Rotação LL
        if (fb > 1 && getFatorBalanceamento(raiz->esquerda) >= 0)
            return rotacaoDireita(raiz);

        // Rotação LR
        if (fb > 1 && getFatorBalanceamento(raiz->esquerda) < 0) {
            raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
            return rotacaoDireita(raiz);
        }

        // Rotação RR
        if (fb < -1 && getFatorBalanceamento(raiz->direita) <= 0)
            return rotacaoEsquerda(raiz);

        // Rotação RL
        if (fb < -1 && getFatorBalanceamento(raiz->direita) > 0) {
            raiz->direita = rotacaoDireita(raiz->direita);
            return rotacaoEsquerda(raiz);
        }

        return raiz;
    }

    NoAVL* buscar(NoAVL* no, string nome) {
        if (no == nullptr || no->contato.getNome() == nome)
            return no;

        if (nome < no->contato.getNome())
            return buscar(no->esquerda, nome);
        else
            return buscar(no->direita, nome);
    }

    void emOrdem(NoAVL* no) {
        if (no != nullptr) {
            emOrdem(no->esquerda);
            cout << "Nome: " << no->contato.nome << ", Telefone: " << no->contato.telefone << ", Email: " << no->contato.email << ", Favorito: " << (no->contato.favorito ? "Sim" : "Não") << endl;
            emOrdem(no->direita);
        }
    }

    void listarFavoritos(NoAVL* no) {
        if (no != nullptr) {
            listarFavoritos(no->esquerda);
            if (no->contato.favorito) {
                cout << "Nome: " << no->contato.nome << ", Telefone: " << no->contato.telefone << ", Email: " << no->contato.email << endl;
            }
            listarFavoritos(no->direita);
        }
    }

    void exportarCSV(NoAVL* no, ofstream& arquivo) {
        if (no != nullptr) {
            exportarCSV(no->esquerda, arquivo);
            arquivo << no->contato.nome << "," << no->contato.telefone << "," << no->contato.email << "," << no->contato.favorito << endl;
            exportarCSV(no->direita, arquivo);
        }
    }

    void obterContatos(NoAVL* no, vector<Contato>& contatos) {
        if (no != nullptr) {
            obterContatos(no->esquerda, contatos);
            contatos.push_back(no->contato);
            obterContatos(no->direita, contatos);
        }
    }

    void marcarDesmarcarFavorito(NoAVL* no, string nome) {
        NoAVL* encontrado = buscar(no, nome);
        if (encontrado != nullptr) {
            encontrado->contato.favorito = !encontrado->contato.favorito;
            cout << "Contato " << (encontrado->contato.favorito ? "marcado" : "desmarcado") << " como favorito.\n";
        } else {
            cout << "Contato não encontrado.\n";
        }
    }

public:
    ArvoreAVL() : raiz(nullptr) {}

    void inserirContato(Contato contato) {
        raiz = inserir(raiz, contato);
    }

    void removerContato(string nome) {
        raiz = remover(raiz, nome);
    }

    Contato* buscarContato(string nome) {
        NoAVL* resultado = buscar(raiz, nome);
        if (resultado != nullptr)
            return &(resultado->contato);
        else
            return nullptr;
    }

    void listarContatos() {
        if (raiz == nullptr)
            cout << "Nenhum contato cadastrado.\n";
        else
            emOrdem(raiz);
    }

    void listarFavoritos() {
        if (raiz == nullptr)
            cout << "Nenhum contato cadastrado.\n";
        else
            listarFavoritos(raiz);
    }

    void exportarContatos(string caminho) {
        ofstream arquivo(caminho);
        if (arquivo.is_open()) {
            exportarCSV(raiz, arquivo);
            arquivo.close();
            cout << "Contatos exportados com sucesso!\n";
        } else {
            cout << "Erro ao abrir o arquivo.\n";
        }
    }

    void importarContatos(string caminho) {
        ifstream arquivo(caminho);
        if (arquivo.is_open()) {
            string linha;
            while (getline(arquivo, linha)) {
                size_t pos = 0;
                string token;
                vector<string> campos;
                while ((pos = linha.find(',')) != string::npos) {
                    token = linha.substr(0, pos);
                    campos.push_back(token);
                    linha.erase(0, pos + 1);
                }
                campos.push_back(linha); // último campo

                if (campos.size() == 4) {
                    string nome = campos[0];
                    string telefone = campos[1];
                    string email = campos[2];
                    bool favorito = campos[3] == "1";
                    Contato contato(nome, telefone, email, favorito);
                    inserirContato(contato);
                }
            }
            arquivo.close();
            cout << "Contatos importados com sucesso!\n";
        } else {
            cout << "Erro ao abrir o arquivo.\n";
        }
    }

    void marcarDesmarcarFavorito(string nome) {
        marcarDesmarcarFavorito(raiz, nome);
    }
};

#endif