// Contato.cpp
#include "Contato.h"

// Construtores
Contato::Contato() : nome(""), telefone(""), email(""), favorito(false) {}

Contato::Contato(std::string nome, std::string telefone, std::string email, bool favorito)
    : nome(nome), telefone(telefone), email(email), favorito(favorito) {}

// Getters
std::string Contato::getNome() const { return nome; }
std::string Contato::getTelefone() const { return telefone; }
std::string Contato::getEmail() const { return email; }
bool Contato::isFavorito() const { return favorito; }

// Setters
void Contato::setNome(const std::string& nome) { this->nome = nome; }
void Contato::setTelefone(const std::string& telefone) { this->telefone = telefone; }
void Contato::setEmail(const std::string& email) { this->email = email; }
void Contato::setFavorito(bool favorito) { this->favorito = favorito; }

// Sobrecarga de operadores
bool Contato::operator<(const Contato& outro) const {
    return this->nome < outro.nome;
}

bool Contato::operator>(const Contato& outro) const {
    return this->nome > outro.nome;
}

bool Contato::operator==(const Contato& outro) const {
    return this->nome == outro.nome;
}
