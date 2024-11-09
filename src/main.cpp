// main.cpp
#include <iostream>
#include "ArvoreAVL.h"

void exibirMenu() {
    std::cout << "==== Gerenciador de Contatos ====\n";
    std::cout << "1. Adicionar novo contato\n";
    std::cout << "2. Remover contato\n";
    std::cout << "3. Buscar contato\n";
    std::cout << "4. Listar todos os contatos\n";
    std::cout << "5. Listar favoritos\n";
    std::cout << "6. Marcar/Desmarcar favorito\n";
    std::cout << "7. Importar contatos (CSV)\n";
    std::cout << "8. Exportar contatos (CSV)\n";
    std::cout << "0. Sair\n";
    std::cout << "Escolha uma opção: ";
}

int main() {
    ArvoreAVL agenda;
    int opcao;

    do {
        exibirMenu();
        std::cin >> opcao;
        std::cin.ignore(); // Limpar o buffer

        switch (opcao) {
            case 1: {
                // Adicionar novo contato
                std::string nome, telefone, email;
                std::cout << "Nome: ";
                std::getline(std::cin, nome);
                std::cout << "Telefone: ";
                std::getline(std::cin, telefone);
                std::cout << "Email: ";
                std::getline(std::cin, email);

                Contato novoContato(nome, telefone, email);
                agenda.inserir(novoContato);

                std::cout << "Contato adicionado com sucesso!\n";
                break;
            }
            case 2: {
                // Remover contato
                std::string nome;
                std::cout << "Nome do contato a remover: ";
                std::getline(std::cin, nome);

                agenda.remover(nome);
                std::cout << "Contato removido (se existia).\n";
                break;
            }
            case 3: {
                // Buscar contato
                std::string nome;
                std::cout << "Nome do contato a buscar: ";
                std::getline(std::cin, nome);

                Contato* contato = agenda.buscar(nome);
                if (contato) {
                    std::cout << "Nome: " << contato->getNome() << "\n";
                    std::cout << "Telefone: " << contato->getTelefone() << "\n";
                    std::cout << "Email: " << contato->getEmail() << "\n";
                    std::cout << "Favorito: " << (contato->isFavorito() ? "Sim" : "Não") << "\n";
                } else {
                    std::cout << "Contato não encontrado.\n";
                }
                break;
            }
            case 4: {
                // Listar todos os contatos
                std::vector<Contato> contatos = agenda.listarContatos();
                for (const auto& contato : contatos) {
                    std::cout << "Nome: " << contato.getNome() << "\n";
                    std::cout << "Telefone: " << contato.getTelefone() << "\n";
                    std::cout << "Email: " << contato.getEmail() << "\n";
                    std::cout << "Favorito: " << (contato.isFavorito() ? "Sim" : "Não") << "\n";
                    std::cout << "-------------------------\n";
                }
                break;
            }
            case 5: {
                // Listar favoritos
                std::vector<Contato> favoritos = agenda.listarFavoritos();
                for (const auto& contato : favoritos) {
                    std::cout << "Nome: " << contato.getNome() << "\n";
                    std::cout << "Telefone: " << contato.getTelefone() << "\n";
                    std::cout << "Email: " << contato.getEmail() << "\n";
                    std::cout << "-------------------------\n";
                }
                break;
            }
            case 6: {
                // Marcar/Desmarcar favorito
                std::string nome;
                std::cout << "Nome do contato: ";
                std::getline(std::cin, nome);

                Contato* contato = agenda.buscar(nome);
                if (contato) {
                    contato->setFavorito(!contato->isFavorito());
                    std::cout << "Favorito " << (contato->isFavorito() ? "marcado" : "desmarcado") << " com sucesso!\n";
                } else {
                    std::cout << "Contato não encontrado.\n";
                }
                break;
            }
            case 7: {
                // Importar contatos
                std::string nomeArquivo;
                std::cout << "Nome do arquivo CSV para importar: ";
                std::getline(std::cin, nomeArquivo);

                agenda.importarCSV(nomeArquivo);
                std::cout << "Contatos importados (se o arquivo existia).\n";
                break;
            }
            case 8: {
                // Exportar contatos
                std::string nomeArquivo;
                std::cout << "Nome do arquivo CSV para exportar: ";
                std::getline(std::cin, nomeArquivo);

                agenda.exportarCSV(nomeArquivo);
                std::cout << "Contatos exportados com sucesso!\n";
                break;
            }
            case 0: {
                std::cout << "Encerrando o programa.\n";
                break;
            }
            default:
                std::cout << "Opção inválida!\n";
                break;
        }

        std::cout << std::endl;

    } while (opcao != 0);

    return 0;
}
