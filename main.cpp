#include <iostream>
#include <string>
#include <fstream>
#include "contato.cpp"
#include "avl_tree.cpp"

using namespace std;

void exibirMenu() {
    cout << "\n=== Sistema de Gerenciamento de Contatos ===\n";
    cout << "1. Adicionar novo contato\n";
    cout << "2. Remover contato\n";
    cout << "3. Buscar contato\n";
    cout << "4. Listar todos os contatos\n";
    cout << "5. Listar favoritos\n";
    cout << "6. Importar contatos (CSV)\n";
    cout << "7. Exportar contatos (CSV)\n";
    cout << "8. Marcar/Desmarcar favorito\n";
    cout << "0. Sair\n";
    cout << "Escolha uma opção: ";
}

int main() {
    ArvoreAVL arvore;
    int opcao;

    do {
        exibirMenu();
        cin >> opcao;
        cin.ignore();

        switch(opcao) {
            case 1: {
                string nome, telefone, email;
                cout << "Nome: ";
                getline(cin, nome);
                cout << "Telefone: ";
                getline(cin, telefone);
                cout << "Email: ";
                getline(cin, email);
                bool favorito;
                cout << "Favorito (1 para favorito, 0 para não favorito): ";
                cin >> favorito;
                cin.ignore();
                Contato novoContato(nome, telefone, email, favorito);
                arvore.inserirContato(novoContato);
                cout << "Contato adicionado com sucesso!\n";
                break;
            }
            case 2: {
                string nome;
                cout << "Nome do contato a ser removido: ";
                getline(cin, nome);
                arvore.removerContato(nome);
                cout << "Contato removido (se existia).\n";
                break;
            }
            case 3: {
                string nome;
                cout << "Nome do contato a buscar: ";
                getline(cin, nome);
                Contato* contato = arvore.buscarContato(nome);
                if (contato != nullptr) {
                    cout << "Nome: " << contato->nome << ", Telefone: " << contato->telefone << ", Email: " << contato->email << ", Favorito: " << (contato->favorito ? "Sim" : "Não") << endl;
                } else {
                    cout << "Contato não encontrado.\n";
                }
                break;
            }
            case 4: {
                cout << "\nLista de contatos em ordem alfabética:\n";
                arvore.listarContatos();
                break;
            }
            case 5: {
                cout << "\nLista de contatos favoritos:\n";
                arvore.listarFavoritos();
                break;
            }
            case 6: {
                string caminho;
                cout << "Informe o caminho do arquivo CSV para importar: ";
                getline(cin, caminho);
                arvore.importarContatos(caminho);
                break;
            }
            case 7: {
                string caminho;
                cout << "Informe o caminho do arquivo CSV para exportar: ";
                getline(cin, caminho);
                arvore.exportarContatos(caminho);
                break;
            }
            case 8: {
                string nome;
                cout << "Nome do contato para marcar/desmarcar como favorito: ";
                getline(cin, nome);
                arvore.marcarDesmarcarFavorito(nome);
                break;
            }
            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção inválida!\n";
        }
    } while (opcao != 0);

    return 0;
}