// Contato.h
#ifndef CONTATO_H
#define CONTATO_H

#include <string>

class Contato {
private:
    std::string nome;
    std::string telefone;
    std::string email;
    bool favorito;

public:
    // Construtores
    Contato();
    Contato(std::string nome, std::string telefone, std::string email, bool favorito = false);

    // Getters
    std::string getNome() const;
    std::string getTelefone() const;
    std::string getEmail() const;
    bool isFavorito() const;

    // Setters
    void setNome(const std::string& nome);
    void setTelefone(const std::string& telefone);
    void setEmail(const std::string& email);
    void setFavorito(bool favorito);

    // Sobrecarga de operadores
    bool operator<(const Contato& outro) const;
    bool operator>(const Contato& outro) const;
    bool operator==(const Contato& outro) const;
};

#endif // CONTATO_H
